#include "object.h"

Object::Object():
    verticesBuffer(QOpenGLBuffer::VertexBuffer),
    uvBuffer(QOpenGLBuffer::VertexBuffer),
    indicesBuffer(QOpenGLBuffer::IndexBuffer)
{
    modelMatrix.setToIdentity();
}

Object::~Object()
{

}

void Object::paintObject(Camera& camera)
{
    program.bind();

    verticesBuffer.bind();
    program.setAttributeBuffer("coord", GL_FLOAT, 0, 3);

    uvBuffer.bind();
    program.setAttributeArray("texCoordIn", GL_FLOAT, 0, 2);

    texture->bind(0);
    program.setUniformValue("tex", 0);

    program.setUniformValue("modelMatrix", modelMatrix);
    program.setUniformValue("cameraMatrix", camera.getCameraMatrix());

    indicesBuffer.bind();
    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, nullptr);
}

void Object::initObject()
{

}

QVector3D Object::getPosition() const
{
    return QVector3D(modelMatrix.column(3));
}

void Object::loadModel(FILE* file, float* &vertices, float* &uv, uint* &indices, uint &verticesSize, uint &uvSize, uint &indicesSize)
{
    //Simple parser for .obj files with certaint settings
    //Normals aren't used there, they will be used for lightning in the next versions of this program
    std::vector<uint> vertexIndices;
    std::vector<uint> uvIndices;
    std::vector<float> tempVertices;
    std::vector<float> tempUv;
    while (true)
    {
        char line[128];
        int res = fscanf(file, "%s", line);
        if (res == EOF)
            break;
        else
        {
            if (strcmp(line, "v") == 0)
            {
                float vertexX, vertexY, vertexZ;
                fscanf(file, "%f %f %f\n", &vertexX, &vertexY, &vertexZ);
                tempVertices.push_back(vertexX);
                tempVertices.push_back(vertexY);
                tempVertices.push_back(vertexZ);
            }
            else if (strcmp(line, "vt") == 0)
            {
                float uvX, uvY;
                fscanf(file, "%f %f\n", &uvX, &uvY);
                tempUv.push_back(uvX);
                tempUv.push_back(uvY);
            }
            else if (strcmp(line, "f") == 0)
            {
                unsigned int vertexIndex[3], uvIndex[3], normalIndex[3]; //Normals
                fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
                //There is a -1 because C++ indexing starts at 0 and OBJ indexing starts at 1
                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);

                uvIndices.push_back(uvIndex[0]);
                uvIndices.push_back(uvIndex[1]);
                uvIndices.push_back(uvIndex[2]);
            }
        }
    }

    verticesSize = vertexIndices.size() * 3;
    vertices = new float[verticesSize];

    uvSize = uvIndices.size() * 2;
    uv = new float[uvSize];

    indicesSize = vertexIndices.size();
    indices = new uint[indicesSize];

    //Writing the data into the passed arrays
    for (uint i = 0; i < vertexIndices.size(); i++)
    {
        unsigned int vertexIndex = vertexIndices[i] - 1;
        float x = tempVertices[(vertexIndex) * 3];
        float y = tempVertices[(vertexIndex) * 3 + 1];
        float z = tempVertices[(vertexIndex) * 3 + 2];

        vertices[i * 3] = x;
        vertices[i * 3 + 1] = y;
        vertices[i * 3 + 2] = z;

        uint uvIndex = uvIndices[i] - 1;
        x = tempUv[(uvIndex) * 2];
        y = tempUv[(uvIndex) * 2 + 1];
        uv[i * 2] = x;
        uv[i * 2 + 1] = y;
        indices[i] = i;
    }
}
