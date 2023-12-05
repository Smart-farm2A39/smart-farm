#ifndef CULTURE_H
#define CULTURE_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QAbstractItemModel>


 class culture
{
    private:
        int id;
        float qualite,pluv,hum,ten,temp;
    public:
        culture();
        culture(int,float,float,float,float,float);
        QSqlQueryModel *  rechercherCacture(QString recherche);
        QSqlQueryModel *triCulture(QString tri);
        //CRUD
        bool ajouterCulture();
        QSqlQueryModel * afficherCulture();
        bool supprimerCulture(int);
        bool modifierCulture();
        //recemment ajoutee
        QSqlQueryModel * rechercherFacture(QString recherche);

};

#endif // CULTURE_H
