#include "animal.h"
#include "connection.h"
#include<QSslKey>
Animal::Animal()
{
   identifiant=0;
   caracteristiques="";
   poids=0;
   age=0;
   sexe="";
   reproduction="";
   race="";
    vaccination="";
    sante="";
}

Animal::Animal(int identifiant,QString caracteristiques,int poids,int age,QString sexe,QString reproduction ,QString race,QString vaccination,QString sante)
{

 this->identifiant=identifiant;
    this->caracteristiques=caracteristiques;
    this->poids= poids;
    this->age=age;
    this->sexe=sexe;
    this->reproduction=reproduction;
    this->race=race;
    this->vaccination=vaccination;
    this->sante=sante;
}
QString Animal::getcaracteristiques(){return caracteristiques;}
 QString Animal::getsexe(){return sexe;}
  QString Animal::getreproduction(){return reproduction;}
   QString Animal::getrace(){return race;}
    QString Animal::getvaccination(){return vaccination;}
     QString Animal::getsante(){return sante;}
     int Animal::getidentifiant(){return identifiant;}
     int Animal::getpoids(){return poids;}
     int Animal::getage(){return age;}

     void Animal::setcaracteristiques(QString c){caracteristiques=c;}
     void Animal::setsexe(QString s){sexe=s;}
     void Animal::setreproduction(QString r){reproduction=r;}
     void Animal::setrace(QString rc){race=rc;}
     void Animal::setvaccination(QString v){vaccination=v;}
     void Animal::setsante(QString sa){sante=sa;}
     void Animal::setidentifiant(int id){this->identifiant=id;}
     void Animal::setpoids(int p){this->poids=p;}
     void Animal::setage(int a){this->age=a;}
  /*   void ouvrirConnexion();
     void ouvrirConnexion() // Définition de la fonction d'ouverture de connexion
     {
         QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
         db.setDatabaseName("source");
         db.setUserName("dhia");
         db.setPassword("esprit18");

         if (!db.open())
         {
             // Gérer l'erreur de connexion à la base de données
         }
     }
*/

bool Animal::ajouter()
{

    QSqlQuery query;
    QString identifiant_string=QString::number(identifiant);
    QString poids_string=QString::number(poids);
    QString age_string=QString::number(age);

        query.prepare("insert into ANIMAUX (IDENTIFIANT,CARACTERISTIQUES,POIDS,AGE,SEXE,REPRODUCTION,RACE,VACCINATION,SANTE) "
                      "VALUES (:identifiant,:caracteristiques,:poids,:age,:sexe, :reproduction, :race, :vaccination, :sante)");

        query.bindValue(":identifiant", identifiant);
         query.bindValue(":caracteristiques", caracteristiques);
        query.bindValue(":poids", poids);
        query.bindValue(":age", age);
         query.bindValue(":sexe", sexe);
         query.bindValue(":reproduction", reproduction);
         query.bindValue(":race", race);
           query.bindValue(":vaccination", vaccination);
             query.bindValue(":sante", sante);
        return query.exec();

}

bool Animal::modifier(int identifiant, QString reproduction, int poids, QString vaccination, QString sante) {
    QSqlQuery query;

    query.prepare("UPDATE Animaux SET IDENTIFIANT=:identifiant, REPRODUCTION=:reproduction, POIDS=:poids, VACCINATION=:vaccination, SANTE=:sante WHERE IDENTIFIANT=:identifiant");
    query.bindValue(":identifiant", identifiant);
    query.bindValue(":reproduction", reproduction);
    query.bindValue(":poids", poids);
    query.bindValue(":vaccination", vaccination);
    query.bindValue(":sante", sante);

    return query.exec();
}

QSqlQueryModel *Animal::afficher()

{

    QSqlQueryModel *model=new QSqlQueryModel();
    //ouvrirConnexion();
            model->setQuery("SELECT* FROM AnimaUX");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("caracteristiques"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("poids"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("age"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("sexe"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("reproduction"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("race"));
            model->setHeaderData(7, Qt::Horizontal, QObject::tr("vaccination"));
            model->setHeaderData(8, Qt::Horizontal, QObject::tr("sante"));
      return model;

}
bool Animal::supprimer(int identifiant)
{

        QSqlQuery query;
        query.prepare("DELETE FROM animaux WHERE identifiant=:identifiant");

        query.bindValue(":identifiant", identifiant);
        return query.exec();

}
QSqlQueryModel* Animal::rechercheID(int identifiant )
{
    QSqlQueryModel * model=new QSqlQueryModel();
    QString id=QString::number(identifiant);
    model->setQuery("select * from ANIMAux where IDENTIFIANT like '"+id+"%' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("carateristiques"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("poids"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("age"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("sexe"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("reproduction"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("race"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("vaccination"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("sante"));
        return model;

}
QSqlQueryModel * Animal::triAnimal(QString tri)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    if(tri == "par defaut"){
        model->setQuery("SELECT * FROM animaux");
    }else if (tri == "id") {
        model->setQuery("SELECT * FROM animaux ORDER BY identifiant");
    } else if (tri == "poids") {
        model->setQuery("SELECT * FROM animaux ORDER BY poids");
    }
    else if (tri == "age") {
            model->setQuery("SELECT * FROM animaux ORDER BY age");
        }
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("carateristiques"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("poids"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("age"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("sexe"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("reproduction"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("race"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("vaccination"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("sante"));
    return model;
}

void Animal::exportpdf(QString s)
{
    QString s1 = "C:/Users/Mannai/Downloads/" + s + ".pdf";
    QPdfWriter pdf(s1);

    QPainter painter(&pdf);

    int i = 4000;
    QImage logoImage("C:/Users/Mannai/Downloads/4_lg.jpg");
    if (!logoImage.isNull()) {
        painter.drawImage(QRect(100, 100, 2000, 500), logoImage); }

    int squareWidth = 4000;
    int squareX = (pdf.width() - squareWidth) / 2;

    painter.setFont(QFont("Century Gothic", 50, QFont::Bold));
    painter.setPen(Qt::blue);

    int titleX = squareX + (squareWidth - painter.fontMetrics().width("LISTE DES ANIMAUX")) / 2;

    painter.drawText(titleX, 1200, "LISTE DES ANIMAUX");
    painter.setFont(QFont("Century Gothic", 9));
    painter.setPen(Qt::black);
    painter.drawText(500, 3300, "IDENTIFIANT");
    painter.drawText(1500, 3300, "CARACTERISTIQUES");
    painter.drawText(3000, 3300, "POIDS");
    painter.drawText(3700, 3300, "AGE");
    painter.drawText(4100, 3300, "SEXE");
    painter.drawText(4700, 3300, "REPRODUCTION");
    painter.drawText(6500, 3300, "RACE");
    painter.drawText(7500, 3300, "VACCINATION");
    painter.drawText(9000, 3300, "SANTE");

    QSqlQuery query;
    query.prepare("SELECT * FROM ANIMAL");
    query.exec();
    while (query.next()) {
        painter.drawText(500, i, query.value(0).toString());
        painter.drawText(1500, i, query.value(1).toString());
        painter.drawText(3000, i, query.value(2).toString());
        painter.drawText(3700, i, query.value(3).toString());
        painter.drawText(4100, i, query.value(4).toString());
        painter.drawText(4700, i, query.value(5).toString());
        painter.drawText(6500, i, query.value(6).toString());
        painter.drawText(7500, i, query.value(7).toString());
        painter.drawText(9000, i, query.value(8).toString());



        i = i + 500;
    }
}

