#ifndef ALIMENT_H
#define ALIMENT_H
#include <QString>
#include <QSqlQueryModel>
#include <QtCore/QDate>
class aliment
{
QString LIEU_REC,REF,NOM;
QDate DATE_EXP,DATE_REC;
int ID_ALIMENT,QUANTITE;

public:
aliment();
aliment(int ,int,QDate,QDate,QString,QString,QString);

QString getLieuREC(){return LIEU_REC;}
QString getREF(){return REF;}

QDate getDateREC(){return DATE_REC;}
QString getRef(){return REF;}

QDate getDateEXP(){return DATE_EXP;}
int getId(){return ID_ALIMENT;}
int getQuantite(){return QUANTITE;}

void setLieuREC(QString Lieu){LIEU_REC=Lieu;}
void setREF(QString Ref){REF=Ref;}

void setDateREC(QDate Date){DATE_REC=Date;}
void setRef(QString rep){REF=rep;}

void setDateEXP(QDate Date){DATE_EXP=Date;}
void setId(int id){ID_ALIMENT=id;}
void setQuantite(int quant){QUANTITE=quant;}

QString getNom(){return NOM;}

void setNom(QString Nom){NOM=Nom;}
bool ajouter();
QSqlQueryModel*  afficher();
bool supprimer(int);
bool modifier();
QSqlQueryModel* searchByNOM(QString NOM);
QSqlQueryModel* sortDataByQUANTITE();
QSqlQueryModel*sortDataByName();
QSqlQueryModel* sortDataByDateexp();
};

#endif // ALIMENT_H
