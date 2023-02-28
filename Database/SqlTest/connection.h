#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("Test");
    db.setUserName("test");
    db.setPassword("test");
    bool ok = db.open();
    if(ok) qDebug() << "link success!";
    else
    {
        QMessageBox::critical(nullptr, "error", "link failed!");
        qDebug() << "error open database: " << db.lastError().text();
        return false;
    }

    return true;
}

#endif // CONNECTION_H
