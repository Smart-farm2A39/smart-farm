#ifndef NOTIFICATION_H
#define NOTIFICATION_H


#include <QSystemTrayIcon>
#include<QString>

class notification
{
public:
    notification();
    void notifAddFacture();
    void notifDeleteFacture();
    void notifUpdateFacture();
    void notif_failed();


};
#endif // NOTIFICATION_H
