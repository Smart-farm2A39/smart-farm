#include "culture.h"
culture::culture()
{

}








culture::culture(int id,float qual,float pluv,float hum,float ten,float temp)
{
    this->id=id;
    this->qualite=qual;
    this->pluv=pluv;
    this->hum=hum;
    this->ten=ten;
    this->temp=temp;
};
////////////////////
QSqlQueryModel *  rechercherCacture(QString recherche){




}


////////////////////////////
QSqlQueryModel * culture::rechercherCacture(QString recherche)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * from cultures WHERE (UPPER(id) LIKE UPPER('%"+recherche+"%') OR UPPER(QUALITE_AIR) LIKE UPPER('%"+recherche+"%') OR UPPER(PLUVIOMETRIE) LIKE UPPER('%"+recherche+"%') )");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Qualité d'air"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Pluviometrie"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Humidité"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Teneur de sol"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Temperature"));
    return model;
}

///////////////////////////////////////////////////////
QSqlQueryModel * culture::triCulture(QString tri)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    if(tri == "par defaut"){
        model->setQuery("SELECT * FROM cultures");
    }else if (tri == "id") {
        model->setQuery("SELECT * FROM cultures ORDER BY id");
    } else if (tri == "temp") {
        model->setQuery("SELECT * FROM cultures ORDER BY TEMPERATURE");
    }
    else if (tri == "qualite") {
            model->setQuery("SELECT * FROM cultures ORDER BY QUALITE_AIR");
        }
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("qualite"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("pluv  "));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("humidité"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("ten "));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("temp "));
    return model;
}



bool culture::ajouterCulture()
{
    QSqlQuery query;
    QString qual = QString::number(qualite);
    QString pl = QString::number(pluv);
    QString h = QString::number(hum);
    QString t = QString::number(ten);
    QString tem = QString::number(temp);
    query.prepare("INSERT INTO cultures (QUALITE_AIR,PLUVIOMETRIE,HUMIDITE,TENEUR,TEMPERATURE)" "VALUES (:q,:p,:h,:ten,:tem)");
    query.bindValue(":q",qual);
    query.bindValue(":p",pl);
    query.bindValue(":h",h);
    query.bindValue(":ten",t);
    query.bindValue(":tem",tem);
    return query.exec();
}
QSqlQueryModel * culture::afficherCulture()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * from cultures");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Qualité d'air"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Pluviometrie"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Humidité"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Teneur de sol"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Temperature"));
    return model;
}
bool culture::modifierCulture()
{
    QSqlQuery query;
    QString idS = QString::number(id);
    QString qual = QString::number(qualite);
    QString pl = QString::number(pluv);
    QString h = QString::number(hum);
    QString t = QString::number(ten);
    QString tem = QString::number(temp);
    query.prepare("UPDATE cultures "" SET QUALITE_AIR=:q, PLUVIOMETRIE=:p, HUMIDITE=:h, TENEUR=:ten, TEMPERATURE=:tem WHERE id=:id");
    query.bindValue(":id",idS);
    query.bindValue(":q",qual);
    query.bindValue(":p",pl);
    query.bindValue(":h",h);
    query.bindValue(":ten",t);
    query.bindValue(":tem",tem);
    return query.exec();
}
bool culture::supprimerCulture(int id_culture)
{
    QSqlQuery query;
    query.prepare("DELETE FROM cultures WHERE id= :id");
    query.bindValue(":id",id_culture);
    return query.exec();
}



QSqlQueryModel * culture::rechercherFacture(QString recherche)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * from cultures WHERE (UPPER(id) LIKE UPPER('%"+recherche+"%') )");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Qualité d'air"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Pluviometrie"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Humidité"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Teneur de sol"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Temperature"));
    return model;
}

