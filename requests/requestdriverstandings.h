#ifndef REQUESTDRIVERSTANDINGS_H
#define REQUESTDRIVERSTANDINGS_H

#include "qpushbutton.h"
#include "qurl.h"
#include <QNetworkAccessManager>
#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
struct DriverStand {
    QString driverId;
    QString permanentNumber;
    QString code;
    QUrl url;
    QString givenName;
    QString familyName;
    QString dateOfBirth;
    QString nationality;
};
struct Constructor {
    QString constructorId;
    QUrl url;
    QString name;
    QString nationality;
};
struct DriverStandings {
    QString position;
    QString positionText;
    QString points;
    QString wins;
    DriverStand driver;
    QList<Constructor> constructors;
};
class RequestDriverStandings:public QObject
{
    Q_OBJECT
public:
    RequestDriverStandings(QObject *parent = nullptr);
public slots:
    void sendRequest(int year);
    void fileDownloaded(QNetworkReply* reply);
signals:
    void driverStandingsFinished(QList<DriverStandings>);
private:
     QNetworkAccessManager m_WebCtrl;
     QList<DriverStandings> driverStandings;
};

#endif // REQUESTDRIVERSTANDINGS_H
