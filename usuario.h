#ifndef USUARIO_H
#define USUARIO_H
#include <QString>

class Usuario
{
public:
    Usuario(QString nombre, QString usuario, int perfil, int estado, QString ultimoLogin, QString fecha);
    Usuario(QString nombre, QString pass, int perfil, QString foto);
    Usuario();

    QString nombre() const;
    void setNombre(const QString& nombre);
    QString usuario() const;
    void setUsuario(const QString& usuario);
    QString pass()const;
    void setPass(const QString& pass);
    int perfil()const;
    void setPerfil(int perfil);
    int estado()const;
    void setEstado(int estado);
    QString ultimoLogin()const;
    void setUltimoLogin(const QString& ultimoLogin);
    QString fecha()const;
    void setFecha(const QString& fecha);
    QString foto() const;
    void setFoto(const QString& foto);

private:
    int mId;
    QString mNombre;
    QString mUsuario;
    int mPerfil;
    int mEstado;
    QString mUltimoLogin;
    QString mFecha;
    QString mPass;
    QString mfoto;

};

#endif // USUARIO_H
