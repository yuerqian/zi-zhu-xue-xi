// MFCActiveXControl控件.cpp : CMFCActiveXControl控件App 和 DLL 注册的实现。

#include "stdafx.h"
#include "MFCActiveXControl控件.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CMFCActiveXControl控件App theApp;

const GUID CDECL _tlid = { 0x23D7284D, 0xB51D, 0x4A24, { 0xA7, 0xEF, 0x20, 0xC7, 0xB3, 0xCF, 0xAC, 0xA3 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CMFCActiveXControl控件App::InitInstance - DLL 初始化

BOOL CMFCActiveXControl控件App::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO:  在此添加您自己的模块初始化代码。
	}

	return bInit;
}



// CMFCActiveXControl控件App::ExitInstance - DLL 终止

int CMFCActiveXControl控件App::ExitInstance()
{
	// TODO:  在此添加您自己的模块终止代码。

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
