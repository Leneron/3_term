#ifndef HEDGEHOG_H
#define HEDGEHOG_H

#include "object.h"

class Hedgehog: public Object
{
public:
    Hedgehog();
    ~Hedgehog();
    void move(QKeyEvent* event);
    void initObject() override;
};

#endif // HEDGEHOG_H
