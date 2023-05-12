#include "benevole.h"
#include <QSqlQuery>

Benevole::Benevole()
{
id=0;
}
Benevole::Benevole(int id,QString nom,QString mail,QDate datenaiss,int numtel,QString adresse,QString dispo,QString vehicle,/*date inscription*/int mission)
{
    this->id=id;
    this->nom=nom;
    this->mail=mail;
    this->datenaiss=datenaiss;
    this->numtel=numtel;
    this->adresse=adresse;
    this->dispo=dispo;
    this->vehicle=vehicle;
    //date inscription
    this->mission=mission;
}

bool Benevole::ajouter()
{

    QSqlQuery query;
    QString res =QString::number(id);
    QString num =QString::number(numtel);
    QString miss =QString::number(mission);

query.prepare("INSERT INTO BENEVOLE (id, nom, mail, datenaiss, numtel, adresse, dispo, vehicle, mission)" "VALUES(:id, :nom, :mail, :datenaiss , :numtel, :adresse, :dispo, :vehicle, :mission)");
query.bindValue(":id",res);
query.bindValue(":nom",nom);
query.bindValue(":mail",mail);
query.bindValue(":datenaiss",datenaiss);
query.bindValue(":numtel",num);
query.bindValue(":adresse",adresse);
query.bindValue(":dispo",dispo);
query.bindValue(":vehicle",vehicle);
query.bindValue(":mission",miss);

return query.exec();

}

QSqlQueryModel* Benevole::afficher()
{
   QSqlQueryModel * model=new QSqlQueryModel();
   model->setQuery("select * from benevole");
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("Email"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("Date de bénévolat"));
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("Num de telephone"));
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("Adresse"));
   model->setHeaderData(6,Qt::Horizontal,QObject::tr("Disponibilité"));
   model->setHeaderData(7,Qt::Horizontal,QObject::tr("Véhicule"));
   model->setHeaderData(8,Qt::Horizontal,QObject::tr("Date d'inscription"));
   model->setHeaderData(9,Qt::Horizontal,QObject::tr("Mission"));


   return model;
}

bool Benevole::supprimer(int id)
{
    QSqlQuery query;
    QString res =QString::number(id);
    query.prepare("delete from benevole where id= :id");
    query.bindValue(":id",res);
    return query.exec();
}

bool Benevole::modifier(int id)
{
    QSqlQuery query;
QString id_string=QString::number(id);

query.prepare("update  benevole set nom =:nom, mail =:mail ,datenaiss=:datenaiss,numtel=:numtel,adresse=:adresse,dispo=:dispo,vehicle=:vehicle,mission=:mission where id=:id");

    query.bindValue(":id",id_string);
    query.bindValue(":nom",nom);
    query.bindValue(":mail",mail);
    query.bindValue(":datenaiss",datenaiss);
    query.bindValue(":numtel",numtel);
    query.bindValue(":adresse",adresse);
    query.bindValue(":dispo",dispo);
    query.bindValue(":vehicle",vehicle);
    query.bindValue(":mission",mission);
    return query.exec();

}

QSqlQueryModel * Benevole::chercherBenevole(QString x){

    QSqlQuery query;
    query.prepare("SELECT *FROM Benevole where nom = :x");
    query.bindValue(":x",x);
    query.exec();
    QSqlQueryModel * model=new QSqlQueryModel();


          model->setQuery(query);
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
          model->setHeaderData(2,Qt::Horizontal,QObject::tr("Email"));
          model->setHeaderData(3,Qt::Horizontal,QObject::tr("Date de bénévolat"));
          model->setHeaderData(4,Qt::Horizontal,QObject::tr("Num de telephone"));
          model->setHeaderData(5,Qt::Horizontal,QObject::tr("Adresse"));
          model->setHeaderData(6,Qt::Horizontal,QObject::tr("Disponibilité"));
          model->setHeaderData(7,Qt::Horizontal,QObject::tr("Véhicule"));
          model->setHeaderData(8,Qt::Horizontal,QObject::tr("Date d'inscription"));
          model->setHeaderData(9,Qt::Horizontal,QObject::tr("Mission"));

    return model;

}


QSqlQueryModel * Benevole::tri_adresse()
{
    QSqlQueryModel * model=new QSqlQueryModel();


          model->setQuery("SELECT * FROM BENEVOLE ORDER BY adresse");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
          model->setHeaderData(2,Qt::Horizontal,QObject::tr("Email"));
          model->setHeaderData(3,Qt::Horizontal,QObject::tr("Date de bénévolat"));
          model->setHeaderData(4,Qt::Horizontal,QObject::tr("Num de telephone"));
          model->setHeaderData(5,Qt::Horizontal,QObject::tr("Adresse"));
          model->setHeaderData(6,Qt::Horizontal,QObject::tr("Disponibilité"));
          model->setHeaderData(7,Qt::Horizontal,QObject::tr("Véhicule"));
          model->setHeaderData(8,Qt::Horizontal,QObject::tr("Date d'inscription"));
          model->setHeaderData(9,Qt::Horizontal,QObject::tr("Mission"));


    return model;
}


QSqlQueryModel * Benevole::tri_dispo()
{
    QSqlQueryModel * model=new QSqlQueryModel();


          model->setQuery("SELECT * FROM BENEVOLE ORDER BY dispo");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
          model->setHeaderData(2,Qt::Horizontal,QObject::tr("Email"));
          model->setHeaderData(3,Qt::Horizontal,QObject::tr("Date de bénévolat"));
          model->setHeaderData(4,Qt::Horizontal,QObject::tr("Num de telephone"));
          model->setHeaderData(5,Qt::Horizontal,QObject::tr("Adresse"));
          model->setHeaderData(6,Qt::Horizontal,QObject::tr("Disponibilité"));
          model->setHeaderData(7,Qt::Horizontal,QObject::tr("Véhicule"));
          model->setHeaderData(8,Qt::Horizontal,QObject::tr("Date d'inscription"));
          model->setHeaderData(9,Qt::Horizontal,QObject::tr("Mission"));


    return model;
}


QSqlQueryModel * Benevole::tri_mission()
{
    QSqlQueryModel * model=new QSqlQueryModel();


          model->setQuery("SELECT * FROM BENEVOLE ORDER BY mission");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
          model->setHeaderData(2,Qt::Horizontal,QObject::tr("Email"));
          model->setHeaderData(3,Qt::Horizontal,QObject::tr("Date de bénévolat"));
          model->setHeaderData(4,Qt::Horizontal,QObject::tr("Num de telephone"));
          model->setHeaderData(5,Qt::Horizontal,QObject::tr("Adresse"));
          model->setHeaderData(6,Qt::Horizontal,QObject::tr("Disponibilité"));
          model->setHeaderData(7,Qt::Horizontal,QObject::tr("Véhicule"));
          model->setHeaderData(8,Qt::Horizontal,QObject::tr("Date d'inscription"));
          model->setHeaderData(9,Qt::Horizontal,QObject::tr("Mission"));




    return model;

}
