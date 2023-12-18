#ifndef TITLE_BUTTON_H
#define TITLE_BUTTON_H
#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <QPoint>
#include <QObject>
//This class need to drag MainWindow
class Title_button:public QPushButton
{
    Q_OBJECT
public:
    Title_button(QWidget *parent = nullptr);
};

#endif // TITLE_BUTTON_H
