#ifndef FILESTABLEMODEL_H
#define FILESTABLEMODEL_H

#include "filedata.h"

#include <vector>

#include <QAbstractTableModel>

class FilesTableDelegate;

class FilesTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    friend class FilesTableDelegate;

    explicit FilesTableModel(QObject *parent = 0);
    void SetPath(const QString& path);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    std::vector<FileData> m_data;
};

#endif // FILESTABLEMODEL_H
