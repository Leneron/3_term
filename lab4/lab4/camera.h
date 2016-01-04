#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include <QVector3D>

//Saves the matrix, that is used for output view
class Camera
{
public:
    Camera();
    ~Camera();

    void initCamera();
    QMatrix4x4 getCameraMatrix() const;

private:
    QMatrix4x4 cameraMatrix;
    QVector3D cameraPosition;
};

#endif // CAMERA_H
