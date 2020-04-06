#ifndef LOGIN_H
#define LOGIN_H

#include "controladorusuario.h"
#include "headers.h"
#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);


    ~Login();

private slots:
    void on_pushButton_login_clicked();

private:
    Ui::Login *ui;
    QSqlQuery *consulta;
    ControladorUsuario* cu;
};

#endif // LOGIN_H
