#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "QXmppRosterManager.h"
#include "QXmppClient.h"
#include <QListWidgetItem>
#include "chatbox.h"
#include "clientmanager.h"
#include <map>

class QXmppRosterManager;

namespace Ui {
class Buddy;
}
/* Class Description : This is the Buddy class which
 *                     displays the list of buddies and their online presence  */

class Buddy : public QDialog
{
    Q_OBJECT

public:
    explicit Buddy(ClientManager* clm);
    ~Buddy();
private slots:
    // Slot invoked when logout is clicked
    void on_logout_clicked();
    // Slot invoked when a roster us recieved
    void rosterReceived();
    // Slot invoked when presence of a buddy is changes
    void presenceChanged(const QString &bareJid,
                             const QString &resource);
    // Slot invoked when a buddy's name is double clicked
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::Buddy *ui;
    QXmppRosterManager* m_rosterManager;
    ClientManager* client;
    std::map<QString,Chatbox*> buddy_chat;
};

#endif // DIALOG_H
