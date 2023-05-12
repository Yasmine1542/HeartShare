#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Employee.h"
#include "donateur.h"
#include "donataires.h"

#include "benevole.h"
#include "smtp.h"
#include "notification.h"
#include "qrcode.h"
#include "aliment.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlDatabase>
#include <QDateTime>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QIntValidator>
#include <QMessageBox>
#include<QIntValidator>

#include "arduino.h"
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts>
#include<QSystemTrayIcon>
#include <QRegExp>
#include "connection.h"
#include <QPainter>
#include <QDate>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include <QPixmap>
#include <QApplication>
#include <QIntValidator>
#include <QSqlQuery>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QtDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>
#include <QApplication>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QtCore>
#include <QFileDialog>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrlQuery>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QtNetwork>
#include <QSslSocket>
#include <QTextDocument>
#include <QSsl>
#include <QInputDialog>
#include <QSqlError>
#include <QTableWidgetItem>
#include <QStandardItem>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->stackedWidget);
    ui->stackedWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->stackedWidget->setCurrentIndex(0);
    ui->tab_don_3->setModel(m.afficher());
    ui->tabhis_2->setModel(m.afficher_historique0());
    ui->table_D_5->setModel(D.afficher());
    ui->table_D_7->setModel(D.afficher());
    ui->le_id_modif_3->setValidator(new QIntValidator(0, 9999999,this));
    ui->le_nb_don_modif_3->setValidator(new QIntValidator(0, 999,this));
    ui->le_quantite_modif_3->setValidator(new QIntValidator(0, 999,this));
    ui->le_numtel_modif_3->setValidator(new QIntValidator(99999999, 99999999,this));
    ui->ID->setValidator(new QIntValidator(0,9999999,this));
    ui->lineEdit_quant->setValidator(new QIntValidator(0,9999999,this));

    ui->dateEditEXP->setCalendarPopup(true);

    ui->dateEditREC->setCalendarPopup(true);
   ui->liste->setModel(b.afficher());

ui->tabStock->setModel(a.afficher());




    /*//maps
       QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                          QCoreApplication::organizationName(), QCoreApplication::applicationName());

       ui->WebBrowser_3->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");*/
    ui->le_id->setValidator(new QIntValidator(0, 9999999, this));
    int ret=A.connect_arduino();
    switch(ret){
    case(0):qDebug()<< "arduino is availble and connected to :"<< A.getarduino_port_name();
        break;
    case(1):qDebug()<< "arduino is availble but not connected to :"<< A.getarduino_port_name();
        break;
    case(-1):qDebug()<< "arduino is not availble";
    }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_RFID()));
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(AJOUT()));

    ui->tab->setModel(E.afficher());
    // ui->tab->setModel(E1.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::update_RFID(){
    QSqlQuery query,q2;
    QByteArray data="";
    QString UserMessage="";
    data=A.read_from_arduino();
    RFID=RFID+data;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    int currentHour = currentDateTime.time().hour();
    if(RFID!="" && RFID.length()==11)
    {
        if (currentHour >= 8 && currentHour < 17)
        {
            query.prepare("select * from gestion_employer where RFID='"+RFID+"'");
            if(query.exec())
            {
                if (query.next())
                {
                    ui->le_nom->setText(query.value(0).toString()) ;
                    ui->le_fonction->setCurrentText(query.value(1).toString()) ;
                    ui->le_email->setText(query.value(2).toString()) ;
                    ui->le_id->setText(query.value(3).toString()) ;
                    ui->le_satut->setText(query.value(4).toString()) ;
                    ui->le_num_tel->setText(query.value(5).toString()) ;
                    ui->le_adresse->setText(query.value(6).toString()) ;
                    ui->le_mdp->setText(query.value(7).toString()) ;
                    ui->le_droit_daccess->setText(query.value(8).toString()) ;
                    ui->le_RFID->setText(query.value(9).toString()) ;
                    QString NOM= query.value(0).toString();
                    UserMessage=NOM;
                    QByteArray m= UserMessage.toUtf8();
                    A.write_to_arduino(m);
                    ui->le_RFID->setText(RFID);
                    ui->label_RFIDInfo->setText("Registred");
                    qDebug() <<  " RFID: " <<RFID;
                    qDebug() <<  " User: " <<UserMessage;
                    qDebug() <<  " Time: " <<currentHour;

                }
                else
                {
                    ui->le_RFID->setText(RFID);
                    QString message ="Error";
                    QByteArray br = message.toUtf8();
                    A.write_to_arduino(br);
                    ui->label_RFIDInfo->setText("Not Registered");
                    qDebug() <<  " RFID: " <<RFID;
                    qDebug() <<  " Message: " <<message;
                    qDebug() <<  " User: " <<UserMessage;
                    qDebug() <<  " Time: " <<currentHour;
                }
            }
        }
        else
        {
            QString message ="Closed";
            QByteArray br = message.toUtf8();
            A.write_to_arduino(br);
            qDebug() <<  " RFID: " <<RFID;
            qDebug() <<  " Message: " <<message;
            qDebug() <<  " User: " <<UserMessage;
            qDebug() <<  " Time: " <<currentHour;
        }
        if(RFID.length()==11)
        {
            RFID="";
        }
    }
}

