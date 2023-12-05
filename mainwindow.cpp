#include "mainwindow.h"
#include "ui_mainwindow.h"

QString user,type;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QIcon icon(":/l/icon/logo.png"); // Use the correct path to your icon resource
        this->setWindowIcon(icon);
    ui->idfacLE->hide();
    ui->triFacturesComboBox->addItem("par défaut");
    ui->triFacturesComboBox->addItem("Bénefice");
    ui->triFacturesComboBox->addItem("Coût d'arrosage");
    ui->triFacturesComboBox->addItem("Gain financier");
    int ret=A.connect_arduino(); // lancer la connexion à arduino
                switch(ret){
                case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                    break;
                case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
                   break;
                case(-1):qDebug() << "arduino is not available";
                }
   /* culture setUp */
    ui->idCultureLE_2->hide();
    /* employes */
    ui->mainStackWidget->setCurrentIndex(0);
    ui->triEmplyeComboBox->addItem("par défaut");
    ui->triEmplyeComboBox->addItem("CIN");
    ui->idfacLE_2->hide();
    /* irrigation */
    ui->idIrrUpdate->hide();
    ui->triIrrigationComboBox->addItem("Par défaut");
    ui->triIrrigationComboBox->addItem("Quantité");
    ui->triIrrigationComboBox->addItem("Réference");
    ui->triIrrigationComboBox->addItem("Nom");
    ui->typeCMBX_2->addItem("Arbre");ui->typeCMBX_2->addItem("Arbuste");
    ui->typeCMBX_2->addItem("Fleure");
    ui->typeCMBX->addItem("Arbre");ui->typeCMBX->addItem("Arbuste");
    ui->typeCMBX->addItem("Fleure");
    ui->labelCache->hide();




 }


MainWindow::~MainWindow()
{
    delete ui;
}


/* irrigation start*/
void MainWindow::on_irrigationBtnPage_clicked()
{
    ui->mainStackWidget->setCurrentIndex(6);
    ui->irrigationStackWidget->setCurrentIndex(0);

}


void MainWindow::on_facturesBtnPage_clicked()
{
    ui->mainStackWidget->setCurrentIndex(2);
}

void MainWindow::on_ajouterFacturePageBtn_clicked()
{
    ui->factureStackWidget->setCurrentIndex(1);
}

void MainWindow::on_employesBtnPage_4_clicked()
{
    ui->factureTableView->setModel(f.afficherFacture());
    ui->factureStackWidget->setCurrentIndex(5);
}

void MainWindow::on_animauxBtnPage_clicked()
{
    ui->mainStackWidget->setCurrentIndex(1);
    ui->factureStackWidget_4->setCurrentIndex(0);
}
void MainWindow::on_backMenuIrr_29_clicked()
{
    ui->mainStackWidget->setCurrentIndex(0);
}
void MainWindow::on_backMenuIrr_30_clicked()
{
    ui->factureStackWidget_4->setCurrentIndex(0);

}
void MainWindow::on_backMenuIrr_31_clicked()
{
    ui->factureStackWidget_4->setCurrentIndex(0);
}

void MainWindow::on_backMenuIrr_32_clicked()
{

    ui->factureStackWidget_4->setCurrentIndex(2);
}


void MainWindow::on_ajouterFacturePageBtn_4_clicked()
{
    ui->factureTableView->setModel(a.afficher());
    ui->factureStackWidget_4->setCurrentIndex(1);

}
void MainWindow::on_employesBtnPage_12_clicked()
{
    ui->factureTableView->setModel(a.afficher());
    ui->factureStackWidget_4->setCurrentIndex(2);
}


