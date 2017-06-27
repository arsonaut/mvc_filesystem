#ifndef FILEDATA_H
#define FILEDATA_H

#include <QString>
#include <QMetaType>

struct FileData
{
    QString name;
    QString suffix;
    bool isDirectory;
    QString size;
    QString date;
};

Q_DECLARE_METATYPE(FileData);

#endif // FILEDATA_H
