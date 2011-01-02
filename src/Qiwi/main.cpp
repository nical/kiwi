#include <QtGui/QApplication>
#include "QiwiMainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QiwiMainWindow w;
    w.show();

    return a.exec();
}
