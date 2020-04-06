#include "dashboard.h"
#include "ui_dashboard.h"
#include "dialoguseradd.h"
#include "dialoguseredit.h"
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QDebug>
Dashboard::Dashboard(QString ruta, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    setWindowFlags(Qt::FramelessWindowHint| Qt::WindowSystemMenuHint);
    cargarImage(ruta);
    getUsuarios();
    ui->tableWidgetUsers->horizontalHeader()->setVisible(true);
    ui->tableWidgetUsers->verticalHeader()->setVisible(true);
    ui->tableWidgetUsers->setRowHidden(0,true);

}

Dashboard::~Dashboard()
{
    delete ui;

}


void Dashboard::on_treeWidget_itemPressed(QTreeWidgetItem *item, int column)
{
    int i=0;
    QString modulo="";
    QList<QString> lista;
    lista <<"Inicio"<<"Dashboard"<<"Usuarios"<<"Categorias"<<"Productos"<<"Clientes"<<"Administrar"<<"Nueva"<<"Reportes";


    for(i=0; i<lista.count(); ++i )
    {
        modulo= item->text(column);
        if (lista[i] == modulo)
        {

            ui->stackedWidget->setCurrentIndex(i);
            switch(i)
            {
            case 0: ui->labelBreadcrum_0->setText("Inicio");break;
            case 1: ui->labelBreadcrum_1->setText("Inicio > Dashboard");break;
            case 2: ui->labelBreadcrum_2->setText("Inicio > Usuarios");break;
            case 3: ui->labelBreadcrum_3->setText("Inicio > Categorias");break;
            case 4: ui->labelBreadcrum_4->setText("Inicio > Productos");break;
            case 5: ui->labelBreadcrum_5->setText("Inicio > Clientes");break;
            case 6: ui->labelBreadcrum_6->setText("Inicio > Administrar Ventas");break;
            case 7: ui->labelBreadcrum_7->setText("Inicio > Nueva venta");break;
            case 8: ui->labelBreadcrum_8->setText("Inicio > Reportes");break;
            }

        }


    }





}

void Dashboard::createActionsButtons(int fila, int estado)
{
    btn_estado=new QPushButton();
    btn_editar=new QPushButton();
    btn_eliminar=new QPushButton();

    QPixmap editar("://images/edit.svg");
    QPixmap eliminar("://images/trash-alt.svg");
    QPixmap activo("://images/user-check.svg");
    QPixmap inactivo(":/images/user-alt-slash.svg");
    QIcon buttonEditar(editar);
    QIcon buttonEliminar(eliminar);
    QIcon buttonActivo(activo);
    QIcon buttonInactivo(inactivo);

    if(estado==1){
        btn_estado->setText("-");
        btn_estado->setIcon(buttonActivo);
        btn_estado->setStyleSheet("QPushButton{"
                                  "background-color: rgb(92,184,92);"
                                  "border-style: outset;"
                                  "border-width: 2px;"
                                  "border-radius: 5px;"
                                  "border-color: beige;}"
                                  "QPushButton:hover { "
                                  "background-color: rgb(110, 205, 69);"
                                  "border-style: inset;}"
                                  );
    }else{
        btn_estado->setText("+");
        btn_estado->setIcon(buttonInactivo);
        btn_estado->setStyleSheet("QPushButton{"
                                  "background-color: rgb(217,83,79);"
                                  "border-style: outset;"
                                  "border-width: 2px;"
                                  "border-radius: 5px;"
                                  "border-color: beige;}"
                                  "QPushButton:hover { "
                                  "background-color: rgb(244, 23, 17);"
                                  "border-style: inset;}"
                                  );
    }

    btn_editar->setIcon(buttonEditar);
    btn_editar->setStyleSheet("QPushButton{"
                              "background-color: rgb(240,173,78);"
                              "border-style: outset;"
                              "border-width: 2px;"
                              "border-radius: 5px;"
                              "border-color: beige;}"
                              "QPushButton:hover { "
                              "background-color: rgb(255, 154, 11);"
                              "border-style: inset;}"
                              );
    btn_eliminar->setIcon(buttonEliminar);
    btn_eliminar->setStyleSheet("QPushButton{"
                                "background-color: rgb(217,83,79);"
                                "border-style: outset;"
                                "border-width: 2px;"
                                "border-radius: 5px;"
                                "border-color: beige;}"
                                "QPushButton:hover { "
                                "background-color: rgb(244, 23, 17);"
                                "border-style: inset;}"
                                );

    ui->tableWidgetUsers->setCellWidget(fila,3, btn_estado);
    ui->tableWidgetUsers->setCellWidget(fila,6,btn_editar);
    ui->tableWidgetUsers->setCellWidget(fila,7,btn_eliminar);

    QObject::connect(btn_estado, &QPushButton::clicked, this, &Dashboard::estadoUsuario);
    QObject::connect(btn_editar, &QPushButton::clicked, this, &Dashboard::editUsuario);
    QObject::connect(btn_eliminar, &QPushButton::clicked, this, &Dashboard::deleteUsuario);
}


