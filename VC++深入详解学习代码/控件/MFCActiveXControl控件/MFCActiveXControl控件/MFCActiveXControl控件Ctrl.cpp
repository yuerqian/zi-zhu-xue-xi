// MFCActiveXControl�ؼ�Ctrl.cpp : CMFCActiveXControl�ؼ�Ctrl ActiveX �ؼ����ʵ�֡�

#include "stdafx.h"
#include "MFCActiveXControl�ؼ�.h"
#include "MFCActiveXControl�ؼ�Ctrl.h"
#include "MFCActiveXControl�ؼ�PropPage.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMFCActiveXControl�ؼ�Ctrl, COleControl)

// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CMFCActiveXControl�ؼ�Ctrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_TIMER()
//	ON_WM_MBUTTONDBLCLK()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// ����ӳ��

BEGIN_DISPATCH_MAP(CMFCActiveXControl�ؼ�Ctrl, COleControl)
	DISP_FUNCTION_ID(CMFCActiveXControl�ؼ�Ctrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_STOCKPROP_BACKCOLOR()
	DISP_STOCKPROP_FORECOLOR()
	DISP_PROPERTY_NOTIFY_ID(CMFCActiveXControl�ؼ�Ctrl, "custom", dispidcustom, m_custom, OncustomChanged, VT_I1)
	DISP_STOCKFUNC_DOCLICK()
	DISP_FUNCTION_ID(CMFCActiveXControl�ؼ�Ctrl, "MyMethod", dispidMyMethod, MyMethod, VT_EMPTY, VTS_BSTR)
	/*DISP_PROPERTY_PARAM_ID(CMFCActiveXControl�ؼ�Ctrl, "myProperty", dispidmyProperty, GetmyProperty, SetmyProperty, VT_BOOL, VTS_BOOL)*/
	DISP_PROPERTY_PARAM_ID(CMFCActiveXControl�ؼ�Ctrl, "myproperty2", dispidmyproperty2, Getmyproperty2, Setmyproperty2, VT_BOOL, VTS_BOOL)
	//DISP_PROPERTY_EX_ID(CMFCActiveXControl�ؼ�Ctrl, "myProperty", dispidmyProperty, GetmyProperty, SetmyProperty, VT_BSTR)
	DISP_PROPERTY_PARAM_ID(CMFCActiveXControl�ؼ�Ctrl, "m1", dispidm1, Getm1, Setm1, VT_BSTR, VTS_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CMFCActiveXControl�ؼ�Ctrl, "Interal", dispidInteral, m_Interal, OnInteralChanged, VT_I2)
	DISP_FUNCTION_ID(CMFCActiveXControl�ؼ�Ctrl, "hallo", dispidhallo, hallo, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_NOTIFY_ID(CMFCActiveXControl�ؼ�Ctrl, "aaa", dispidaaa, m_aaa, OnaaaChanged, VT_BSTR)
END_DISPATCH_MAP()

// �¼�ӳ��

BEGIN_EVENT_MAP(CMFCActiveXControl�ؼ�Ctrl, COleControl)
	EVENT_STOCK_CLICK()
	EVENT_CUSTOM_ID("Myevent", eventidMyevent, Myevent, VTS_NONE)
	EVENT_CUSTOM_ID("MyEvent2", eventidMyEvent2, MyEvent2, VTS_BSTR)
END_EVENT_MAP()

// ����ҳ

// TODO:  ����Ҫ��Ӹ�������ҳ��  ���ס���Ӽ���!
BEGIN_PROPPAGEIDS(CMFCActiveXControl�ؼ�Ctrl, 2)
	PROPPAGEID(CMFCActiveXControl�ؼ�PropPage::guid)
	PROPPAGEID(CLSID_CColorPropPage);
END_PROPPAGEIDS(CMFCActiveXControl�ؼ�Ctrl)

// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CMFCActiveXControl�ؼ�Ctrl, "MFCACTIVEXCONTRO.MFCActiveXControCtrl.1",
	0x5d7fe87e, 0x11da, 0x4e62, 0x8b, 0x9c, 0x65, 0xa, 0x4e, 0xd9, 0xf, 0xda)

// ����� ID �Ͱ汾

IMPLEMENT_OLETYPELIB(CMFCActiveXControl�ؼ�Ctrl, _tlid, _wVerMajor, _wVerMinor)

// �ӿ� ID

const IID IID_DMFCActiveXControl�ؼ� = { 0x76028768, 0xB3C4, 0x4406, { 0xBB, 0x5F, 0x94, 0xB7, 0xC4, 0x13, 0x67, 0xFB } };
const IID IID_DMFCActiveXControl�ؼ�Events = { 0xBAD78B2F, 0x154B, 0x433F, { 0x8C, 0x1, 0x60, 0x46, 0x36, 0xF6, 0x1E, 0x96 } };

// �ؼ�������Ϣ

static const DWORD _dwMFCActiveXControl�ؼ�OleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMFCActiveXControl�ؼ�Ctrl, IDS_MFCACTIVEXCONTROL, _dwMFCActiveXControl�ؼ�OleMisc)

