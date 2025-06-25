#include "jsonparser.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JsonParser w;
    w.show();
    return a.exec();
}
