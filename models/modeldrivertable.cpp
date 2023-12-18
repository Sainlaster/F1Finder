#include "modeldrivertable.h"

ModelDriverTable::ModelDriverTable(QObject *parent)
    : QAbstractTableModel{parent}
{
    requester=new RequestDrivers();
    QObject::connect(requester, SIGNAL (driversFinished(QList<Driver>)),this, SLOT (setDrivers(QList<Driver>)));
}
void ModelDriverTable::setDrivers(const QList<Driver> &data)
{
driver = data;
emit layoutChanged();
}

void ModelDriverTable::takeData(int year)
{
requester->sendRequest(year);
}
