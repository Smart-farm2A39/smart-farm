#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Employee
{
public:
    Employee();
    Employee(int,int,QString,QString,QString,QString);
    //crud
    bool ajouterEmployee();
    QSqlQueryModel * afficherEmployee();
    bool supprimerEmployee(int);
    bool modifierEmployee();
    //Métiers
    QSqlQueryModel * rechercherEmployee(QString recherche);
    QSqlQueryModel * triEmployee(QString tri);
    QVector<int> statEmployee();


private:
    int cin;
    int numero;
    QString nom;
    QString prenom;
    QString mdp;
    QString email;


};

#endif // EMPLOYEE_H
