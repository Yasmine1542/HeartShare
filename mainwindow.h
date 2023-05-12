#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "Employee.h"
#include "arduino.h"
#include "donateur.h"
#include "donataires.h"
#include "benevole.h"

#include <aliment.h>
#include <notification.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_le_add_clicked();

    void on_bouton_supp_clicked();

    void on_le_modifier_clicked();

    void on_butt_pdf_clicked();

    void on_tri_id_clicked();

    void on_tri_nom_clicked();

    void on_stat_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_connexion_clicked();

    void on_logout_clicked();

    void on_reset_clicked();

    void on_tri_fonction_clicked();

    void update_RFID();

    void on_button_add_3_clicked();

    void on_button_add_4_clicked();

    void on_button_sup_4_clicked();

    void on_pushButton_93_clicked();

    void on_button_sup_3_clicked();

    void on_searchLineEdit_3_textChanged(const QString &arg1);

    void on_comboBox_3_activated(const QString &arg1);

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_supprimer_M_clicked();

    void on_ajouter_M_clicked();

    void on_modifier_M_clicked();

    void on_Clear_M_clicked();

    void on_pushButton_M_clicked();

    void on_searchlineEdit_M_textChanged(const QString &arg1);

    void on_comboBox_M_activated(const QString &arg1);

    void on_PDF_M_clicked();

    void on_tabStock_activated(const QModelIndex &index);

    void on_tabWidget_3_currentChanged(int index);

    void on_ajout_2_clicked();

    void on_supprimer_2_clicked();

    void on_modifier_2_clicked();

    void on_pushButton_11_clicked();

    void on_Clear_2_clicked();

    void on_msg_c_3_clicked();
    void postrequest(QString smsmsg,QString phonenumber) ;

    void on_le_sss_3_returnPressed();

    void on_comboBox_tri_2_currentIndexChanged(const QString &arg1);

    void on_Button_stat_3_clicked();

    void on_Button_stat_4_clicked();

    void on_supprimer_his_2_clicked();

    void on_msg_c_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_supp_clicked();

    void on_pushButton_chercher_clicked();

    void on_le_chercher_textChanged(const QString &arg1);

    void on_pdf_clicked();


    void on_modifier_clicked();


    void on_pushButton_31_clicked();

    void on_pushButton_35_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_33_clicked();

    void on_pushButton_32_clicked();



    void on_logout_menu_clicked();

    void on_Clear_3_clicked();

    void on_calendarWidget_clicked(const QDate &date);


    void on_tabWidget_5_currentChanged(int index);

    void on_pushButton_3_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_le_chat_returnPressed();



    void on_logout_2_clicked();

    void on_logout_3_clicked();

    void on_logout_4_clicked();

    void on_logout_5_clicked();

    void on_logout_6_clicked();

    void on_logout_7_clicked();

    void on_logout_8_clicked();

    void on_logout_9_clicked();
 void AJOUT();
 void on_pushButton_4_clicked();

 void on_button_sup_5_clicked();



private:
    Ui::MainWindow *ui;
    Employee E;

    Donateur D ;
     Donataire m;
     aliment a;
     Benevole b;
       notification n;
    QByteArray data;
    Arduino A;
    QString RFID="";
};




#endif // MAINWINDOW_H
