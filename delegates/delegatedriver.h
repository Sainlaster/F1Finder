#ifndef DELEGATEDRIVER_H
#define DELEGATEDRIVER_H

#include <QStyledItemDelegate>

class DelegateDriver : public QStyledItemDelegate
{
    Q_OBJECT
public:
    DelegateDriver(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}
    void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const override
    {
        // Set text alignment to left for the first column, center for others
        QStyledItemDelegate::initStyleOption(option, index);
        switch (index.column()) {
        case 1:
            option->displayAlignment = Qt::AlignCenter;
            break;
        case 2:
            option->displayAlignment = Qt::AlignCenter;
            option->rect.adjust(135, 0, 135, 0);
            break;
        default:
            option->displayAlignment = Qt::AlignLeft;
            break;
        }
    }
};

#endif // DELEGATEDRIVER_H
