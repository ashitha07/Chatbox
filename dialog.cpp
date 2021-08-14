#include "dialog.h"
#include "ui_dialog.h"


Buddy::Buddy(ClientManager* clm) :
    ui(new Ui::Buddy),
    client(clm),
    m_rosterManager(clm->client->findExtension<QXmppRosterManager>())
{
    ui->setupUi(this);
    this->setWindowTitle("My Buddies");

    connect(m_rosterManager, &QXmppRosterManager::rosterReceived,
                this, &Buddy::rosterReceived);

    connect(m_rosterManager, &QXmppRosterManager::presenceChanged,
                this, &Buddy::presenceChanged);

    connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),
                this,SLOT(on_listWidget_itemDoubleClicked(QListWidgetItem*)),
                Qt::UniqueConnection);

}

Buddy::~Buddy()
{
    delete ui;
}

void Buddy::rosterReceived()
{
    // Get the list of buddies from the server
    const QStringList jids = m_rosterManager->getRosterBareJids();
    for (const QString &bareJid : jids) {
        QString name = m_rosterManager->getRosterEntry(bareJid).name();
        if (name.isEmpty())
            name = "-";
        qDebug(" Roster received: %s [%s]", qPrintable(bareJid), qPrintable(name));
        QListWidgetItem *itm = new QListWidgetItem();
        itm->setText(qPrintable(bareJid));

        //Get the presence attribute for the given buddy
        QXmppPresence pres = m_rosterManager->getPresence(bareJid,"QXmpp");

        if(pres.type()== QXmppPresence::Available ) {
            itm->setIcon(QIcon("../Chatboxx/icons/online.png"));
        }
        else {
            itm->setIcon(QIcon("../Chatboxx/icons/offline.png"));
        }
        // Add the item to the list of buddies
        ui->listWidget->addItem(itm);
        Chatbox *ch= new Chatbox(itm->text(),client);
        buddy_chat[qPrintable(bareJid)]=ch;
    }
}

void Buddy::presenceChanged(const QString &bareJid,
                                 const QString &resource)
{
    qDebug(" Presence changed %s/%s", qPrintable(bareJid), qPrintable(resource));
    QXmppPresence pres = m_rosterManager->getPresence(bareJid,resource);
    QList<QListWidgetItem *> items = ui->listWidget->findItems(bareJid, Qt::MatchExactly);

    for ( QListWidgetItem* item : items) {
        if(pres.type()== QXmppPresence::Available ) {
          item->setIcon(QIcon("../Chatboxx/icons/online.png"));
        }
        else {
          item->setIcon(QIcon("../Chatboxx/icons/offline.png"));
        }
     }
}

void Buddy::on_logout_clicked() {
   client->disconnectFromServer();
   this->close();
}

void Buddy::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    Chatbox *temp = buddy_chat.find(item->text())->second;
    temp->exec();
}
