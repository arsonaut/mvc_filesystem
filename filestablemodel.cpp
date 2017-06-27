#include "filestablemodel.h"

#include <QDirIterator>
#include <QBrush>
#include <QDateTime>

FilesTableModel::FilesTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

void FilesTableModel::SetPath(const QString& path)
{
    beginResetModel();

    m_data.clear();

    QDirIterator dirIter(path);
    while (dirIter.hasNext())
    {
        dirIter.next();
        const QFileInfo& fileInfo = dirIter.fileInfo();
        m_data.emplace_back(FileData{fileInfo.completeBaseName(),
                                     fileInfo.suffix(),
                                     fileInfo.isDir(),
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

    return m_data.size();
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
    if (row >= 0 && static_cast<size_t>(row) < m_data.size() && role == Qt::DisplayRole)
    {
        return QVariant::fromValue(m_data[row]);
    }

    return QVariant();
}