void MainWindow::on_le_add_clicked()
{
    int id = ui->le_id->text().toInt();
    QString nom = ui->le_nom->text();
    // QString fonction = ui->le_fonction->text();
    QString fonction = ui->le_fonction->currentText();
    QString adresse = ui->le_adresse->text();
    QString email = ui->le_email->text();
    int num_tel = ui->le_num_tel->text().toInt();
    QString mdp = ui->le_mdp->text();
    QString droit_access = ui->le_droit_daccess->text();
    QString statut = ui->le_satut->text();
    QString RFID = ui->le_RFID->text();

    Employee E(id, nom, fonction, email, statut, num_tel, adresse, mdp, droit_access,RFID);
    bool test = E.ajouter();

    if (test) {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué.\nClick Cancel to exit."), QMessageBox::Cancel);
        ui->tab->setModel(E.afficher());

    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_bouton_supp_clicked()
{
    Employee E ;
    E.setid(ui->le_id->text().toInt());
    bool test=E.supprimer(E.getid());
    if(test)
    { QMessageBox::information(nullptr, QObject::tr("ok"),
                               QObject::tr("supprission effectue\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab->setModel(E.afficher()) ;
    }
    else
    { QMessageBox::critical(nullptr, QObject::tr("not ok "),
                            QObject::tr("supprission non effectue.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel );}
}

void MainWindow::on_le_modifier_clicked()
{  int id = ui->le_id->text().toInt();
    QString nom = ui->le_nom->text();
    //QString fonction = ui->le_fonction->text();
    QString fonction = ui->le_fonction->currentText();
    QString adresse = ui->le_adresse->text();
    QString email = ui->le_email->text();
    int num_tel = ui->le_num_tel->text().toInt();
    QString mdp = ui->le_mdp->text();
    QString droit_access = ui->le_droit_daccess->text();
    QString statut = ui->le_satut->text();
    QString RFID = ui->le_RFID->text();

    Employee E(id, nom, fonction, email, statut, num_tel, adresse, mdp, droit_access,RFID);
    bool test = E.modifier();

    if (test) {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("modification effectué.\nClick Cancel to exit."), QMessageBox::Cancel);
        ui->tab->setModel(E.afficher());

    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("modification non effectué.\nClick Cancel to exit."), QMessageBox::Cancel);
    }

}


void MainWindow::on_butt_pdf_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    qDebug()<<dir;
    QPdfWriter pdf(dir+"/PdfList.pdf");
    QPainter painter(&pdf);
    int i = 4000;

    // painter.drawPixmap(QRect(100,100,2500,2500),QPixmap("C:/integration_finale/logo-crewative.png"));
    painter.drawText(900,650,"akrem");
    painter.setPen(Qt::red);
    painter.setFont(QFont("Time New Roman", 25));
    painter.drawText(3000,1400,"Liste des employees");
    painter.setPen(Qt::black);
    painter.setFont(QFont("Time New Roman", 15));
    painter.drawRect(100,100,9400,2500);
    painter.drawRect(100,3000,9400,500);
    painter.setFont(QFont("Time New Roman", 9));
    painter.drawText(300,3300,"nom");
    painter.drawText(2000,3300,"fonction");
    painter.drawText(4000,3300,"email");
    painter.drawText(5600,3300,"id");
    painter.drawText(7100,3300,"statu");
    painter.drawText(8100,3300,"age");
    painter.drawText(9100,3300,"adresse");

    painter.drawRect(100,3000,9400,10700);
    //QTextDocument previewDoc;
    QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");
    //QTextCursor cursor(&previewDoc);
    QSqlQuery query;
    query.prepare("select * from gestion_employer");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(2000,i,query.value(1).toString());
        painter.drawText(4000,i,query.value(2).toString());
        painter.drawText(5600,i,query.value(3).toString());
        painter.drawText(7000,i,query.value(4).toString());
        painter.drawText(8000,i,query.value(5).toString());
        painter.drawText(9000,i,query.value(6).toString());
        painter.drawText(10000,i,query.value(7).toString());
        painter.drawText(11000,i,query.value(8).toString());
        i = i +500;
    }
    int reponse = QMessageBox::question(this, "Générer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                        QMessageBox::Yes|QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));

        painter.end();
    }
    else
    {
        painter.end();
    }
}

void MainWindow::on_tri_id_clicked()
{  Employee E ;
    ui->tab_tri->setModel(E.trie_id());
}

void MainWindow::on_tri_nom_clicked()
{ Employee E ;
    ui->tab_tri->setModel(E.trie_nom());
}

void MainWindow::on_stat_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from gestion_employer where fonction = 'chef' ");
    float e=model->rowCount();
    model->setQuery("select * from gestion_employer where fonction = 'membre' ");
    float ee=model->rowCount();
    float total=e+ee;
    QString a=QString("chef"+QString::number((e*100)/total,'f',2)+"%" );
    QString b=QString("membre"+QString::number((ee*100)/total,'f',2)+"%" );
    QPieSeries *series = new QPieSeries();
    series->append(a,e);
    series->append(b,ee);
    if (e!=0)
    {QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());}
    if ( ee!=0)
    {
        // Add label, explode and define brush for 2nd slice
        QPieSlice *slice1 = series->slices().at(1);
        //slice1->setExploded();
        slice1->setLabelVisible();
    }
    // Create the chart widget
    QChart *chart = new QChart();
    // Add data to chart with title and hide legend
    chart->addSeries(series);
    chart->setTitle("Pourcentage des membre et chef : nombre total : "+ QString::number(total));
    chart->legend()->hide();
    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000,500);
    chartView->show();
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM gestion_employer WHERE id  LIKE'"+arg1+"%' or nom  LIKE'"+arg1+"%' or fonction LIKE'"+arg1+"%'");
    query->exec();
    if (query->next()) {
        model->setQuery(*query);
        ui->tab_tri->setModel(model);
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("SEARCH"),
                              QObject::tr("NO MATCH FOUND !!\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_connexion_clicked()
{
    QString username = ui->lineEdit_2->text();
        QString password = ui->lineEdit_3->text();

        QSqlQuery query;
        query.prepare("SELECT username, password FROM authentification WHERE username = :username");
        query.bindValue(":username", username);

        if (query.exec() && query.next()) {
            QString dbUsername = query.value(0).toString();
            QString dbPassword = query.value(1).toString();

            if (username == dbUsername && password == dbPassword) {
                if (username == "yasmine"){
                     ui->stackedWidget->setCurrentIndex(3);}


                  else  if (username == "akrem"){
                         ui->stackedWidget->setCurrentIndex(2);}
             else   if (username == "raouf"){
                     ui->stackedWidget->setCurrentIndex(5);}
                else   if (username == "maram"){
                        ui->stackedWidget->setCurrentIndex(4);}
                else   if (username == "rayen"){
                        ui->stackedWidget->setCurrentIndex(6);}
                else   if (username == "admin"){
                        ui->stackedWidget->setCurrentIndex(1);}


                    else{
                // Authentication successful, switch to next page
                ui->stackedWidget->setCurrentIndex(1);
             }
            } else {
                QMessageBox::critical(nullptr, tr("Authentication failed"),
                                      tr("Incorrect username or password"), QMessageBox::Cancel);
            }
        } else {
            QMessageBox::critical(nullptr, tr("Database error"),
                                  tr("Information inexistante dans la base de données"), QMessageBox::Cancel);
        }
        ui->lineEdit_3->clear();
        ui->lineEdit_2->clear();
}

void MainWindow::on_logout_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_reset_clicked()
{
    // Affiche une boîte de dialogue pour saisir le nom d'utilisateur
    QString username = QInputDialog::getText(this, tr("Changer le mot de passe"), tr("Nom d'utilisateur :"), QLineEdit::Normal);

    // Vérifie si le nom d'utilisateur existe dans la base de données
    QSqlQuery query;
    query.prepare("SELECT username, password FROM authentification WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec() || !query.next()) {
        QMessageBox::critical(nullptr, tr("Erreur d'authentification"),
                              tr("Nom d'utilisateur incorrect ou inexistant dans la base de données"), QMessageBox::Cancel);
        return;
    }

    // Affiche une boîte de dialogue pour saisir le nouveau mot de passe
    QString newPassword = QInputDialog::getText(this, tr("Changer le mot de passe"), tr("Nouveau mot de passe :"), QLineEdit::Normal);

    // Met à jour le mot de passe dans la base de données
    query.prepare("UPDATE authentification SET password = :newPassword WHERE username = :username");
    query.bindValue(":newPassword", newPassword);
    query.bindValue(":username", username);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, tr("Erreur de mise à jour du mot de passe"),
                              tr("Impossible de mettre à jour le mot de passe dans la base de données"), QMessageBox::Cancel);
        return;
    }

    // Enregistre le nouveau mot de passe et le nom d'utilisateur dans un fichier texte sur le bureau
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/nouveau_mot_de_passe_reset.txt";
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, tr("Erreur d'écriture dans le fichier"),
                              tr("Impossible d'écrire dans le fichier sur le bureau"), QMessageBox::Cancel);
        return;
    }

    QTextStream out(&file);
    out << "Nom d'utilisateur : " << username << "\n";
    out << "Nouveau mot de passe : " << newPassword;

    file.close();

    QMessageBox::information(nullptr, tr("Mot de passe mis à jour"),
                             tr("Le mot de passe a été mis à jour avec succès"), QMessageBox::Ok);
}

void MainWindow::on_tri_fonction_clicked()
{
    Employee E ;
    ui->tab_tri->setModel(E.trie_fonction());
}

