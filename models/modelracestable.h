#ifndef MODELRACESTABLE_H
#define MODELRACESTABLE_H

#include <QAbstractTableModel>
#include "requests/requestraces.h"
class ModelRacesTable : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ModelRacesTable(QObject *parent = nullptr);
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
            Q_UNUSED(parent);
            return races.size();
        }

        int columnCount(const QModelIndex &parent = QModelIndex()) const override {
            Q_UNUSED(parent);
            return 4; // Количество полей в структуре DriverStandings
        }
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
               if (!index.isValid())
                   return QVariant();

               const int row = index.row();
               const int col = index.column();

               if (row < 0 || row >= races.size())
                   return QVariant();
               const Race &standings = races.at(row);
               switch (col) {
               case 0: // driverName
                   return role == Qt::DisplayRole ? standings.round : QVariant();
               case 1: // driverConstructor
                   return role == Qt::DisplayRole ? standings.raceName : QVariant();
               case 2: // driverPoints
                   return role == Qt::DisplayRole ? standings.date : QVariant();
               case 3:
                   return role == Qt::DisplayRole ? standings.circuit.circuitName : QVariant();
               default:
                   return QVariant();
               }
           }
        QVariant returnGrandPrixUrl(const QModelIndex &index){
                    if (!index.isValid())
                        return QVariant();

                    const int row = index.row();
                    const int col = index.column();

                    if (row < 0 || row >= races.size())
                        return QVariant();
                    const Race &standings = races.at(row);
                    return standings.url;
                }
        QVariant returnCircuitUrl(const QModelIndex &index){
                    if (!index.isValid())
                        return QVariant();

                    const int row = index.row();
                    const int col = index.column();

                    if (row < 0 || row >= races.size())
                        return QVariant();
                    const Race &standings = races.at(row);
                    return standings.circuit.url;
                }
public slots:
    void setRaces(const QList<Race> &data);
    void takeData(int year);
private:
    QList<Race> races;
    RequestRaces* requester;
};

#endif // MODELRACESTABLE_H
