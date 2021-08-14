#include "chatbox.h"
#include "ui_chatbox.h"

Chatbox::Chatbox(QString buddy_jid,ClientManager* cl) :
    ui(new Ui::Chatbox),
    buddy(buddy_jid),
    client(cl)
{
    ui->setupUi(this);
    this->setWindowTitle(buddy);

    // Adding default resouce to JID
    buddy = buddy + "/QXmpp";

    rec = new QXmppMessageReceiptManager();
    cl->client->addExtension(rec);

    connect( (QObject*)cl->client, SIGNAL( messageReceived( QXmppMessage ) ),
                      (QObject*)this, SLOT( message_Received( QXmppMessage ) ) );
}

Chatbox::~Chatbox()
{
    delete ui;
}

void Chatbox::message_Received(const QXmppMessage &message)
{
    QString from = message.from();
    QString msg = message.body();
    bool val = message.isReceiptRequested();
    if(msg!=""){
     FromMessage = from + ":- " + msg;
     ui->textBrowser->append(FromMessage);
     FromMessage.clear();
    }
}

void Chatbox::on_send_clicked()
{
    // Formulate and send the message
    ToMessage = ui->message->text();
    QXmppMessage msg("",buddy,ToMessage);
    msg.setReceiptRequested(true);
    client->sendPacket(msg);

    qDebug()<<"Sent message with id"<<msg.id();

    if(ToMessage!=""){
       ToMessage = "Me:- " + ToMessage;
       ui->textBrowser->append(ToMessage);
       ToMessage.clear();
       ui->message->clear();
    }
}

void Chatbox::on_close_clicked()
{
    this->close();
}
