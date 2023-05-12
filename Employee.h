#ifndef Employee_H
#define Employee_H
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QObject>
#include <QSqlQueryModel>
class Employee
{
public:
    Employee();
    Employee(int,QString,QString,QString,QString,int,QString,QString,QString,QString);
    int getid();
    QString getnom();
    QString getfonction();
    QString getemail();
    QString getstatut();
    int getnum_tel();
    QString getadresse();
    QString getmdp();
    QString getdroit_access();
    QString getRFID();

    void setid(int);
    void setnom(QString);
    void setfonction(QString);
    void setemail (QString);
    void setstatut (QString);
    void setnum_tel (int);
    void setadresse (QString);
    void setmdp (QString);
    void setdroit_access (QString);
    void setRFID(QString);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * trie_id();
    QSqlQueryModel * trie_nom();
    QSqlQueryModel * trie_fonction();
private:
    int id,num_tel ;
    QString nom,fonction,email,statut,adresse,mdp,droit_access,RFID;

};


#endif // Employee_H