void Dashboard::cargarImage(QString r)
{
    QImage imagen;
    bool valid = imagen.load(r);

    if(valid)
    {
        ui->etiqueta->setPixmap(QPixmap::fromImage(imagen));
    }else{

        ui->etiqueta->setText("!");
    }

}

void Dashboard::on_btnUserAdd_clicked()
{

    DialogUserAdd dua(this);
    dua.setModal(true);
    dua.exec();
    //agregar la fila a nueva a la tabla
    int res=dua.response();
    if(res>0)
    {
        Usuario u = dua.addUsuario();
        QTableWidgetItem* mNombreItem= new QTableWidgetItem(u.nombre());
        QTableWidgetItem* mUsuarioItem= new QTableWidgetItem(u.usuario());
        QTableWidgetItem* mPerfilItem= new QTableWidgetItem();
        QTableWidgetItem* mUltimoLoginItem= new QTableWidgetItem(u.ultimoLogin());
        QTableWidgetItem* mFechaItem= new QTableWidgetItem(u.fecha());

        switch (u.perfil())
        {
        case 1:mPerfilItem->setData(0,"Adminsitrador");break;
        case 2:mPerfilItem->setData(0,"Especial");break;
        case 3:mPerfilItem->setData(0,"Vendedor");break;
        }
        addRowUsuario(mNombreItem, mUsuarioItem, mPerfilItem, mUltimoLoginItem, mFechaItem, 1);
    }
}

void Dashboard::getUsuarios()
{


    ui->tableWidgetUsers->setColumnCount(8);
    ui->tableWidgetUsers->setColumnWidth(0,200);
    ui->tableWidgetUsers->setColumnWidth(1,100);
    ui->tableWidgetUsers->setColumnWidth(2,100);
    ui->tableWidgetUsers->setColumnWidth(3,100);
    ui->tableWidgetUsers->setColumnWidth(4,150);
    ui->tableWidgetUsers->setColumnWidth(5,150);
    ui->tableWidgetUsers->setColumnWidth(6,100);
    ui->tableWidgetUsers->setColumnWidth(7,100);



    consulta= new QSqlQuery();
    consulta->clear();
    consulta->prepare("SELECT * FROM usuarios");
    consulta->exec();

    while(consulta->next()){
        QString mNombre=consulta->value(1).toString();
        QString mUsuario=consulta->value(2).toString();
        QString mPerfil=consulta->value(4).toString();
        int mEstado=consulta->value(6).toInt();
        QString mUltimoLogin=consulta->value(7).toString();
        QString mFecha=consulta->value(8).toString();

        QTableWidgetItem* mNombreItem= new QTableWidgetItem(mNombre);
        QTableWidgetItem* mUsuarioItem= new QTableWidgetItem(mUsuario);
        QTableWidgetItem* mPerfilItem= new QTableWidgetItem(mPerfil);
        QTableWidgetItem* mUltimoLoginItem= new QTableWidgetItem(mUltimoLogin);
        QTableWidgetItem* mFechaItem= new QTableWidgetItem(mFecha);

        addRowUsuario(mNombreItem, mUsuarioItem, mPerfilItem, mUltimoLoginItem, mFechaItem, mEstado);

    }


}

