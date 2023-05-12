#include "arduino.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlDatabase>
#include <QDateTime>
Arduino::Arduino()
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial=new QSerialPort;
}
QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}
QSerialPort *Arduino::getserial()
{
    return serial;
}
int Arduino::connect_arduino()
{
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
        if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
            if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier()
                    == arduino_uno_producy_id) {
                arduino_is_available = true;
                arduino_port_name=serial_port_info.portName();
            } } }
    qDebug() << "arduino_port_name is :" << arduino_port_name;
    if(arduino_is_available){ // configuration de la communication ( débit...)
        serial->setPortName(arduino_port_name);
        if(serial->open(QSerialPort::ReadWrite)){
            serial->setBaudRate(QSerialPort::Baud9600); // débit : 9600 bits/s
            serial->setDataBits(QSerialPort::Data8); //Longueur des données : 8 bits,
            serial->setParity(QSerialPort::NoParity); //1 bit de parité optionnel
            serial->setStopBits(QSerialPort::OneStop); //Nombre de bits de stop : 1
            serial->setFlowControl(QSerialPort::NoFlowControl);
            return 0;
        }
        return 1;
    }
    return -1;
}
int Arduino::close_arduino()
{
    if(serial->isOpen()){
        serial->close();
        return 0;
    }
    return 1;
}
QByteArray Arduino::read_from_arduino()
{
    if(serial->isReadable()){
        data=serial->readAll(); //récupérer les données reçues
        return data;
    }
}
int Arduino::write_to_arduino( QByteArray d)

{
    if(serial->isWritable()){
        serial->write(d);  // envoyer des donnés vers Arduino
    }else{
        qDebug() << "Couldn't write to serial!";
    }
}
QString Arduino::recuperer(){
     QSqlDatabase bd = QSqlDatabase::database();
     QSqlQuery query;
     query.prepare("SELECT DATEALERT FROM GAZ2 ORDER BY QUALITE");
     //query.bindValue(":id", 1);
     if (query.exec() && query.next()) {
        QDateTime DATEE;
       DATEE = query.value(0).toDateTime();

         // If the query executed successfully and returned at least one result row
         return DATEE.toString(); // Return the value of the first field in the first row as a string
     }
     else {
         return ""; // Query execution failed or returned no rows
     }
 }
