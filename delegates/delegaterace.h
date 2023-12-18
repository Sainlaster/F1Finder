#ifndef DELEGATERACE_H
#define DELEGATERACE_H

#include <QStyledItemDelegate>
class DelegateRace : public QStyledItemDelegate
{
    Q_OBJECT
public:
    DelegateRace(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}
    void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const override
    {
        // Set text alignment to left for the first column, center for others
        QStyledItemDelegate::initStyleOption(option, index);
        switch (index.column()) {
        case 0:
            option->displayAlignment = Qt::AlignCenter;
            break;
        case 2:
            option->displayAlignment = Qt::AlignCenter;
            break;
        default:
            option->displayAlignment = Qt::AlignLeft;
            break;
        }
    }
};

#endif // DELEGATERACE_H
