#ifdef DLL1_API
#else
#define DLL1_API _declspec(dllimport)
#endif

DLL1_API int add(int a, int b);

extern"C" DLL1_API int  subtract(int a, int b);

class /* DLL1_API */Point
{
public:
    void  output(int x, int y);
	void test();
};