void MainWindow::on_factureTableView_clicked(const QModelIndex &index)
{
    int row = index.row();
    QString qrCodeData;
    QModelIndex sibling = index.sibling(row,0);
    QString id = ui->factureTableView->model()->data(sibling).toString();
        QSqlQuery qry;
        qry.prepare("SELECT * FROM factures WHERE id=:id" );
        qry.bindValue(":id",id);
        if(qry.exec())
        {
            while(qry.next())
            {
                ui->idfacLE->setText(qry.value(0).toString());
                ui->lineEdit_10->setText(qry.value(1).toString());
                ui->lineEdit_6->setText(qry.value(2).toString());
                ui->lineEdit_8->setText(qry.value(3).toString());
                ui->lineEdit_9->setText(qry.value(4).toString());
                ui->lineEdit_7->setText(qry.value(5).toString());
                qrCodeData ="Facture ID : "+qry.value(0).toString()+" | Produit et Dep : "+qry.value(1).toString()+" | Bénéfice : "+qry.value(2).toString()+" | Frais d'alimentation : "+qry.value(3).toString()+" | Coût d'arrosage : "+qry.value(4).toString()+" | Gain financier : "+qry.value(5).toString();
            }
        }
        //QR CODE
        using namespace qrcodegen;
        // Create the QR Code object
          QrCode qr = QrCode::encodeText( qrCodeData.toUtf8().data(), QrCode::Ecc::MEDIUM );
          qint32 sz = qr.getSize();
          QImage im(sz,sz, QImage::Format_RGB32);
          QRgb black = qRgb(  0,  0,  0);
          QRgb white = qRgb(255,255,255);
       for (int y = 0; y < sz; y++)
            for (int x = 0; x < sz; x++)
                 im.setPixel(x,y,qr.getModule(x, y) ? black : white );
       ui->qrCodeLabel->setPixmap( QPixmap::fromImage(im.scaled(150,150,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );
A.write_to_arduino("Creation de QRCODE");
QSqlQuery query;
  query.prepare("insert into rfid (mess,daterfid)""values(:mess,:daterfid)");
          query.bindValue(":mess", "Creation de QRCODE");
  query.bindValue(":daterfid", QDateTime::currentDateTime());
query.exec();
}

void MainWindow::on_modifierIrrBtnPage_clicked()
{
    ui->factureStackWidget->setCurrentIndex(3);
}

void MainWindow::on_addFacBtn_clicked()
{
    QString prod_dep = ui->lineEdit->text();
    float ben=ui->lineEdit_2->text().toFloat(),fr=ui->lineEdit_3->text().toFloat();
    float cout=ui->lineEdit_4->text().toFloat(),gain=ui->lineEdit_5->text().toFloat();
    Facture fac(0,prod_dep,ben,fr,cout,gain);
    if(fac.ajouterFacture()){
            ui->factureTableView->setModel(f.afficherFacture());
            ui->factureStackWidget->setCurrentIndex(2);
            notif.notifAddFacture();
            A.write_to_arduino("ajout d'un facture "+prod_dep);
            QSqlQuery query;
              query.prepare("insert into rfid (mess,daterfid)""values(:mess,:daterfid)");
                      query.bindValue(":mess", "ajout d'un facture");
              query.bindValue(":daterfid", QDateTime::currentDateTime());
            query.exec();
    }else{
        QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                              QObject::tr("Echec de l'opération. \n"
                                          "Click me to exit."), QMessageBox::Cancel);
        notif.notif_failed();
        A.write_to_arduino("ERROR");
    }
}

void MainWindow::on_addFacBtn_2_clicked()
{
    int id=ui->idfacLE->text().toInt();
    QString prod_dep = ui->lineEdit_10->text();
    float ben=ui->lineEdit_6->text().toFloat(),fr=ui->lineEdit_8->text().toFloat();
    float cout=ui->lineEdit_9->text().toFloat(),gain=ui->lineEdit_7->text().toFloat();
    Facture fac(id,prod_dep,ben,fr,cout,gain);
    if(fac.modifierFacture()){
            ui->factureTableView->setModel(f.afficherFacture());
            ui->factureStackWidget->setCurrentIndex(2);
            notif.notifUpdateFacture();
            A.write_to_arduino("mod d'un facture "+prod_dep);
            QSqlQuery query;
              query.prepare("insert into rfid (mess,daterfid)""values(:mess,:daterfid)");
                      query.bindValue(":mess", "mod d'un facture");
              query.bindValue(":daterfid", QDateTime::currentDateTime());
            query.exec();
    }else{
        QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                              QObject::tr("Echec de l'opération. \n"
                                          "Click me to exit."), QMessageBox::Cancel);
        notif.notif_failed();
        A.write_to_arduino("ERROR");

    }
}

void MainWindow::on_deleteIrrBtn_clicked()
{
    QModelIndex indexItem = ui->factureTableView->currentIndex();
    int row = indexItem.row();
    QModelIndex sibling = indexItem.sibling(row,0);
    int id = ui->factureTableView->model()->data(sibling).toInt();
    if(f.supprimerFacture(id))
    {
         ui->factureTableView->setModel(f.afficherFacture());
         notif.notifDeleteFacture();
         A.write_to_arduino("del d'un facture "+id);

         QSqlQuery query;
           query.prepare("insert into rfid (mess,daterfid)""values(:mess,:daterfid)");
                   query.bindValue(":mess", "delete d'une facture");
           query.bindValue(":daterfid", QDateTime::currentDateTime());
         query.exec();
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                              QObject::tr("Echec d'opération. \n"
                                          "Click me to exit."), QMessageBox::Cancel);
        notif.notif_failed();
        A.write_to_arduino("ERROR");

    }
}

void MainWindow::on_backMenuIrr_4_clicked()
{
    ui->mainStackWidget->setCurrentIndex(0);
}

void MainWindow::on_backMenuIrr_2_clicked()
{
    ui->factureStackWidget->setCurrentIndex(0);
}

void MainWindow::on_backMenuIrr_3_clicked()
{
    ui->factureStackWidget->setCurrentIndex(0);
}

void MainWindow::on_backMenuIrr_clicked()
{
    ui->factureStackWidget->setCurrentIndex(0);
}

void MainWindow::on_rechercheBar_textChanged(const QString &arg1)
{
    if(arg1!=""){
    ui->factureTableView->setModel(f.rechercherFacture(arg1));
    A.write_to_arduino("rech par : "+arg1);

    }
    else
        ui->factureTableView->setModel(f.afficherFacture());
}

void MainWindow::on_triFacturesComboBox_currentIndexChanged(const QString &arg1)
{
       ui->factureTableView->setModel(f.triFacture(arg1));
          A.write_to_arduino("tri affectuee");
          QSqlQuery query;
            query.prepare("insert into rfid (mess,daterfid)""values(:mess,:daterfid)");
                    query.bindValue(":mess", "tri affectuee");
            query.bindValue(":daterfid", QDateTime::currentDateTime());
          query.exec();
}

