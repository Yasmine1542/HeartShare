#ifndef DONATAIRES_H
#define DONATAIRES_H
#include <QString>
#include <QSqlQueryModel>
#include <QDate>


class Donataire
{
public:
    Donataire();
    Donataire(int,QString,QString,int,QString, QString ,QString, QDate, QString ) ;
      int getId() ;
     void setId(int);

     QString getNom();
     void setNom(QString);

     QString gettype_de_don() ;
     void settype_de_don(QString);

     QString getAdresse();
     void setAdresse(QString);

     QString getNum() ;
     void setNum (QString);

     QString getMail() ;
     void setMail(QString);

     QString getTypeD() ;
     void setTypeD(QString);

     QDate getnbDons();
     void setNbDons(QDate);

     int getquantite_de_don();
     void setquantite_de_don(int);
     bool ajouter();
     QSqlQueryModel* afficher();
     bool supprimer (int) ;
     bool modifier(int  ,QString  ,QString ,int ,QString, QString ,QString ,QDate, QString ) ;
     bool ajouter_historique(QString n,QString etat,int id);
     QSqlQueryModel* afficher_historique0();

bool supprimer_his(int);



        QSqlQueryModel * trie_ID();
        QSqlQueryModel * trie_NOM();
        QSqlQueryModel * trie_adresse();
        QSqlQueryModel * trie_type_de_don();
        QSqlQueryModel * trie_num_tel();
        QSqlQueryModel * trie_besoin();
        QSqlQueryModel * trie_type_donataire();
        QSqlQueryModel * trie_date_de_don();
        QSqlQueryModel * trie_quantite();



     private :
     int id_donataire ;
     QString nom ;
     QString type_de_don ;
     QString adresse ;
     QString num_tel ;
     QString besoin ;
     QString type_donataire ;
     QDate date_de_don ;
     int quantite_de_don ;

};
#endif // DONATAIRES_H
