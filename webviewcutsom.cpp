#include "webviewcutsom.h"

WebViewCutsom::WebViewCutsom(QWidget* parent):QWidget(parent)
{
view=new QWebEngineView(this);
view->setGeometry(0,0,parent->width(),parent->height());
close = new QPushButton(this);
close->setGeometry(861,0,40,40);
close->setText("X");
close->setStyleSheet("background:black; color:white;font-size:20px;");
QObject::connect(close,&QPushButton::clicked,this,&QWidget::hide);
}

void WebViewCutsom::setUrl(QUrl url)
{
view->setUrl(url);
}
