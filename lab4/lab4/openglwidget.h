#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

//Using Qt as wrapper around OpenGL buffers, texture and shaders

#include <vector>
#include <QDebug>
#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QMatrix>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QMouseEvent>
#include <QMessageBox>
#include <ctime>
#include "hedgehog.h"
#include "apple.h"
#include "camera.h"
#include "ground.h"


class OpenGLWidget: public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
protected:
    QOpenGLVertexArrayObject vao;

    void initializeGL();
    void paintGL();

    Ground ground;
    Hedgehog hedgehog;
    std::vector<Apple*> apples;

    Camera camera;

    void keyPressEvent(QKeyEvent* event);
public:
    OpenGLWidget(QWidget* parent = 0);
    ~OpenGLWidget();
};

#endif // OPENGLWIDGET_H
