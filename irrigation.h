#ifndef IRRIGATION_H
#define IRRIGATION_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVector>


class Irrigation
{
private:
    int id,ref,quantite;
    QString nom,type,etat,emplacement,humidite;
public:
    Irrigation();
    Irrigation(int,int,int,QString,QString,QString,QString,QString);
    bool addIrrigation();
    QSqlQueryModel * showIrrigation();
    bool deleteIrrigation(int);
    bool updateIrrigation();
    QSqlQueryModel * searchIrrigation(QString recherche);
    QSqlQueryModel * triIrrigation(QString tri);
    QVector<int> statQuantity();
};

#endif // IRRIGATION_H
