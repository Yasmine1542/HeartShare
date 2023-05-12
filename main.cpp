// main.cpp
#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setApplicationDisplayName("HeartShare");
    QApplication::setApplicationName("HeartShare");
        QApplication::setWindowIcon(QIcon("C:/integration_finale/logo-heartShare.png"));
        QApplication::setApplicationVersion("1.0.4");


    Connection c;
    bool test = c.createconnect();
    MainWindow w;

    if (test) {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                                 QObject::tr("Connection successful.\nClick Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                               QObject::tr("Connection failed.\nClick Cancel to exit."), QMessageBox::Cancel);
        return 1;
    }

    return a.exec();
}
