#include <QTimer>
#include <QSettings>
#include <QPainter>
#include <QMenu>
#include <QPaintEvent>
#include <math.h>
#include <stdlib.h>
#include <qmmp/qmmp.h>

#include "inlines.h"
#include "plusfoldwave.h"

PlusFoldWave::PlusFoldWave(QWidget *parent)
    : Visual(parent)
{
    setWindowTitle(tr("Plus FoldWave Widget"));
    setMinimumSize(2 * 300 - 30, 105);

    for(int i=0; i<50; ++i)
    {
        m_starPoints << new StarPoint();
    }

    m_starTimer = new QTimer(this);
    connect(m_starTimer, SIGNAL(timeout()), this, SLOT(starTimeout()));

    m_starAction = new QAction(tr("Star"), this);
    m_starAction->setCheckable(true);
    connect(m_starAction, SIGNAL(triggered(bool)), this, SLOT(changeStarState(bool)));

    m_starTimer->setInterval(1000);

    readSettings();
}

PlusFoldWave::~PlusFoldWave()
{
    qDeleteAll(m_starPoints);
    if(m_x_scale)
    {
        delete[] m_x_scale;
    }
}

void PlusFoldWave::start()
{
    Visual::start();
    if(isVisible())
    {
        m_starTimer->start();
    }
}

void PlusFoldWave::stop()
{
    Visual::stop();
    m_starTimer->stop();
}

void PlusFoldWave::starTimeout()
{
    for(StarPoint *point : qAsConst(m_starPoints))
    {
        point->m_alpha = rand() % 255;
        point->m_pt = QPoint(rand() % width(), rand() % height());
    }
}

void PlusFoldWave::readSettings()
{
    QSettings settings(Qmmp::configFile(), QSettings::IniFormat);
    settings.beginGroup("PlusFoldWave");
    m_colors = ColorWidget::readColorConfig(settings.value("colors").toString());
    m_starAction->setChecked(settings.value("show_star", false).toBool());
    m_starColor = ColorWidget::readSingleColorConfig(settings.value("star_color").toString());
    settings.endGroup();
}

void PlusFoldWave::writeSettings()
{
    QSettings settings(Qmmp::configFile(), QSettings::IniFormat);
    settings.beginGroup("PlusFoldWave");
    settings.setValue("colors", ColorWidget::writeColorConfig(m_colors));
    settings.setValue("show_star", m_starAction->isChecked());
    settings.setValue("star_color", ColorWidget::writeSingleColorConfig(m_starColor));
    settings.endGroup();
}

void PlusFoldWave::changeColor()
{
    ColorWidget c;
    c.setColors(m_colors);
    if(c.exec())
    {
        m_colors = c.getColors();
    }
}

void PlusFoldWave::changeStarState(bool state)
{
    m_starAction->setChecked(state);
    update();
}

void PlusFoldWave::changeStarColor()
{
    ColorWidget c;
    c.setSingleColorMode(true);
    c.setColor(m_starColor);
    if(c.exec())
    {
        m_starColor = c.getColor();
        update();
    }
}

void PlusFoldWave::hideEvent(QHideEvent *e)
{
    Visual::hideEvent(e);
    m_starTimer->stop();
}

void PlusFoldWave::showEvent(QShowEvent *e)
{
    Visual::showEvent(e);
    if(m_running)
    {
        m_starTimer->start();
    }
}

void PlusFoldWave::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.fillRect(e->rect(), Qt::black);
    draw(&painter);
}

void PlusFoldWave::contextMenuEvent(QContextMenuEvent *)
{
    QMenu menu(this);
    connect(&menu, SIGNAL(triggered(QAction*)), SLOT(writeSettings()));

    menu.addAction(m_screenAction);
    menu.addSeparator();
    menu.addAction(tr("Color"), this, SLOT(changeColor()));
    menu.addAction(m_starAction);
    menu.addAction(tr("StarColor"), this, SLOT(changeStarColor()));
    menu.exec(QCursor::pos());
}

