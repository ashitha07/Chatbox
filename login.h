#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMainWindow>
#include <QXmppClient.h>
#include <QXmppLogger.h>
#include <QXmppPresence.h>
#include "QXmppMessage.h"
#include <QDebug>

#include "clientmanager.h"
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
   class Login;
}
QT_END_NAMESPACE


/* Class Description : This is the login class which
 *                     handles the login operation by prompting, accepting user
 *                     credentials and validating the same by connecting
 *                     to the XMPP server                                      */
class Login : public QDialog
{
      Q_OBJECT
   public:
        Login(QWidget *parent = 0);
       ~Login();
       // Username and Password fields
       QString name;
       QString password;

   private slots:
       // Slot invoked on clicking "ok" pushbutton
       void on_ok_clicked();
       // Slot invoked on clicking "cancel" pushbutton
       void on_cancel_clicked();
       // Slot invoked on catching signal for
       //connection establishment with XMPP server
       void connection_established();
       // Slot invoked on catching signal for
       // authentication failure for a given user from XMPP server
       void authentication_error();

   private:
       Ui::Login *ui;
       QXmppClient* client;
       QXmppConfiguration* config;
       ClientManager* clm;
};

#endif // LOGIN_H
