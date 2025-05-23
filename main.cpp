#include "biculatormainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BiculatorMainWindow w;
    w.show();
    return a.exec();
}
