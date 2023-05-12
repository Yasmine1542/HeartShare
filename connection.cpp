#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");//test
db.setUserName("system");//akrem
db.setPassword("titta1500");//akrem
if (db.open())
test=true;





    return  test;
}
