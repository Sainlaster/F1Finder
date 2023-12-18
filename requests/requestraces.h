#ifndef REQUESTRACES_H
#define REQUESTRACES_H
#include "qnetworkreply.h"
#include "qurl.h"
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
struct Location {
    QString lat;
    QString lon;
    QString locality;
    QString country;
};

struct Circuit {
    QString circuitId;
    QUrl url;
    QString circuitName;
    Location location;
};

struct EventTime {
    QString date;
    QString time;
};

struct Race {
    QString season;
    QString round;
    QUrl url;
    QString raceName;
    Circuit circuit;
    QString date;
    QString time;
    EventTime firstPractice;
    EventTime secondPractice;
    EventTime thirdPractice;
    EventTime qualifying;
};
class RequestRaces : public QObject
{
    Q_OBJECT
public:
    explicit RequestRaces(QObject *parent = nullptr);
public slots:
    void sendRequest(int year);
    void fileDownloaded(QNetworkReply* reply);
signals:
    void racesFinished(QList<Race>);
private:
    QNetworkAccessManager m_WebCtrl;
    QList<Race> races;

};

#endif // REQUESTRACES_H