void Dashboard::deleteUsuario()
{
    cu = new ControladorUsuario;
    QMessageBox msgBox;
    QString usuario=getItem(ui->tableWidgetUsers);

    msgBox.setInformativeText("Eliminar usuario, esta operacion no tiene reversa");


    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    msgBox.setButtonText(QMessageBox::Yes, tr("Aceptar"));
    msgBox.setButtonText(QMessageBox::No, tr("Cancelar"));
    switch (msgBox.exec()) {
    case QMessageBox::Yes:
        if(cu->ctrEliminarUsuario(usuario)){
            QMessageBox::information(
                        this,
                        tr("Qcms"),
                        tr("El usuario ha sido eliminado correctamente.") );
            ui->tableWidgetUsers->removeRow(mfila);
        }else{
            QMessageBox::critical(
                        this,
                        tr("Qcms"),
                        tr("Error al eliminar usuario.") );
        }
        break;
    case QMessageBox::No:
        // no was clicked
        break;
    default:
        // should never be reached
        break;
    }
}

void Dashboard::editUsuario()
{
    QString usr =getItem(ui->tableWidgetUsers);
    cu = new ControladorUsuario();
    Usuario u;
    DialogUserEdit due(getItem(ui->tableWidgetUsers),this);
    due.setModal(true);
    due.exec();
    u=due.getUsuario();
    /*****/
    QTableWidgetItem* mNombreItem= new QTableWidgetItem(u.nombre());
    QTableWidgetItem* mUsuarioItem= new QTableWidgetItem(usr);
    QTableWidgetItem* mPerfilItem= new QTableWidgetItem();

    QString perfil;
    switch (u.perfil()) {
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

    mPerfilItem->setData(0,perfil);
    ui->tableWidgetUsers->setItem(mfila, 0, mNombreItem);
    ui->tableWidgetUsers->setItem(mfila, 1, mUsuarioItem);
    ui->tableWidgetUsers->setItem(mfila, 2 ,mPerfilItem);

    createActionsButtons(mfila, getEstado(usr));
}

void Dashboard::estadoUsuario()
{

    cu = new ControladorUsuario;
    QMessageBox msgBox;
    QString usuario=getItem(ui->tableWidgetUsers);
    int estado = getEstado(usuario);

    if (estado == 1){
        msgBox.setInformativeText("Desactivar usuario");
    }else{
        msgBox.setInformativeText("Activar usuario");
    }

    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    msgBox.setButtonText(QMessageBox::Yes, tr("Aceptar"));
    msgBox.setButtonText(QMessageBox::No, tr("Cancelar"));
    switch (msgBox.exec()) {
    case QMessageBox::Yes:
        if(estado == 1){
            estado=0;
            cu->ctrActivarUsuario(usuario,estado);
            createActionsButtons(mfila,0);
        }
        else{
            estado=1;
            cu->ctrActivarUsuario(usuario,estado);
            createActionsButtons(mfila,1);

        }
        break;
    case QMessageBox::No:
        // no was clicked
        break;
    default:
        // should never be reached
        break;
    }



}

void Dashboard::addRowUsuario(QTableWidgetItem *mNombreItem, QTableWidgetItem *mUsuarioItem, QTableWidgetItem *mPerfilItem, QTableWidgetItem *mUltimoLoginItem, QTableWidgetItem *mFechaItem, int mEstado)
{
    int fila;
    ui->tableWidgetUsers->insertRow(ui->tableWidgetUsers->rowCount());
    fila=ui->tableWidgetUsers->rowCount() -1;

    ui->tableWidgetUsers->setItem(fila, 0, mNombreItem);
    ui->tableWidgetUsers->setItem(fila, 1, mUsuarioItem);
    ui->tableWidgetUsers->setItem(fila, 2 ,mPerfilItem);
    ui->tableWidgetUsers->setItem(fila, 4, mUltimoLoginItem);
    ui->tableWidgetUsers->setItem(fila, 5, mFechaItem);

    createActionsButtons(fila, mEstado);
}

QString Dashboard::getItem(QTableWidget *tabla)
{
    int fila;
    int columna=1;
    QString item;
    fila = tabla->currentRow();
    item = tabla->item(fila,columna)->text();
    mfila=fila;
    return item;
}

int Dashboard::getEstado(QString usuario)
{
    cu = new ControladorUsuario();
    int estado = cu->ctrEstadoUsuario(usuario);
    return estado;
}

void Dashboard::on_pushButtonSalir_clicked()
{
    this->close();
}


