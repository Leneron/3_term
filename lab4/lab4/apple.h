#ifndef APPLE_H
#define APPLE_H

#include "object.h"

class Apple: public Object
{
public:
    Apple();
    ~Apple();
    void initObject() override;
    void setPosition(GLfloat x, GLfloat z);
    void setRotation(GLfloat angle);
};

#endif // APPLE_H