void MainWindow::on_pdfBtn_clicked()
{
    QString strStream;
       QTextStream out(&strStream);
       QDate currentDate = QDate::currentDate();
       QString date = currentDate.toString("dd-MM-yyyy");


       const int rowCount = ui->factureTableView->model()->rowCount();
       const int columnCount = ui->factureTableView->model()->columnCount();

       out <<  "<html>\n"
           "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
           <<  QString("<title>%1</title>\n").arg("col1")
           <<  "</head>\n"
           "<body bgcolor=#ffffff link=#5000A0>\n"
           "<h3 style='position: absolute; top: 0; right: 0; margin: 0; padding: 10px; text-align: right; font-size: 24px; color: #333;'> Tunis "+date+"</h3>"
           "<h1 style='text-align: center;'>Liste des Factures</h1>\n"
           "<br>\n"
           "<br>\n"
               "<div align='center'>"
           "<table border=1 cellspacing=0 cellpadding=2>\n";

       // headers
       out << "<thead><tr bgcolor=#f0f0f0>";
       for (int column = 0; column < columnCount; column++)
           if (!ui->factureTableView->isColumnHidden(column))
               out << QString("<th>%1</th>").arg(ui->factureTableView->model()->headerData(column, Qt::Horizontal).toString());
       out << "</tr></thead>\n";

       // data table
       for (int row = 0; row < rowCount; row++) {
           out << "<tr>";
           for (int column = 0; column < columnCount; column++) {
               if (!ui->factureTableView->isColumnHidden(column)) {
                   QString data = ui->factureTableView->model()->data(ui->factureTableView->model()->index(row, column)).toString().simplified();
                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
               }
           }
           out << "</tr>\n";
       }
       out <<  "</table>\n"
               "</div>"
           "</body>\n"
           "</html>\n";

       QTextDocument *document = new QTextDocument();
       document->setHtml(strStream);

       QPrinter printer;

           document->print(&printer);


       delete document;
           A.write_to_arduino("PDF generee");
           QSqlQuery query;
             query.prepare("insert into rfid (mess,daterfid)""values(:mess,:daterfid)");
                     query.bindValue(":mess", "PDF generee");
             query.bindValue(":daterfid", QDateTime::currentDateTime());
           query.exec();

}

void MainWindow::statPieFactures()
{
    QLayout* layoutTest = ui->facturesStatContainer->layout();
    if (layoutTest) {
        delete layoutTest;  // Delete the existing layout object
    }
    QVector<int> stat = f.statFacture();
    QBarSet *set = new QBarSet("Montant en DT");

    for(int i=0; i <stat.size(); i++)
    {
        *set << stat[i];
    }
    QBarSeries *series = new QBarSeries();
    series->append(set);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Bénefice ET Frais d'alimentations");
    chart->setAnimationOptions(QChart::AllAnimations);
    QStringList list;
        list << "Bénefice" << "Frais d'alimentations";
    QValueAxis *axisY = new QValueAxis();
    chart->setAxisY(axisY,series);
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(list);
    chart->createDefaultAxes();
    chart->setAxisX(axisX,series);
    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window, QRgb(0xffffff));
    pal.setColor(QPalette::WindowText, QRgb(0x404044));
    qApp->setPalette(pal);
    QChartView * chartView= new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(801,311);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    ui->facturesStatContainer->setLayout(layout);
}

void MainWindow::on_statBtnPage_clicked()
{
    ui->factureStackWidget->setCurrentIndex(4);
    statPieFactures();
}

void MainWindow::on_backMenuIrr_5_clicked()
{
    ui->factureStackWidget->setCurrentIndex(0);
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    // You can add custom behavior here before the application closes

    // For example, display a confirmation dialog
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exit", "Are you sure you want to exit?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // User clicked Yes, close the application
        event->accept();
        A.write_to_arduino("Good Bye");
    } else {
        // User clicked No, ignore the close event
        event->ignore();
    }
}
/* Culture intégration */
void MainWindow::on_ajouterCulturesPageBtn_3_clicked()
{
    ui->culturesStackWidget_2->setCurrentIndex(1);
}

void MainWindow::on_employesBtnPage_6_clicked()


 {
    ui->culturesStackWidget_2->setCurrentIndex(5);
}

void MainWindow::on_modifierCultBtnPage_2_clicked()
{
    ui->culturesStackWidget_2->setCurrentIndex(3);
}

