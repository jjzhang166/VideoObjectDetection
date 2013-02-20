#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Dinosaurus Software");
    QCoreApplication::setApplicationName("VideoObjectDetection");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
