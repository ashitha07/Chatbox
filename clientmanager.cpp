#include "clientmanager.h"

ClientManager::ClientManager(QString name, QString password)
{
   client = new QXmppClient();
   config = new QXmppConfiguration();
   pres = new QXmppPresence();

   // Get server config from config file
   QSettings settings(QString("../Chatboxx/server.ini"), QSettings::IniFormat);
   qDebug()<<settings.contains ("Host");
   qDebug()<<settings.fileName();

   int port         = settings.value("Port").toInt();
   QString domain   = settings.value("Domain").toString();
   QString host     = settings.value("Host").toString();
   QString resource = settings.value("Resource").toString();

   qDebug()<<"port"<<port<<"host"<<host<<"Domain"<<domain;
   // Configure server
   config->setPort(port);
   config->setUser(name);
   config->setPassword(password);
   config->setDomain(domain);
   config->setHost(host);
   config->setIgnoreSslErrors(true);
   config->setResource(resource);

   pres->setType(QXmppPresence::Available);
   pres->setAvailableStatusType(QXmppPresence::AvailableStatusType::Online);

   /* Uncomment below lines for debugging purposes */
   //client->logger()->setLoggingType(QXmppLogger::StdoutLogging);
   //client->logger()->setMessageTypes(QXmppLogger::AnyMessage);

   QObject::connect( (QObject*)client, SIGNAL( connected() ), (QObject*)this, SLOT( connection_completed() ) );
   QObject::connect( (QObject*)client, SIGNAL( error (QXmppClient::Error) ), (QObject*)this, SLOT( error (QXmppClient::Error) ) );
}

ClientManager::~ClientManager() {
}

void ClientManager::connection_completed()
{
    qDebug()<<"Connection completed ";
    client->setClientPresence(*pres);
    emit connection_established();
}
void ClientManager::error(QXmppClient::Error err)
{
    if(err==QXmppClient::XmppStreamError) {
        emit auth_error();
    }
}

void ClientManager::connectToServer()
{
    client->connectToServer(*config, *pres);
    QEventLoop loop;
    loop.exec();
}
void ClientManager::disconnectFromServer()
{
    client->disconnectFromServer();
}

bool ClientManager::isAuthenticated()
{
    return client->isAuthenticated();
}

bool ClientManager::isConnected()
{
    return client->isConnected();
}

void ClientManager::sendPacket(QXmppMessage msg)
{
    client->sendPacket(msg);
}