void MainWindow::on_cultureTableView_2_clicked(const QModelIndex &index)
{
    int row = index.row();
       QString qrCodeData="";
    QModelIndex sibling = index.sibling(row,0);
    QString id = ui->cultureTableView_2->model()->data(sibling).toString();
        QSqlQuery qry;
        qry.prepare("SELECT * FROM cultures WHERE id=:id" );
        qry.bindValue(":id",id);
        if(qry.exec())
        {
            while(qry.next())
            {
                ui->idCultureLE_2->setText(qry.value(0).toString());
                ui->lineEdit_28->setText(qry.value(1).toString());
                ui->lineEdit_27->setText(qry.value(2).toString());
                ui->lineEdit_26->setText(qry.value(3).toString());
                ui->lineEdit_30->setText(qry.value(4).toString());
                ui->lineEdit_29->setText(qry.value(5).toString());
                qrCodeData = "ID : "+qry.value(0).toString()+" Qualite : "+qry.value(1).toString()+" Pluviometrie : "+qry.value(2).toString();
            }
        }
        //QR CODE
        using namespace qrcodegen;
        // Create the QR Code object
          QrCode qr = QrCode::encodeText( qrCodeData.toUtf8().data(), QrCode::Ecc::MEDIUM );
          qint32 sz = qr.getSize();
          QImage im(sz,sz, QImage::Format_RGB32);
          QRgb black = qRgb(  0,  0,  0);
          QRgb white = qRgb(255,255,255);
       for (int y = 0; y < sz; y++)
            for (int x = 0; x < sz; x++)
                 im.setPixel(x,y,qr.getModule(x, y) ? black : white );
       ui->qrCodeLabel_3->setPixmap( QPixmap::fromImage(im.scaled(150,150,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );
}

void MainWindow::on_addCultBtn_3_clicked()
{
    float qual = ui->lineEdit_21->text().toFloat();
    float pl = ui->lineEdit_22->text().toFloat();
    float hum = ui->lineEdit_23->text().toFloat();
    float ten = ui->lineEdit_24->text().toFloat();
    float temp = ui->lineEdit_25->text().toFloat();
    culture cult(0,qual,pl,hum,ten,temp);
    if(cult.ajouterCulture()){
            ui->cultureTableView_2->setModel(c.afficherCulture());
            ui->culturesStackWidget_2->setCurrentIndex(2);
            notif.notifAddFacture();
    }else{
        QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                              QObject::tr("Echec de l'opération. \n"
                                          "Click me to exit."), QMessageBox::Cancel);
    notif.notif_failed();
    }
}

void MainWindow::on_deleteICultBtn_2_clicked()
{
    QModelIndex indexItem = ui->cultureTableView_2->currentIndex();
    int row = indexItem.row();
    QModelIndex sibling = indexItem.sibling(row,0);
    int id = ui->cultureTableView_2->model()->data(sibling).toInt();
    if(c.supprimerCulture(id))
    {
         ui->cultureTableView_2->setModel(c.afficherCulture());
    notif.notifDeleteFacture();
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                              QObject::tr("Echec d'opération. \n"
                                          "Click me to exit."), QMessageBox::Cancel);
     notif.notif_failed();
    }
}

void MainWindow::on_imprimerBtn_2_clicked()
{
      QPrinter printer(QPrinter::HighResolution);
        QPrintDialog printDialog(&printer, this);
        if (printDialog.exec() == QDialog::Accepted) {
            QTextDocument document;
            // Ajoutez le contenu de la table à document
            QString tableContent;
            for (int row = 0; row < ui->cultureTableView_2->model()->rowCount(); ++row) {
                for (int column = 0; column < ui->cultureTableView_2->model()->columnCount(); ++column) {
                    QModelIndex index = ui->cultureTableView_2->model()->index(row, column);
                    QString data = ui->cultureTableView_2->model()->data(index).toString();
                    tableContent.append(data + "\t");
                }
                tableContent.append("\n");
            }
            document.setPlainText(tableContent);
            // Imprimez le document
            document.print(&printer);
        }
}

void MainWindow::on_addCultBtn_4_clicked()
{
    int id = ui->idCultureLE_2->text().toInt();
    float qual = ui->lineEdit_28->text().toFloat();
    float pl = ui->lineEdit_27->text().toFloat();
    float hum = ui->lineEdit_26->text().toFloat();
    float ten = ui->lineEdit_30->text().toFloat();
    float temp = ui->lineEdit_29->text().toFloat();
    culture cult(id,qual,pl,hum,ten,temp);
    if(cult.modifierCulture()){
            ui->cultureTableView_2->setModel(c.afficherCulture());
            ui->culturesStackWidget_2->setCurrentIndex(2);
            notif.notifUpdateFacture();
    }else{
        QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                              QObject::tr("Echec de l'opération. \n"
                                          "Click me to exit."), QMessageBox::Cancel);
        notif.notif_failed();
    }
}

void MainWindow::on_backMenuIrr_10_clicked()
{
    ui->mainStackWidget->setCurrentIndex(0);
}

void MainWindow::on_backMenuIrr_11_clicked()
{
    ui->culturesStackWidget_2->setCurrentIndex(0);
}

void MainWindow::on_backMenuIrr_12_clicked()
{
    ui->culturesStackWidget_2->setCurrentIndex(0);
}

void MainWindow::on_backMenuIrr_13_clicked()
{
    ui->culturesStackWidget_2->setCurrentIndex(0);
}

void MainWindow::on_rechercheBar_3_textChanged(const QString &arg1)
{
    if(arg1 != "")
    ui->cultureTableView_2->setModel(c.rechercherCacture(arg1));
    else
        ui->cultureTableView_2->setModel(c.afficherCulture());
}

void MainWindow::on_TriBtn_2_currentIndexChanged(const QString &arg1)
{
    ui->cultureTableView_2->setModel(c.triCulture(arg1));
}

void MainWindow::on_culturesBtnPage_clicked()
{
    ui->mainStackWidget->setCurrentIndex(3);
}
/* employes integration */
void MainWindow::on_pushButton_conn_2_clicked()
{
    QString cin = ui->lineEdit_usernamee_2->text();
    QString pass = ui->lineEdit_passwordd_2->text();
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYES WHERE cin = :cin AND MDP = :password");
    query.bindValue(":cin", cin);
    query.bindValue(":password", pass);
    query.exec();
    if (query.next()) {
        user= query.value(0).toString();
     ui->mainStackWidget->setCurrentIndex(5);
    }
    if( user=="dhia"){
        ui->irrigationBtnPage->hide();
        ui->animauxBtnPage->hide();
        ui->facturesBtnPage->hide();
        ui->employesBtnPage->hide();
        ui->widget->hide();
        ui->widget_2->hide();

        ui->widget_3->hide();

        ui->widget_5->hide();
    }
}

