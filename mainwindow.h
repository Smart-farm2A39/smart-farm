#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMessageBox>
#include <QMainWindow>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QPrinter>
#include <QPainter>
#include <QDate>
#include <QTextStream>
#include <QTextDocument>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QHBoxLayout>
#include <QtCharts/QLegend>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include "facture.h"
#include "qrcode.h"
#include "notification.h"
#include "arduino.h"
#include "culture.h"
#include "employee.h"
#include "irrigation.h"
#include "smtp.h"
#include"animal.h"
#include "exportexcel.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void statPieFactures();
    void statQuantity();
void closeEvent(QCloseEvent *event);

private slots:
    void on_facturesBtnPage_clicked();

    void on_ajouterFacturePageBtn_clicked();

    void on_employesBtnPage_4_clicked();

    void on_factureTableView_clicked(const QModelIndex &index);

    void on_modifierIrrBtnPage_clicked();

    void on_addFacBtn_clicked();

    void on_addFacBtn_2_clicked();

    void on_deleteIrrBtn_clicked();

    void on_backMenuIrr_4_clicked();

    void on_backMenuIrr_2_clicked();

    void on_backMenuIrr_3_clicked();

    void on_backMenuIrr_clicked();

    void on_rechercheBar_textChanged(const QString &arg1);

    void on_triFacturesComboBox_currentIndexChanged(const QString &arg1);

    void on_pdfBtn_clicked();

    void on_statBtnPage_clicked();

    void on_backMenuIrr_5_clicked();

    void on_ajouterCulturesPageBtn_3_clicked();

    void on_employesBtnPage_6_clicked();

    void on_modifierCultBtnPage_2_clicked();

    void on_cultureTableView_2_clicked(const QModelIndex &index);

    void on_addCultBtn_3_clicked();

    void on_deleteICultBtn_2_clicked();

    void on_imprimerBtn_2_clicked();

    void on_addCultBtn_4_clicked();

    void on_backMenuIrr_10_clicked();

    void on_backMenuIrr_11_clicked();

    void on_backMenuIrr_12_clicked();

    void on_backMenuIrr_13_clicked();

    void on_rechercheBar_3_textChanged(const QString &arg1);

    void on_TriBtn_2_currentIndexChanged(const QString &arg1);

    void on_culturesBtnPage_clicked();

    void on_pushButton_conn_2_clicked();

    void on_employesBtnPage_clicked();

    void on_backMenulrr_4_clicked();

    void on_ajouterEmployePageBtn_clicked();

    void on_addEmplBtn_clicked();

    void on_pdfBtn_2_clicked();

    void on_employeeTableView_2_clicked(const QModelIndex &index);

    void on_modifierIrrBtnPage_2_clicked();

    void on_modifierBtn_clicked();

    void on_deleteIrrBtn_2_clicked();

    void on_triEmplyeComboBox_currentIndexChanged(const QString &arg1);

    void on_rechercheBar_2_textChanged(const QString &arg1);

    void on_employesBtnPage_5_clicked();

    void on_backMenuIrr_8_clicked();

    void on_backMenuIrr_9_clicked();

    void on_backMenuIrr_7_clicked();

    void on_irrigationBtnPage_clicked();

    void on_addIrrBtn_clicked();
    void browse();
    void sendMail(QString ref,QString nom);
    void mailsent(QString status);

    void on_irrigationTableView_clicked(const QModelIndex &index);

    void on_updateIrrBtn_clicked();

    void on_pdfBtn_3_clicked();

    void on_deleteIrrBtn_3_clicked();


    void on_rechercheBar_4_textChanged(const QString &arg1);

    void on_triIrrigationComboBox_activated(const QString &arg1);

    void on_sendChatBtn_clicked();

    void on_ajouterPlantePageBtn_clicked();

    void on_employesBtnPage_7_clicked();

    void on_employesBtnPage_8_clicked();

    void on_employesBtnPage_9_clicked();

    void on_backMenuIrr_6_clicked();

    void on_backMenuIrr_14_clicked();

    void on_backMenuIrr_15_clicked();

    void on_backMenuIrr_16_clicked();

    void on_backMenuIrr_17_clicked();

    void on_backMenuIrr_18_clicked();

    void on_modifierIrrBtnPage_3_clicked();

    void on_addFacBtn_7_clicked();
    void on_deleteIrrBtn_6_clicked() ;

    void on_rechercheBar_7_textChanged(const QString &arg1);
    void on_triFacturesComboBox_4_currentIndexChanged(const QString &arg1);
    void on_exportBTN_clicked();
    void on_animauxBtnPage_clicked();

    void on_ajouterFacturePageBtn_4_clicked();





    void on_employesBtnPage_12_clicked();

    void on_backMenuIrr_29_clicked();

    void on_backMenuIrr_30_clicked();

    void on_backMenuIrr_32_clicked();

    void on_backMenuIrr_31_clicked();

    void on_addFacBtn_8_clicked();

    void on_modifierIrrBtnPage_6_clicked();

private:
    Ui::MainWindow *ui;
    Facture f;
    notification notif;
    QByteArray data; // variable contenant les données reçues
    Arduino A;
    culture c;
    QString ref;
    Employee e;
    Irrigation irg;
    QStringList files;
    Animal a;
    QFile sourceFile;
     QStringList filess;
};
#endif // MAINWINDOW_H
