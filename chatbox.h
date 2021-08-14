#ifndef CHATBOX_H
#define CHATBOX_H

#include <QDialog>
#include <QCoreApplication>
#include "clientmanager.h"
#include "QXmppClient.h"
#include "QXmppMessage.h"
#include "QXmppMessageReceiptManager.h"

class QXmppMessageReceiptManager;

namespace Ui {
class Chatbox;
}
/* Class Description : This is the class corresponding to the chatbox dialog
 *                     box. This class handles the display, sending and
 *                     recieval of messages between clients               */
class Chatbox : public QDialog
{
    Q_OBJECT

public:
    explicit Chatbox(QString buddy, ClientManager* cl);
    ~Chatbox();

private slots:
    // Slot invoked on clicking "send" pushbutton
    void on_send_clicked();
    // Slot invoked when messageRecieval signal is emitted
    void message_Received(const QXmppMessage &message);
    // Slot invoked on clicking "close" pushbutton
    void on_close_clicked();

private:
    Ui::Chatbox *ui;
    ClientManager* client;
    QXmppMessageReceiptManager *rec;
    QString buddy;
    QString ToMessage;
    QString FromMessage;
};

#endif // CHATBOX_H
