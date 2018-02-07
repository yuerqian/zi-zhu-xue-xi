#pragma once

// MFCActiveXControl控件Ctrl.h : CMFCActiveXControl控件Ctrl ActiveX 控件类的声明。


// CMFCActiveXControl控件Ctrl : 有关实现的信息，请参阅 MFCActiveXControl控件Ctrl.cpp。

class CMFCActiveXControl控件Ctrl : public COleControl
{
	DECLARE_DYNCREATE(CMFCActiveXControl控件Ctrl)

// 构造函数
public:
	CMFCActiveXControl控件Ctrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	
// 实现
protected:
	~CMFCActiveXControl控件Ctrl();

	DECLARE_OLECREATE_EX(CMFCActiveXControl控件Ctrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CMFCActiveXControl控件Ctrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMFCActiveXControl控件Ctrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CMFCActiveXControl控件Ctrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
		dispidaaa = 9,
		dispidhallo = 8L,
		dispidInteral = 7,
		dispidm1 = 6,
		dispidmyProperty = 5,
		dispidmyproperty2 = 4,
		//dispidmyProperty = 3,
		dispidMyMethod = 2L,
		eventidMyEvent2 = 2L,
		eventidMyevent = 1L,
		dispidcustom = 1
	};
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	void OncustomChanged();
	CHAR m_custom;

	void Myevent()
	{
		FireEvent(eventidMyevent, EVENT_PARAM(VTS_NONE));
	}
public:
//	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
protected:

	void MyEvent2(LPCTSTR msg)
	{
		FireEvent(eventidMyEvent2, EVENT_PARAM(VTS_BSTR), msg);
	}
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
protected:
	void MyMethod(LPCTSTR msg);
	VARIANT_BOOL GetmyProperty(VARIANT_BOOL mproperty);
	void SetmyProperty(VARIANT_BOOL mproperty, VARIANT_BOOL newVal);
	VARIANT_BOOL Getmyproperty2(VARIANT_BOOL msg2);
	void Setmyproperty2(VARIANT_BOOL msg2, VARIANT_BOOL newVal);
	BSTR GetmyProperty();
	void SetmyProperty(LPCTSTR newVal);
	BSTR Getm1(LPCTSTR msg);
	void Setm1(LPCTSTR msg, LPCTSTR newVal);
	void OnInteralChanged();
	SHORT m_Interal;
public:
	int MyMethod2();
	int m2();
protected:
	void hallo();
public:
	int m_timer;
protected:
	void OnaaaChanged();
	CString m_aaa;
};

