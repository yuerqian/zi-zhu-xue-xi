
// Clipboard.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CClipboardApp: 
// �йش����ʵ�֣������ Clipboard.cpp
//

class CClipboardApp : public CWinApp
{
public:
	CClipboardApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CClipboardApp theApp;