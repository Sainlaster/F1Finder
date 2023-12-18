#include "modelracestable.h"

ModelRacesTable::ModelRacesTable(QObject *parent)
    : QAbstractTableModel{parent}
{
    requester=new RequestRaces();
    QObject::connect(requester, SIGNAL (racesFinished(QList<Race>)),this, SLOT (setRaces(QList<Race>)));
}
void ModelRacesTable::setRaces(const QList<Race> &data)
{
races = data;
emit layoutChanged();
}

void ModelRacesTable::takeData(int year)
{
requester->sendRequest(year);
}
