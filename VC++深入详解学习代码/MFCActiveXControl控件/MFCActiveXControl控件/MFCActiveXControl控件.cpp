// MFCActiveXControl�ؼ�.cpp : CMFCActiveXControl�ؼ�App �� DLL ע���ʵ�֡�

#include "stdafx.h"
#include "MFCActiveXControl�ؼ�.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CMFCActiveXControl�ؼ�App theApp;

const GUID CDECL _tlid = { 0x23D7284D, 0xB51D, 0x4A24, { 0xA7, 0xEF, 0x20, 0xC7, 0xB3, 0xCF, 0xAC, 0xA3 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CMFCActiveXControl�ؼ�App::InitInstance - DLL ��ʼ��

BOOL CMFCActiveXControl�ؼ�App::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO:  �ڴ�������Լ���ģ���ʼ�����롣
	}

	return bInit;
}



// CMFCActiveXControl�ؼ�App::ExitInstance - DLL ��ֹ

int CMFCActiveXControl�ؼ�App::ExitInstance()
{
	// TODO:  �ڴ�������Լ���ģ����ֹ���롣

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - ������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - �����ϵͳע������Ƴ�

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
