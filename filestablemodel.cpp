#include "filestablemodel.h"

#include <QDirIterator>
#include <QBrush>
#include <QDateTime>

struct FileData
{
    QString name;
    bool isDirectory;
    QString size;
    QString date;
};

struct FilesTableModelPrivate
{
    std::vector<FileData> files;
};

FilesTableModel::FilesTableModel(QObject *parent)
    : QAbstractTableModel(parent)
    , m_data(new FilesTableModelPrivate)
{

}

void FilesTableModel::SetPath(const QString& path)
{
    beginResetModel();

    m_data->files.clear();

    QDirIterator dirIter(path);
    while (dirIter.hasNext())
    {
        dirIter.next();
        const QFileInfo& fileInfo = dirIter.fileInfo();
        m_data->files.emplace_back(FileData{fileInfo.fileName(), fileInfo.isDir(),
                                            QString("%L1").arg(fileInfo.size()),
                                            fileInfo.lastModified().toString("dd-MM-yyyy")});
    }

    endResetModel();
}

QVariant FilesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        switch (role)
        {
        case Qt::DisplayRole:
            switch (section)
            {
            case 0:
                return QString("Name");
            case 1:
                return QString("Size");
            case 2:
                return QString("Date");
            }

        case Qt::TextAlignmentRole:
            return Qt::AlignHCenter;

        case Qt::BackgroundRole:
            return QBrush(Qt::darkBlue);

        case Qt::ForegroundRole:
            return QBrush(Qt::yellow);
        }
    }

    return QVariant();
}

int FilesTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_data->files.size();
}

int FilesTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 3;
}

QVariant FilesTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const int row = index.row();
    if (row >= 0 && row < m_data->files.size())
    {
        const FileData& fileData = m_data->files[row];
        switch (role) {
        case Qt::DisplayRole:
            switch (index.column()) {
            case 0:
                return fileData.name;
            case 1:
                return fileData.isDirectory ? QString("<Folder>") : fileData.size;
            case 2:
                return fileData.date;
            }

        case Qt::TextAlignmentRole:
            switch (index.column()) {
            case 0:
                return Qt::AlignLeft;
            case 1:
            case 2:
                return Qt::AlignRight;
            }

        case Qt::BackgroundRole:
            return QBrush(Qt::darkBlue);

        case Qt::ForegroundRole:
            return QBrush(fileData.isDirectory ? Qt::white : Qt::cyan);
        }
    }

    // FIXME: Implement me!
    return QVariant();
}
