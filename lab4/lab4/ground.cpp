#include "ground.h"

Ground::Ground()
{

}

Ground::~Ground()
{

}

void Ground::initObject()
{
    indicesSize = 6;
    //Buffers
    float vertices[12] = {
        -1, 0, -1,
        1, 0, -1,
        1, 0, 1,
        -1, 0, 1
    };

    uint indices[6] = {
        0, 1, 2,
        3, 2, 0,
    };

    float uv[8] = {
        1.0, 1.0,
        0.0, 1.0,
        0.0, 0.0,
        1.0, 0.0,
    };

    verticesBuffer.create();
    verticesBuffer.bind();
    verticesBuffer.allocate(vertices, 4 * 3 * sizeof(float));

    indicesBuffer.create();
    indicesBuffer.bind();
    indicesBuffer.allocate(indices, 2 * 3 * sizeof(uint));

    uvBuffer.create();
    uvBuffer.bind();
    uvBuffer.allocate(uv, 4 * 2 * sizeof(float));

    //ShadersProgram
    if (program.create())
    {
        program.addShaderFromSourceFile(QOpenGLShader::Vertex, "../lab4/ground.vert");
        program.addShaderFromSourceFile(QOpenGLShader::Fragment, "../lab4/ground.frag");
    }

    program.link();

    texture = new QOpenGLTexture(QImage("../lab4/graphics/grass.png"));

    uvBuffer.bind();
    program.enableAttributeArray("coord");
    program.enableAttributeArray("texCoordIn");

    verticesBuffer.bind();
    program.setAttributeBuffer("coord", GL_FLOAT, 0, 3);

    indicesBuffer.bind();

    modelMatrix.setToIdentity();
    modelMatrix.scale(-8, 1, 8);
    modelMatrix.translate(0, -0.3, -0.1);


    texture->generateMipMaps();
}

