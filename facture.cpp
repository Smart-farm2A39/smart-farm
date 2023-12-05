#include "facture.h"

Facture::Facture()
{

}
Facture::Facture(int id,QString prod,float ben,float frais,float cout,float gain)
{
    this->id=id;
    this->prod_dep=prod;
    this->benefice=ben;
    this->frais_alim=frais;
    this->cout_arr=cout;
    this->gain=gain;
}
bool Facture::ajouterFacture()
{
    QSqlQuery query;
    QString ben = QString::number(benefice);
    QString frais = QString::number(frais_alim);
    QString cout = QString::number(cout_arr);
    QString gainS = QString::number(gain);
    query.prepare("INSERT INTO factures (prod_dep,benefice,frais_alimentation,cout_arr,gain)" "VALUES (:prod,:ben,:fr,:cout,:g)");
    query.bindValue(":prod",prod_dep);
    query.bindValue(":ben",ben);
    query.bindValue(":fr",frais);
    query.bindValue(":cout",cout);
    query.bindValue(":g",gainS);
    return query.exec();
}
QSqlQueryModel * Facture::afficherFacture()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * from factures");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Produits et dépenses"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Bénefice"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Frais d'alimentation"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Coût d'arrosage"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("gain financier"));
    return model;
}

bool Facture::supprimerFacture(int idF)
{
    QSqlQuery query;
    query.prepare("DELETE FROM factures WHERE id= :id");
    query.bindValue(":id",idF);
    return query.exec();
}

bool Facture::modifierFacture()
{
    QSqlQuery query;
    QString idS = QString::number(id);
    QString ben = QString::number(benefice);
    QString frais = QString::number(frais_alim);
    QString cout = QString::number(cout_arr);
    QString gainS = QString::number(gain);
    query.prepare("UPDATE factures "" SET prod_dep=:prod, benefice=:ben, frais_alimentation=:fr, cout_arr=:cout, gain=:g WHERE id=:id");
    query.bindValue(":id",idS);
    query.bindValue(":prod",prod_dep);
    query.bindValue(":ben",ben);
    query.bindValue(":fr",frais);
    query.bindValue(":cout",cout);
    query.bindValue(":g",gainS);
    return query.exec();
}

QSqlQueryModel * Facture::rechercherFacture(QString recherche)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * from factures WHERE (UPPER(id) LIKE UPPER('%"+recherche+"%') OR UPPER(prod_dep) LIKE UPPER('%"+recherche+"%') OR benefice LIKE UPPER('%"+recherche+"%') )");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Produits et dépenses"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Bénefice"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Frais d'alimentation"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Coût d'arrosage"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("gain financier"));
    return model;
}

QSqlQueryModel * Facture::triFacture(QString tri)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    if(tri == "par défaut"){
        model->setQuery("SELECT * FROM factures");
    }else if (tri == "Bénefice") {
        model->setQuery("SELECT * FROM factures ORDER BY benefice");
    } else if (tri == "Coût d'arrosage") {
        model->setQuery("SELECT * FROM factures ORDER BY cout_arr");
    }
    else if (tri == "Gain financier") {
            model->setQuery("SELECT * FROM factures ORDER BY gain");
        }
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Produits et dépenses"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Bénefice"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Frais d'alimentation"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Coût d'arrosage"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("gain financier"));
    return model;
}

QVector<int> Facture::statFacture()
{
    QSqlQuery query;
    QVector<int> statFacture;
    float sommeB,sommeF;
    query.prepare("SELECT SUM(benefice) AS ben FROM factures");
    if(query.exec())
    {
        if (query.next()) {
            sommeB = query.value("ben").toFloat();
        }
    }
    statFacture.push_back(sommeB);
    query.prepare("SELECT SUM(frais_alimentation) AS frais FROM factures");
    if(query.exec())
    {
        if (query.next()) {
            sommeF = query.value("frais").toFloat();
        }
    }
    statFacture.push_back(sommeF);
    return statFacture;

}
