#include <QApplication>

#include "PackageManager.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    PackageManager w;
    w.show();
    return a.exec();
}
