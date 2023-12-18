#include "requestraces.h"

RequestRaces::RequestRaces(QObject *parent)
    : QObject{parent}
{
    QObject::connect(&m_WebCtrl, SIGNAL (finished(QNetworkReply*)),this, SLOT (fileDownloaded(QNetworkReply*)));
    sendRequest(2023);
}
void RequestRaces::sendRequest(int year)
{
    QString apiUrl = QString("https://ergast.com/api/f1/%1.json").arg(year);
    QNetworkRequest request((QUrl(apiUrl)));
    m_WebCtrl.get(request);
}
void RequestRaces::fileDownloaded(QNetworkReply *reply)
{
    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject root = jsonDoc.object();
    QJsonObject mrData = root.value("MRData").toObject();
       QJsonObject raceTableObject = mrData.value("RaceTable").toObject();
       QJsonArray racesArray = raceTableObject.value("Races").toArray();
       for (const QJsonValue& raceValue : racesArray) {
           QJsonObject raceObject = raceValue.toObject();
           Race race;
           race.season = raceObject.value("season").toString();
           race.round = raceObject.value("round").toString();
           race.url = QUrl(raceObject.value("url").toString());
           race.raceName = raceObject.value("raceName").toString();
           QJsonObject circuitObject = raceObject.value("Circuit").toObject();
           race.circuit.circuitId = circuitObject.value("circuitId").toString();
           race.circuit.url = QUrl(circuitObject.value("url").toString());
           race.circuit.circuitName = circuitObject.value("circuitName").toString();
           QJsonObject locationObject = circuitObject.value("Location").toObject();
           race.circuit.location.lat = locationObject.value("lat").toString();
           race.circuit.location.lon = locationObject.value("long").toString();
           race.circuit.location.locality = locationObject.value("locality").toString();
           race.circuit.location.country = locationObject.value("country").toString();
           race.date = raceObject.value("date").toString();
           race.time = raceObject.value("time").toString();
           race.firstPractice.date = raceObject.value("FirstPractice").toObject().value("date").toString();
           race.firstPractice.time = raceObject.value("FirstPractice").toObject().value("time").toString();
           race.secondPractice.date = raceObject.value("SecondPractice").toObject().value("date").toString();
           race.secondPractice.time = raceObject.value("SecondPractice").toObject().value("time").toString();
           race.thirdPractice.date = raceObject.value("ThirdPractice").toObject().value("date").toString();
           race.thirdPractice.time = raceObject.value("ThirdPractice").toObject().value("time").toString();
           race.qualifying.date = raceObject.value("Qualifying").toObject().value("date").toString();
           race.qualifying.time = raceObject.value("Qualifying").toObject().value("time").toString();
           races.append(race);
       }
    emit racesFinished(races);
       races.clear();
}
