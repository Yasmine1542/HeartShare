#include "donateur.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QObject>
#include <QSqlQueryModel>
#include <QPdfWriter>
#include <QPainter>
#include <QPrinter>
#include <QFileDialog>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>

Donateur::Donateur()
{
     id_donateur = 0;
     nom = " " ;
     prenom = " " ;
     addresse = " " ;
     num_tel= 0  ;
     email = " " ;
     type_donateur = " " ;
     nb_don = 0  ;
     quantite = 0  ;

}
Donateur::Donateur(int id_donateur , QString nom , QString prenom , QString addresse , int num_tel , QString email , QString type_donateur , int nb_don  , int quantite  )
{
    this->id_donateur = id_donateur ;
    this->nom = nom ;
    this->prenom = prenom ;
    this->addresse = addresse ;
    this->num_tel = num_tel ;
    this->email = email ;
    this->type_donateur = type_donateur ;
    this->nb_don = nb_don ;
    this->quantite = quantite ;

}
int Donateur::getId()
{return id_donateur; }
void Donateur::setId(int id_donateur )
{ this->id_donateur = id_donateur ;}
QString Donateur::getNom()
{return nom ; }
void Donateur::setNom(QString nom)
{this->nom = nom ;}

QString  Donateur::getPrenom()
{return prenom ; }
void  Donateur::setPrenom(QString prenom)
{this->prenom = prenom ;}
QString  Donateur::getAdresse()
{return addresse ; }
void  Donateur::setAdresse(QString addresse )
{this->addresse = addresse ; }

int Donateur::getNum()
{return num_tel; }
void Donateur::setNum (int num_tel)
{ this->num_tel = num_tel ;}

QString  Donateur::getMail()
{return email ; }
void  Donateur::setMail(QString email)
{ this->email = email ;}
QString  Donateur::getTypeD()
{return type_donateur ;}
void  Donateur::setTypeD(QString type_donateur)
{ this->type_donateur = type_donateur ;}
int  Donateur::getnbDons()
{return nb_don ; }
void  Donateur::setNbDons (int nb_don)
{ this->nb_don = nb_don ;}


int  Donateur::getQuantite()
{return quantite  ;}
void  Donateur::setQuantite(int quantite)
{this->quantite = quantite ; }

bool Donateur::ajouter()
{
     // Check if the ID already exists in the database
        QSqlQuery check_query;
        check_query.prepare("SELECT id_donateur FROM donateur WHERE id_donateur = ?");
        check_query.addBindValue(id_donateur);
        if (check_query.exec() && check_query.next()) {
            // ID already exists, display an error message and return false
            QMessageBox::critical(nullptr, "Error", "Donor ID already exists in the database.");
            return false;
        }

        // Check if the name, phone number are not empty
        if (nom.trimmed().isEmpty() && QString::number(num_tel).trimmed().isEmpty()) {
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
        if (!email.contains("@")) {
            // Invalid email format, display an error message and return false
            QMessageBox::critical(nullptr, "Error", "Invalid email format.");
            return false;
        }

        // Check if the donation quantity is a valid number
        int quantite_int = QString::number(quantite).toInt(&ok);
        if (!ok || quantite_int <= 0) {
            QMessageBox::critical(nullptr, "Error", "Please enter a valid donation quantity.");
            return false;
        }
    QString id_string=QString::number(id_donateur);
    QString num_tel_string=QString::number(num_tel);
    QString nb_don_string=QString::number(nb_don);
    QString quantite_string=QString::number(quantite);
    QSqlQuery query;
    query.prepare("INSERT INTO DONATEUR (id_donateur , nom, prenom, addresse , num_tel ,  email , type_donateur ,nb_don ,quantite ) "
                  "VALUES ( :id_donateur, :nom, :prenom, :addresse , :num_tel ,  :email , :type_donateur , :nb_don  , :quantite )");
    query.bindValue(":id_donateur", id_string);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":addresse" , addresse);
    query.bindValue(":num_tel",  num_tel_string);
    query.bindValue(":email", email);
    query.bindValue(":type_donateur", type_donateur);
    query.bindValue(":nb_don", nb_don_string);
    query.bindValue(":quantite", quantite_string);


    return   query.exec();
}

