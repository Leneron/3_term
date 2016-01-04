#include "openglwidget.h"

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);

    vao.create(); //vertex array object
    vao.bind();

    camera.initCamera();

    ground.initObject();

    hedgehog.initObject();

    srand(time(0));
    int applesN = rand() % 7 + 3;

    for (int i = 0; i < applesN; i++)
    {
        Apple* apple = new Apple;
        apple->initObject();
        apple->setPosition(pow(-1, rand() % 2) * (rand() % 100) / 100 * 8 , pow(-1, rand() % 2) * (rand() % 100) / 100 * 8);
        apple->setRotation(rand() % 360);
        apples.push_back(apple);
    }

    glClearColor(0, 0.01, 0.1, 1);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    ground.paintObject(camera);

    for (size_t i = 0; i < apples.size(); i++)
    {
        apples[i]->paintObject(camera);
    }

    hedgehog.paintObject(camera);
}

void OpenGLWidget::keyPressEvent(QKeyEvent* event)
{
    hedgehog.move(event);
    size_t i = 0;
    QVector3D hedgehogPosition = hedgehog.getPosition();
    while(i < apples.size())
    {
        if (hedgehogPosition.distanceToPoint(apples[i]->getPosition()) < 2.2)
        {
            apples.erase(apples.begin() + i);
        }
        else i++;
    }

    repaint();

    if (apples.size() == 0)
    {
        QMessageBox::information(this, "GAME OVER", "You win!");
        close();
    }
}

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
    this->resize(700, 700);
    this->setWindowTitle("Hedgehog");
}

OpenGLWidget::~OpenGLWidget()
{

}
