#pragma once

// MFCActiveXControl�ؼ�.h : MFCActiveXControl�ؼ�.DLL ����ͷ�ļ�

#if !defined( __AFXCTL_H__ )
#error "�ڰ������ļ�֮ǰ������afxctl.h��"
#endif

#include "resource.h"       // ������


// CMFCActiveXControl�ؼ�App : �й�ʵ�ֵ���Ϣ������� MFCActiveXControl�ؼ�.cpp��

class CMFCActiveXControl�ؼ�App : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

