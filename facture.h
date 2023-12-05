#ifndef FACTURE_H
#define FACTURE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Facture
{
private:
    int id;
    QString prod_dep;
    float benefice,frais_alim,cout_arr,gain;
public:
    Facture();
    Facture(int,QString,float,float,float,float);
    //crud
    bool ajouterFacture();
    QSqlQueryModel * afficherFacture();
    bool supprimerFacture(int);
    bool modifierFacture();
    //Métiers
    QSqlQueryModel * rechercherFacture(QString recherche);
    QSqlQueryModel * triFacture(QString tri);
    QVector<int> statFacture();
};

#endif // FACTURE_H
