
// innerHook.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CinnerHookApp: 
// �йش����ʵ�֣������ innerHook.cpp
//

class CinnerHookApp : public CWinApp
{
public:
	CinnerHookApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CinnerHookApp theApp;