void MainWindow::on_employesBtnPage_clicked()
{
    ui->mainStackWidget->setCurrentIndex(4);


}

void MainWindow::on_backMenulrr_4_clicked()
{
    ui->mainStackWidget->setCurrentIndex(0);
}

void MainWindow::on_ajouterEmployePageBtn_clicked()
{
    ui->employeWidget->setCurrentIndex(1);
}

void MainWindow::on_addEmplBtn_clicked()
{
    int cin = ui->lineEdit_11->text().toInt();
    int numero = ui->lineEdit_12->text().toInt();
    QString nom = ui->lineEdit_13->text();
    QString prenom = ui->lineEdit_14->text();
    QString mdp = ui->lineEdit_15->text();
    QString email = ui->lineEdit_31->text(); // Corrected line number and variable name
    Employee emp(cin, numero, nom, prenom, mdp, email);
    // Now you can use 'emp' as needed, for example, to add it to a list, database, etc.
    if(emp.ajouterEmployee()){
            ui->employeeTableView_2->setModel(e.afficherEmployee());
            ui->employeWidget->setCurrentIndex(2);
            notif.notifAddFacture();
    }else{
        QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                              QObject::tr("Echec de l'opération. \n"
                                          "Click me to exit."), QMessageBox::Cancel);
        notif.notif_failed();

    }
}

void MainWindow::on_pdfBtn_2_clicked()
{
    QString strStream;
       QTextStream out(&strStream);
       QDate currentDate = QDate::currentDate();
       QString date = currentDate.toString("dd-MM-yyyy");


       const int rowCount = ui->employeeTableView_2->model()->rowCount();
       const int columnCount = ui->employeeTableView_2->model()->columnCount();

       out <<  "<html>\n"
           "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
           <<  QString("<title>%1</title>\n").arg("col1")
           <<  "</head>\n"
           "<body bgcolor=#ffffff link=#5000A0>\n"
           "<h3 style='position: absolute; top: 0; right: 0; margin: 0; padding: 10px; text-align: right; font-size: 24px; color: #333;'> Tunis "+date+"</h3>"
           "<h1 style='text-align: center;'>Liste des Factures</h1>\n"
           "<br>\n"
           "<br>\n"
               "<div align='center'>"
           "<table border=1 cellspacing=0 cellpadding=2>\n";

       // headers
       out << "<thead><tr bgcolor=#f0f0f0>";
       for (int column = 0; column < columnCount; column++)
           if (!ui->employeeTableView_2->isColumnHidden(column))
               out << QString("<th>%1</th>").arg(ui->employeeTableView_2->model()->headerData(column, Qt::Horizontal).toString());
       out << "</tr></thead>\n";

       // data table
       for (int row = 0; row < rowCount; row++) {
           out << "<tr>";
           for (int column = 0; column < columnCount; column++) {
               if (!ui->employeeTableView_2->isColumnHidden(column)) {
                   QString data = ui->employeeTableView_2->model()->data(ui->employeeTableView_2->model()->index(row, column)).toString().simplified();
                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
               }
           }
           out << "</tr>\n";
       }
       out <<  "</table>\n"
               "</div>"
           "</body>\n"
           "</html>\n";

       QTextDocument *document = new QTextDocument();
       document->setHtml(strStream);

       QPrinter printer;

           document->print(&printer);


       delete document;
}

void MainWindow::on_employeeTableView_2_clicked(const QModelIndex &index)
{
    int row = index.row();
    QString qrCodeData;
    QModelIndex sibling = index.sibling(row,0);
    QString id = ui->employeeTableView_2->model()->data(sibling).toString();
        QSqlQuery qry;
        qry.prepare("SELECT * FROM employes WHERE cin=:id" );
        qry.bindValue(":id",id);
        if(qry.exec())
        {
            while(qry.next())
            {
                ui->lineEdit_18->setText(qry.value(0).toString());
                ui->lineEdit_19->setText(qry.value(1).toString());
                ui->lineEdit_20->setText(qry.value(2).toString());
                ui->lineEdit_32->setText(qry.value(3).toString());
                ui->lineEdit_16->setText(qry.value(4).toString());
                ui->lineEdit_17->setText(qry.value(5).toString());
            }
        }
        //QR CODE
        using namespace qrcodegen;
        // Create the QR Code object
          QrCode qr = QrCode::encodeText( qrCodeData.toUtf8().data(), QrCode::Ecc::MEDIUM );
          qint32 sz = qr.getSize();
          QImage im(sz,sz, QImage::Format_RGB32);
          QRgb black = qRgb(  0,  0,  0);
          QRgb white = qRgb(255,255,255);
       for (int y = 0; y < sz; y++)
            for (int x = 0; x < sz; x++)
                 im.setPixel(x,y,qr.getModule(x, y) ? black : white );
       ui->qrCodeLabel->setPixmap( QPixmap::fromImage(im.scaled(150,150,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );
}

void MainWindow::on_modifierIrrBtnPage_2_clicked()
{
    ui->employeWidget->setCurrentIndex(3);
}

void MainWindow::on_modifierBtn_clicked()
{
    int cin = ui->lineEdit_20->text().toInt();
    int numero = ui->lineEdit_16->text().toInt();
    QString nom = ui->lineEdit_18->text();
    QString prenom = ui->lineEdit_19->text();
    QString mdp = ui->lineEdit_17->text();
    QString email = ui->lineEdit_32->text();
    Employee emp(cin, numero, nom, prenom, mdp, email);
    if(emp.modifierEmployee()){
            ui->employeeTableView_2->setModel(e.afficherEmployee());
            ui->employeWidget->setCurrentIndex(2);
            notif.notifUpdateFacture();

    }else{
        QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                              QObject::tr("Echec de l'opération. \n"
                                          "Click me to exit."), QMessageBox::Cancel);
         notif.notif_failed();
    }
}

void MainWindow::on_deleteIrrBtn_2_clicked()
{
    QModelIndex indexItem = ui->employeeTableView_2->currentIndex();
    int row = indexItem.row();
    QModelIndex sibling = indexItem.sibling(row,0);
    int id = ui->employeeTableView_2->model()->data(sibling).toInt();
    if((e.supprimerEmployee(id)))
    {
         ui->employeeTableView_2->setModel(e.afficherEmployee());
        notif.notifDeleteFacture();
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                              QObject::tr("Echec d'opération. \n"
                                          "Click me to exit."), QMessageBox::Cancel);
     notif.notif_failed();
    }
}

