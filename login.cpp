#include "login.h"
#include "ui_login.h"
#include "dashboard.h"
#include <QDebug>


Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    consulta=new QSqlQuery;
    ui->labelErrorMess->setVisible(false);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_login_clicked()
{
    if(ui->lineEdit_user->text().isEmpty() || ui->lineEdit_pass->text().isEmpty()){

        ui->labelErrorMess->setVisible(true);
        ui->labelErrorMess->setText("Usuario y contraseña son requeridos");
        ui->lineEdit_user->setFocus();

    }else{
        ControladorUsuario* l = new ControladorUsuario();
        QString pwd = l->encrypt(ui->lineEdit_pass->text());
        QString res = l->ctrIngresoUsuario(ui->lineEdit_user->text(),pwd);
        if(res.length()>1){
            this->close();
            Dashboard* d = new Dashboard(res);
            d->show();
        }else if(res == "1"){
            ui->labelErrorMess->setVisible(true);
            ui->labelErrorMess->setText("usuario/contraseña invalidos");
            ui->lineEdit_user->setFocus();
        }else{
            ui->labelErrorMess->setVisible(true);
            ui->labelErrorMess->setText("usuario inactivo");
            ui->lineEdit_user->setFocus();
        }
    }

    cu = new ControladorUsuario();
    cu->ctrUltimoLogin(ui->lineEdit_user->text());
}