void MainWindow::on_button_add_3_clicked()
{
    int id_donateur = ui->le_id_modif_3->text().toInt() ;
    QString nom = ui->le_nom_modif_3->text();
    QString prenom = ui->le_prenom_modif_3->text();
    QString addresse = ui->le_addresse_modif_3->text();
    int num_tel = ui->le_numtel_modif_3->text().toInt() ;
    QString email = ui->le_mail_modif_3->text();
    QString type_donateur = ui->le_type_d_modif_3->text();
    int nb_don = ui->le_nb_don_modif_3->text().toInt() ;
    int quantite = ui->le_quantite_modif_3->text().toInt() ;

 Donateur d(id_donateur , nom , prenom , addresse , num_tel , email , type_donateur , nb_don, quantite );
 bool test = d.ajouter() ;
 if(test)
 { QMessageBox::information(nullptr, QObject::tr("ok"),
                            QObject::tr("ajouter effectue\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
      ui->table_D_5->setModel(D.afficher()) ;
      ui->table_D_7->setModel(D.afficher()) ;


        }
            else
               { QMessageBox::critical(nullptr, QObject::tr("not ok "),
                            QObject::tr("ajout non effectue.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel );}
}

void MainWindow::on_button_add_4_clicked()
{
    int id_donateur = ui->le_id_modif_3->text().toInt() ;
    QString nom = ui->le_nom_modif_3->text();
    QString prenom = ui->le_prenom_modif_3->text();
    QString addresse = ui->le_addresse_modif_3->text();
    int num_tel = ui->le_numtel_modif_3->text().toInt() ;
    QString email = ui->le_mail_modif_3->text();
    QString type_donateur = ui->le_type_d_modif_3->text();
    int nb_don = ui->le_nb_don_modif_3->text().toInt() ;
    int quantite = ui->le_quantite_modif_3->text().toInt() ;
    Donateur d(id_donateur , nom , prenom , addresse , num_tel , email , type_donateur , nb_don, quantite );
    bool test = d.modifier() ;
    if(test)
    { QMessageBox::information(nullptr, QObject::tr("ok"),
                               QObject::tr("Modification avec succes\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
      ui->table_D_5->setModel(d.afficher()) ;
       ui->table_D_7->setModel(d.afficher()) ;
           }
               else
                  { QMessageBox::critical(nullptr, QObject::tr("not ok "),
                               QObject::tr("Echec de modification\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel );}
}

void MainWindow::on_button_sup_4_clicked()
{
    Donateur D1 ;
    D1.setId(ui->le_id_modif_3->text().toInt());
    bool test=D1.supprimer(D1.getId());
    if(test)
    { QMessageBox::information(nullptr, QObject::tr("ok"),
                               QObject::tr("supprission effectue\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
                ui->table_D_7->setModel(D1.afficher()) ;
                ui->table_D_5->setModel(D1.afficher()) ;
    }
               else
                  { QMessageBox::critical(nullptr, QObject::tr("not ok "),
                               QObject::tr("supprission non effectue.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel );}
}

void MainWindow::on_pushButton_93_clicked()
{
    Donateur D1 ;
    D1.generatePDF() ;
}

void MainWindow::on_button_sup_3_clicked()
{
    ui->le_id_modif_3->clear();
    ui->le_nom_modif_3->clear();
    ui->le_prenom_modif_3->clear();
    ui->le_addresse_modif_3->clear();
    ui->le_numtel_modif_3->clear();
    ui->le_mail_modif_3->clear();
    ui->le_type_d_modif_3->clear();
    ui->le_nb_don_modif_3->clear();
    ui->le_quantite_modif_3->clear();
}

void MainWindow::on_searchLineEdit_3_textChanged(const QString &arg1)
{

    Donateur D1 ;

    QString name = ui->searchLineEdit_3->text();
      QSqlQueryModel* model = D1.searchDonateur(name);
          // Update the view with the new search results
          ui->table_D_5->setModel(model);
          ui->table_D_5->resizeColumnsToContents();
}

void MainWindow::on_comboBox_3_activated(const QString &arg1)
{
    Donateur D1 ;

    if(arg1 =="nom")
    {
    QSqlQueryModel* model = D1.sortByName();
    ui->table_D_5->setModel(model); }
    else if(arg1 =="quantite de don")
    {
        QSqlQueryModel* model = D1.sortByQunatite();
        ui->table_D_5->setModel(model);
    }
    else if (arg1 == "nombre de don")
    {
        QSqlQueryModel* model = D1.sortByNbD();
        ui->table_D_5->setModel(model); //
    }
}

void MainWindow::on_pushButton_15_clicked()
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
                  int total = 0;
                  while(query.next())
                  {
                      // Get the type and count for the current row
                      QString type = query.value(0).toString();
                      int count = query.value(1).toInt();

                      // Add the type and count to the series
                      series->append(type, count);

                      // Increment the total count
                      total += count;
                  }

                  // Set the series as the data source for the chart
                  chart->addSeries(series);

                  // Set the chart legend to show the percentage values
                  QPieSlice *slice;
                  foreach(slice, series->slices()) {
                      slice->setLabel(QString("%1\n%2%").arg(slice->label()).arg(100 * slice->percentage(), 0, 'f', 1));
                  }

                  // Create a chart view and set its size
                  QChartView *chartView = new QChartView(chart, this);
                  chartView->setRenderHint(QPainter::Antialiasing);
                  chartView->resize(800, 600);

                  // Create a layout for the chart view widget and add it to the frame
                  QVBoxLayout *layout = new QVBoxLayout(ui->frame_11);
                  layout->addWidget(chartView);
                  ui->frame_11->setLayout(layout);
              }
}

void MainWindow::on_pushButton_16_clicked()
{
    Smtp * smtp = new Smtp("heartshare02@gmail.com" , "hitbroinbnnqhuul", "smtp.gmail.com",465);
            connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

           QString msg=ui->msgmail_2->toPlainText();

            smtp->sendMail("ilyes_test",ui->mail_2->text(),ui->objetmail_2->text(),msg);

            QMessageBox::information(nullptr, QObject::tr("SENT"),
                                     QObject::tr("Email Sended Successfully.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_17_clicked()
{

    ui->objetmail_2->clear();
    ui->mail_2->clear() ;
    ui->msgmail_2->clear() ;
}

void MainWindow::on_supprimer_M_clicked()
{
    int id = ui->ID->text().toInt();
    bool success = a.supprimer(id);
    if (success) {
        // Update the table view to reflect the deletion
        ui->tabStock->setModel(a.afficher());
        QMessageBox::information(this, "Success", "Entry successfully deleted.");
        n.notification_outofstock();
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete entry.");
    }
}

void MainWindow::on_ajouter_M_clicked()
{
    QString ref;

      int ID=ui->ID->text().toInt();
      int quant=ui->lineEdit_quant->text().toInt();

       QDate dateexp=ui->dateEditEXP->date();


       QDate daterec=ui->dateEditREC->date();


      QString lieu=ui->lineEdit_lieu->text();

      if(ui->radioButtonOUI->isChecked())
      {ref="oui";} else {ref="non";}

      if (ref.isEmpty() || ref.isNull())
        {
            QMessageBox::warning(this, "Error", "Please select a value for the Refrigerator field.");
            return;
        }


      QDate currentDate = QDate::currentDate();
     if (daterec > currentDate) {
          QMessageBox::warning(this, "Error", "Please select a past value for the rec date field.");
          return; // dateNOM is in the past
      }

      QString NOM=ui->lineEdit_NOM->text();
      aliment a(ID,quant,dateexp,daterec,lieu,ref,NOM);
      qDebug() << NOM;
      bool test=a.ajouter();
qDebug() << NOM;
              if(test)
              {QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Ajout avec succée\n click cancel to exit"),QMessageBox::Cancel);
ui->tabStock->setModel(a.afficher());
n.notification_nouv();
              }
              else QMessageBox::critical(nullptr,QObject::tr("Not ok"),QObject::tr("Ajout non effectué.\n Click to cancel"),QMessageBox::Cancel);
}

void MainWindow::on_modifier_M_clicked()
{
    // Retrieve the modified data from the form
      int id = ui->ID->text().toInt();
      int quantite = ui->lineEdit_quant->text().toInt();
      QString lieu_rec=ui->lineEdit_lieu->text();
      QString ref;
      if(ui->radioButtonOUI->isChecked())
      {ref="oui";} else {ref="non";}

      if (ref.isEmpty() || ref.isNull())
        {
            QMessageBox::warning(this, "Error", "Please select a value for the Refrigerator field.");
            return;
        }
    QDate dateexp=ui->dateEditEXP->date();

      QDate daterec=ui->dateEditREC->date();

      QDate currentDate = QDate::currentDate();
     if (daterec > currentDate) {
          QMessageBox::warning(this, "Error", "Saisir une valeur dans le passé pour la date de recuperation .");
          return; // dateNOM is in the past
      }

      QString NOM=ui->lineEdit_NOM->text();

      qDebug() << "ID ALIMENT" <<id;
      qDebug() << "QUANTITE"<<quantite;
      qDebug() << "LIEU RECUPERATION"<<lieu_rec;
      qDebug() << "REFRIGERATOR"<<ref;
      qDebug() << "DATE EXPIRATION!"<<dateexp;
      qDebug() << "DATE RECUPERATION"<<daterec;
      qDebug() <<"NOMination"<<NOM;

      // Create an aliment object with the modified data
      //aliment a(id,quantite,dateexp,daterec,lieu_rec,ref,NOM);

      // Call the modifier function
      bool success = a.modifier();

      if (success) {
          QMessageBox::information(this, "Success", "Record modified successfully.");
          ui->tabStock->setModel(a.afficher()) ;
      } else {
          QMessageBox::warning(this, "Error", "Failed to modify record.");
      }
}

void MainWindow::on_Clear_M_clicked()
{
    ui->ID->clear();
    ui->lineEdit_NOM->clear();
    ui->lineEdit_quant->clear();
    ui->lineEdit_lieu->clear();
    ui->dateEditEXP->clear();
    ui->dateEditREC->clear();
    ui->radioButtonNON->setChecked(false);
    ui->radioButtonOUI->setChecked(false);
}

void MainWindow::on_pushButton_M_clicked()
{
    QString dest = ui->searchlineEdit_M->text();
        QSqlQueryModel* model = a.searchByNOM(dest);
        ui->tabStock->setModel(model);
}

void MainWindow::on_searchlineEdit_M_textChanged(const QString &arg1)
{
    QSqlQueryModel* model = a.searchByNOM(arg1);
    ui->tabStock->setModel(model);

}


void MainWindow::on_comboBox_M_activated(const QString &arg1)
{
    if(arg1 =="Date d'expiration")
   {
       QSqlQueryModel* model = a.sortDataByDateexp(); // assuming "a" is an instance of the "aliment" class
       ui->tabStock->setModel(model); // assuming "tabStock" is the ID of a QtabStock widget
   }
   else if(arg1 =="Nom de l'aliment")
   {
       QSqlQueryModel* model = a.sortDataByName(); // assuming "a" is an instance of the "aliment" class
       ui->tabStock->setModel(model); // assuming "tabStock" is the ID of a QtabStock widget
   }
   else if(arg1 =="Quantité")
   {
       QSqlQueryModel* model = a.sortDataByQUANTITE(); // assuming "a" is an instance of the "aliment" class
       ui->tabStock->setModel(model); // assuming "tabStock" is the ID of a QtabStock widget
   }
}

void MainWindow::on_PDF_M_clicked()
{
    QString dir = "D:/interface_0";
       QDir().mkpath(dir);
       QString fileName = dir + "/Stock.pdf";
       QPdfWriter pdf(fileName);
       QPainter painter(&pdf);
       int i = 4000;
       QPixmap pixmap("C:/integration_finale/logo-crewative.png");
       int width = pixmap.width() * 3;
       int height = pixmap.height() * 3;
       painter.drawPixmap(QRect(100, 100, width, height), pixmap);

        painter.setPen(Qt::red);
        painter.setFont(QFont("Time New Roman", 25));
        painter.drawText(3000,1450,"Liste de Stock");
        painter.setPen(Qt::black);
        painter.setFont(QFont("Time New Roman", 15));
        painter.drawRect(0,100,9600,2500);
        painter.drawRect(100,3000,9600,500);
        painter.setFont(QFont("Time New Roman", 10));
        painter.drawText(300,3300,"ID Aliment");
        painter.drawText(1300,3300,"Quantite");
        painter.drawText(2200,3300,"Date d'expiration ");
        painter.drawText(3800,3300,"Date de recuperation");
        painter.drawText(5600,3300,"Lieu de recuperation");
        painter.drawText(7400,3300,"Refrigerateur");
        painter.drawText(8800,3300,"NOM");

        painter.drawRect(100,3000,9600,10700);

        QTextDocument previewDoc;
        QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");

        QTextCursor cursor(&previewDoc);

        QSqlQuery query;
        query.prepare("SELECT ID_ALIMENT, QUANTITE, DATE_EXP, DATE_REC, LIEU_REC, REF, NOM FROM GESTION_STOCK");
        query.exec();
        while (query.next())
        {
            painter.drawText(300,i,query.value(0).toString());
            painter.drawText(1300,i,query.value(1).toString());
            painter.drawText(2100,i,query.value(2).toString());
            painter.drawText(3900,i,query.value(3).toString());
            painter.drawText(5800,i,query.value(4).toString());
            painter.drawText(7400,i,query.value(5).toString());
            painter.drawText(8800,i,query.value(6).toString());

            i = i +500;
        }

        int reponse = QMessageBox::question(this, "Générer PDF", " PDF Enregistré ! Voulez Vous Affichez Le PDF ?",
            QMessageBox::Yes|QMessageBox::No);
        if (reponse == QMessageBox::Yes)
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/Stock.pdf"));
            painter.end();
        }
        else
        {
             painter.end();
        }
}

void MainWindow::on_tabStock_activated(const QModelIndex &index)
{
    QString val=ui->tabStock->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM GESTION_STOCK WHERE ID_ALIMENT='"+val+"' OR NOM='"+val+"' OR LIEU_REC='"+val+"' OR QUANTITE='"+val+"'");

    if (qry.exec())
    { while (qry.next())
        {
            //update
            //id
            ui->ID->setText(qry.value(0).toString());
            ui->lineEdit_NOM->setText(qry.value(6).toString());
            ui->lineEdit_lieu->setText(qry.value(4).toString());
            ui->lineEdit_quant->setText(qry.value(1).toString());
            ui->dateEditEXP->setDate(qry.value(2).toDate());
            ui->dateEditREC->setDate(qry.value(3).toDate());
            if(qry.value(5)=="non")
            ui->radioButtonNON->setChecked(true);
            else
                ui->radioButtonOUI->setChecked(true);




        }
    }
    QString text ="Stock Heartshare :"+ ui->tabStock->model()->data(ui->tabStock->model()->index(ui->tabStock->currentIndex().row(),1)).toString()
                        +" "+ui->tabStock->model()->data(ui->tabStock->model()->index(ui->tabStock->currentIndex().row(),2)).toString()
                        +" "+ui->tabStock->model()->data(ui->tabStock->model()->index(ui->tabStock->currentIndex().row(),3)).toString()
                        +" "+ui->tabStock->model()->data(ui->tabStock->model()->index(ui->tabStock->currentIndex().row(),4)).toString();
                     +" "+ui->tabStock->model()->data(ui->tabStock->model()->index(ui->tabStock->currentIndex().row(),5)).toString();
                     +" "+ui->tabStock->model()->data(ui->tabStock->model()->index(ui->tabStock->currentIndex().row(),6)).toString();
    using namespace qrcodegen;
    QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );
                  qint32 sz = qr.getSize();
                  QImage im(sz,sz, QImage::Format_RGB32);
                    QRgb black = qRgb(  0,  0,  0);
                    QRgb white = qRgb(255,255,255);
                  for (int y = 0; y < sz; y++)
                    for (int x = 0; x < sz; x++)
                      im.setPixel(x,y,qr.getModule(x, y) ? black : white );
                  ui->QR_code->setPixmap( QPixmap::fromImage(im.scaled(256,256,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );

}

void MainWindow::on_tabWidget_3_currentChanged(int index)
{// Create a chart object
    QChart *chart = new QChart();

    // Set the chart title
    chart->setTitle("Type de Donateurs");

    // Create a pie series and add it to the chart
    QPieSeries *series = new QPieSeries();

    // Query the database to get the data for the chart
    QSqlQuery query;
    query.prepare("SELECT REF, COUNT(*) FROM GESTION_STOCK GROUP BY REF");
    if(query.exec())
    {
        int total = 0;
        while(query.next())
        {
            // Get the type and count for the current row
            QString type = query.value(0).toString();
            int count = query.value(1).toInt();

            // Add the type and count to the series
            series->append(type, count);

            // Increment the total count
            total += count;
        }

        // Set the series as the data source for the chart
        chart->addSeries(series);

        // Set the chart legend to show the percentage values
        QPieSlice *slice;
        foreach(slice, series->slices()) {
            slice->setLabel(QString("%1\n%2%").arg(slice->label()).arg(100 * slice->percentage(), 0, 'f', 1));
        }

        // Create a chart view and set its size
        QChartView *chartView = new QChartView(chart, this);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->resize(800, 600);

        // Create a layout for the chart view widget and add it to the frame
        QVBoxLayout *layout = new QVBoxLayout(ui->statframe);
        layout->addWidget(chartView);
        ui->statframe->setLayout(layout);
    }
}

void MainWindow::on_ajout_2_clicked()
{
    int id = ui->le_id->text().toInt();

    // Vérifier que tous les champs sont remplis
        if (ui->le_date_3->text().isEmpty() || ui->le_quant_3->text().isEmpty() ||
            ui->le_tel_3->text().isEmpty() || ui->le_nom_3->text().isEmpty() ||
            ui->le_besoin_3->text().isEmpty() || ui->le_type_3->text().isEmpty() ||
            ui->le_type_don_3->text().isEmpty() || ui->le_adress_3->text().isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs !");
            return;
        }

        QDate date = ui->le_date_3->date();
        int quant = ui->le_quant_3->text().toInt();
        QString num = ui->le_tel_3->text();
        if(num.length() > 8) {
            QMessageBox::warning(this, "Erreur", "Le numéro de téléphone doit contenir au maximum 8 chiffres !");
            return;
        }
        QString nom = ui->le_nom_3->text();
        QString besoin = ui->le_besoin_3->text();
        QString type_de_don = ui->le_type_3->text();
        QString type_donat = ui->le_type_don_3->text();
        QString adress = ui->le_adress_3->text();

        // Vérifier si l'identifiant existe déjà dans la base de données
        QSqlQuery verif_query;
        verif_query.prepare("SELECT COUNT(*) FROM Donataire WHERE id_donataire = :id");
        verif_query.bindValue(":id", id);
        verif_query.exec();
        verif_query.next();
        int id_count = verif_query.value(0).toInt();

        if (id_count > 0) {
            QMessageBox::warning(this, "Erreur", "L'identifiant est déjà utilisé !");
            return;
        }

        Donataire m(id, type_de_don, num, quant, nom, besoin, adress, date, type_donat);

        bool test = m.ajouter();
        if(test) {
            QMessageBox::information(this, "Succès", "Ajout réussi !");
            ui->tab_don_3->setModel(m.afficher());
            ui->tab_don_3->resizeColumnsToContents();
            m.ajouter_historique(nom,"ajout",id);
            ui->tabhis_2->setModel(m.afficher_historique0());
            stat();
        }
        else {
            QMessageBox::critical(this, "Erreur", "Ajout non effectué !");
}
}
void MainWindow::on_supprimer_2_clicked()
{
    // Récupère la ligne sélectionnée dans le tableau
        int row = ui->tab_don_3->currentIndex().row();

        // Vérifie si une ligne est sélectionnée
        if (row < 0) {
            QMessageBox::warning(this, "Avertissement", "Veuillez sélectionner une ligne à supprimer.");
            return;
        }

        // Récupère l'ID de l'enregistrement sélectionné dans le tableau
        int id = ui->tab_don_3->model()->data(ui->tab_don_3->model()->index(row, 0)).toInt();


        // Affiche un message de confirmation demandant à l'utilisateur s'il est sûr de vouloir supprimer les informations de l'enregistrement sélectionné
        QMessageBox msgbox;
        msgbox.setText("Voulez-vous vraiment supprimer ces informations ?");
        msgbox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgbox.setDefaultButton(QMessageBox::No);
        int res = msgbox.exec();

        // Si l'utilisateur confirme la suppression, crée un objet Donataire et appelle la fonction "supprimer" pour supprimer l'enregistrement correspondant
        if (res == QMessageBox::Yes) {
            Donataire m1;
            m1.setId(id);
            bool test = m1.supprimer(m1.getId());

            // Affiche un message de succès ou d'échec
            if(test) {
                QMessageBox::information(this, "Succès", "Suppression avec succès");
                ui->tab_don_3->setModel(m1.afficher());
                m.ajouter_historique(m.getNom(),"supprimer",id);
                ui->tabhis_2->setModel(m.afficher_historique0());
            } else {
                QMessageBox::warning(this, "Échec", "Échec de suppression");
            }
        }
}

void MainWindow::on_modifier_2_clicked()
{

    int id=ui->le_id->text().toInt();

    // Vérifier que tous les champs sont remplis
        if (ui->le_date_3->text().isEmpty() || ui->le_quant_3->text().isEmpty() ||
            ui->le_tel_3->text().isEmpty() || ui->le_nom_3->text().isEmpty() ||
            ui->le_besoin_3->text().isEmpty() || ui->le_type_3->text().isEmpty() ||
            ui->le_type_don_3->text().isEmpty() || ui->le_adress_3->text().isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs !");
            return;
        }


    QDate date=ui->le_date_3->date();
    int quant=ui->le_quant_3->text().toInt();
    QString num=ui->le_tel_3->text();
    if(num.length() > 8) {
        QMessageBox::warning(this, "Erreur", "Le numéro de téléphone doit contenir au maximum 8 chiffres !");
        return;
    }
    QString nom=ui->le_nom_3->text();
    QString besoin=ui->le_besoin_3->text();
    QString type_de_don=ui->le_type_3->text();
    QString type_donat=ui->le_type_don_3->text();
    QString adress=ui->le_adress_3->text();





    Donataire m(id,type_de_don,num,quant,nom,besoin,adress,date,type_donat);

     bool test=m.modifier(id,type_de_don,num,quant,nom,besoin,adress,date,type_donat);
     if(test)
     {ui->tab_don_3->setModel(m.afficher());
         m.ajouter_historique(nom,"modifier",id);
         ui->tabhis_2->setModel(m.afficher_historique0());
         stat();
         QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("modif successful.\n"
                                             "click OK to continue."),QMessageBox::Ok);

     }
     else QMessageBox::critical(nullptr, QObject::tr(" not OK"),
                                   QObject::tr("modif non effectue.\n"
                                               "click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_11_clicked()
{
    QString dir = "C:/integration_finale";
       QDir().mkpath(dir);
       QString fileName = dir + "/Donataires.pdf";
       QPdfWriter pdf(fileName);
       QPainter painter(&pdf);
       int i = 4000;
    painter.drawPixmap(QRect(100,100,2000,2000),QPixmap("C:/integration_finale/logo-crewative.png"));
        painter.setPen(Qt::red);
        painter.setFont(QFont("Time New Roman", 25));
        painter.drawText(3000,1450,"Liste des Donataires");
        painter.setPen(Qt::black);
        painter.setFont(QFont("Time New Roman", 15));
        painter.drawRect(100,100,9400,2500);
        painter.drawRect(100,3000,9400,500);
        painter.setFont(QFont("Time New Roman", 10));
        painter.drawText(300,3300,"ID Donataire");
        painter.drawText(1500,3300,"Type de don");
        painter.drawText(3000,3300,"Numéro de téléphone");
        painter.drawText(4800,3300,"Quantité de don");
        painter.drawText(6600,3300,"Nom");
        painter.drawText(8400,3300,"Besoin");
        painter.drawText(10000,3300,"Adresse");
        painter.drawText(11500,3300,"Date de don");
        painter.drawText(13500,3300,"Type de donataire");

        painter.drawRect(100,3000,9400,10700);

        QTextDocument previewDoc;
        QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");

        QTextCursor cursor(&previewDoc);

        QSqlQuery query;
        query.prepare("SELECT ID_DONATAIRE, TYPE_DE_DON, NUM_TEL, QUANTITE_DE_DON, NOM, BESOIN, ADRESSE, DATE_DE_DON, TYPE_DONATAIRE FROM DONATAIRES");
        query.exec();
        while (query.next())
        {
            painter.drawText(300,i,query.value(0).toString());
            painter.drawText(1500,i,query.value(1).toString());
            painter.drawText(3000,i,query.value(2).toString());
            painter.drawText(4800,i,query.value(3).toString());
            painter.drawText(6600,i,query.value(4).toString());
            painter.drawText(8400,i,query.value(5).toString());
            //painter.drawText(10000,i,query.value(6).toString());
            //painter.drawText(11500,i,query.value(7).toString());
            //painter.drawText(13500,i,query.value(8).toString());

            i = i +500;
        }

        int reponse = QMessageBox::question(this, "Générer PDF", " PDF Enregistré ! Voulez Vous Affichez Le PDF ?",
            QMessageBox::Yes|QMessageBox::No);
        if (reponse == QMessageBox::Yes)
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/Donataires.pdf"));
            painter.end();
        }
        else
        {
             painter.end();
        }

}

void MainWindow::on_Clear_2_clicked()
{
    ui->le_id_3->clear();
        ui->le_nom_3->clear();
        ui->le_tel_3->clear();
        ui->le_date_3->clear();
        ui->le_type_3->clear();
        ui->le_quant_3->clear();
        ui->le_adress_3->clear();
        ui->le_besoin_3->clear();
        ui->le_type_don_3->clear();
}

void MainWindow::postrequest(QString smsmsg,QString phonenumber){
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest req( QUrl( QString("https://api.orange.com/smsmessaging/v1/outbound/tel%3A%2B322804/requests") ) );
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    req.setRawHeader("Authorization", "Bearer eyJ2ZXIiOiIxLjAiLCJ0eXAiOiJKV1QiLCJhbGciOiJFUzM4NCIsImtpZCI6ImRzRUN2TDVaTENQbTl1R081RHltUjZCRTdMcnFGak5hX1VKbl9Ody1zdVUifQ.eyJhcHBfbmFtZSI6IlFUIFByb2plY3QiLCJzdWIiOiJwSTc1SlNYeVNZMThRdk9jcWl5MU0xQzB3N1RwVlliVyIsImlzcyI6Imh0dHBzOlwvXC9hcGkub3JhbmdlLmNvbVwvb2F1dGhcL3YzIiwiZXhwIjoxNjgzMDQ0MjA4LCJhcHBfaWQiOiJ3QXBZNU05MDBYU21XcVpUIiwiaWF0IjoxNjgzMDQwNjA4LCJjbGllbnRfaWQiOiJwSTc1SlNYeVNZMThRdk9jcWl5MU0xQzB3N1RwVlliVyIsImp0aSI6IjY2OTY3MjEzLTY4NzgtNGEyNy1hYjIyLTQ2YWFlYzQ2MGU1ZSJ9.5rAucyHYrXLRnTFSQ2RWEQZeiEfN0ICL-VJr0szpknZUXmWEIt0u101XghRsCa91MA_fym6OfYuVyPK48qO_I68ythDLJESsMP8jaia1rjoRhvMHcypoKnGuF22I0Jfo");
    QJsonObject msg;
    msg["message"] = smsmsg;
    QJsonObject obj;
    obj["address"] = "tel:+216"+phonenumber;
    obj["senderAddress"] = "tel:+322804";
    obj["outboundSMSTextMessage"] = msg;
    QJsonObject body;
    body["outboundSMSMessageRequest"] = obj;
    QJsonDocument doc(body);
    QByteArray data = doc.toJson();
    QNetworkReply *reply = mgr.post(req,data);
    eventLoop.exec(); // blocks stack until "finished()" has been called
    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Success" <<reply->readAll();
        delete reply;
    }
    else {
        qDebug() << "Failure" <<reply->errorString() << reply->error();
        delete reply;
    }
}
void MainWindow::on_msg_c_3_clicked()
{
    // Execute a query to retrieve the phone numbers
        QSqlQuery query;
        query.exec("SELECT num_tel FROM DONATAIRES");
        QStringList phone_numbers;
        while (query.next()) {
            QString phone_number = query.value(0).toString();
            phone_numbers.append(phone_number);
        }

        // Display a dialog box to select the phone number
        bool ok;
        QString phone_number = QInputDialog::getItem(this, "Phone Number", "Select the phone number to send the SMS to:", phone_numbers, 0, false, &ok);
        if (!ok) {
            return;
        }
        QString msg="Votre demande à été confirmée avec succées! HeartShare";
           postrequest(msg,phone_number);
}

void MainWindow::on_le_sss_3_returnPressed()
{
    QString search_text = ui->le_sss_3->text().trimmed();
        QString uppercase_search_text = search_text.toUpper();

        QSqlQueryModel* model = new QSqlQueryModel();
        QString query("SELECT * FROM DONATAIRES WHERE UPPER(ID_DONATAIRE) LIKE '%' || :search_text || '%' "
                        " OR UPPER(TYPE_DE_DON) LIKE '%' || :search_text || '%' "
                        " OR UPPER(NUM_TEL) LIKE '%' || :search_text || '%' "
                        " OR UPPER(QUANTITE_DE_DON) LIKE '%' || :search_text || '%' "
                        " OR UPPER(NOM) LIKE '%' || :search_text || '%' "
                        " OR UPPER(BESOIN) LIKE '%' || :search_text || '%' "
                        " OR UPPER(ADRESSE) LIKE '%' || :search_text || '%' "
                        " OR UPPER(DATE_DE_DON) LIKE '%' || :search_text || '%' "
                        " OR UPPER(TYPE_DONATAIRE) LIKE '%' || :search_text || '%'"
                        " OR UPPER(ID_DONATAIRE) LIKE '%' || :uppercase_search_text || '%' "
                        " OR UPPER(TYPE_DE_DON) LIKE '%' || :uppercase_search_text || '%' "
                        " OR UPPER(NUM_TEL) LIKE '%' || :uppercase_search_text || '%' "
                        " OR UPPER(QUANTITE_DE_DON) LIKE '%' || :uppercase_search_text || '%' "
                        " OR UPPER(NOM) LIKE '%' || :uppercase_search_text || '%' "
                        " OR UPPER(BESOIN) LIKE '%' || :uppercase_search_text || '%' "
                        " OR UPPER(ADRESSE) LIKE '%' || :uppercase_search_text || '%' "
                        " OR UPPER(DATE_DE_DON) LIKE '%' || :uppercase_search_text || '%' "
                        " OR UPPER(TYPE_DONATAIRE) LIKE '%' || :uppercase_search_text || '%'");

        QSqlQuery sql_query;
        sql_query.prepare(query);
        sql_query.bindValue(":search_text", search_text);
        sql_query.bindValue(":uppercase_search_text", uppercase_search_text);

        if (sql_query.exec())
        {
            model->setQuery(sql_query);
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type de don"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("Numéro"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantité"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("Nom"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("Besoin"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
            model->setHeaderData(7, Qt::Horizontal, QObject::tr("Date"));
            model->setHeaderData(8, Qt::Horizontal, QObject::tr("Type de donataire"));

            ui->tab_don_3->setModel(model);
        }
        else
        {
            qDebug() << "Error executing query: " << sql_query.lastError().text();
        }
}

void MainWindow::on_comboBox_tri_2_currentIndexChanged(const QString &choix)
{
    Donataire m;
        if (choix == "nom")
        {
            bool test = m.trie_NOM();
            if (test)
            {
                ui->tab_don_3->setModel(m.afficher());
                ui->tab_don_3->setModel(m.trie_NOM());
                QMessageBox::information(nullptr,QObject::tr("ok"),
                                         QObject::tr("tri Nom effectué \n"
                                                     "Click Cancel to exist ."), QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("non"),
                                      QObject::tr("tri Nom failed.\n"
                                                  "Click Cancel to exit."), QMessageBox::Cancel);
            }
        }
        else if (choix == "adresse")
        {
            bool test = m.trie_adresse();
            if (test)
            {
                ui->tab_don_3->setModel(m.afficher());
                ui->tab_don_3->setModel(m.trie_adresse());
                QMessageBox::information(nullptr,QObject::tr("ok"),
                                         QObject::tr("tri adresse effectué \n"
                                                     "Click Cancel to exist ."),QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("non"),
                                      QObject::tr("tri adresse failed.\n"
                                                  "Click Cancel to exit."), QMessageBox::Cancel);
            }
        }
        else if (choix == "id")
        {
            bool test = m.trie_ID();
            if (test)
            {
                ui->tab_don_3->setModel(m.afficher());
                ui->tab_don_3->setModel(m.trie_ID());
                QMessageBox::information(nullptr,QObject::tr("ok"),
                                         QObject::tr("tri id effectué \n"
                                                     "Click Cancel to exist ."),QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("non"),
                                      QObject::tr("tri id failed.\n"
                                                  "Click Cancel to exit."), QMessageBox::Cancel);
            }
        }
}

void MainWindow::on_Button_stat_3_clicked()
{
    // Create a chart object
          QChart *chart = new QChart();

          // Set the chart title
          chart->setTitle("Type de Donateurs");

          // Create a pie series and add it to the chart
          QPieSeries *series = new QPieSeries();

          // Query the database to get the data for the chart
          QSqlQuery query;
          query.prepare("SELECT TYPE_DONATAIRE, COUNT(*) FROM DONATAIRES GROUP BY TYPE_DONATAIRE");
          if(query.exec())
          {
              int total = 0;
              while(query.next())
              {
                  // Get the type and count for the current row
                  QString type = query.value(0).toString();
                  int count = query.value(1).toInt();

                  // Add the type and count to the series
                  series->append(type, count);

                  // Increment the total count
                  total += count;
              }

              // Set the series as the data source for the chart
              chart->addSeries(series);

              // Set the chart legend to show the percentage values
              QPieSlice *slice;
              foreach(slice, series->slices()) {
                  slice->setLabel(QString("%1\n%2%").arg(slice->label()).arg(100 * slice->percentage(), 0, 'f', 1));
              }

              // Create a chart view and set its size
              QChartView *chartView = new QChartView(chart, this);
              chartView->setRenderHint(QPainter::Antialiasing);
              chartView->resize(800, 600);

              // Create a layout for the chart view widget and add it to the frame
              QVBoxLayout *layout = new QVBoxLayout(ui->frame_10);
              layout->addWidget(chartView);
              ui->frame_10->setLayout(layout);
          }
}

void MainWindow::on_Button_stat_4_clicked()
{
    // Clear the existing layout from the frame
           QLayout *layout = ui->frame_10->layout();
           if (layout) {
               delete layout;
           }

           // Create a chart object
           QChart *chart = new QChart();

           // Set the chart title
           chart->setTitle("Type de Donateurs");

           // Create a pie series and add it to the chart
           QPieSeries *series = new QPieSeries();

           // Query the database to get the data for the chart
           QSqlQuery query;
           query.prepare("SELECT TYPE_DONATAIRE, COUNT(*) FROM DONATAIRES GROUP BY TYPE_DONATAIRE");
           if(query.exec())
           {
               int total = 0;
               while(query.next())
               {
                   // Get the type and count for the current row
                   QString type = query.value(0).toString();
                   int count = query.value(1).toInt();

                   // Add the type and count to the series
                   series->append(type, count);

                   // Increment the total count
                   total += count;
               }

               // Set the series as the data source for the chart
               chart->addSeries(series);

               // Set the chart legend to show the percentage values
               QPieSlice *slice;
               foreach(slice, series->slices()) {
                   slice->setLabel(QString("%1\n%2%").arg(slice->label()).arg(100 * slice->percentage(), 0, 'f', 1));
               }

               // Create a chart view and set its size
               QChartView *chartView = new QChartView(chart, this);
               chartView->setRenderHint(QPainter::Antialiasing);
               chartView->resize(800, 600);

               // Create a layout for the chart view widget and add it to the frame
               QVBoxLayout *layout = new QVBoxLayout(ui->frame_10);
               layout->addWidget(chartView);
               ui->frame_10->setLayout(layout);
           }
}

void MainWindow::on_supprimer_his_2_clicked()
{
    // Récupère la ligne sélectionnée dans le tableau
        int row = ui->tabhis_2->currentIndex().row();

        // Vérifie si une ligne est sélectionnée
        if (row < 0) {
            QMessageBox::warning(this, "Avertissement", "Veuillez sélectionner une ligne à supprimer.");
            return;
        }

        // Récupère l'ID de l'enregistrement sélectionné dans le tableau
        int id = ui->tabhis_2->model()->data(ui->tabhis_2->model()->index(row, 0)).toInt();

        // Affiche un message de confirmation demandant à l'utilisateur s'il est sûr de vouloir supprimer les informations de l'enregistrement sélectionné
        QMessageBox msgbox;
        msgbox.setText("Voulez-vous vraiment supprimer ces informations ?");
        msgbox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgbox.setDefaultButton(QMessageBox::No);
        int res = msgbox.exec();

        // Si l'utilisateur confirme la suppression, crée un objet Donataire et appelle la fonction "supprimer_his" pour supprimer l'enregistrement correspondant
        if (res == QMessageBox::Yes) {
            Donataire m2;
            m2.setId(id);
            bool test = m2.supprimer_his(m2.getId());

            // Supprime la ligne du modèle si la suppression a réussi
            if (test) {
                ui->tabhis_2->model()->removeRow(row);
            }

            // Affiche un message de succès ou d'échec
            if (test) {
                QMessageBox::information(this, "Succès", "Suppression avec succès");
            } else {
                QMessageBox::warning(this, "Échec", "Échec de suppression");
            }
        }
}

void MainWindow::on_msg_c_4_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery("SELECT Nom, COUNT(*) AS Demandes, MIN(date_de_don) AS Première_date, MAX(date_de_don) AS Dernière_date,LISTAGG(num_tel, ' , ') WITHIN GROUP (ORDER BY num_tel) AS Num_tels FROM DONATAIRES GROUP BY Nom ORDER BY Nom");
        if (model->lastError().isValid()) {
            qDebug() << "Erreur lors de l'exécution de la requête : " << model->lastError().text();

            return;
        }

        // Binding the model to the table
        ui->tab2h_2->setModel(model);

        // Setting column headers
        model->setHeaderData(0, Qt::Horizontal, tr("Nom"));
        model->setHeaderData(1, Qt::Horizontal, tr("Demandes"));
        model->setHeaderData(2, Qt::Horizontal, tr("1ère demande"));
        model->setHeaderData(3, Qt::Horizontal, tr("Dernière demande"));
        model->setHeaderData(4, Qt::Horizontal, tr("Numéros de téléphone"));

        // Resize columns based on their content
        ui->tab2h_2->resizeColumnsToContents();
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox msgbox;
    int id=ui->le_id_K->text().toInt();
    QString nom=ui->le_nom_K->text();
    QString mail=ui->le_mail_k->text();
    QDate datenaiss=ui->le_date_k->date();
    int numtel=ui->le_tel_k->text().toInt();
    QString adresse=ui->le_adress_k->text();
    QString dispo=ui->le_disp_k->text();
    QString vehicle=ui->le_desc_k->text();
    int mission=ui->le_nb_m_k->text().toInt();
    Benevole B(id,nom,mail,datenaiss,numtel,adresse,dispo,vehicle,mission);



    msgbox.setText("erreur");

    bool test=B.ajouter();

        if(test){
            ui->liste->setModel(b.afficher());
            msgbox.setText("ajouté avec succes");
        }

       msgbox.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    int id=ui->le_id_K->text().toInt();
    QString nom=ui->le_nom_K->text();
    QString mail=ui->le_mail_k->text();
    QDate datenaiss=ui->le_date_k->date();
    int numtel=ui->le_tel_k->text().toInt();
    QString adresse=ui->le_adress_k->text();
    QString dispo=ui->le_disp_k->text();
    QString vehicle=ui->le_desc_k->text();
    int mission=ui->le_nb_m_k->text().toInt();
    Benevole b(id,nom,mail,datenaiss,numtel,adresse,dispo,vehicle,mission);

        QSqlQuery query;
        query.prepare("SELECT * FROM benevole WHERE id = :id");
        query.bindValue(":id", id);

        if (!query.exec())
        {
            QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de la vérification de l'identifiant.");
            return;
        }
        if (!query.next())
        {
            QMessageBox::warning(this, "Attention", "L'identifiant à modifier n'existe pas dans la table.");
            return;
        }


        QMessageBox::StandardButton confirmUpdate = QMessageBox::question(this, "Confirmation",
            "Êtes-vous sûr de vouloir modifier cet enregistrement ?",
            QMessageBox::Yes|QMessageBox::No);

        if (confirmUpdate == QMessageBox::No) {
            return;
        }



         bool test=b.modifier(id);

        if (test)
        {

            QMessageBox::information(nullptr, QObject::tr("OK"),
                         QObject::tr("Modification effectuée\n"
                                     "Click Cancel to exit"), QMessageBox::Cancel);
           ui->liste->setModel(b.afficher());
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                         QObject::tr("Modification échouée\n"
                                     "Click Cancel to exit"), QMessageBox::Cancel);
        }
}

void MainWindow::on_pushButton_supp_clicked()
{
    int id=ui->le_id_K->text().toInt();
    bool test=b.supprimer(id);
    if(test)
    {
        ui->liste->setModel(b.afficher());
        QMessageBox::critical(nullptr, QObject::tr("OK"),
                    QObject::tr("Bénévole retiré.\n""Proceed."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("Suppression échouée.\n""Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pushButton_chercher_clicked()
{

}

void MainWindow::on_le_chercher_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM benevole WHERE nom  LIKE'"+arg1+"%' or nom  LIKE'"+arg1+"%' or fonction LIKE'"+arg1+"%'");

    query->exec();
    if (query->next()) {
        model->setQuery(*query);
        ui->liste_2->setModel(model);
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("SEARCH"),
                              QObject::tr("NO MATCH FOUND !!\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pdf_clicked()
{
    QPdfWriter pdf("C:/integration_finale/logo-crewative.png");

           QPainter painter(&pdf);
           int i = 4100;



                  QColor dateColor(0x4a5bcf);
                  painter.setPen(dateColor);

                  painter.setFont(QFont("Montserrat SemiBold", 11));
                  QDate cd = QDate::currentDate();
                  painter.drawText(8400,250,cd.toString("Tunis"));
                  painter.drawText(8100,500,cd.toString("dd/MM/yyyy"));

                  QColor titleColor(0x341763);
                  painter.setPen(titleColor);
                  painter.setFont(QFont("Montserrat SemiBold", 25));

                  painter.drawText(3000,1450,"Liste des benevoles");

                  painter.setPen(Qt::black);
                  painter.setFont(QFont("Time New Roman", 15));
                  painter.drawRect(100,100,9400,2500);
                  painter.drawRect(100,3300,9400,500);

                  painter.setFont(QFont("Montserrat SemiBold", 10));

                  painter.drawText(500,3600,"ID");
                  painter.drawText(2000,3600,"NOM");
                  painter.drawText(3300,3600,"mail");
                   painter.drawText(4500,3600,"datenaiss");
                   painter.drawText(6700,3600,"numtel");
                  painter.drawText(8500,3600,"adresse");
                  painter.setFont(QFont("Montserrat", 10));
                  painter.drawRect(100,3300,9400,9000);

                  QSqlQuery query;
                  query.prepare("select * from benevole");
                  query.exec();
                  int y=4300;
                  while (query.next())
                  {
                      painter.drawLine(100,y,9490,y);
                      y+=500;
                      painter.drawText(500,i,query.value(0).toString());
                      painter.drawText(2000,i,query.value(1).toString());
                      painter.drawText(3300,i,query.value(2).toString());
                      painter.drawText(4500,i,query.value(3).toString());
                       painter.drawText(6700,i,query.value(4).toString());
                      painter.drawText(8500,i,query.value(5).toString());

                     i = i + 500;
                  }
                  QMessageBox::information( nullptr, tr( "PDF" ), tr( "PDF enregistré !\n\n" ) );
}


void MainWindow::on_modifier_clicked()
{

        // Retrieve the modified data from the form
          int id = ui->ID->text().toInt();
          int quantite = ui->lineEdit_quant->text().toInt();
          QString lieu_rec=ui->lineEdit_lieu->text();
          QString ref;
          if(ui->radioButtonOUI->isChecked())
          {ref="oui";} else {ref="non";}

          if (ref.isEmpty() || ref.isNull())
            {
                QMessageBox::warning(this, "Error", "Please select a value for the Refrigerator field.");
                return;
            }
        QDate dateexp=ui->dateEditEXP->date();

          QDate daterec=ui->dateEditREC->date();

          QDate currentDate = QDate::currentDate();
         if (daterec > currentDate) {
              QMessageBox::warning(this, "Error", "Saisir une valeur dans le passé pour la date de recuperation .");
              return; // dateNOM is in the past
          }

          QString NOM=ui->lineEdit_NOM->text();

          qDebug() << "ID ALIMENT" <<id;
          qDebug() << "QUANTITE"<<quantite;
          qDebug() << "LIEU RECUPERATION"<<lieu_rec;
          qDebug() << "REFRIGERATOR"<<ref;
          qDebug() << "DATE EXPIRATION!"<<dateexp;
          qDebug() << "DATE RECUPERATION"<<daterec;
          qDebug() <<"NOMination"<<NOM;

          // Create an aliment object with the modified data
          aliment a(id,quantite,dateexp,daterec,lieu_rec,ref,NOM);

          // Call the modifier function
          bool success = a.modifier();

          if (success) {
              QMessageBox::information(this, "Success", "Record modified successfully.");
              ui->tabStock->setModel(a.afficher()) ;
          } else {
              QMessageBox::warning(this, "Error", "Failed to modify record.");
          }
    }


void MainWindow::on_pushButton_31_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_35_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_34_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_pushButton_33_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_pushButton_32_clicked()
{
     ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_logout_menu_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_Clear_3_clicked()
{
    ui->le_nom_K->clear();
    ui->le_mail_k->clear();
    ui->le_date_k->clear();
    ui->le_tel_k->clear();
    ui->le_adress_k->clear();
    ui->le_disp_k->clear();
    ui->le_desc_k->clear();
    ui->le_nb_m_k->clear();

}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    QDate datee=ui->calendarWidget->selectedDate();
            qDebug() << datee;
            QDate d= datee;
            qDebug() << d;
            QSqlQuery query;
            query.prepare("SELECT id,nom,mail,datenaiss from benevole where datenaiss = :date");
            query.bindValue(":date",d);
            query.exec();
            QSqlQueryModel * model=new QSqlQueryModel();


                  model->setQuery(query);
                  model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
                  model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
                  model->setHeaderData(2, Qt::Horizontal, QObject::tr("mail"));
                  model->setHeaderData(3, Qt::Horizontal, QObject::tr("datenaiss"));

                 ui->liste_cal->setModel(model);

}



void MainWindow::on_tabWidget_5_currentChanged(int index)
{
    QChart *chart = new QChart();
            QSqlQueryModel * model= new QSqlQueryModel();
                                                model->setQuery("SELECT adesse FROM Benevole ");
                                                float e=model->rowCount();
                                                model->setQuery("SELECT mission FROM Benevole ");
                                                float ee=model->rowCount();
                                                float total=e+ee;
                                                QString a=QString("adresse"+QString::number((e*100)/total,'f',2)+"%" );
                                                QString b=QString("mission"+QString::number((ee*100)/total,'f',2)+"%" );
                                                QPieSeries *series = new QPieSeries();
                                                series->append(a,e);
                                                series->append(b,ee);
                                        if (e!=0)
                                        {QPieSlice *slice = series->slices().at(0);
                                         slice->setLabelVisible();
                                         slice->setPen(QPen());}
                                        if ( ee!=0)
                                        {
                                                 // Add label, explode and define brush for 2nd slice
                                                 QPieSlice *slice1 = series->slices().at(1);
                                                 //slice1->setExploded();
                                                 slice1->setLabelVisible();
                                        }
                                                // Create the chart widget
                                        QChartView *chartView = new QChartView(chart, this);
                                                          chartView->setRenderHint(QPainter::Antialiasing);
                                                          chartView->resize(800, 600);
                                                          // Add data to chart with title and hide legend
                                                chart->addSeries(series);
                                                chart->setTitle("Pourcentage de l'origine des benevoles et ses missions");
                                                chart->legend()->hide();
                                                // Used to display the chart
                                                QVBoxLayout *layout = new QVBoxLayout(ui->frame9);
                                                                  layout->addWidget(chartView);
                                                                  ui->frame9->setLayout(layout);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString nom;
        QSqlQuery query;

        // affichage du nom
        query.prepare("Select nom from benevole ORDER BY mission");
        if(query.exec())
        {
            while(query.next())
            {
                nom=query.value(0).toString();

            }

        }
        qDebug()<<nom;
        QByteArray name(nom.toUtf8(),16)    ;
        A.write_to_arduino(name);




        // affichage d'adresse
            QString adresse;

        query.prepare("Select adresse from benevole ORDER BY mission");
        if(query.exec())
        {
            while(query.next())
            {
                adresse=query.value(0).toString();

            }

        }
        qDebug()<<adresse;
        QByteArray adress(adresse.toUtf8(),16);
        A.write_to_arduino(adress);
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    Benevole B1 ;

    if(arg1 =="Adresse")
    {
    QSqlQueryModel* model = B1.tri_adresse();
    ui->liste_2->setModel(model); }
    else if(arg1 =="Disponibilité")
    {
        QSqlQueryModel* model = B1.tri_dispo();
        ui->liste_2->setModel(model);
    }
    else if (arg1 == "Mission")
    {
        QSqlQueryModel* model = B1.tri_mission();
        ui->liste_2->setModel(model); //
    }
}

void MainWindow::on_le_chat_returnPressed()
{
    QString text,space="";
        QString msg=ui->le_chat->text();
        ui->chatbot->appendPlainText(space);
        ui->chatbot->appendPlainText(msg);
        ui->chatbot->clear();
        QString chemin;

        if(msg=="salut" || msg=="bonjour" || msg=="yo"){

            text="Bienvenu utilisateur,quel type d'aide voulez vous obtenir ? "
                 "Utilisation de l'applicationObjectif de l'application||Information sur l'application";

        }
        else if(msg=="objectif de l'application")
        {


            text="L'application healthshare est dédiée à la pour gérer des entités et des modules variés, tels que les employés, les donataires et les donateurs, afin de fournir un outil intuitif et efficace pour améliorer la gestion du centre et coordonner leurs activités de manière optimale afin de réduire le temps et d'augmenter la productivité des processus.  ";
        }
        else if(msg=="utilisation de l'application")
        {

            text="...";
        }
        else if(msg=="information sur l'application")
        {

            text="Cette application est développée par l'équipe Crewative;Maram Bouaziz responsable gestion stock,Yasmine Temimi responsable gestion donnateur,Raouf Mahmoudi responsable gestion donnataire,Mohamed Akrem Bachta responsable gestion employe et Rayene ksouri responsable gestion benevole.En utilisant l'application Qt et le language C++.";
        }
        else if(msg=="9riitchi kawwantchi 3arrastchi")
        {
    text="W lalaaalaa laa la laaaaaa";
        }
        else if(msg=="chantez")
        {


            text="DRRRRRRR chtibidi dob dob dob yes yes yes yes chtib chtib chtibididob";
        }
        else if(msg=="how to get a qrcode" || msg=="qrcode")
        {

            text="Go to ""client"" and click on the button ""generateQR""";
        }
        else if(msg=="how to generate a pdf" || msg=="pdf")
        {

            text="Go to ""Afficher employe"" and click on the button ""generate""";
        }
        else if(msg=="sorry" || msg=="excuse me")
        {

            text="Don't worry about it friend";
        }
        else if(msg=="tell me" || msg=="talk")
        {

            text="Waht do you want to talk about mate? need help in somthing? or just company?";
        }
        else if(msg=="money" || msg=="salary")
        {

            text="We want  money don't we? work hard until you deserve it!";
        }
        else if(msg=="bored" ||  msg=="i'm bored")
        {

            text="Sorry for that , a cup of coffee would help i guess!";
        }
        else if(msg=="thanks" || msg=="thank you")
        {

            text="You're welcome i'm alwasy at your service";
        }
        else if(msg=="fuck you" || msg=="shit" || msg=="fuck" || msg=="damn" || msg=="stupid" || msg=="idiot")
        {

            text="How dare you!Please Do not use cursing words it can hurt others like it did to me!";
        }
        else if(msg=="you are sweet" || msg=="u're sweet" )
        {

            text="I know that but i'm only  sweet with yosr ";
        }
        else if(msg=="i love you" || msg=="i like you")
        {

            text="i love you too, bro !";
        }
        else if(msg=="" || msg=="?" || msg==" ")
        {

            text="?";
        }
        else{

            text="Sorry i didnt understant , please try again";
        }

        ui->le_chat->clear();
        ui->chatbot->appendPlainText(space);
        ui->chatbot->appendPlainText(text);
}

void MainWindow::on_logout_2_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_logout_3_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_logout_4_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_logout_5_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_logout_6_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_logout_7_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_logout_8_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_logout_9_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::AJOUT()
{
    QByteArray data;
    QDateTime DATEALERT = QDateTime::currentDateTime();
    QSqlQuery qry;

//    QString DataAsString = QTextCodec::codecForMib(106)->toUnicode(data);
//    qDebug() << "Data received from Arduino:" << DataAsString;

    qDebug() << "data fel ajout" << A.data;
    QList<QByteArray> dataList = A.data.split(',');
    for(int i = 0; i < dataList.size(); i++) {

        QByteArray dataItem = dataList[i].trimmed();

       if(!dataItem.isEmpty()) {

        int value = dataList[i].toInt();
        qDebug() << "kbal 300" << dataList[i];

int number = value ;
QString stringn = QString::number(number) ;
ui->gaz->setText(stringn);
            if(value > 300) {
            qry.prepare("INSERT INTO GAZ2 (QUALITE, DATEALERT) VALUES (:QUALITE, :DATEALERT)");
            qry.bindValue(":QUALITE", value);
            qry.bindValue(":DATEALERT", DATEALERT);
             qDebug() << "execcc"<<qry.exec();
            if(qry.exec()) {

                qDebug() << "SUCCESSFULLY ADDED";
            } else {
                qDebug() << "Error adding record: " << qry.lastError().text();
            }



            }

        }
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Voulez vous afficher la date dont la plus forte concentration de gaz ?");
                msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                int confirmation = msgBox.exec();

                if (confirmation == QMessageBox::Yes)
                {
                    // Convert the result of A.recuperer() to a QByteArray and send it to the Arduino
                    QByteArray message = QByteArray::fromStdString(A.recuperer().toStdString());
                    A.write_to_arduino(message);
                }
}

void MainWindow::on_button_sup_5_clicked()
{
    ui->le_id->clear();
    ui->le_nom->clear();
    ui->le_fonction->clear();
    ui->le_adresse->clear();
    ui->le_email->clear();
    ui->le_num_tel->clear();
    ui->le_mdp->clear();
    ui->le_droit_daccess->clear();
    ui->le_satut->clear();
    ui->le_RFID->clear();
}
