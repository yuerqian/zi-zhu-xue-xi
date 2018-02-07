// ActiveX.cpp : CActiveXApp �� DLL ע���ʵ�֡�

#include "stdafx.h"
#include "ActiveX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CActiveXApp theApp;

const GUID CDECL _tlid = { 0x4F3B047B, 0x88CC, 0x4FBF, { 0xB5, 0x7B, 0xD6, 0xDF, 0x6D, 0xD8, 0x42, 0x29 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CActiveXApp::InitInstance - DLL ��ʼ��

BOOL CActiveXApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: �ڴ�������Լ���ģ���ʼ�����롣
	}

	return bInit;
}



// CActiveXApp::ExitInstance - DLL ��ֹ

int CActiveXApp::ExitInstance()
{
	// TODO: �ڴ�������Լ���ģ����ֹ���롣

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
