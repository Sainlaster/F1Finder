#include "ModelDriverTableStandings.h"

ModelDriverTableStandings::ModelDriverTableStandings(QObject *parent):QAbstractTableModel(parent)
{
    requester=new RequestDriverStandings();
    QObject::connect(requester, SIGNAL (driverStandingsFinished(QList<DriverStandings>)),this, SLOT (setDriverStandings(QList<DriverStandings>)));
}

void ModelDriverTableStandings::setDriverStandings(const QList<DriverStandings> &data)
{
driverStandings = data;
emit layoutChanged();
}

void ModelDriverTableStandings::takeData(int year)
{
requester->sendRequest(year);
}
