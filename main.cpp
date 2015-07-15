#include "mainscreen.h"
//#include "formulator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainScreen w;
    w.show();

    return a.exec();
}
