#ifndef BENEVOLE_H
#define BENEVOLE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class Benevole
{
private:
    int id,numtel,mission;
    QString nom,mail,adresse,dispo,vehicle;
    QDate datenaiss,dateinsc;

public:
    Benevole();
    Benevole(int,QString,QString,QDate,int,QString,QString,QString,/*date inscription*/int);

    int getid();
    QString getnom();
    QString getmail();
    QDate getdatenaiss();
    int getnumtel();
    QString getadresse();
    QString getdispo();
    QString getvehicle();
    //sysdate inscription
    int getmission();

    void setid(int);
    void setnom(QString);
    void setmail(QString);
    void setdatenaiss(QDate);
    void setnumtel(int);
    void setadresse(QString);
    void setdispo(QString);
    void setvehicle(QString);
    //date inscription
    void setmission(int);

bool ajouter();
QSqlQueryModel* afficher();
bool supprimer(int);
bool modifier(int id);
QSqlQueryModel * chercherBenevole(QString x);
QSqlQueryModel * tri_adresse();
QSqlQueryModel * tri_dispo();
QSqlQueryModel * tri_mission();

};

#endif // BENEVOLE_H
