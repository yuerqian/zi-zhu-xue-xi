
// �ڴ�ӳ��-�ļ���д.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// C�ڴ�ӳ���ļ���дApp:
// See �ڴ�ӳ��-�ļ���д.cpp for the implementation of this class
//

class C�ڴ�ӳ���ļ���дApp : public CWinApp
{
public:
	C�ڴ�ӳ���ļ���дApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern C�ڴ�ӳ���ļ���дApp theApp;