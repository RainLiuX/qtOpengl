#include "glwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GLWidget qglwidget;
    qglwidget.resize(600, 600);
    qglwidget.setWindowTitle("Create Shader");
    qglwidget.show();

    return a.exec();
}
