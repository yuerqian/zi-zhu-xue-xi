
// ConsoleApplication�Ի���.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CConsoleApplication�Ի���App: 
// �йش����ʵ�֣������ ConsoleApplication�Ի���.cpp
//

class CConsoleApplication�Ի���App : public CWinApp
{
public:
	CConsoleApplication�Ի���App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CConsoleApplication�Ի���App theApp;