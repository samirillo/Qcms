#ifndef MODELOUSUARIO_H
#define MODELOUSUARIO_H

#include <QObject>
#include "headers.h"
#include "usuario.h"


class ModeloUsuario
{
public:
    ModeloUsuario();
    QSqlRecord mdlMostrarUsuario(QString mTabla, QString mItem, QString mValor);
    bool mdlCrearUsuario(QString mTabla, QString mNombre, QString mUsuario, QString mPass, int mPerfil, QString mFoto);
    bool mdlExisteUsuario(QString usuario);
    bool mdlUltimoLogin(QString usuario);
    bool mdlActivarUsuario(QString usuario, int estado);
    int  mdlEstadoUsuario(QString usuario);
    bool mdlActualizarUsuario(QString usuario, QString nombre, int perfil, QString foto);
    bool mdlActualizarUsuario(QString usuario, QString nombre, QString pass, int mPerfil, QString foto);
    bool mdlEliminarUsuario(QString usuario);
    Usuario getUsuario(QString usuario);
private:
    QSqlQuery *consulta;
    Usuario *u;
    QString FechaIngreso();
};

#endif // MODELOUSUARIO_H
