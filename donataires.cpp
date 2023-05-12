#include "donataires.h"
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QMessageBox>
#include <QDate>


Donataire::Donataire()
{
     id_donataire = 0;
     nom = " " ;
     type_de_don = " " ;
     adresse = " " ;
     num_tel= " " ;
     besoin = " " ;
     type_donataire = " " ;
     date_de_don.currentDate();
     quantite_de_don = 0  ;

}
Donataire::Donataire(int id_donataire ,QString type_de_don ,QString num_tel ,int quantite_de_don,QString nom , QString besoin ,QString adresse, QDate date_de_don  , QString type_donataire)
{
    this->id_donataire = id_donataire ;
     this->type_de_don = type_de_don ;
     this->num_tel = num_tel ;
     this->quantite_de_don = quantite_de_don ;
    this->nom = nom ;
    this->besoin = besoin ;
    this->adresse = adresse ;
     this->date_de_don = date_de_don ;
    this->type_donataire = type_donataire ;



}
int Donataire::getId()
{return id_donataire; }
void Donataire::setId(int id_donataire )
{ this->id_donataire = id_donataire ;}


QString Donataire::getNom()
{return nom ; }
void Donataire::setNom(QString nom)
{this->nom = nom ;}


QString  Donataire::gettype_de_don()
{return type_de_don ; }
void  Donataire::settype_de_don(QString type_de_don)
{this->type_de_don = type_de_don ;}


QString  Donataire::getAdresse()
{return adresse ; }
void  Donataire::setAdresse(QString adresse )
{this->adresse = adresse ; }


QString Donataire::getNum()
{return num_tel; }
void Donataire::setNum (QString num_tel)
{ this->num_tel = num_tel ;}


QString  Donataire::getMail()
{return besoin ; }
void  Donataire::setMail(QString besoin)
{ this->besoin = besoin ;}
//getter w setter lel besoin

QString  Donataire::getTypeD()
{return type_donataire ;}
void  Donataire::setTypeD(QString type_donataire)
{ this->type_donataire = type_donataire ;}


QDate  Donataire::getnbDons()
{return date_de_don ; }
void  Donataire::setNbDons (QDate date_de_don)
{ this->date_de_don = date_de_don ;}
//getter w setter lel date de don

int  Donataire::getquantite_de_don()
{return quantite_de_don  ;}
void  Donataire::setquantite_de_don(int quantite_de_don)
{this->quantite_de_don = quantite_de_don ;}





bool Donataire::ajouter()
{
 QSqlQuery query;
 QString id_string=QString::number(id_donataire);
 QString quantite_string=QString::number(quantite_de_don);

       query.prepare("INSERT INTO DONATAIRES (id_donataire,type_de_don,num_tel,quantite_de_don,nom,besoin,adresse,date_de_don,type_donataire) "
                     "VALUES (:id_donataire, :type_de_don, :num_tel, :quantite_de_don, :nom, :besoin, :adresse, :date_de_don, :type_donataire)");
       query.bindValue(":id_donataire", id_string);
       query.bindValue(":type_de_don", type_de_don);
       query.bindValue(":num_tel", num_tel);
       query.bindValue(":quantite_de_don",quantite_string);
       query.bindValue(":nom", nom);
       query.bindValue(":besoin", besoin);
       query.bindValue(":adresse", adresse);
       query.bindValue(":date_de_don", date_de_don);
       query.bindValue(":type_donataire",type_donataire);

       return query.exec();



}
bool Donataire::supprimer(int id_donataire)
{
    QSqlQuery query;
    QString id_string=QString::number(id_donataire);

          query.prepare(" Delete from DONATAIRES where id_donataire=:id_donataire");
          query.bindValue(0, id_string);



    return query.exec();
}

bool Donataire::modifier(int id_donataire ,QString type_de_don ,QString num_tel ,int quantite_de_don,QString nom , QString besoin ,QString adresse, QDate date_de_don  , QString type_donataire)
{
    QSqlQuery query;
    QString id_string=QString::number(id_donataire);
    QString quantite_string=QString::number(quantite_de_don);

          query.prepare("update DONATAIRES set id_donataire=:id_donataire,type_de_don=:type_de_don,num_tel=:num_tel,quantite_de_don=:quantite_de_don,nom=:nom,besoin=:besoin,adresse=:adresse,date_de_don=:date_de_don,type_donataire=:type_donataire where id_donataire=:id_donataire");
          query.bindValue(":id_donataire", id_string);
          query.bindValue(":type_de_don", type_de_don);
          query.bindValue(":num_tel", num_tel);
          query.bindValue(":quantite_de_don",quantite_string);
          query.bindValue(":nom", nom);
          query.bindValue(":besoin", besoin);
          query.bindValue(":adresse", adresse);
          query.bindValue(":date_de_don", date_de_don);
          query.bindValue(":type_donataire",type_donataire);


  return query.exec();
}
QSqlQueryModel* Donataire::afficher()
{
 QSqlQueryModel* model=new QSqlQueryModel();

       model->setQuery("SELECT* FROM DONATAIRES");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("type_de_don"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("num_tel"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("quantite de don"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("nom"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("besoin"));
       model->setHeaderData(6, Qt::Horizontal, QObject::tr("adresse"));
       model->setHeaderData(7, Qt::Horizontal, QObject::tr("date de don"));
       model->setHeaderData(8, Qt::Horizontal, QObject::tr("type donataire"));



  return model;}


bool Donataire::ajouter_historique(QString n,QString etat,int id)
{
    QSqlQuery query;
    QString res= QString::number(id);
    query.prepare("INSERT INTO history (nom,etat,id, date_historique)"
                  "VALUES (:nom, :etat, :id, :date_historique)");
    query.bindValue(":nom", n);
        query.bindValue(":etat", etat);
            query.bindValue(":id", res);
query.bindValue(":date_historique", QDateTime::currentDateTime());
    return    query.exec();
}
QSqlQueryModel * Donataire::afficher_historique0()
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * FROM history");
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Etat d'historique"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("date"));
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom partenaire"));


    return model;
    }
bool Donataire::supprimer_his(int id)
{
    QSqlQuery query;
    QString id_s=QString::number(id);

          query.prepare(" Delete from history where id=:id");
          query.bindValue(0, id_s);



    return query.exec();
}


QSqlQueryModel * Donataire::trie_ID()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM DONATAIRES ORDER BY id_donataire ");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("type_de_don"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("num_tel"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("quantite de don"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("nom"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("besoin"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("adresse"));
          model->setHeaderData(7, Qt::Horizontal, QObject::tr("date de don"));
          model->setHeaderData(8, Qt::Horizontal, QObject::tr("type donataire"));

    return model;
}
QSqlQueryModel * Donataire::trie_NOM()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM DONATAIRES ORDER BY nom ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("type_de_don"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("num_tel"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("quantite de don"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("besoin"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("date de don"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("type donataire"));
    return model;
}
QSqlQueryModel * Donataire::trie_adresse()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM DONATAIRES ORDER BY adresse ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("type_de_don"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("num_tel"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("quantite de don"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("besoin"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("date de don"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("type donataire"));
    return model;
}

