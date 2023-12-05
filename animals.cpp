#include "animals.h"
#include"animal.h"
#include"ui_animals.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <QCoreApplication>
#include <QSslSocket>
/*
int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // Ensure SSL support is available
    if (!QSslSocket::supportsSsl()) {
        qDebug() << "SSL not supported!";
        return 1;
    }

    // Create the SSL socket
    QSslSocket sslSocket;

    // Connect to the server
    sslSocket.connectToHostEncrypted("smtp.gmail.com",465);

    // Check for errors
    if (sslSocket.waitForConnected()) {
        qDebug() << "Connected!";
    } else {
        qDebug() << "Connection error:" << sslSocket.errorString();
    }

    // Your networking code here using sslSocket...

    return a.exec();
}
*/

animals::animals(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::animals)
{
    ui->setupUi(this);
    ui->tableView->setModel(a.afficher());
    ui->tableView_2->setModel(a.afficher());
    ui->tableView_3->setModel(a.afficher());
    ui->affichage_1->setModel(a.afficher());
}

animals::~animals()
{
    delete ui;
}
void animals::on_pushButton_ajouter_clicked()
{
    int identifiant= ui->lineEdit_15->text().toInt();
    QString caracteristiques= ui->lineEdit_19->text();
    int poids= ui->lineEdit_12->text().toInt();
    int age= ui->lineEdit_11->text().toInt();
     QString sexe= ui->lineEdit_16->text();
      QString reproduction= ui->lineEdit_17->text();
       QString race= ui->lineEdit_13->text();
        QString vaccination= ui->lineEdit_18->text();
         QString sante= ui->lineEdit_14->text();

    Animal a (identifiant,caracteristiques, poids, age,sexe,reproduction,race,vaccination,sante);
    bool test = a.ajouter();
    if (test)
    {
        ui->tableView->setModel(a.afficher());
        ui->tableView_2->setModel(a.afficher());
        ui->tableView_3->setModel(a.afficher());
        ui->affichage_1->setModel(a.afficher());
        QMessageBox::information(nullptr,QObject::tr("OK"),
                             QObject::tr("Ajout effectué\n" "Click cancel to exit."),
                             QMessageBox::Ok);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                              QObject::tr("Ajout non effectué\n" "Click cancel to exit."), QMessageBox::Cancel);

    }

}

void animals::on_pushButton_supprimer_clicked()
{
    int identifiant = ui->lineEdit_15->text().toInt();
    bool test = a.supprimer(identifiant);
    if (test)
    {
        ui->tableView->setModel(a.afficher());
        ui->tableView_2->setModel(a.afficher());
        ui->tableView_3->setModel(a.afficher());
        ui->affichage_1->setModel(a.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée\n" "Click cancel to exit."), QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                              QObject::tr("Suppression non effectuée\n" "Click cancel to exit."), QMessageBox::Cancel);
    }
}

void animals::on_pushButton_modifier_clicked()
{
    bool  test;
    int identifiant= ui->lineEdit_20->text().toInt();
    QString reproduction = ui->lineEdit_13->text();
    int poids = ui->lineEdit_11->text().toInt();
    QString vaccination = ui->lineEdit_12->text();
    QString sante = ui->lineEdit_14->text();
     test =  a.modifier (identifiant , reproduction , poids , vaccination , sante);

          if (test)
          {
              ui->tableView->setModel(a.afficher());
              ui->tableView_2->setModel(a.afficher());
              ui->tableView_3->setModel(a.afficher());
              ui->affichage_1->setModel(a.afficher());
              QMessageBox::information(nullptr,QObject::tr("OK"),
                                   QObject::tr("modification établie"),
                                   QMessageBox::Ok);}
          else{
          QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                  QObject::tr("modification non établie"),
                                  QMessageBox::Cancel);}
}
void animals::on_rechercheID_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
                   QSqlQuery   *query= new QSqlQuery();
           if(ui->rechercheID->text()==arg1)
                   {
               query->prepare("SELECT * FROM ANIMAL WHERE IDENTIFIANT LIKE'"+arg1+"%'");//
       query->exec();
           model->setQuery(*query);
      ui->affichage_1->setModel(model);
}
}
void animals::on_Trie_botto_clicked()
{
    ui->affichage_1->setModel(a.sortid_up());
}

void animals::on_Trie_botton_clicked()
{
    ui->affichage_1->setModel(a.sortid_down());
}
void animals::on_Trie_race_clicked()
{
    ui->affichage_1->setModel(a.sortrace());

}
void animals::on_pb_pdf_clicked()
{   QString s;
    s=ui->PDF->text();
    a.exportpdf(s);
}
void animals::on_export_button_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                                  tr("Excel Files (*.xls)"));
                  if (fileName.isEmpty())
                      return;

                  ExportExcel obj(fileName, "Taches", ui->tableView);

                  //colums to export
                  obj.addField(0, "IDENTIFIANT", "char(20)");
                  obj.addField(1, "CARACTERISTIQUES", "char(20)");
                  obj.addField(2, "POIDS", "char(20)");
                  obj.addField(3, "AGE", "char(20)");
                  obj.addField(4, "SEXE", "char(20)");
                  obj.addField(5, "REPRODUCTION", "char(20)");
                  obj.addField(6, "RACE", "char(20)");
                  obj.addField(7, "VACCINATION", "char(20)");
                  obj.addField(8, "SANTE", "char(20)");




                  int retVal = obj.export2Excel();
                  if( retVal > 0)
                  {
                      QMessageBox::information(this, tr("Done"),
                                               tr("Exportatoin reussite"));
                  }

}



