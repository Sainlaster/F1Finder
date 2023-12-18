#ifndef REQUESTDRIVERS_H
#define REQUESTDRIVERS_H


#include "qnetworkreply.h"
#include "qurl.h"
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
struct Driver {
    QString driverId;
    QString permanentNumber;
    QString code;
    QUrl url;
    QString givenName;
    QString familyName;
    QString dateOfBirth;
    QString nationality;
};
class RequestDrivers : public QObject
{
    Q_OBJECT
public:
    explicit RequestDrivers(QObject *parent = nullptr);
public slots:
    void sendRequest(int year);
    void fileDownloaded(QNetworkReply* reply);
signals:
    void driversFinished(QList<Driver>);
private:
    QNetworkAccessManager m_WebCtrl;
    QList<Driver> drivers;
signals:

};

#endif // REQUESTDRIVERS_H
