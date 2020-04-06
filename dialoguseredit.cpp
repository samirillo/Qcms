#include "dialoguseredit.h"
#include "ui_dialoguseredit.h"
#include <QImage>
#include <QFileDialog>
#include <QDir>
#include <dashboard.h>
#include "controladorusuario.h"


DialogUserEdit::DialogUserEdit(QString usr, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUserEdit)
{
    ui->setupUi(this);
    Usuario u;
    cu = new ControladorUsuario();
    u=cu->getUsuario(usr);
    QImage imagen;
    imagen.load(u.foto());
    ui->lineEditNombre->setText(u.nombre());
    ui->lineEditUsuario->setText(usr);
    ui->lineEditPassword->setText(u.pass());
    ui->comboBoxPerfiles->setCurrentIndex(u.perfil());
    ui->labelUserImage->setPixmap(QPixmap::fromImage(imagen));
    ui->labelImagePath->setText(u.foto());
}

DialogUserEdit::~DialogUserEdit()
{
    delete ui;
}

Usuario DialogUserEdit::getUsuario()
{
    Usuario u;

    u.setNombre(ui->lineEditNombre->text());
    u.setUsuario(ui->lineEditUsuario->text());
    u.setPerfil(ui->comboBoxPerfiles->currentIndex());
    return u;
}

void DialogUserEdit::on_pushButtonResetPassword_clicked()
{
    ui->lineEditPassword->setDisabled(false);
    ui->lineEditPassword->setText("");
    ui->lineEditPassword->setFocus();
    res=1;
}

void DialogUserEdit::on_pushButtonUpload_clicked()
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

void DialogUserEdit::on_pushButtonActualizar_clicked()
{
    QString nombre=ui->lineEditNombre->text();
    QString usuario=ui->lineEditUsuario->text();
    QString pass = cu->encrypt(ui->lineEditPassword->text());
    int perfil=ui->comboBoxPerfiles->currentIndex();
    QString foto=ui->labelImagePath->text();
    cu = new ControladorUsuario();
    if(res==1){

        if(cu->ctrActualizarUsuario(usuario,nombre,pass,perfil,foto)){
            QMessageBox::information(
                           this,
                           tr("Qcms"),
                           tr("El usuario se ha actualizado correctamente.") );
            this->close();
        }else{
            QMessageBox::critical(
                           this,
                           tr("Qcms"),
                           tr("Ha ocurrido un error, al actualizar usuario.") );
            this->close();
        }
    }else{
        if(cu->ctrActualizarUsuario(usuario,nombre,perfil,foto)){
            QMessageBox::information(
                           this,
                           tr("Qcms"),
                           tr("El usuario se ha actualizado correctamente.") );
            this->close();
        }else{
            QMessageBox::critical(
                           this,
                           tr("Qcms"),
                           tr("Ha ocurrido un error, al actualizar usuario .") );
            this->close();
        }
    }
}

void DialogUserEdit::on_pushButtonCancelar_clicked()
{
    this->close();
}

void DialogUserEdit::on_lineEditPassword_editingFinished()
{
    ui->lineEditPassword->setDisabled(true);
}
