
// �б�ؼ�.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// C�б�ؼ�App:
// See �б�ؼ�.cpp for the implementation of this class
//

class C�б�ؼ�App : public CWinApp
{
public:
	C�б�ؼ�App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern C�б�ؼ�App theApp;