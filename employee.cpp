#include "employee.h"
#include "QDebug"
Employee::Employee()
{

}
Employee::Employee(int cin,int numero,QString nom,QString prenom ,QString mdp,QString email)
{
    this->cin=cin;
    this->numero=numero;
    this->nom=nom;
    this->prenom=prenom;
    this->mdp=mdp;
    this->email=email;
}
bool Employee::ajouterEmployee()
{
    QSqlQuery query;
    QString cins = QString::number(cin);
    QString numero_de_telephone = QString::number(numero);

    // Assuming nom, prenom, mdp, and email are QString (or you can convert them to QString if they are of a different string type)
    // If they are not QString, you may need to use the appropriate conversion function or constructor.
    QString nomStr = nom;
    QString prenomStr = prenom;
    QString mdpStr = mdp;
    QString emailStr = email;
qDebug()<<nomStr<<prenomStr<<mdpStr<<emailStr<<cins<<numero_de_telephone;
    query.prepare("INSERT INTO EMPLOYES (CIN, NUMERO, NOM, PRENOM, MDP,EMAIL) "" VALUES (:cin, :numero, :nom, :prenom, :mdp,:email)");
    query.bindValue(":cin", cin);
    query.bindValue(":numero", numero);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":mdp", mdp);
    query.bindValue(":email", email);

    return query.exec();
}

QSqlQueryModel * Employee::afficherEmployee()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT cin,NUMERO,NOM,preNOM,MDP,EMAIL from EMPLOYES");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Numero de Telephone"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Mot de Passe"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Email"));
    return model;
}

bool Employee::supprimerEmployee(int cin)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYES WHERE cin= :cin");
    query.bindValue(":cin",cin);
    return query.exec();
}

bool Employee::modifierEmployee()
{
    QSqlQuery query;
    QString cins = QString::number(cin);
    QString numero_de_tel= QString::number(numero);

    // Assuming nom, prenom, mdp, and email are QString (or you can convert them to QString if they are of a different string type)
    // If they are not QString, you may need to use the appropriate conversion function or constructor.
    QString nomStr = nom;
    QString prenomStr = prenom;
    QString mdpStr = mdp;
    QString emailStr = email;

    query.prepare("UPDATE EMPLOYES SET CIN=:cin, NUMERO=:numero, NOM=:nom, PRENOM=:prenom, MDP=:mdp, EMAIL=:email WHERE cin=:cin");
    query.bindValue(":cin", cins);
    query.bindValue(":numero", numero);
    query.bindValue(":nom", nomStr);
    query.bindValue(":prenom", prenomStr);
    query.bindValue(":mdp", mdpStr);
    query.bindValue(":email", emailStr);

    return query.exec();
}


QSqlQueryModel * Employee::rechercherEmployee(QString recherche)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * from EMPLOYES WHERE (UPPER(cin) LIKE UPPER('%"+recherche+"%') OR UPPER(nom) LIKE UPPER('%"+recherche+"%') OR prenom LIKE UPPER('%"+recherche+"%') )");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NUMERO DE TELEPHONE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("MOT DE PASSE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("EMAIL"));
    return model;
}

QSqlQueryModel *Employee::triEmployee(QString tri)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    if(tri == "par défaut"){
        model->setQuery("SELECT * FROM employes");
    }else if (tri == "CIN") {
        model->setQuery("SELECT * FROM employes ORDER BY cin");
    }
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NUMERO DE TELEPHONE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("MOT DE PASSE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("EMAIL"));
    return model;
}
