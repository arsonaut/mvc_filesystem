#ifndef FILESTABLEMODEL_H
#define FILESTABLEMODEL_H

#include <QAbstractTableModel>
#include <memory>

struct FilesTableModelPrivate;

class FilesTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit FilesTableModel(QObject *parent = 0);
    void SetPath(const QString& path);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    std::unique_ptr<FilesTableModelPrivate> m_data;
};

#endif // FILESTABLEMODEL_H
