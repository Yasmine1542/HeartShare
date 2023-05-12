#include "aliment.h"
#include <QtSql/QSqlQuery>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QObject>
#include <QString>

aliment::aliment(){};
aliment::aliment(int id,int quant,QDate dateEXP,QDate dateREC,QString Lieurec,QString ref,QString nom)
{
ID_ALIMENT=id;
QUANTITE=quant;
DATE_EXP=dateEXP;
DATE_REC=dateREC;
NOM=nom;
LIEU_REC=Lieurec;
REF=ref;

}



bool aliment::ajouter()
{
    QSqlQuery checkQuery;
       checkQuery.prepare("SELECT ID_ALIMENT FROM GESTION_STOCK WHERE ID_ALIMENT = :ID");
       checkQuery.bindValue(":ID", ID_ALIMENT);
       if (checkQuery.exec() && checkQuery.next()) {
           // ID already exists
           return false;
       }


qDebug() << NOM;

    QSqlQuery query;
    QString res = QString::number(ID_ALIMENT);
    query.prepare("INSERT INTO GESTION_STOCK (ID_ALIMENT, QUANTITE, DATE_EXP, DATE_REC, LIEU_REC, REF, NOM) "
                        "VALUES (:ID_ALIMENT, :QUANTITE, :DATE_EXP, :DATE_REC, :LIEU_REC, :REF,:NOM)");
    query.bindValue(":ID_ALIMENT", res);
    query.bindValue(":QUANTITE", QUANTITE);
    query.bindValue(":DATE_EXP", DATE_EXP);
    query.bindValue(":DATE_REC", DATE_REC);
    query.bindValue(":LIEU_REC", LIEU_REC);
    query.bindValue(":REF", REF);

    query.bindValue(":NOM", NOM);
 qDebug() << NOM;
    if (!query.exec()) {
        qDebug() << query.lastError().text();
        return false;
    }
 qDebug() << NOM;
    return true;

}
QSqlQueryModel* aliment::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM GESTION_STOCK");

    // Set header data

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_ALIMENT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE_EXP"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_REC"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("LIEU_REC"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("REF"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("NOM"));


    return model;
}
bool aliment::supprimer(int id_aliment)
{
    QSqlQuery query;
    query.prepare("DELETE FROM GESTION_STOCK WHERE ID_ALIMENT = :id");
    query.bindValue(":id", id_aliment);
    bool success = query.exec();
    if (!success) {
        qDebug() << "Error executing query:" << query.lastError().text();
    }
    return success;
}
bool aliment::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE GESTION_STOCK SET QUANTITE=:QUANTITE, DATE_EXP=:DATE_EXP, DATE_REC=:DATE_REC, LIEU_REC=:LIEU_REC, REF=:REF, NOM=:NOM WHERE ID_ALIMENT=:ID_ALIMENT");
    query.bindValue(":ID_ALIMENT", ID_ALIMENT);
    query.bindValue(":QUANTITE", QUANTITE);
    query.bindValue(":DATE_EXP", DATE_EXP);
    query.bindValue(":DATE_REC", DATE_REC);
    query.bindValue(":LIEU_REC", LIEU_REC);
    query.bindValue(":REF", REF);
    query.bindValue(":NOM", NOM);

    if(!query.exec())
    {  qDebug()<<"falsefalsefjeuduzp"<<query.exec();
        qDebug() << "Error modifying record:" << query.lastError().text();
        return false;

    }
    else
    {qDebug()<<"true labes truessssss"<<query.exec();
      return true;
    }
}

QSqlQueryModel* aliment::sortDataByQUANTITE()
{

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM GESTION_STOCK ORDER BY QUANTITE ASC;");

    // Set header data

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_ALIMENT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE_EXP"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_REC"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("LIEU_REC"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("REF"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("NOM"));


    return model;
}
QSqlQueryModel* aliment::sortDataByDateexp()
{

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM GESTION_STOCK ORDER BY DATE_EXP ASC;");

    // Set header data

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_ALIMENT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE_EXP"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_REC"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("LIEU_REC"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("REF"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("NOM"));


    return model;
}
QSqlQueryModel* aliment::sortDataByName()
{

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM GESTION_STOCK ORDER BY NOM ASC;");

    // Set header data

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_ALIMENT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE_EXP"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_REC"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("LIEU_REC"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("REF"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("NOM"));


    return model;
}
QSqlQueryModel* aliment::searchByNOM(QString NOM)
{

    QSqlQueryModel* model = new QSqlQueryModel();
    QString sql = "SELECT * FROM GESTION_STOCK WHERE NOM LIKE '%" + NOM + "%';";
    model->setQuery(sql);

    // Set header data

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_ALIMENT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE_EXP"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_REC"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("LIEU_REC"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("REF"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("NOM"));

    return model;
}
