#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QString>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include "headers.h"
#include "controladorusuario.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dashboard; }
QT_END_NAMESPACE

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    Dashboard(QString ruta, QWidget *parent = nullptr);
    ~Dashboard();



private slots:
    void on_treeWidget_itemPressed(QTreeWidgetItem *item, int column);
    void createActionsButtons(int fila, int estado);
    void cargarImage(QString r);
    void on_btnUserAdd_clicked();
    void getUsuarios();
    void deleteUsuario();
    void editUsuario();
    void estadoUsuario();
    void addRowUsuario(QTableWidgetItem* mNombreItem,
                       QTableWidgetItem* mUsuarioItem,
                       QTableWidgetItem* mPerfilItem,
                       QTableWidgetItem* mUltimoLoginItem,
                       QTableWidgetItem* mFechaItem,
                       int mEstado);

    QString getItem(QTableWidget *tabla);
    int getEstado(QString usuario);
    void on_pushButtonSalir_clicked();


private:
    Ui::Dashboard *ui;
    ControladorUsuario *cu;
    QSqlQuery *consulta;
    QSqlQueryModel *modelo;
    QPushButton* btn_eliminar;
    QPushButton* btn_editar;
    QPushButton* btn_estado;
    int mfila;
    enum Columnas
    {
        N, NOMBRE, USUARIO, PERFIL, FOTO, ESTADO, ULTIMO_LOGIN, ACCIONES
    };
};
#endif // DASHBOARD_H
