
// 内存映射-文件读写.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// C内存映射文件读写App:
// See 内存映射-文件读写.cpp for the implementation of this class
//

class C内存映射文件读写App : public CWinApp
{
public:
	C内存映射文件读写App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern C内存映射文件读写App theApp;