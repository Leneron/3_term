#ifndef GROUND_H
#define GROUND_H

#include "object.h"

class Ground: public Object
{
public:
    Ground();
    ~Ground();
    void initObject() override;
};

#endif // GROUND_H
