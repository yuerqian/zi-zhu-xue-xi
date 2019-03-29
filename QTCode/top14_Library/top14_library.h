#ifndef TOP14_LIBRARY_H
#define TOP14_LIBRARY_H

#include "top14_library_global.h"


class TOP14_LIBRARYSHARED_EXPORT Top14_Library
{

public:
    Top14_Library();



    virtual void Encrypt()=0;
};

extern "C" TOP14_LIBRARYSHARED_EXPORT Top14_Library* create();

#endif // TOP14_LIBRARY_H
