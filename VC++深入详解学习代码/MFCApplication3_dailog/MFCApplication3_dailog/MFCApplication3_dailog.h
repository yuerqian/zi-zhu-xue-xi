
// MFCApplication3_dailog.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCApplication3_dailogApp: 
// �йش����ʵ�֣������ MFCApplication3_dailog.cpp
//

class CMFCApplication3_dailogApp : public CWinApp
{
public:
	CMFCApplication3_dailogApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication3_dailogApp theApp;