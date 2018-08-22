#include "mainwindow.h"
#include <QApplication>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    MainWindow mw;
    mw.show();
    mw.loadPCDFile("test.pcd");
    return a.exec();
}
