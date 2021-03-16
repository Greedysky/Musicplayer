#ifndef MUSICITEMDELEGATE_H
#define MUSICITEMDELEGATE_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (C) 2015 - 2021 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ================================================= */

#include <QItemDelegate>
#include "musicglobaldefine.h"

#define MUSIC_CHECK_ROLE    Qt::UserRole + 1
#define MUSIC_PROGRESS_ROLE Qt::UserRole + 2
#define MUSIC_TEXT_ROLE     Qt::UserRole + 3
#define MUSIC_TIME_ROLE     Qt::UserRole + 4
#define MUSIC_ENABLE_ROLE   Qt::UserRole + 5
#define MUSIC_DATA_ROLE     Qt::UserRole + 100

class QLabel;
class QCheckBox;
class QRadioButton;
class QProgressBar;
class QPushButton;

/*! @brief The class of the radio button item delegate.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_WIDGET_EXPORT MusicRadioButtonDelegate : public QItemDelegate
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicRadioButtonDelegate)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicRadioButtonDelegate(QObject* parent = nullptr);

    virtual ~MusicRadioButtonDelegate();

    /*!
     * Set delegate item style.
     */
    void setStyleSheet(const QString &style);
    /*!
     * Set tree model.
     */
    void setTreeModel(bool tree);

    /*!
     * Override size hint.
     */
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &) const override;
    /*!
     * Override paint.
     */
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

protected:
    bool m_treeMode;
    QRadioButton *m_radioButton;

};


/*! @brief The class of the checkbox item delegate.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_WIDGET_EXPORT MusicCheckBoxDelegate : public QItemDelegate
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicCheckBoxDelegate)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicCheckBoxDelegate(QObject* parent = nullptr);

    virtual ~MusicCheckBoxDelegate();

    /*!
     * Set delegate item style.
     */
    void setStyleSheet(const QString &style);
    /*!
     * Show text mode.
     */
    void showTextMode(bool mode);
    /*!
     * Set tree model.
     */
    void setTreeModel(bool tree);

    /*!
     * Override size hint.
     */
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &) const override;
    /*!
     * Override paint.
     */
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

Q_SIGNALS:
    /*!
     * Button state changed.
     */
    void buttonChecked();

protected:
    bool m_textMode;
    bool m_treeMode;
    bool m_background;
    QCheckBox *m_checkBox;

};


/*! @brief The class of the progress bar item delegate.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_WIDGET_EXPORT MusicProgressBarDelegate : public QItemDelegate
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicProgressBarDelegate)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicProgressBarDelegate(QObject* parent = nullptr);

    ~MusicProgressBarDelegate();

    /*!
     * Set delegate item style.
     */
    void setStyleSheet(const QString &style);
    /*!
     * Set tree model.
     */
    void setTreeModel(bool tree);

    /*!
     * Override size hint.
     */
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &) const override;
    /*!
     * Override paint.
     */
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    bool m_treeMode;
    QProgressBar *m_progress;

};


/*! @brief The class of the label item delegate.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_WIDGET_EXPORT MusicLabelDelegate : public QItemDelegate
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicLabelDelegate)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicLabelDelegate(QObject* parent = nullptr);

    virtual ~MusicLabelDelegate();

    /*!
     * Set delegate item style.
     */
    void setStyleSheet(const QString &style);
    /*!
     * Set text alignment.
     */
    void setAlignment(Qt::Alignment alignment);
    /*!
     * Set tree model.
     */
    void setTreeModel(bool tree);

    /*!
     * Override size hint.
     */
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &) const override;
    /*!
     * Override paint.
     */
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

protected:
    bool m_treeMode;
    QLabel *m_label;

};


/*! @brief The class of the push button item delegate.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_WIDGET_EXPORT MusicPushButtonDelegate : public QItemDelegate
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicPushButtonDelegate)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicPushButtonDelegate(QObject* parent = nullptr);

    virtual ~MusicPushButtonDelegate();

    /*!
     * Set delegate item style.
     */
    void setStyleSheet(const QString &style);
    /*!
     * Set tree model.
     */
    void setTreeModel(bool tree);

    /*!
     * Override size hint.
     */
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &) const override;
    /*!
     * Override paint.
     */
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

protected:
    bool m_treeMode;
    QPushButton *m_pushButton;

};


/*! @brief The class of the rename lineedit item delegate.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_WIDGET_EXPORT MusicRenameLineEditDelegate : public QItemDelegate
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicRenameLineEditDelegate)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicRenameLineEditDelegate(QObject *parent);

    /*!
     * Override createEditor.
     */
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};

#endif // MUSICITEMDELEGATE_H
