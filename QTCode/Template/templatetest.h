#ifndef TEMPLATETEST_H
#define TEMPLATETEST_H

template<class T>
class TemplateTest
{
public:
    TemplateTest(T temp);
    T function(T a,int b);
    T temp;
};
template<class T>
TemplateTest<T>::TemplateTest(T temp)
{
    this->temp=temp;
}

template<class T>
T TemplateTest<T>::function(T a, int b)
{
    return (a>b)?a:b;
}


template<class tee,class a>
int functiontest(tee &t1,int &b);

template<class tee,class a>
int functiontest(tee &t1,int &b)
{
    return 0;
}


#endif // TEMPLATETEST_H
