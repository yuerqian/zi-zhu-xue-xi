
// AsyncChat.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAsyncChatApp: 
// �йش����ʵ�֣������ AsyncChat.cpp
//

class CAsyncChatApp : public CWinApp
{
public:
	CAsyncChatApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAsyncChatApp theApp;