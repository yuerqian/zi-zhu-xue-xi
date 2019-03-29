#include "top14_library.h"
#include<QDebug>
#include "ctest.h"


Top14_Library::Top14_Library()
{
}

Top14_Library* create()
{
    return new Ctest();
}

//void Top14_Library::Encrypt()
//{
//    qDebug()<<"teeeeeee";
//}
