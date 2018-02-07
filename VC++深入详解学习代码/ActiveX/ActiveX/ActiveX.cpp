// ActiveX.cpp : CActiveXApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "ActiveX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CActiveXApp theApp;

const GUID CDECL _tlid = { 0x4F3B047B, 0x88CC, 0x4FBF, { 0xB5, 0x7B, 0xD6, 0xDF, 0x6D, 0xD8, 0x42, 0x29 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CActiveXApp::InitInstance - DLL 初始化

BOOL CActiveXApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: 在此添加您自己的模块初始化代码。
	}

	return bInit;
}



// CActiveXApp::ExitInstance - DLL 终止

int CActiveXApp::ExitInstance()
{
	// TODO: 在此添加您自己的模块终止代码。

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