void MainWindow::on_triEmplyeComboBox_currentIndexChanged(const QString &arg1)
{
    ui->employeeTableView_2->setModel(e.triEmployee(arg1));
}

void MainWindow::on_rechercheBar_2_textChanged(const QString &arg1)
{
    if(arg1!="")
    ui->employeeTableView_2->setModel(e.rechercherEmployee(arg1));
    else
        ui->employeeTableView_2->setModel(e.afficherEmployee());
}

void MainWindow::on_employesBtnPage_5_clicked()
{
    ui->employeWidget->setCurrentIndex(2);
}

void MainWindow::on_backMenuIrr_8_clicked()
{
    ui->employeWidget->setCurrentIndex(0);
}

void MainWindow::on_backMenuIrr_9_clicked()
{
    ui->employeWidget->setCurrentIndex(2);
}

void MainWindow::on_backMenuIrr_7_clicked()
{
    ui->employeWidget->setCurrentIndex(0);
}
void MainWindow::on_addIrrBtn_clicked()
{
    int ref=ui->lineEdit_33->text().toInt(),quant=ui->lineEdit_36->text().toInt();
    QString nom=ui->lineEdit_34->text();
    QString type=ui->typeCMBX_2->currentText();
    QString etat=ui->lineEdit_35->text();
    QString emp=ui->lineEdit_37->text();
    QString humidite=ui->lineEdit_38->text();
    Irrigation i(0,ref,quant,nom,type,etat,emp,humidite);
    if(i.addIrrigation()){
            statQuantity();
            ui->irrigationTableView->setModel(irg.showIrrigation());
            ui->irrigationStackWidget->setCurrentIndex(2);
            if(quant>1000)
              sendMail(QString::number(ref),nom);
    }else{
        QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                              QObject::tr("Echec de l'opération. \n"
                                          "Click me to exit."), QMessageBox::Cancel);
    }
}
void MainWindow::browse()
{
    files.clear();
   QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->mailAttachementLineEdit->setText( fileListString );

}
void MainWindow::sendMail(QString ref,QString nom)
{
    Smtp* smtp = new Smtp("nawres.bensethom@esprit.tn","11451428", "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailsent(QString)));
        smtp->sendMail("nawres.bensethom@esprit.tn", "zied.mahjoub@esprit.tn" , "ALERTE DE COLLECTE","Plante prete à collecter REF : '"+ref+"', Nom : '"+nom+"' ");
}
void   MainWindow::mailsent(QString status)
{

    if(status == "Message sent")
    {
        QMessageBox::information(nullptr,QObject::tr("MAIL Sent!"),
                              QObject::tr("Done ! \n"
                                          "Click me to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_irrigationTableView_clicked(const QModelIndex &index)
{
    int row = index.row();
    QModelIndex sibling = index.sibling(row,0);
    QString id = ui->irrigationTableView->model()->data(sibling).toString();
        QSqlQuery qry;
        qry.prepare("SELECT * FROM irrigations WHERE id=:id" );
        qry.bindValue(":id",id);
        if(qry.exec())
        {
            while(qry.next())
            {
                ui->idIrrUpdate->setText(qry.value(0).toString());
                ui->lineEdit_40->setText(qry.value(1).toString());
                ui->lineEdit_39->setText(qry.value(2).toString());
                ui->typeCMBX->setCurrentText(qry.value(3).toString());
                ui->lineEdit_42->setText(qry.value(4).toString());
                ui->lineEdit_41->setText(qry.value(5).toString());
                ui->lineEdit_43->setText(qry.value(6).toString());
            }
        }
}

void MainWindow::on_updateIrrBtn_clicked()
{
    int ref=ui->lineEdit_39->text().toInt(),quant=ui->lineEdit_41->text().toInt(),id=ui->idIrrUpdate->text().toInt();
    QString nom=ui->lineEdit_40->text();
    QString type=ui->typeCMBX->currentText();
    QString etat=ui->lineEdit_42->text();
    QString emp=ui->lineEdit_43->text();

    Irrigation i(id,ref,quant,nom,type,etat,emp,"humidite");
    if(i.updateIrrigation()){
            ui->irrigationTableView->setModel(irg.showIrrigation());
            ui->irrigationStackWidget->setCurrentIndex(2);
            statQuantity();
    }else{
        QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                              QObject::tr("Echec de l'opération. \n"
                                          "Click me to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pdfBtn_3_clicked()
{
    QString strStream;
       QTextStream out(&strStream);
       QDate currentDate = QDate::currentDate();
       QString date = currentDate.toString("dd-MM-yyyy");


       const int rowCount = ui->irrigationTableView->model()->rowCount();
       const int columnCount = ui->irrigationTableView->model()->columnCount();

       out <<  "<html>\n"
           "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
           <<  QString("<title>%1</title>\n").arg("col1")
           <<  "</head>\n"
           "<body bgcolor=#ffffff link=#5000A0>\n"
           "<h3 style='position: absolute; top: 0; right: 0; margin: 0; padding: 10px; text-align: right; font-size: 24px; color: #333;'> Tunis "+date+"</h3>"
           "<h1 style='text-align: center;'>Liste des employes</h1>\n"
           "<br>\n"
           "<br>\n"
               "<div align='center'>"
           "<table border=1 cellspacing=0 cellpadding=2>\n";

       // headers
       out << "<thead><tr bgcolor=#f0f0f0>";
       for (int column = 0; column < columnCount; column++)
           if (!ui->irrigationTableView->isColumnHidden(column))
               out << QString("<th>%1</th>").arg(ui->irrigationTableView->model()->headerData(column, Qt::Horizontal).toString());
       out << "</tr></thead>\n";

       // data table
       for (int row = 0; row < rowCount; row++) {
           out << "<tr>";
           for (int column = 0; column < columnCount; column++) {
               if (!ui->irrigationTableView->isColumnHidden(column)) {
                   QString data = ui->irrigationTableView->model()->data(ui->irrigationTableView->model()->index(row, column)).toString().simplified();
                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
               }
           }
           out << "</tr>\n";
       }
       out <<  "</table>\n"
               "</div>"
           "</body>\n"
           "</html>\n";

       QTextDocument *document = new QTextDocument();
       document->setHtml(strStream);

       QPrinter printer;

           document->print(&printer);


       delete document;
}

void MainWindow::on_deleteIrrBtn_3_clicked()
{
    QModelIndex indexItem = ui->irrigationTableView->currentIndex();
    int row = indexItem.row();
    QModelIndex sibling = indexItem.sibling(row,0);
    int id = ui->irrigationTableView->model()->data(sibling).toInt();
    if(irg.deleteIrrigation(id))
    {
        statQuantity();
         ui->irrigationTableView->setModel(irg.showIrrigation());

    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                              QObject::tr("Echec d'opération. \n"
                                          "Click me to exit."), QMessageBox::Cancel);
    }
}


void MainWindow::on_rechercheBar_4_textChanged(const QString &arg1)
{
    if(arg1 != "")
    ui->irrigationTableView->setModel(irg.searchIrrigation(arg1));
    else
        ui->irrigationTableView->setModel(irg.showIrrigation());
}

void MainWindow::on_triIrrigationComboBox_activated(const QString &arg1)
{
    ui->irrigationTableView->setModel(irg.triIrrigation(arg1));
}
void MainWindow::statQuantity(){
    QLayout* layoutTest = ui->irrigationPieContainer->layout();  // Get the existing layout object

    if (layoutTest) {
        delete layoutTest;  // Delete the existing layout object
    }
    QChart *chart = new QChart();
    chart->setTitle("% TYPE");
    chart->setTheme(QChart::ChartThemeDark);
    chart->setAnimationOptions(QChart::AllAnimations);
    QVector<int> stat = irg.statQuantity();
    QPieSeries * seriesQuantity = new QPieSeries();
    for(unsigned int i=0;i < stat.size(); i++){
        QString type;
        if(i==0)
           type="Arbre";
        else if(i==1)
           type="Arbuste";
        else
            type="Fleure";
       seriesQuantity->append(type, stat[i]);
    }
    chart->addSeries(seriesQuantity);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    ui->irrigationPieContainer->setLayout(layout);
}

void MainWindow::on_sendChatBtn_clicked()
{
    QString text,space="";
    float rassemblance=0;
    int tr=0;
    QString msg=ui->inputChatbot->text();
    ui->chatBot->appendPlainText(space);
    ui->chatBot->appendPlainText(msg);
    QSqlQuery qry,query;
     if(msg[0]!="#")
     {
        qry.prepare("select * from chatbot" );
        qry.exec();
        while(qry.next() && tr==0)
        {
            QString quest = qry.value(0).toString();
                int eq = 0,dif = 0;
                for(int i=0 ; i < msg.size(); i++)
                {
                       if(quest[i] == msg[i])
                           eq++;
                       else
                           dif++;
                }
                rassemblance = (eq / static_cast<float>(msg.size()))*100;
                if(rassemblance > 80)
                {
                    ui->chatBot->appendPlainText( "\n"+qry.value(1).toString());
                    tr=1;
                }
         }
        if(tr == 0)
        {

                ui->chatBot->appendPlainText( "Voulez vous ajouter un nouveau mot ? Écrivez votre réponse avec un # au début.");
                ui->labelCache->setText(msg);

        }
     }
     else if (msg[0]=="#"){
         QString msg1=msg.mid(1,msg.length()-1);
         query.prepare("insert into chatbot (quest,rep)""values(:quest,:rep)");
         query.bindValue(":quest", ui->labelCache->text());
         query.bindValue(":rep", msg1);
         query.exec();
         ui->chatBot->appendPlainText( "\n Merci ! Pour cette information");

     }
}

void MainWindow::on_ajouterPlantePageBtn_clicked()
{
    ui->irrigationStackWidget->setCurrentIndex(1);
}

void MainWindow::on_employesBtnPage_7_clicked()
{
    ui->irrigationStackWidget->setCurrentIndex(2);
}

void MainWindow::on_employesBtnPage_8_clicked()
{
    ui->irrigationStackWidget->setCurrentIndex(4);
}

void MainWindow::on_employesBtnPage_9_clicked()
{
    ui->irrigationStackWidget->setCurrentIndex(5);
}

void MainWindow::on_backMenuIrr_6_clicked()
{
    ui->mainStackWidget->setCurrentIndex(0);
}

void MainWindow::on_backMenuIrr_14_clicked()
{
   ui->irrigationStackWidget->setCurrentIndex(0);
}

void MainWindow::on_backMenuIrr_15_clicked()
{
    ui->irrigationStackWidget->setCurrentIndex(0);
}

void MainWindow::on_backMenuIrr_16_clicked()
{
    ui->irrigationStackWidget->setCurrentIndex(0);
}

void MainWindow::on_backMenuIrr_17_clicked()
{
    ui->irrigationStackWidget->setCurrentIndex(0);
    statQuantity();
}

void MainWindow::on_backMenuIrr_18_clicked()
{
    ui->irrigationStackWidget->setCurrentIndex(0);
}

void MainWindow::on_modifierIrrBtnPage_3_clicked()
{
    ui->irrigationStackWidget->setCurrentIndex(3);
}



void MainWindow::on_addFacBtn_7_clicked()
{
    int identifiant= ui->lineEdit_64->text().toInt();
    QString caracteristiques= ui->lineEdit_65->text();
    int poids= ui->lineEdit_66->text().toInt();
    int age= ui->lineEdit_67->text().toInt();
     QString sexe= ui->lineEdit_68->text();
      QString reproduction= ui->lineEdit_74->text();
       QString race= ui->lineEdit_75->text();
        QString vaccination= ui->lineEdit_76->text();
         QString sante= ui->lineEdit_77->text();

    Animal a (identifiant,caracteristiques, poids, age,sexe,reproduction,race,vaccination,sante);
    bool test = a.ajouter();
    if (test)
    {
        ui->factureTableView_4->setModel(a.afficher());

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

void MainWindow::on_deleteIrrBtn_6_clicked()

{
    QModelIndex indexItem = ui->factureTableView_4->currentIndex();
    int row = indexItem.row();
    QModelIndex sibling = indexItem.sibling(row,0);
    int id = ui->factureTableView_4->model()->data(sibling).toInt();
    if(a.supprimer(id))
    {
         ui->factureTableView_4->setModel(a.afficher());

    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                              QObject::tr("Echec d'opération. \n"
                                          "Click me to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_addFacBtn_8_clicked()

{


    bool  test;
    int identifiant= ui->lineEdit_73->text().toInt();
    QString reproduction = ui->lineEdit_69->text();
    int poids = ui->lineEdit_71->text().toInt();
    QString vaccination = ui->lineEdit_72->text();
    QString sante = ui->lineEdit_70->text();
     test =  a.modifier (identifiant , reproduction , poids , vaccination , sante);

          if (test)
          {
              ui->factureTableView_4->setModel(a.afficher());

              QMessageBox::information(nullptr,QObject::tr("OK"),
                                   QObject::tr("modification établie"),
                                   QMessageBox::Ok);}
          else{
          QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                  QObject::tr("modification non établie"),
                                  QMessageBox::Cancel);}
}

void MainWindow::on_rechercheBar_7_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
                   QSqlQuery   *query= new QSqlQuery();
           if(ui->rechercheBar_7->text()==arg1)
                   {
               query->prepare("SELECT * FROM ANIMAux WHERE IDENTIFIANT LIKE'"+arg1+"%'");//
       query->exec();
           model->setQuery(*query);
      ui->factureTableView_4->setModel(model);
}
}
void MainWindow::on_triFacturesComboBox_4_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "par défaut")
    {
       ui->factureTableView_4->setModel(a.triAnimal(arg1));
    }
    else if(arg1 == "identifiant")
    {
        ui->factureTableView_4->setModel(a.triAnimal(arg1));
    }
    else if(arg1 == "poids")
    {
        ui->factureTableView_4->setModel(a.triAnimal(arg1));
    }
    else if(arg1 == "age")
    {
        ui->factureTableView_4->setModel(a.triAnimal(arg1));
    }
    else
    {
        ui->factureTableView_4->setModel(a.triAnimal(arg1));
    }
}



void MainWindow::on_exportBTN_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                                  tr("Excel Files (*.xls)"));
                  if (fileName.isEmpty())
                      return;

                  ExportExcel obj(fileName, "Taches", ui->factureTableView_4);

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















void MainWindow::on_modifierIrrBtnPage_6_clicked()
{
    ui->factureStackWidget_4->setCurrentIndex(3);
}
