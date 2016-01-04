#include "camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

void Camera::initCamera()
{
    cameraMatrix.setToIdentity();
    cameraPosition = QVector3D(0,10, 12);

    cameraMatrix.perspective(70, 1, 0.05, 100);
    cameraMatrix.lookAt(cameraPosition, QVector3D(0, 0, 0), QVector3D(0, 1, 0));
}

QMatrix4x4 Camera::getCameraMatrix() const
{
    return cameraMatrix;
}


