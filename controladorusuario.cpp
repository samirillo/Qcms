#include "controladorusuario.h"
#include <QList>
#include <QSqlRecord>
#include <QCryptographicHash>


ControladorUsuario::ControladorUsuario()
{

}

QString ControladorUsuario::ctrIngresoUsuario(QString mValor, QString pass)
{
    mu=new ModeloUsuario();
    QString mTabla="usuarios";
    QString mItem="usuario";
    QString res="1";
    QSqlRecord respuesta=mu->mdlMostrarUsuario(mTabla,mItem,mValor);


   if(pass == respuesta.value(3).toString() && respuesta.value(6).toInt() == 1){
       res = respuesta.value(5).toString();
        return res;
   }else if(pass == respuesta.value(3).toString() && respuesta.value(6).toInt() != 1){
       res = "0";
       return res;
   }else{

       return res;
   }


}

bool ControladorUsuario::ctrCrearUsuario(QString mNombre, QString mUsuario, QString mPass, int mPerfil, QString mFoto)
{
    mu=new ModeloUsuario();
    QString mTabla="usuarios";

    if(mu->mdlCrearUsuario(mTabla, mNombre, mUsuario, mPass, mPerfil, mFoto)){
        return 1;
    }else{
        return 0;
    }
}

bool ControladorUsuario::existeUsuario(QString usuario)
{
    mu= new ModeloUsuario();
bool valido = mu->mdlExisteUsuario(usuario);
    if(valido){
        return true;
    }
}

bool ControladorUsuario::ctrUltimoLogin(QString usuario)
{
    mu= new ModeloUsuario();
   if(mu->mdlUltimoLogin(usuario)){
       return true;
   }
}

bool ControladorUsuario::ctrActivarUsuario(QString usuario, int estado)
{
    mu = new ModeloUsuario;
    return mu->mdlActivarUsuario(usuario, estado);
}

int ControladorUsuario::ctrEstadoUsuario(QString usuario)
{

    mu = new ModeloUsuario();
     int estado = mu->mdlEstadoUsuario(usuario);
     return estado;
}

QString ControladorUsuario::encrypt(QString pwd)
{

       QByteArray hash = QCryptographicHash::hash(pwd.toLocal8Bit(), QCryptographicHash::Md5);

       return hash;

}

bool ControladorUsuario::ctrActualizarUsuario(QString usuario, QString nombre, int perfil, QString foto)
{
    mu = new ModeloUsuario();
    if(mu->mdlActualizarUsuario(usuario, nombre, perfil, foto)){
        return true;
    }else{
        return false;
    }


}

bool ControladorUsuario::ctrActualizarUsuario(QString usuario, QString nombre, QString pass, int perfil, QString foto)
{
    mu = new ModeloUsuario();
     if(mu->mdlActualizarUsuario(usuario, nombre, pass,  perfil, foto)){
         return true;
     }else{
         return false;
     }
}

bool ControladorUsuario::ctrEliminarUsuario(QString usuario)
{
    mu = new ModeloUsuario();
    if(mu->mdlEliminarUsuario(usuario)){
        return true;
    }else{
        return false;
    }
}

Usuario ControladorUsuario::getUsuario(QString usuario)
{
    Usuario u;
    mu =new  ModeloUsuario();
    u= mu->getUsuario(usuario);
    return u;
}






