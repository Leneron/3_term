#ifndef OBJ_H
#define OBJ_H

#include <string>
#include <fstream>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include "camera.h"

//Base class for the objects at the scene
//Contents buffers, shader programs and a model loader
class Object
{
public:
    Object();
    virtual ~Object();

    void paintObject(Camera& camera);
    virtual void initObject();

    QVector3D getPosition() const;

protected:
    QMatrix4x4 modelMatrix;

    QOpenGLBuffer verticesBuffer;
    QOpenGLBuffer indicesBuffer;
    QOpenGLBuffer uvBuffer;

    uint indicesSize;
    uint verticesSize;
    uint uvSize;

    QOpenGLTexture *texture;

    QOpenGLShaderProgram program;

    //Simple parser
    void loadModel(FILE* file, float* &vertices, float* &uv, uint* &indices, uint &verticesSize, uint &uvSize, uint &indicesSize);
};

#endif // OBJ_H
