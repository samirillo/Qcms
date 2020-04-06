#ifndef DIALOGUSEREDIT_H
#define DIALOGUSEREDIT_H

#include <QDialog>
#include "modelousuario.h"
#include "controladorusuario.h"

namespace Ui {
class DialogUserEdit;
}

class DialogUserEdit : public QDialog
{
    Q_OBJECT

public:
    explicit DialogUserEdit(QString usr, QWidget *parent = nullptr);
    ~DialogUserEdit();
    Usuario getUsuario();

private slots:
    void on_pushButtonResetPassword_clicked();

    void on_pushButtonUpload_clicked();

    void on_pushButtonActualizar_clicked();

    void on_pushButtonCancelar_clicked();

    void on_lineEditPassword_editingFinished();

private:
    Ui::DialogUserEdit *ui;
    ModeloUsuario* mu;
    ControladorUsuario* cu;
    int res;
};

#endif // DIALOGUSEREDIT_H
