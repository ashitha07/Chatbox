#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H


#include <QDialog>
#include <QMainWindow>
#include <QXmppClient.h>
#include <QXmppLogger.h>
#include <QXmppPresence.h>
#include <QMessageBox>
#include <QEventLoop>
#include <QXmppMessage.h>
#include <QDebug>
#include <QSettings>
#include <unistd.h>


QT_BEGIN_NAMESPACE
namespace Ui {
   class Login;
}
QT_END_NAMESPACE

/* Class Description : This is the wrapper class for XMPP client
 *                     operations .              */

class ClientManager : public QObject
{
    Q_OBJECT
public:
    ClientManager(QString, QString);
    ~ClientManager();

    // Member function to connect to XMPP server
    void connectToServer();
    // Member function to disconnect to XMPP server
    void disconnectFromServer();
    // Member function to check if the client is authenticated
    bool isAuthenticated();
    // Member function to check if the client is connected to server
    bool isConnected();
    // Member function to send the message
    void sendPacket(QXmppMessage msg);
    QXmppClient* client;

private slots:
    // Slot invoked when connected signal is emitted
    void connection_completed();
    // Slot invoked when an error signal is emitted
    void error(QXmppClient::Error err);

private:
    QXmppConfiguration* config;
    QXmppPresence *pres;

signals:
      // Signal used by other objects when connection is established
      void connection_established();
      // Signal used by other objects when connection is failed due to error
      void auth_error();
};


#endif // CLIENTMANAGER_H
