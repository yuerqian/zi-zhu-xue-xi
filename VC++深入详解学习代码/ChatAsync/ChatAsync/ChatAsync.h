
// ChatAsync.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CChatAsyncApp: 
// �йش����ʵ�֣������ ChatAsync.cpp
//

class CChatAsyncApp : public CWinApp
{
public:
	CChatAsyncApp();
	~CChatAsyncApp();
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CChatAsyncApp theApp;