void PlusFoldWave::process(float *left, float *right)
{
    const int rows = (height() - 2) / m_cell_size.height();
    const int cols = (width() - 2) / m_cell_size.width() / 2;

    if(m_rows != rows || m_cols != cols)
    {
        m_rows = rows;
        m_cols = cols;

        if(m_intern_vis_data)
        {
            delete[] m_intern_vis_data;
        }

        if(m_x_scale)
        {
            delete[] m_x_scale;
        }

        m_intern_vis_data = new int[m_cols * 2]{0};
        m_x_scale = new int[m_cols + 1]{0};

        for(int i = 0; i < m_cols + 1; ++i)
        {
            m_x_scale[i] = pow(pow(255.0, 1.0 / m_cols), i);
        }
    }

    short dest_l[256];
    short dest_r[256];

    calc_freq(dest_l, left);
    calc_freq(dest_r, right);

    const double y_scale = (double) 1.25 * m_rows / log(256);

    for(int i = 0; i < m_cols; i++)
    {
        int j = m_cols * 2 - i - 1; //mirror index
        short yl = 0;
        short yr = 0;
        int magnitude_l = 0;
        int magnitude_r = 0;

        if(m_x_scale[i] == m_x_scale[i + 1])
        {
            yl = dest_l[i];
            yr = dest_r[i];
        }

        for(int k = m_x_scale[i]; k < m_x_scale[i + 1]; k++)
        {
            yl = qMax(dest_l[k], yl);
            yr = qMax(dest_r[k], yr);
        }

        yl >>= 7; //256
        yr >>= 7;

        if(yl)
        {
            magnitude_l = int(log(yl) * y_scale);
            magnitude_l = qBound(0, magnitude_l, m_rows);
        }

        if(yr)
        {
            magnitude_r = int(log(yr) * y_scale);
            magnitude_r = qBound(0, magnitude_r, m_rows);
        }

        m_intern_vis_data[i] -= m_analyzer_falloff * m_rows / 15;
        m_intern_vis_data[i] = magnitude_l > m_intern_vis_data[i] ? magnitude_l : m_intern_vis_data[i];

        m_intern_vis_data[j] -= m_analyzer_falloff * m_rows / 15;
        m_intern_vis_data[j] = magnitude_r > m_intern_vis_data[j] ? magnitude_r : m_intern_vis_data[j];
    }
}

void PlusFoldWave::draw(QPainter *p)
{
    if(m_starAction->isChecked())
    {
        for(StarPoint *point : qAsConst(m_starPoints))
        {
            m_starColor.setAlpha(point->m_alpha);
            p->setPen(QPen(m_starColor, 3));
            p->drawPoint(point->m_pt);
        }
    }

    QLinearGradient line(0, 0, 0, height());
    for(int i = 0; i < m_colors.count(); ++i)
    {
        line.setColorAt((i + 1) * 1.0 / m_colors.count(), m_colors[i]);
    }
    p->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    p->setPen(QPen(line, 1));

    const int rdx = qMax(0, width() - 2 * m_cell_size.width() * m_cols);

    for(int i = 0; i < m_cols * 2; ++i)
    {
        int x = i * m_cell_size.width() + 1;
        if(i >= m_cols)
        {
            x += rdx; //correct right part position
        }
        int offset = m_intern_vis_data[i] * m_cell_size.height() / 2;
        if(abs(offset) > height() / 2)
        {
            offset = height() / 2;
        }

        p->drawLine(QPoint(x, height() / 2 - offset), QPoint(x, height() / 2 + offset));

        if((i + 1) >= m_cols * 2)
        {
            break;
        }

        int x1 = (i + 1) * m_cell_size.width() + 1;
        if((i + 1) >= m_cols)
        {
            x1 += rdx; //correct right part position
        }

        int offset1 = m_intern_vis_data[i + 1] * m_cell_size.height() / 2;
        if(abs(offset1) > height() / 2)
        {
            offset1 = height() / 2;
        }

        p->drawLine(QPoint(x, height() / 2 - offset), QPoint(x1, height() / 2 - offset1));
        p->drawLine(QPoint(x, height() / 2 + offset), QPoint(x1, height() / 2 + offset1));
    }
}