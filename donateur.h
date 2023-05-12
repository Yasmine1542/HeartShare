#ifndef DONATEUR_H
#define DONATEUR_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
class Donateur
{
public:
    Donateur();
    Donateur(int,QString,QString,QString,int,QString,QString,int,int ) ;
      int getId() ;
     void setId(int);

     QString getNom();
     void setNom(QString);

     QString getPrenom() ;
     void setPrenom(QString);

     QString getAdresse();
     void setAdresse(QString);

     int getNum() ;
     void setNum (int);

     QString getMail() ;
     void setMail(QString);

     QString getTypeD() ;
     void setTypeD(QString);

     int getnbDons();
     void setNbDons(int);

     int getQuantite();
     void setQuantite(int);
     QSqlQueryModel* afficher();
     bool supprimer (int) ;
     bool ajouter();
     bool modifier() ;
     void generatePDF() ;
     void generateStatistics () ;
     //void generateStatistics_2() ;
     QSqlQueryModel* searchDonateur(QString name) ;
     QSqlQueryModel* sortByQunatite() ;
     QSqlQueryModel* sortByNbD() ;
     QSqlQueryModel* sortByName() ;
     private :
     int id_donateur ;
     QString nom ;
     QString prenom ;
     QString addresse ;
     int num_tel ;
     QString email ;
     QString type_donateur ;
     int nb_don ;
     int quantite ;

};

#endif // DONATEUR_H
