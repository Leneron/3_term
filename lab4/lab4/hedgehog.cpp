#include "hedgehog.h"

Hedgehog::Hedgehog()
{

}

Hedgehog::~Hedgehog()
{

}

void Hedgehog::move(QKeyEvent* event)
{
    QMatrix4x4 mat;
    switch(event->key())
    {
        case Qt::Key_Up:
        {
            mat.rotate(180, 0, 1, 0);
            break;
        }
        case Qt::Key_Down:
        {
            break;
        }
        case Qt::Key_Right:
        {
            mat.rotate(90, 0, 1, 0);
            break;
        }
        case Qt::Key_Left:
        {
            mat.rotate(-90, 0, 1, 0);
            break;
        }
    }
    mat.setColumn(3, modelMatrix.column(3));
    mat.translate(0, 0, 0.08);
    modelMatrix = mat;
}

void Hedgehog::initObject()
{
    //Buffers
    float* verticesPtr;
    float* uvPtr;
    uint* indicesPtr;

    FILE * file = fopen("../lab4/graphics/hedgehogModel.obj", "r");

    loadModel(file, verticesPtr, uvPtr, indicesPtr, verticesSize, uvSize, indicesSize);
    fclose(file);

    verticesBuffer.create();
    verticesBuffer.bind();
    verticesBuffer.allocate(verticesPtr, verticesSize * sizeof(float));

    uvBuffer.create();
    uvBuffer.bind();
    uvBuffer.allocate(uvPtr, uvSize * sizeof(float));

    indicesBuffer.create();
    indicesBuffer.bind();
    indicesBuffer.allocate(indicesPtr, indicesSize * sizeof(uint));

    //ShadersProgram
    if (program.create())
    {
        program.addShaderFromSourceFile(QOpenGLShader::Vertex, "../lab4/hedgehog.vert");
        program.addShaderFromSourceFile(QOpenGLShader::Fragment, "../lab4/hedgehog.frag");
    }

    program.link();

    texture = new QOpenGLTexture(QImage("../lab4/graphics/hedgehogModel.png"));

    uvBuffer.bind();
    program.enableAttributeArray("coord");
    program.enableAttributeArray("texCoordIn");

    verticesBuffer.bind();
    program.setAttributeBuffer("coord", GL_FLOAT, 0, 3);

    indicesBuffer.bind();

    modelMatrix.setToIdentity();
    modelMatrix.translate(0.2, 0.2, 0);

    texture->generateMipMaps();
}

