#include "requestdrivers.h"

RequestDrivers::RequestDrivers(QObject *parent):QObject(parent)
{
    QObject::connect(&m_WebCtrl, SIGNAL (finished(QNetworkReply*)),this, SLOT (fileDownloaded(QNetworkReply*)));
    sendRequest(2023);
}

void RequestDrivers::sendRequest(int year)
{
    QString apiUrl = QString("https://ergast.com/api/f1/%1/drivers.json").arg(year);
    QNetworkRequest request((QUrl(apiUrl)));
    m_WebCtrl.get(request);
}

void RequestDrivers::fileDownloaded(QNetworkReply *reply)
{
    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject root = jsonDoc.object();
        QJsonObject mrData = root.value("MRData").toObject();
        QJsonObject driverTableObject = mrData.value("DriverTable").toObject();
        QJsonArray driversArray = driverTableObject.value("Drivers").toArray();
        for (const QJsonValue& driverValue : driversArray) {
            QJsonObject driverObject = driverValue.toObject();
            Driver driver;
            driver.driverId = driverObject.value("driverId").toString();
            driver.permanentNumber = driverObject.value("permanentNumber").toString();
            driver.code = driverObject.value("code").toString();
            driver.url = QUrl(driverObject.value("url").toString());
            driver.givenName = driverObject.value("givenName").toString();
            driver.familyName = driverObject.value("familyName").toString();
            driver.dateOfBirth = driverObject.value("dateOfBirth").toString();
            driver.nationality = driverObject.value("nationality").toString();
            drivers.append(driver);
        }
    emit driversFinished(drivers);
        drivers.clear();
}
