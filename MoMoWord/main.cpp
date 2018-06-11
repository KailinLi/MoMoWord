#include "momomaindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MoMoMainDialog w;
    w.show();

    return a.exec();
}
