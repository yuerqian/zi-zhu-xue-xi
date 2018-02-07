#pragma once

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装器类

// 注意:  不要修改此文件的内容。  如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被覆盖。

/////////////////////////////////////////////////////////////////////////////
// CMfcactivexcontroctrl1 包装器类

class CMfcactivexcontroctrl1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CMfcactivexcontroctrl1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x5D7FE87E, 0x11DA, 0x4E62, { 0x8B, 0x9C, 0x65, 0xA, 0x4E, 0xD9, 0xF, 0xDA } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 特性
public:


// 操作
public:

// _DMFCActiveXControl控件

// Functions
//

	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void DoClick()
	{
		InvokeHelper(DISPID_DOCLICK, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void MyMethod(LPCTSTR msg)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, msg);
	}
	BOOL get_myProperty(BOOL mproperty)
	{
		BOOL result;
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, mproperty);
		return result;
	}
	void put_myProperty(BOOL mproperty, BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL VTS_BOOL ;
		InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, mproperty, newValue);
	}
	BOOL get_myproperty2(BOOL msg2)
	{
		BOOL result;
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, msg2);
		return result;
	}
	void put_myproperty2(BOOL msg2, BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL VTS_BOOL ;
		InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, msg2, newValue);
	}
	CString get_m1(LPCTSTR msg)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, msg);
		return result;
	}
	void put_m1(LPCTSTR msg, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, msg, newValue);
	}
	void hallo()
	{
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

// Properties
//

unsigned long GetBackColor()
{
	unsigned long result;
	GetProperty(DISPID_BACKCOLOR, VT_UI4, (void*)&result);
	return result;
}
void SetBackColor(unsigned long propVal)
{
	SetProperty(DISPID_BACKCOLOR, VT_UI4, propVal);
}
unsigned long GetForeColor()
{
	unsigned long result;
	GetProperty(DISPID_FORECOLOR, VT_UI4, (void*)&result);
	return result;
}
void SetForeColor(unsigned long propVal)
{
	SetProperty(DISPID_FORECOLOR, VT_UI4, propVal);
}
signed char Getcustom()
{
	signed char result;
	GetProperty(0x1, VT_I1, (void*)&result);
	return result;
}
void Setcustom(signed char propVal)
{
	SetProperty(0x1, VT_I1, propVal);
}
short GetInteral()
{
	short result;
	GetProperty(0x7, VT_I2, (void*)&result);
	return result;
}
void SetInteral(short propVal)
{
	SetProperty(0x7, VT_I2, propVal);
}


};
