#ifndef CTEST_H
#define CTEST_H

#include "top14_library.h"


class Ctest:public Top14_Library
{
public:
    Ctest();
//    Ctest* create();
    virtual void Encrypt();
};

#endif // CTEST_H
