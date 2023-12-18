#ifndef DELEGATEDRIVERSTABLE_H
#define DELEGATEDRIVERSTABLE_H

#include <QStyledItemDelegate>

class DelegateDriversTable : public QStyledItemDelegate
{
    Q_OBJECT
public:
    DelegateDriversTable(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}

    void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const override
    {
        // Set text alignment to left for the first column, center for others
        QStyledItemDelegate::initStyleOption(option, index);
        switch (index.column()) {
        case 1:
            option->displayAlignment = Qt::AlignLeft;
            break;
        case 3:
            option->displayAlignment = Qt::AlignCenter;
            option->rect.adjust(79, 0, 79, 0);
            break;
        case 4:
            option->displayAlignment = Qt::AlignCenter;
            option->rect.adjust(79, 0, 79, 0);
            break;
        default:
            option->displayAlignment = Qt::AlignCenter;
            break;
        }
    }
};
#endif // DELEGATEDRIVERSTABLE_H
