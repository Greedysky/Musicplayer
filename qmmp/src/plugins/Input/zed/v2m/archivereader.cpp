#include "archivereader.h"

#include <QProcess>
#include <qmmp/qmmp.h>

#define ARCHIVE_PATH    (Qmmp::ttkPluginPath() + "/archive.tkx")

QStringList ArchiveReader::filters()
{
    QStringList path;
    path << "*.v2mz";
    return path;
}

bool ArchiveReader::isSupported(const QString &path)
{
    if(!QFile::exists(ARCHIVE_PATH) || path.isEmpty())
    {
        return false;
    }

    const QString &filePath = path.toLower();
    for(const QString &suffix : filters())
    {
        if(filePath.endsWith(suffix.mid(1)))
        {
            return true;
        }
    }
    return false;
}

QByteArray ArchiveReader::unpack(const QString &path)
{
    QProcess process;
    QStringList args;
    args << "-so" << "e" << path;
    process.start(ARCHIVE_PATH, args);
    process.waitForFinished();
    return process.readAllStandardOutput();
}
