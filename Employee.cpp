#include "Employee.h"
#include<QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QObject>
#include <QSqlQueryModel>
Employee::Employee()
{
    id=0; nom ="";fonction="";email="";statut="";num_tel=0;adresse="";mdp="";droit_access=""; RFID="";
}

Employee::Employee(int id ,QString nom,QString fonction,QString email,QString statut,int num_tel,QString adresse,QString mdp,QString droit_acces, QString RFID)
{   this->id=id;
    this->nom=nom;
    this->fonction=fonction;
    this->email=email;
    this->statut=statut;
    this->num_tel=num_tel;
    this->adresse=adresse;
    this->mdp=mdp;
    this->droit_access=droit_acces;
    this->RFID=RFID;
}
int Employee:: getid(){return id;}
QString Employee:: getnom(){return nom;}
QString Employee::getfonction(){return fonction;}
QString Employee:: getemail(){return email;}
QString Employee::getstatut(){return statut;}
int Employee:: getnum_tel(){return num_tel;}
QString Employee::getadresse(){return adresse;}
QString Employee:: getmdp(){return mdp;}
QString Employee::getdroit_access(){return droit_access;}
QString Employee::getRFID(){return RFID;}

void Employee::setid(int id ){this->id=id;}
void Employee:: setnom(QString nom){this->nom=nom;}
void Employee::setfonction(QString fonction){this->fonction=fonction;}
void Employee:: setemail(QString email){this->email=email;}
void Employee::setstatut(QString statut){this->statut=statut;}
void Employee:: setnum_tel(int num_tel){this->num_tel=num_tel;}
void Employee::setadresse(QString adresse){this->adresse=adresse;}
void Employee:: setmdp(QString mdp){this->mdp=mdp;}
void Employee::setdroit_access(QString droit_access){this->droit_access=droit_access;}
void Employee::setRFID(QString RFID){this->RFID=RFID;}

bool Employee::ajouter()
{
    // Check if the ID already exists in the database
    QSqlQuery check_query;
    check_query.prepare("SELECT id FROM gestion_employer WHERE id = ?");
    check_query.addBindValue(id);
    if (check_query.exec() && check_query.next()) {
        // ID already exists, display an error message and return false
        QMessageBox::critical(nullptr, "Error", "Employee ID already exists in the database.");
        return false;
    }

    // Check if the name, phone number are not empty
    if (nom.trimmed().isEmpty() || QString::number(num_tel).trimmed().isEmpty()) {
        QMessageBox::critical(nullptr, "Error", "Please fill in all required fields.");
        return false;
    }

    // Check if the phone number is a valid number
    bool ok;
    int num_tel_int = QString::number(num_tel).toInt(&ok);
    if (!ok) {
        QMessageBox::critical(nullptr, "Error", "Please enter a valid phone number.");
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO gestion_employer(nom, fonction, email, id, statut, num_tel, adresse, mdp, droit_access,RFID) "
                  "VALUES (:nom, :fonction, :email, :id, :statut, :num_tel, :adresse, :mdp, :droit_access,:RFID)");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":fonction", fonction);
    query.bindValue(":email", email);
    query.bindValue(":statut", statut);
    query.bindValue(":num_tel", num_tel_int);
    query.bindValue(":adresse", adresse);
    query.bindValue(":mdp", mdp);
    query.bindValue(":droit_access", droit_access);
    query.bindValue(":RFID", RFID);

    if (query.exec()) {
        // Query executed successfully
        return true;
    } else {
        // Error executing query, display an error message and return false
        QMessageBox::critical(nullptr, "Error", "Failed to add employee to database.");
        return false;
    }
}

QSqlQueryModel*Employee::afficher()
{

    QSqlQueryModel* model = new QSqlQueryModel() ;

    model->setQuery("SELECT * FROM gestion_employer");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("fonction"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("email"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("id"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("statut"));
    model->setHeaderData(5, Qt::Horizontal,QObject::tr("num_tel"));
    model->setHeaderData(6, Qt::Horizontal,QObject::tr("adresse"));
    model->setHeaderData(7, Qt::Horizontal,QObject::tr("sexe"));
    model->setHeaderData(8, Qt::Horizontal,QObject::tr("age"));
    model->setHeaderData(9, Qt::Horizontal,QObject::tr("RFID"));


    return model;

}
bool Employee::supprimer(int id){
    QSqlQuery query;
    query.prepare("Delete from gestion_employer where id=:id");
    query.bindValue(0, id);

    return query.exec();

}
bool Employee::modifier()
{

    QSqlQuery query;
    QString id_string=QString::number(id);
    QString num_tel_string=QString::number(num_tel);
    query.prepare ("UPDATE gestion_employer SET nom = :nom,  fonction = :fonction, email= :email,  statut = :statut, num_tel = :num_tel, adresse = :adresse, mdp = :mdp, droit_access = :droit_access, RFID=:RFID WHERE id = :id");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":fonction", fonction);
    query.bindValue(":email", email);
    query.bindValue(":statut", statut);
    query.bindValue(":num_tel", num_tel);
    query.bindValue(":adresse", adresse);
    query.bindValue(":mdp", mdp);
    query.bindValue(":droit_access", droit_access);
    query.bindValue(":RFID", RFID);

    return query.exec();

}

QSqlQueryModel * Employee::trie_id()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM gestion_employer order by id");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("fonction"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("email"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("id"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("statut"));
    model->setHeaderData(5, Qt::Horizontal,QObject::tr("num_tel"));
    model->setHeaderData(6, Qt::Horizontal,QObject::tr("adresse"));
    model->setHeaderData(7, Qt::Horizontal,QObject::tr("sexe"));
    model->setHeaderData(8, Qt::Horizontal,QObject::tr("age"));
    model->setHeaderData(9, Qt::Horizontal,QObject::tr("RFID"));


    return model;
}

QSqlQueryModel * Employee::trie_nom()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM gestion_employer order by nom");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("fonction"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("email"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("id"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("statut"));
    model->setHeaderData(5, Qt::Horizontal,QObject::tr("num_tel"));
    model->setHeaderData(6, Qt::Horizontal,QObject::tr("adresse"));
    model->setHeaderData(7, Qt::Horizontal,QObject::tr("sexe"));
    model->setHeaderData(8, Qt::Horizontal,QObject::tr("age"));
    model->setHeaderData(9, Qt::Horizontal,QObject::tr("RFID"));


    return model;
}


QSqlQueryModel * Employee::trie_fonction()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM gestion_employer order by fonction");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("fonction"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("email"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("id"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("statut"));
    model->setHeaderData(5, Qt::Horizontal,QObject::tr("num_tel"));
    model->setHeaderData(6, Qt::Horizontal,QObject::tr("adresse"));
    model->setHeaderData(7, Qt::Horizontal,QObject::tr("sexe"));
    model->setHeaderData(8, Qt::Horizontal,QObject::tr("age"));
    model->setHeaderData(9, Qt::Horizontal,QObject::tr("RFID"));


    return model;
}







