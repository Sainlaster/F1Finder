#ifndef WEBVIEWCUTSOM_H
#define WEBVIEWCUTSOM_H

#include "qpushbutton.h"
#include <QWebEngineView>
#include <QWidget>

class WebViewCutsom : public QWidget
{
    Q_OBJECT
public:
    WebViewCutsom(QWidget *parent=nullptr);
public slots:
    void setUrl(QUrl url);
private:
    QWebEngineView *view;
    QPushButton* close;
};

#endif // WEBVIEWCUTSOM_H
