#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowTitle("Chatboxx Login");
}

Login::~Login()
{
   delete ui;
}

void Login::authentication_error()
{
   QMessageBox messageBox;
   messageBox.critical(0,"Error","Authentication Failure!!!");
   messageBox.setFixedSize(500,200);
   ui->name->clear();
   ui->password->clear();
   name.clear();
   password.clear();
}

void Login::connection_established()
{
    if(clm->isAuthenticated()) {
        Buddy m(clm);
        m.exec();
    }
    ui->name->clear();
    ui->password->clear();
    name.clear();
    password.clear();
}

void Login::on_ok_clicked()
{
    name = ui->name->text();
    password = ui->password->text();

    clm= new ClientManager(name,password);
    QObject::connect( (QObject*)clm, SIGNAL( connection_established() ), (QObject*)this, SLOT( connection_established() ) );
    QObject::connect( (QObject*)clm, SIGNAL( auth_error() ), (QObject*)this, SLOT( authentication_error() ) );
    clm->connectToServer();
}

void Login::on_cancel_clicked()
{
    this->close();
}
