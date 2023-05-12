#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include "aliment.h"
#include <QSystemTrayIcon>
#include <QString>
class notification
{
public:
    notification(){};

void notification_nouv();
void notification_outofstock();


private:
    int num;
};

#endif // NOTIFICATION_H
