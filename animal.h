#ifndef ANIMAL_H
#define ANIMAL_H
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QMessageBox>
#include <QMainWindow>
#include <QSqlQuery>
#include <QTableWidget>
#include<QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QPdfWriter>
#include <QPainter>
class Animal
{
    QString caracteristiques, sexe, reproduction,race,vaccination,sante;
    int identifiant,poids,age;
public:
    Animal();
    Animal(int ,QString ,int ,int ,QString ,QString  ,QString ,QString ,QString);

    QString getcaracteristiques();
     QString getsexe();
      QString getreproduction();
       QString getrace();
        QString getvaccination();
         QString getsante();
         int getidentifiant();
         int getpoids();
         int getage();

         void setcaracteristiques(QString c);
         void setsexe(QString s);
         void setreproduction(QString r);
         void setsante(QString sa);
         void setrace(QString rc);
         void setvaccination(QString v);
         void setidentifiant(int id);
         void setpoids(int p);
         void setage(int a);
         bool ajouter();
          QSqlQueryModel * afficher();
         bool supprimer(int identifiant);
         bool rechercher(int identifiant);
         bool modifier(int identfiant,QString reproduction,int poids,QString vaccination,QString sante);
         QSqlQueryModel* rechercheID(int identifiant);
         QSqlQueryModel* triAnimal(QString tri);
         void exportpdf(QString s);
};

#endif // ANIMAL_H
