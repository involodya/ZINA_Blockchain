#include "networkwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    NetworkWindow w1(33333);
    NetworkWindow w2(33334);
    w1.show();
    w2.show();
    return a.exec();
}
