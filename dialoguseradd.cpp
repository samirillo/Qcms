#include "dialoguseradd.h"
#include "ui_dialoguseradd.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <dashboard.h>
#include <QTableWidgetItem>
#include "controladorusuario.h"


DialogUserAdd::DialogUserAdd(QWidget *parent) : QDialog(parent),
    ui(new Ui::DialogUserAdd)
{
    ui->setupUi(this);
    res =0;
    ui->labelUsuarioError->setVisible(false);
}

DialogUserAdd::~DialogUserAdd()
{
    delete ui;
}

Usuario DialogUserAdd::addUsuario()
{
    Usuario u;
    QString fecha = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    u.setNombre(ui->lineEditNombre->text());
    u.setUsuario(ui->lineEditUsuario->text());
    u.setPerfil(ui->comboBoxPerfiles->currentIndex());
    u.setEstado(1);
    u.setUltimoLogin("");
    u.setFecha(fecha);
    res = 0;
    return u;
}

int DialogUserAdd::response()
{
    return res;
}




void DialogUserAdd::on_pushButtonCancelar_clicked()
{
    res=0;
    this->close();
}

void DialogUserAdd::on_pushButtonGuardar_clicked()
{
    if(ui->lineEditNombre->text().isEmpty() || ui->lineEditPassword->text().isEmpty() || ui->lineEditUsuario->text().isEmpty())
    {
        QMessageBox::warning(
                       this,
                       tr("Qcms"),
                       tr("Todos los campos son requeridos.") );
    }else{
        ControladorUsuario* cu = new ControladorUsuario();
QString pwd = cu->encrypt(ui->lineEditPassword->text());
        if(cu->ctrCrearUsuario(ui->lineEditNombre->text(),
                              ui->lineEditUsuario->text(),
                              pwd,
                              ui->comboBoxPerfiles->currentIndex(),
                              ui->labelImagePath->text()))
        {

            QMessageBox::information(
                           this,
                           tr("Qcms"),
                           tr("El usuario ha sido registrado correctamente.") );
            res=1;
            this->close();

        }else{

            QMessageBox::critical(
                           this,
                           tr("Qcms"),
                           tr("Ha ocurrido un error, comuniquese con soporte tecnico.") );
        }
    }
}

void DialogUserAdd::on_pushButtonUpload_clicked()
{
    QString nombreArchivo = QFileDialog::getOpenFileName(this, tr("elegir..."),"",tr("images(*.png *.jpg *.jpeg *.bmp *.gif)"));

    if(QString::compare(nombreArchivo, QString()) != 0){
        QImage imagen;
        bool valid = imagen.load(nombreArchivo);

        if(valid)
        {
            ui->labelUserImage->setPixmap(QPixmap::fromImage(imagen));
            QDir dir;

            ui->labelImagePath->setText(dir.absoluteFilePath(nombreArchivo));
        }else{
            QMessageBox::critical(
                           this,
                           tr("Qcms"),
                           tr("Ha ocurrido un error, debe cargar una archivo de imagen.") );
        }
    }


}

bool DialogUserAdd::existeUsuario()
{
    bool existe;
    cu = new ControladorUsuario;
    existe=cu->existeUsuario(ui->lineEditUsuario->text());
    if(existe){

        ui->lineEditUsuario->setStyleSheet("QLineEdit{ "
                                                "background-color:rgb(217,83,79);"
                                                "border: 2px solid red;"
                                                "padding: 0 8px;"
                                                "font-size: 16px;}"

                                                );
        ui->lineEditUsuario->setFocus();
        ui->labelUsuarioError->setVisible(true);
        ui->labelUsuarioError->setText("Usuario no disponible");
        return true;
    }else{
        ui->labelUsuarioError->setVisible(false);
        ui->lineEditUsuario->setStyleSheet("QLineEdit{ "
                                                "color:black"
                                                "padding: 0 8px;"
                                                "font-size: 8px;}"

                                                );
    }
}


void DialogUserAdd::on_lineEditUsuario_editingFinished()
{
    existeUsuario();
}
