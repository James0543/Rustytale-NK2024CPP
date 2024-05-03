#include "loadingInterface.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loadingInterface w;
    w.show();
    return a.exec();
}