QSqlQueryModel* Donateur::afficher()
{

    QSqlQueryModel* model = new QSqlQueryModel() ;

          model->setQuery("SELECT* FROM DONATEUR");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Addresse"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("Numero tel"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("Type Donateur"));
          model->setHeaderData(7, Qt::Horizontal, QObject::tr("Nombre de don"));
          model->setHeaderData(8, Qt::Horizontal, QObject::tr("Quantite"));

  return model;
}
bool Donateur::supprimer(int id_donateur)
{
    QSqlQuery check_query;
    check_query.prepare("SELECT id_donateur FROM donateur WHERE id_donateur = ?");
    check_query.addBindValue(id_donateur);
    if (!check_query.exec() || !check_query.next()) {
        // ID does not exist, display an error message and return false
        QMessageBox::critical(nullptr, "Error", "Donor ID does not exist in the database.");
        return false;
    }

    QSqlQuery query;
    query.prepare("Delete from donateur where id_donateur=:id_donateur");
    query.bindValue(0, id_donateur);

     return   query.exec();
}
bool Donateur::modifier()
{
    // Check if the ID exists in the database
    QSqlQuery check_query;
    check_query.prepare("SELECT id_donateur FROM donateur WHERE id_donateur = ?");
    check_query.addBindValue(id_donateur);
    if (!check_query.exec() || !check_query.next()) {
        // ID does not exist, display an error message and return false
        QMessageBox::critical(nullptr, "Error", "Donor ID does not exist in the database.");
        return false;
    }

    // Check if the name, phone number are not empty
    if (nom.trimmed().isEmpty() && QString::number(num_tel).trimmed().isEmpty()) {
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

    // Check if the donation quantity is a valid number
    int quantite_int = QString::number(quantite).toInt(&ok);
    if (!ok || quantite_int <= 0) {
        QMessageBox::critical(nullptr, "Error", "Please enter a valid donation quantity.");
        return false;
    }

    QString id_string=QString::number(id_donateur);
    QString num_tel_string=QString::number(num_tel);
    QString nb_don_string=QString::number(nb_don);
    QString quantite_string=QString::number(quantite);

    QSqlQuery query;
    query.prepare("UPDATE DONATEUR SET nom = :nom, prenom = :prenom, addresse = :addresse, num_tel = :num_tel, email = :email, type_donateur = :type_donateur, nb_don = :nb_don, quantite = :quantite WHERE id_donateur = :id_donateur");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":addresse", addresse);
    query.bindValue(":num_tel", num_tel_string);
    query.bindValue(":email", email);
    query.bindValue(":type_donateur", type_donateur);
    query.bindValue(":nb_don", nb_don_string);
    query.bindValue(":quantite", quantite_string);
    query.bindValue(":id_donateur", id_string);

    return query.exec();
}
void Donateur::generatePDF()
{
    /*QString dir = "C:\\interface_1 - Copie";
    QDir().mkpath(dir);
    QString fileName = dir + "/Donateur.pdf";*/
 QString fileName = QFileDialog::getSaveFileName(nullptr, "Save PDF", "", "*.pdf");
 if (fileName.isEmpty()) {
     return;
 }
 QPrinter printer(QPrinter::PrinterResolution);

 // Set printer properties
 printer.setOutputFormat(QPrinter::PdfFormat);
 printer.setPaperSize(QPrinter::A4);
 printer.setOutputFileName(fileName);
    QPdfWriter pdf(fileName);
    QPainter painter(&pdf);
    int i = 4000;
     painter.drawPixmap(QRect(300,300,1000,1000),QPixmap("C:/integration_finale/logo-crewative.png"));
     painter.setPen(Qt::blue);
     painter.setFont(QFont("Time New Roman", 25));
     painter.drawText(3000,1450,"Liste des Donateur");
     painter.setPen(Qt::black);
     painter.setFont(QFont("Time New Roman", 15));
     painter.drawRect(100,100,9400,2500);
     painter.drawRect(100,3000,9400,500);
     painter.setFont(QFont("Time New Roman", 10));
     painter.drawText(200,3300,"ID");
     painter.drawText(700,3300,"Nom");
     painter.drawText(1700,3300,"Prenom");
     painter.drawText(2600,3300,"Adresse");
     painter.drawText(3500,3300,"Num");
     painter.drawText(4400,3300,"Email");
     painter.drawText(6500,3300,"Type D ");
     painter.drawText(7500,3300,"Nb don");
     painter.drawText(8500,3300,"Quantite");

     painter.drawRect(100,3000,9400,9000);

     QTextDocument previewDoc;


     QTextCursor cursor(&previewDoc);

     QSqlQuery query;
     query.prepare("SELECT* FROM DONATEUR");
     query.exec();
     while (query.next())
     {
         //painter.drawLine(100,i,9490,i) ;
         painter.drawText(300,i,query.value(0).toString());
         painter.drawText(700,i,query.value(1).toString());
         painter.drawText(1700,i,query.value(2).toString());
         painter.drawText(2600,i,query.value(3).toString());
         painter.drawText(3500,i,query.value(4).toString());
         painter.drawText(4400,i,query.value(5).toString());
         painter.drawText(6500,i,query.value(6).toString());
         painter.drawText(7500,i,query.value(7).toString());
         painter.drawText(8500,i,query.value(8).toString());

         i = i +500;
     }

     QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("ajouter effectue\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
       painter.end();
}
void Donateur::generateStatistics()
{
    // Create a new dialog window
        QDialog *dialog = new QDialog();

        // Set the window title
        dialog->setWindowTitle("Statistics");

        // Define the width and height of the chart
        int width = 400;
        int height = 400;

        // Create a chart object
        QChart chart;

        // Set the chart title
        chart.setTitle("Type de Donateurs");

        // Create a pie series and add it to the chart
        QPieSeries *series = new QPieSeries();

        // Query the database to get the data for the chart
        QSqlQuery query;
        query.prepare("SELECT type_donateur, COUNT(*) FROM DONATEUR GROUP BY type_donateur");
        if(query.exec())
        {
            while(query.next())
            {
                // Get the type and count for the current row
                QString type = query.value(0).toString();
                int count = query.value(1).toInt();

                // Add the type and count to the series
                series->append(type, count);
            }

            // Set the series as the data source for the chart
            chart.addSeries(series);

            // Create a chart view and set its size
            QChartView *chartView = new QChartView(&chart, dialog);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->resize(width, height);

            // Create a layout for the dialog window and add the chart view widget to it
            QVBoxLayout *layout = new QVBoxLayout();
            layout->addWidget(chartView);
            dialog->setLayout(layout);
        }

        // Show the dialog window
        dialog->exec();
}
/*void Donateur::generateStatistics_2()
{
    // Create a chart object
       QChart *chart = new QChart();

       // Set the chart title
       chart->setTitle("Type de Donateurs");

       // Create a pie series and add it to the chart
       QPieSeries *series = new QPieSeries();

       // Query the database to get the data for the chart
       QSqlQuery query;
       query.prepare("SELECT type_donateur, COUNT(*) FROM DONATEUR GROUP BY type_donateur");
       if(query.exec())
       {
           while(query.next())
           {
               // Get the type and count for the current row
               QString type = query.value(0).toString();
               int count = query.value(1).toInt();

               // Add the type and count to the series
               series->append(type, count);
           }

           // Set the series as the data source for the chart
           chart->addSeries(series);

           // Create a chart view and set its size
           QChartView *chartView = new QChartView(chart);

           // Add the chart view to the StatsWidget layout

       }
}
*/
QSqlQueryModel*  Donateur::searchDonateur(QString name)
{
    // Execute SQL query to retrieve the search results
        QSqlQueryModel* model = new QSqlQueryModel();
        QString sql = "SELECT * FROM DONATEUR WHERE nom LIKE '%" + name + "%';";
        model->setQuery(sql);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Addresse"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Numero tel"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Type Donateur"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("Nombre de don"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("Quantite"));

         return model;
}
QSqlQueryModel*  Donateur::sortByName()
{

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM DONATEUR ORDER BY nom ASC");


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Addresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Numero tel"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Type Donateur"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Nombre de don"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Quantite"));
    return model;
    }
QSqlQueryModel* Donateur::sortByNbD()
{ // Query the database to get the donors sorted by name
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM DONATEUR ORDER BY nb_don ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Addresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Numero tel"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Type Donateur"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Nombre de don"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Quantite"));
    return model;}
QSqlQueryModel* Donateur::sortByQunatite()
{ // Query the database to get the donors sorted by name
QSqlQueryModel *model = new QSqlQueryModel();
model->setQuery("SELECT * FROM DONATEUR ORDER BY quantite ASC");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Addresse"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Numero tel"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("Type Donateur"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("Nombre de don"));
model->setHeaderData(8, Qt::Horizontal, QObject::tr("Quantite"));
return model;}
