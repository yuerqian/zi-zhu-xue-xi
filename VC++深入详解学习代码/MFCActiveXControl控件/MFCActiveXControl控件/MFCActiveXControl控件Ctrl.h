#pragma once

// MFCActiveXControl�ؼ�Ctrl.h : CMFCActiveXControl�ؼ�Ctrl ActiveX �ؼ����������


// CMFCActiveXControl�ؼ�Ctrl : �й�ʵ�ֵ���Ϣ������� MFCActiveXControl�ؼ�Ctrl.cpp��

class CMFCActiveXControl�ؼ�Ctrl : public COleControl
{
	DECLARE_DYNCREATE(CMFCActiveXControl�ؼ�Ctrl)

// ���캯��
public:
	CMFCActiveXControl�ؼ�Ctrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	
// ʵ��
protected:
	~CMFCActiveXControl�ؼ�Ctrl();

	DECLARE_OLECREATE_EX(CMFCActiveXControl�ؼ�Ctrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CMFCActiveXControl�ؼ�Ctrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMFCActiveXControl�ؼ�Ctrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CMFCActiveXControl�ؼ�Ctrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
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

