#include "usuario.h"


Usuario::Usuario(QString nombre, QString usuario, int perfil,
                 int estado, QString ultimoLogin, QString fecha)
{
    mNombre=nombre;
    mUsuario=usuario;
    mPerfil=perfil;
    mEstado=estado;
    mUltimoLogin=ultimoLogin;
    mFecha=fecha;
}

Usuario::Usuario(QString nombre, QString pass, int perfil, QString foto)
{
    mNombre=nombre;
    mPass=pass;
    mPerfil=perfil;
    mfoto=foto;

}

Usuario::Usuario()
{

}

QString Usuario::nombre() const
{
    return mNombre;
}

void Usuario::setNombre(const QString &nombre)
{
    mNombre = nombre;
}

QString Usuario::usuario() const
{
    return mUsuario;
}

void Usuario::setUsuario(const QString &usuario)
{
    mUsuario=usuario;
}

QString Usuario::pass() const
{
    return mPass;
}

void Usuario::setPass(const QString &pass)
{
    mPass=pass;
}

int Usuario::perfil() const
{
    return mPerfil;
}

void Usuario::setPerfil(int perfil)
{
    mPerfil = perfil;
}

int Usuario::estado() const
{
    return mEstado;
}

void Usuario::setEstado(int estado)
{
    mEstado = estado;
}

QString Usuario::ultimoLogin() const
{
    return mUltimoLogin;
}

void Usuario::setUltimoLogin(const QString &ultimoLogin)
{
    mUltimoLogin = ultimoLogin;
}

QString Usuario::fecha() const
{
    return mFecha;
}

void Usuario::setFecha(const QString &fecha)
{
    mFecha = fecha;
}

QString Usuario::foto() const
{
    return mfoto;
}

void Usuario::setFoto(const QString &foto)
{
    mfoto=foto;
}


