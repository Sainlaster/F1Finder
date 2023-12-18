#ifndef MODELDRIVERTABLE_H
#define MODELDRIVERTABLE_H

#include <QAbstractTableModel>
#include "requests/requestdrivers.h"
class ModelDriverTable : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ModelDriverTable(QObject *parent = nullptr);
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
            Q_UNUSED(parent);
            return driver.size();
        }

        int columnCount(const QModelIndex &parent = QModelIndex()) const override {
            Q_UNUSED(parent);
            return 3; // Количество полей в структуре DriverStandings
        }
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
               if (!index.isValid())
                   return QVariant();

               const int row = index.row();
               const int col = index.column();

               if (row < 0 || row >= driver.size())
                   return QVariant();
               const Driver &standings = driver.at(row);
               switch (col) {
               case 0: // driverName
                   return role == Qt::DisplayRole ? standings.givenName+" "+standings.familyName : QVariant();
               case 1: // driverConstructor
                   return role == Qt::DisplayRole ? standings.permanentNumber : QVariant();
               case 2: // driverPoints
                   return role == Qt::DisplayRole ? standings.nationality : QVariant();
               default:
                   return QVariant();
               }
           }
        QVariant returnDriverUrl(const QModelIndex &index){
            if (!index.isValid())
                return QVariant();

            const int row = index.row();
            const int col = index.column();
            if (row < 0 || row >= driver.size())
                return QVariant();
            const Driver &standings = driver.at(row);
            return standings.url;
        }
public slots:
    void setDrivers(const QList<Driver> &data);
    void takeData(int year);
private:
    QList<Driver> driver;
    RequestDrivers* requester;
};

#endif // MODELDRIVERTABLE_H
