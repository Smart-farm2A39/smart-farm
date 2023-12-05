#include "connection.h"

connection::connection()
{

}

bool connection::createconnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("Source_Projet2A39");
    db.setUserName("system");
    db.setPassword("hassen96");
    if(db.open())
        test=true;

    return test;
}

void connection::closeconnection()
{
    db.close();
}