// CMFCActiveXControl�ؼ�Ctrl::CMFCActiveXControl�ؼ�CtrlFactory::UpdateRegistry -
// ��ӻ��Ƴ� CMFCActiveXControl�ؼ�Ctrl ��ϵͳע�����

BOOL CMFCActiveXControl�ؼ�Ctrl::CMFCActiveXControl�ؼ�CtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO:  ��֤���Ŀؼ��Ƿ���ϵ�Ԫģ���̴߳������
	// �йظ�����Ϣ����ο� MFC ����˵�� 64��
	// ������Ŀؼ������ϵ�Ԫģ�͹�����
	// �����޸����´��룬��������������
	// afxRegApartmentThreading ��Ϊ 0��

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_MFCACTIVEXCONTROL,
			IDB_MFCACTIVEXCONTROL,
			afxRegApartmentThreading,
			_dwMFCActiveXControl�ؼ�OleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


// CMFCActiveXControl�ؼ�Ctrl::CMFCActiveXControl�ؼ�Ctrl - ���캯��

CMFCActiveXControl�ؼ�Ctrl::CMFCActiveXControl�ؼ�Ctrl()
: m_timer(0)
{
	InitializeIIDs(&IID_DMFCActiveXControl�ؼ�, &IID_DMFCActiveXControl�ؼ�Events);
	// TODO:  �ڴ˳�ʼ���ؼ���ʵ�����ݡ�
	m_timer = 0;
}

// CMFCActiveXControl�ؼ�Ctrl::~CMFCActiveXControl�ؼ�Ctrl - ��������

CMFCActiveXControl�ؼ�Ctrl::~CMFCActiveXControl�ؼ�Ctrl()
{
	// TODO:  �ڴ�����ؼ���ʵ�����ݡ�
}

// CMFCActiveXControl�ؼ�Ctrl::OnDraw - ��ͼ����

void CMFCActiveXControl�ؼ�Ctrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& /* rcInvalid */)
{
	if (!pdc)
		return;

	// TODO:  �����Լ��Ļ�ͼ�����滻����Ĵ��롣
	//pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	//pdc->Ellipse(rcBounds);

	CBrush brush(TranslateColor(GetBackColor()));
	pdc->FillRect(rcBounds,&brush);
	//if (pdc->SetBkColor(TranslateColor(GetBackColor())) == CLR_INVALID)
	//{
	//	AfxMessageBox(_T("���ñ���ɫʧ��"));
	//}
	pdc->SetTextColor(TranslateColor(GetForeColor()));
	pdc->SetBkMode(TRANSPARENT);


	CTime time = CTime::GetCurrentTime();
	CString timeText = time.Format("%H,%M,%S");
	RECT rectM=CRect(0, 10, 500, 500);
	pdc->DrawText(timeText, timeText.GetLength(), &rectM, DT_LEFT);
	if (time.GetSecond() == 0)
	{
		Myevent();
	}
}

// CMFCActiveXControl�ؼ�Ctrl::DoPropExchange - �־���֧��

void CMFCActiveXControl�ؼ�Ctrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO:  Ϊÿ���־õ��Զ������Ե��� PX_ ������
	PX_Short(pPX, _T("Interal"), m_Interal, 1000);
}


// CMFCActiveXControl�ؼ�Ctrl::OnResetState - ���ؼ�����ΪĬ��״̬

void CMFCActiveXControl�ؼ�Ctrl::OnResetState()
{
	COleControl::OnResetState();  // ���� DoPropExchange ���ҵ���Ĭ��ֵ

	// TODO:  �ڴ��������������ؼ�״̬��
}


