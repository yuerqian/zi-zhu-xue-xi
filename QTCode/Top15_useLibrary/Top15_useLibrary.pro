SOURCES += \
    main.cpp
#如果window下安装qt mingv版本，使用动态库的方式和Linux没区别，-L+路径 -l+lib库名
#如果qt mingw版本，要调用vs写的动态库，需要使用一个工具生成libXXX.a
LIBS += -L..\build-top14_Library-Desktop_Qt_5_9_2_MinGW_32bit-Debug\debug -llibtop14_Library \
#        -L..\build-top16_lib-Desktop_Qt_5_9_2_MinGW_32bit-Debug\debug -llibtop16_lib
