#include "dashboard.h"
#include "login.h"
#include "headers.h"
#include "connection.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!initConexion()) {
         return 1;
     }else{
        Login w;

        w.show();

        return a.exec();

    }








}
