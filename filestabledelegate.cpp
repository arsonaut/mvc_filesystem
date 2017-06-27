#include "filestabledelegate.h"

#include "filedata.h"

#include <QPainter>

FilesTableDelegate::FilesTableDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

void FilesTableDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (index.isValid() && index.data().canConvert<FileData>())
    {
        const FileData& fileData = index.data().value<FileData>();

        QBrush background(Qt::darkBlue);
        painter->fillRect(option.rect, background);

        QColor foreground(fileData.isDirectory ? Qt::white : Qt::cyan);
        painter->setPen(foreground);
        painter->setFont(option.font);

        switch (index.column())
        {
        case 0:
            painter->drawText(option.rect, fileData.name, QTextOption{Qt::AlignLeft});
            painter->setBackground(background);
            painter->setBackgroundMode(Qt::OpaqueMode);
            painter->drawText(option.rect, fileData.suffix, QTextOption{Qt::AlignRight});
            return;
        case 1:
            painter->drawText(option.rect, fileData.isDirectory ? "<Folder>" : fileData.size, QTextOption{Qt::AlignRight});
            return;
        case 2:
            painter->drawText(option.rect, fileData.date, QTextOption{Qt::AlignRight});
            return;
        }
    }

    QStyledItemDelegate::paint(painter, option, index);
}
