
// 列表控件.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// C列表控件App:
// See 列表控件.cpp for the implementation of this class
//

class C列表控件App : public CWinApp
{
public:
	C列表控件App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern C列表控件App theApp;