// CMFCActiveXControl�ؼ�Ctrl::AboutBox - ���û���ʾ�����ڡ���

void CMFCActiveXControl�ؼ�Ctrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_MFCACTIVEXCONTROL);
	dlgAbout.DoModal();
}


// CMFCActiveXControl�ؼ�Ctrl ��Ϣ�������


int CMFCActiveXControl�ؼ�Ctrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	if (m_timer != 1)
	{
		m_timer = SetTimer(1, m_Interal, NULL);
	}
	
	return 0;
}


void CMFCActiveXControl�ؼ�Ctrl::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == 1&&AmbientUserMode())
		Invalidate();
	COleControl::OnTimer(nIDEvent);
}


void CMFCActiveXControl�ؼ�Ctrl::OncustomChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:  �ڴ�������Դ���������
	AfxMessageBox(_T("shuxing"));
	SetModifiedFlag();
}


//void CMFCActiveXControl�ؼ�Ctrl::OnMButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	AfxMessageBox(_T("a"));
//
//	COleControl::OnMButtonDblClk(nFlags, point);
//}


void CMFCActiveXControl�ؼ�Ctrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	MyEvent2(_T("nihao "));
	AfxMessageBox(_T("dbclickk"));
	COleControl::OnLButtonDblClk(nFlags, point);
}


void CMFCActiveXControl�ؼ�Ctrl::MyMethod(LPCTSTR msg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	// TODO:  �ڴ���ӵ��ȴ���������
	AfxMessageBox(msg);
}


VARIANT_BOOL CMFCActiveXControl�ؼ�Ctrl::GetmyProperty(VARIANT_BOOL mproperty)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:  �ڴ���ӵ��ȴ���������
	AfxMessageBox(_T("get"));
	return VARIANT_TRUE;
}


void CMFCActiveXControl�ؼ�Ctrl::SetmyProperty(VARIANT_BOOL mproperty, VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:  �ڴ�������Դ���������
	AfxMessageBox(_T("set"));
	SetModifiedFlag();
}


VARIANT_BOOL CMFCActiveXControl�ؼ�Ctrl::Getmyproperty2(VARIANT_BOOL msg2)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:  �ڴ���ӵ��ȴ���������

	return VARIANT_TRUE;
}


void CMFCActiveXControl�ؼ�Ctrl::Setmyproperty2(VARIANT_BOOL msg2, VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:  �ڴ�������Դ���������

	SetModifiedFlag();
}


BSTR CMFCActiveXControl�ؼ�Ctrl::GetmyProperty()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO:  �ڴ���ӵ��ȴ���������

	return strResult.AllocSysString();
}


void CMFCActiveXControl�ؼ�Ctrl::SetmyProperty(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:  �ڴ�������Դ���������

	SetModifiedFlag();
}


BSTR CMFCActiveXControl�ؼ�Ctrl::Getm1(LPCTSTR msg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO:  �ڴ���ӵ��ȴ���������

	return strResult.AllocSysString();
}


void CMFCActiveXControl�ؼ�Ctrl::Setm1(LPCTSTR msg, LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:  �ڴ�������Դ���������

	SetModifiedFlag();
}


void CMFCActiveXControl�ؼ�Ctrl::OnInteralChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:  �ڴ�������Դ���������
	if (m_Interal<0 || m_Interal>6000)
	{
		m_Interal = 1000;
	}
	else
	{
		m_Interal = m_Interal / 1000 * 1000;
	}
	/*if (AmbientUserMode())
	{
		
	}*/
	::KillTimer(m_hWnd, 1);
	m_timer = ::SetTimer(m_hWnd, 1, m_Interal, NULL);
	MessageBox(_T("interval"));
	BoundPropertyChanged(0x7);
	SetModifiedFlag();
}


int CMFCActiveXControl�ؼ�Ctrl::MyMethod2()
{
	return 0;
}


int CMFCActiveXControl�ؼ�Ctrl::m2()
{
	return 0;
}


void CMFCActiveXControl�ؼ�Ctrl::hallo()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:  �ڴ���ӵ��ȴ���������
	MessageBox(_T("hallo"));
}


void CMFCActiveXControl�ؼ�Ctrl::OnaaaChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:  �ڴ�������Դ���������

	SetModifiedFlag();
}
