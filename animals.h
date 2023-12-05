#ifndef ANIMALS_H
#define ANIMALS_H
#include <QMessageBox>
#include <QMainWindow>
#include <QSqlQuery>
#include <QTableWidget>
#include<QTableView>
#include "animal.h"
#include <QLineEdit>
#include <QPushButton>
#include <QDate>
#include <QFile>
#include <QCoreApplication>
#include <QSslSocket>
#include <QDesktopServices>
#include<QtDebug>
#include "exportexcel.h"
#include<QFileDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class animals; }
QT_END_NAMESPACE

class animals : public QWidget
{
    Q_OBJECT

public:
   animals(QWidget *parent = nullptr);
    ~animals();
private slots:
    void on_pushButton_ajouter_clicked();
     void on_pushButton_supprimer_clicked();
      void on_pushButton_modifier_clicked();
         void on_rechercheID_textChanged(const QString &arg1);
         void on_Trie_botton_clicked();
         void on_Trie_botto_clicked();
          void on_Trie_race_clicked();
           void on_pb_pdf_clicked();
            void on_export_button_clicked();

private:
    Ui::animals*ui;
    Animal a;
    QFile sourceFile;
     QStringList files;
};



#endif // ANIMALS_H
