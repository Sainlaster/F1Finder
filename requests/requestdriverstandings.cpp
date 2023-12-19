#include "requestdriverstandings.h"

RequestDriverStandings::RequestDriverStandings(QObject *parent):QObject(parent)
{
    QObject::connect(&m_WebCtrl, SIGNAL (finished(QNetworkReply*)),this, SLOT (fileDownloaded(QNetworkReply*)));
}

void RequestDriverStandings::sendRequest(int year)
{
    QString apiUrl = QString("https://ergast.com/api/f1/%1/driverStandings.json").arg(year);
    QNetworkRequest request((QUrl(apiUrl)));
    m_WebCtrl.get(request);
}

void RequestDriverStandings::fileDownloaded(QNetworkReply *reply)
{
    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject root = jsonDoc.object();
    QJsonObject mrData = root.value("MRData").toObject();
    QJsonObject standingsTable = mrData.value("StandingsTable").toObject();
    QJsonArray standingsLists = standingsTable.value("StandingsLists").toArray();
    for (const QJsonValue& standingsListValue : standingsLists) {
           QJsonObject standingsList = standingsListValue.toObject();
           QJsonArray driverStandingsArray = standingsList.value("DriverStandings").toArray();
           for (const QJsonValue& standingsValue : driverStandingsArray) {
               QJsonObject standingsObject = standingsValue.toObject();
               DriverStandings standings;
               standings.position = standingsObject.value("position").toString();
               standings.positionText = standingsObject.value("positionText").toString();
               standings.points = standingsObject.value("points").toString();
               standings.wins = standingsObject.value("wins").toString();
               QJsonObject driverObject = standingsObject.value("Driver").toObject();
               standings.driver.driverId = driverObject.value("driverId").toString();
               standings.driver.permanentNumber = driverObject.value("permanentNumber").toString();
               standings.driver.code = driverObject.value("code").toString();
               standings.driver.url = QUrl(driverObject.value("url").toString());
               standings.driver.givenName = driverObject.value("givenName").toString();
               standings.driver.familyName = driverObject.value("familyName").toString();
               standings.driver.dateOfBirth = driverObject.value("dateOfBirth").toString();
               standings.driver.nationality = driverObject.value("nationality").toString();
               QJsonArray constructorsArray = standingsObject.value("Constructors").toArray();
               for (const QJsonValue& constructorValue : constructorsArray) {
                   QJsonObject constructorObject = constructorValue.toObject();
                   Constructor constructor;
                   constructor.constructorId = constructorObject.value("constructorId").toString();
                   constructor.url = QUrl(constructorObject.value("url").toString());
                   constructor.name = constructorObject.value("name").toString();
                   constructor.nationality = constructorObject.value("nationality").toString();
                   standings.constructors.append(constructor);

               }

               driverStandings.append(standings);
           }
       }
    emit driverStandingsFinished(driverStandings);
    driverStandings.clear();
}
