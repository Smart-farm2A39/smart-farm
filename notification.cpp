#include "notification.h"
#include <QSystemTrayIcon>
#include<QString>

notification::notification()
{

}

void notification::notifAddFacture()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon(":/l/icon/logo.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des factures","Nouveau facture est ajoutée ",QSystemTrayIcon::Information,15000);
}

void notification::notifDeleteFacture(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon(":/l/icon/logo.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des factures","Nouveau facture est supprimée",QSystemTrayIcon::Information,15000);
}


void notification::notifUpdateFacture(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon(":/l/icon/logo.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des factures","Nouveau facture est modifiée",QSystemTrayIcon::Information,15000);
}


void notification::notif_failed(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon(":/l/icon/logo.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des factures","Action Failed",QSystemTrayIcon::Critical,15000);
}
