#ifndef DIALOGUSERADD_H
#define DIALOGUSERADD_H

#include <QDialog>
#include "usuario.h"
#include "modelousuario.h"
#include "controladorusuario.h"

namespace Ui {
class DialogUserAdd;
}

class DialogUserAdd : public QDialog
{
    Q_OBJECT

public:
    explicit DialogUserAdd(QWidget *parent = nullptr);
    ~DialogUserAdd();
    Usuario addUsuario();
    int response();


private slots:
    void on_pushButtonCancelar_clicked();

    void on_pushButtonGuardar_clicked();

    void on_pushButtonUpload_clicked();

    bool existeUsuario();

    void on_lineEditUsuario_editingFinished();

private:
    Ui::DialogUserAdd *ui;
    int res;
    ModeloUsuario* mu;
    ControladorUsuario* cu;
};

#endif // DIALOGUSERADD_H
