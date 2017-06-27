#ifndef FILESTABLEDELEGATE_H
#define FILESTABLEDELEGATE_H

#include <QStyledItemDelegate>

class FilesTableDelegate : public QStyledItemDelegate
{
public:
    FilesTableDelegate(QObject* parent = nullptr);
    virtual void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

#endif // FILESTABLEDELEGATE_H
