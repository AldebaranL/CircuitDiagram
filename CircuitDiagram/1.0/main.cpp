#include "drawingboard.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DrawingBoard w;
    w.show();
    return a.exec();
}
