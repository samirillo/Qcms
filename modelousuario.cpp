#include "modelousuario.h"
#include <QDateTime>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QDebug>
#include <QTextCodec>

ModeloUsuario::ModeloUsuario()
{
    consulta = new QSqlQuery;
}

QSqlRecord ModeloUsuario::mdlMostrarUsuario(QString mTabla, QString mItem, QString mValor)
{
    consulta->clear();
    consulta->prepare("SELECT * FROM "+mTabla+" WHERE "+mItem+" =:mItem");
    consulta->bindValue(":mItem",mValor);
    consulta->exec();

    consulta->first();

    return consulta->record();
}

bool ModeloUsuario::mdlCrearUsuario(QString mTabla, QString mNombre, QString mUsuario, QString mPass, int mPerfil, QString mFoto)
{
    QString mFecha = FechaIngreso();
    if(mFoto == "subir una foto"){
        mFoto ="://images/user-secret.svg";
    }
    QString perfil;
    switch (mPerfil) {
    case 1:
        perfil="Administrador";
        break;
    case 2:
        perfil="Especial";
        break;
    case 3:
        perfil="Vendedor";
        break;
    default:
        break;
    }
    consulta->clear();
    consulta->prepare("INSERT INTO "+mTabla+"(nombre, usuario, password, perfil, foto, estado, fecha) "
                      "VALUES(:nombre, :usuario, :password, :perfil, :foto, :estado, :fecha)");
    consulta->bindValue(":nombre", mNombre);
    consulta->bindValue(":usuario", mUsuario);
    consulta->bindValue(":password", mPass);
    consulta->bindValue(":perfil", perfil);
    consulta->bindValue(":foto", mFoto);
    consulta->bindValue(":estado", 1);
    consulta->bindValue(":fecha", mFecha);

   return  consulta->exec();


}

bool ModeloUsuario::mdlExisteUsuario(QString usuario)
{
    bool res;
    consulta->clear();
    consulta->prepare("SELECT * FROM usuarios WHERE usuario = :usuario");

    consulta->bindValue(":usuario",usuario);
    consulta->exec();

    res=consulta->next();
    return res;
}

bool ModeloUsuario::mdlUltimoLogin(QString usuario)
{
    QString login=FechaIngreso();
    consulta->clear();
    consulta->prepare("UPDATE usuarios SET ultimo_login = :login WHERE usuario = :usuario");
    consulta->bindValue(":usuario",usuario);
    consulta->bindValue(":login", login);
    return consulta->exec();
}

bool ModeloUsuario::mdlActivarUsuario(QString usuario, int estado)
{
    consulta->clear();
    consulta->prepare("UPDATE usuarios SET estado = :estado WHERE usuario = :usuario");
    consulta->bindValue(":usuario",usuario);
    consulta->bindValue(":estado", estado);
    return consulta->exec();
}

int ModeloUsuario::mdlEstadoUsuario(QString usuario)
{

    consulta->clear();
    consulta->prepare("SELECT usuario,estado FROM usuarios WHERE usuario =:usuario");
    consulta->bindValue(":usuario",usuario);

  consulta->exec();
  consulta->next();

  int estado = consulta->value(1).toInt();

  return estado;
}



bool ModeloUsuario::mdlActualizarUsuario(QString usuario, QString nombre, int mPerfil, QString foto)
{
    consulta->clear();
    consulta->prepare("UPDATE usuarios SET nombre =:nombre, perfil =:perfil, foto=:foto WHERE usuario = :usuario");
    consulta->bindValue(":usuario",usuario);
    consulta->bindValue(":nombre",nombre);
    QString perfil;
    switch (mPerfil) {
    case 1:
        perfil="Administrador";
        break;
    case 2:
        perfil="Especial";
        break;
    case 3:
        perfil="Vendedor";
        break;
    default:
        break;
    }
    consulta->bindValue(":perfil",perfil);
    consulta->bindValue(":foto",foto);
    return consulta->exec();
}

bool ModeloUsuario::mdlActualizarUsuario(QString usuario, QString nombre, QString pass, int mPerfil, QString foto)
{
    QString perfil;
    switch (mPerfil) {
    case 1:
        perfil="Administrador";
        break;
    case 2:
        perfil="Especial";
        break;
    case 3:
        perfil="Vendedor";
        break;
    default:
        break;
    }
    consulta->clear();
    consulta->prepare("UPDATE usuarios SET nombre =:nombre, password=:pass, perfil =:perfil, foto=:foto WHERE usuario = :usuario");
    consulta->bindValue(":usuario",usuario);
    consulta->bindValue(":nombre",nombre);
    consulta->bindValue(":pass",pass);
    consulta->bindValue(":perfil",perfil);
    consulta->bindValue(":foto",foto);

    return consulta->exec();
}

bool ModeloUsuario::mdlEliminarUsuario(QString usuario)
{
    consulta->clear();
    consulta->prepare("DELETE FROM usuarios WHERE usuario =:usuario");
    consulta->bindValue(":usuario",usuario);

    return consulta->exec();
}

Usuario ModeloUsuario::getUsuario(QString usuario)
{
    consulta->clear();
    consulta->prepare("SELECT * FROM usuarios WHERE usuario =:usuario");
    consulta->bindValue(":usuario",usuario);
    consulta->exec();
    consulta->next();
    QString nombre=consulta->value(1).toString();


   QByteArray ba = consulta->value(3).toByteArray();

   QString pass = QString(ba.toHex());

    QString p = consulta->value(4).toString();;
    int perfil;
    if(p=="Administrador"){
        perfil=1;
    }
    if(p=="Especial"){
        perfil=2;
    }
    if(p=="Vendedor"){
        perfil=3;
    }
    QString foto=consulta->value(5).toString();
    u = new Usuario(nombre,pass,perfil,foto);

    return *u;
}

QString ModeloUsuario::FechaIngreso()
{
    QString fecha = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    return fecha;
}





