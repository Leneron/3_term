#include "apple.h"

Apple::Apple()
{

}

Apple::~Apple()
{

}

void Apple::initObject()
{
    //buffers
    float* verticesPtr;
    float* uvPtr;
    uint* indicesPtr;

    FILE * file = fopen("../lab4/graphics/appleModel.obj", "r");

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
        program.addShaderFromSourceFile(QOpenGLShader::Vertex, "../lab4/apple.vert");
        program.addShaderFromSourceFile(QOpenGLShader::Fragment, "../lab4/apple.frag");
    }

    program.link();

    texture = new QOpenGLTexture(QImage("../lab4/graphics/appleModel.png"));

    uvBuffer.bind();
    program.enableAttributeArray("coord");
    program.enableAttributeArray("texCoordIn");

    verticesBuffer.bind();
    program.setAttributeBuffer("coord", GL_FLOAT, 0, 3);

    indicesBuffer.bind();

    modelMatrix.setToIdentity();
    modelMatrix.scale(0.8);
    modelMatrix.translate(0.2, 0.2, 0);

    texture->generateMipMaps();
}

void Apple::setPosition(GLfloat x, GLfloat z)
{
    modelMatrix.setToIdentity();
    modelMatrix.scale(0.8);
    modelMatrix.translate(x, 0, z);
}

void Apple::setRotation(GLfloat angle)
{
    modelMatrix.rotate(angle, 0, 1, 0);
}

