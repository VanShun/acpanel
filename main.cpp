#include "acpanel.h"
//#include "offpanel.h"
#include "globalsetting.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
/*
** main func
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AcPanel w;
    //OffPanel w;
    w.setFixedSize(RESOLUTION_X, RESOLUTION_Y);
    w.setGeometry(0, 0, RESOLUTION_X, RESOLUTION_Y);
    //const QRect availableGeometry = QApplication::desktop()->availableGeometry(&w);
    //w.resize(availableGeometry.width(),availableGeometry.height());
    w.setWindowFlags(Qt::FramelessWindowHint);
    //w.setWindowFlags(Qt::CustomizeWindowHint);
    //should not call this func, otherwise "double free or corruption (out)" err occurs
    //w.setAttribute(Qt::WA_DeleteOnClose);
    //w.setAutoFillBackground(true);
    w.show();
    return a.exec();
}
