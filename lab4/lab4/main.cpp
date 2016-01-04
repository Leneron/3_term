//Drawing a hedgehog, that picks up apples, with OpenGL

#include <QWidget>
#include <QApplication>
#include <QSurfaceFormat>
#include "openglwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Set the version to 4.0
    QSurfaceFormat format;
    format.setVersion(4, 0);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    //Creating the main window
    OpenGLWidget w;
    w.show();

    return a.exec();
}
