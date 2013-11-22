#include <QApplication>

#include "gconfig.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("GreenMusic");
    MainWindow w;
    w.show();
    
    return a.exec();
}
