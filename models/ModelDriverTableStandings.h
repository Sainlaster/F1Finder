#ifndef MODELDRIVERTABLESTANDINGS_H
#define MODELDRIVERTABLESTANDINGS_H

#include "qurl.h"
#include <QObject>
#include <QTableView>
#include "requests/requestdriverstandings.h"

class ModelDriverTableStandings:public QAbstractTableModel
{
    Q_OBJECT
public:
    ModelDriverTableStandings(QObject *parent = nullptr);
public slots:
    void setDriverStandings(const QList<DriverStandings> &data);
    void takeData(int year);
private:
    QList<DriverStandings> driverStandings;
    RequestDriverStandings* requester;
    QObject * QAbstractTableModel;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
            Q_UNUSED(parent);
            return driverStandings.size();
        }

        int columnCount(const QModelIndex &parent = QModelIndex()) const override {
            Q_UNUSED(parent);
            return 5; // Количество полей в структуре DriverStandings
        }
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
               if (!index.isValid())
                   return QVariant();

               const int row = index.row();
               const int col = index.column();

               if (row < 0 || row >= driverStandings.size())
                   return QVariant();
               const DriverStandings &standings = driverStandings.at(row);

               switch (col) {
               case 0: // driverName
                   return role == Qt::DisplayRole ? standings.position : QVariant();
               case 1: // driverName
                   return role == Qt::DisplayRole ? standings.driver.givenName+" "+standings.driver.familyName : QVariant();
               case 2: // driverConstructor
                   return role == Qt::DisplayRole ? standings.constructors.at(0).name : QVariant();
               case 3: // driverPoints
                   return role == Qt::DisplayRole ? standings.points : QVariant();
               case 4: // driverWins
                   return role == Qt::DisplayRole ? standings.wins : QVariant();
               default:
                   return QVariant();
               }
           }
        QVariant returnDriverUrl(const QModelIndex &index){
            if (!index.isValid())
                return QVariant();

            const int row = index.row();
            const int col = index.column();

            if (row < 0 || row >= driverStandings.size())
                return QVariant();
            const DriverStandings &standings = driverStandings.at(row);
            return standings.driver.url;
        }
        QVariant returnConstructorUrl(const QModelIndex &index){
            if (!index.isValid())
                return QVariant();

            const int row = index.row();
            const int col = index.column();

            if (row < 0 || row >= driverStandings.size())
                return QVariant();
            const DriverStandings &standings = driverStandings.at(row);
            return standings.constructors[0].url;
        }
};

#endif // MODELDRIVERTABLESTANDINGS_H
