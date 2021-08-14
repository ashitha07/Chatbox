#include "login.h"
#include <QDebug>

#include <QApplication>

/* Function Description : This is the main function which
 *                        invokes the login screen where the user
 *                        is prompted for user credentials to login.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.show();
    return a.exec();
}
