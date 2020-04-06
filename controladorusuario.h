#ifndef CONTROLADORUSUARIO_H
#define CONTROLADORUSUARIO_H

#include <QObject>
#include <QSqlQueryModel>
#include "modelousuario.h"
#include "usuario.h"


class ControladorUsuario
{
public:
    ControladorUsuario();
    QString ctrIngresoUsuario(QString mValor, QString pass);
    bool ctrCrearUsuario(QString mNombre, QString mUsuario, QString mPass, int mPerfil, QString mFoto);
    bool existeUsuario(QString usuario);
    bool ctrUltimoLogin(QString usuario);
    bool ctrActivarUsuario(QString usuario, int estado);
    int ctrEstadoUsuario(QString usuario);
    QString encrypt(QString pwd);
    bool ctrActualizarUsuario(QString usuario, QString nombre, int perfil, QString foto);
    bool ctrActualizarUsuario(QString usuario, QString nombre, QString pass, int perfil, QString foto);
    bool ctrEliminarUsuario(QString usuario);
    Usuario getUsuario(QString usuario);
private:
 ModeloUsuario* mu;

};

#endif // CONTROLADORUSUARIO_H
