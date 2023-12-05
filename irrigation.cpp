#include "irrigation.h"

Irrigation::Irrigation()
{

}
Irrigation::Irrigation(int id,int ref,int quant,QString nom,QString type,QString etat,QString emp,QString humidite)
{
    this->id=id;
    this->ref=ref;
    this->quantite=quant;
    this->nom=nom;
    this->type=type;
    this->etat=etat;
    this->emplacement=emp;
    this->humidite=humidite;
}
bool Irrigation::addIrrigation()
{
    QSqlQuery query;
    QString refS = QString::number(ref);
    QString quant = QString::number(quantite);
    query.prepare("INSERT INTO irrigations (nom,reference,type,etat,quantite,emplacement,HUMIDITE)" "VALUES (:nom,:ref,:type,:etat,:quant,:emp,:HUMIDITE)");
    query.bindValue(":nom",nom);
    query.bindValue(":ref",refS);
    query.bindValue(":type",type);
    query.bindValue(":etat",etat);
    query.bindValue(":quant",quant);
    query.bindValue(":emp",emplacement);
        query.bindValue(":HUMIDITE",humidite);
    return query.exec();
}
QSqlQueryModel * Irrigation::showIrrigation()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * from irrigations");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Reference"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Quantité"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Emplacement"));
        model->setHeaderData(7,Qt::Horizontal,QObject::tr("humidite"));
    return model;
}

bool Irrigation::deleteIrrigation(int id_Del)
{
    QSqlQuery query;
    query.prepare("DELETE FROM irrigations WHERE id= :id");
    query.bindValue(":id",id_Del);
    return query.exec();
}

bool Irrigation::updateIrrigation()
{
    QSqlQuery query;
    QString idS = QString::number(id);
    QString refS = QString::number(ref);
    QString quant = QString::number(quantite);
    query.prepare("UPDATE irrigations "" SET nom=:nom, reference=:ref, type=:type, etat=:etat, quantite=:quant, emplacement=:emp WHERE id=:id");
    query.bindValue(":id",idS);
    query.bindValue(":nom",nom);
    query.bindValue(":ref",refS);
    query.bindValue(":type",type);
    query.bindValue(":etat",etat);
    query.bindValue(":quant",quant);
    query.bindValue(":emp",emplacement);
    return query.exec();
}

QSqlQueryModel * Irrigation::searchIrrigation(QString recherche)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM irrigations WHERE (UPPER(nom) LIKE UPPER('%"+recherche+"%') OR UPPER(id) LIKE UPPER('%"+recherche+"%') OR UPPER(reference) LIKE UPPER('%"+recherche+"%'))");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Reference"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Quantité"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Emplacement"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("humidite"));

    return model;
}

QSqlQueryModel * Irrigation::triIrrigation(QString tri)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    if(tri == "Par défaut"){
        model->setQuery("SELECT * FROM irrigations");
    }
    else if(tri == "Nom"){
        model->setQuery("SELECT * FROM irrigations ORDER BY nom");
    }else if (tri == "Réference") {
        model->setQuery("SELECT * FROM irrigations ORDER BY reference");
    } else if (tri == "Quantité") {
        model->setQuery("SELECT * FROM irrigations ORDER BY quantite");
    }
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Reference"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Quantité"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Emplacement"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("humidite"));

    return model;
}

QVector<int> Irrigation::statQuantity()
{
    QVector<int> stat;
    QSqlQuery query;
    int nbr1=0,nbr2=0,nbr3=0;
    query.exec("SELECT "
               "SUM(CASE WHEN type = 'Arbre' THEN 1 ELSE 0 END) AS num_1, "
               "SUM(CASE WHEN type = 'Arbuste' THEN 1 ELSE 0 END) AS num_2, "
               "SUM(CASE WHEN type = 'Fleure' THEN 1 ELSE 0 END) AS num_3 "
               "FROM irrigations");
    if (query.next()) {
        nbr1 = query.value("num_1").toInt();
        nbr2 = query.value("num_2").toInt();
        nbr3 = query.value("num_3").toInt();
    }
    stat.push_back(nbr1);
    stat.push_back(nbr2);
    stat.push_back(nbr3);
    return stat;
}
