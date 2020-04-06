#ifndef CONNECTION_H
#define CONNECTION_H

#include "headers.h"

bool initConexion()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("pos.db");
    if (!db.open())
    {
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text());

        return false;
    }

    return true;
}






#endif // CONNECTION_H
