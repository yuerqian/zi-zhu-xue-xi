
// 迷你管理系统.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// C迷你管理系统App:
// See 迷你管理系统.cpp for the implementation of this class
//

class C迷你管理系统App : public CWinApp
{
public:
	C迷你管理系统App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern C迷你管理系统App theApp;