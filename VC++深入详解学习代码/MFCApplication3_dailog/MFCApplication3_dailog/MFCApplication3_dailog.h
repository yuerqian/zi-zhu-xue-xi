
// MFCApplication3_dailog.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CMFCApplication3_dailogApp: 
// 有关此类的实现，请参阅 MFCApplication3_dailog.cpp
//

class CMFCApplication3_dailogApp : public CWinApp
{
public:
	CMFCApplication3_dailogApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication3_dailogApp theApp;