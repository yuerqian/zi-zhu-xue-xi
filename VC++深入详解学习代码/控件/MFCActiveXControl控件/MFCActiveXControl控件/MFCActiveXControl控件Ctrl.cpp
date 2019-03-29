// MFCActiveXControl控件Ctrl.cpp : CMFCActiveXControl控件Ctrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "MFCActiveXControl控件.h"
#include "MFCActiveXControl控件Ctrl.h"
#include "MFCActiveXControl控件PropPage.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMFCActiveXControl控件Ctrl, COleControl)

// 消息映射

BEGIN_MESSAGE_MAP(CMFCActiveXControl控件Ctrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_TIMER()
//	ON_WM_MBUTTONDBLCLK()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// 调度映射

BEGIN_DISPATCH_MAP(CMFCActiveXControl控件Ctrl, COleControl)
	DISP_FUNCTION_ID(CMFCActiveXControl控件Ctrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_STOCKPROP_BACKCOLOR()
	DISP_STOCKPROP_FORECOLOR()
	DISP_PROPERTY_NOTIFY_ID(CMFCActiveXControl控件Ctrl, "custom", dispidcustom, m_custom, OncustomChanged, VT_I1)
	DISP_STOCKFUNC_DOCLICK()
	DISP_FUNCTION_ID(CMFCActiveXControl控件Ctrl, "MyMethod", dispidMyMethod, MyMethod, VT_EMPTY, VTS_BSTR)
	/*DISP_PROPERTY_PARAM_ID(CMFCActiveXControl控件Ctrl, "myProperty", dispidmyProperty, GetmyProperty, SetmyProperty, VT_BOOL, VTS_BOOL)*/
	DISP_PROPERTY_PARAM_ID(CMFCActiveXControl控件Ctrl, "myproperty2", dispidmyproperty2, Getmyproperty2, Setmyproperty2, VT_BOOL, VTS_BOOL)
	//DISP_PROPERTY_EX_ID(CMFCActiveXControl控件Ctrl, "myProperty", dispidmyProperty, GetmyProperty, SetmyProperty, VT_BSTR)
	DISP_PROPERTY_PARAM_ID(CMFCActiveXControl控件Ctrl, "m1", dispidm1, Getm1, Setm1, VT_BSTR, VTS_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CMFCActiveXControl控件Ctrl, "Interal", dispidInteral, m_Interal, OnInteralChanged, VT_I2)
	DISP_FUNCTION_ID(CMFCActiveXControl控件Ctrl, "hallo", dispidhallo, hallo, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_NOTIFY_ID(CMFCActiveXControl控件Ctrl, "aaa", dispidaaa, m_aaa, OnaaaChanged, VT_BSTR)
END_DISPATCH_MAP()

// 事件映射

BEGIN_EVENT_MAP(CMFCActiveXControl控件Ctrl, COleControl)
	EVENT_STOCK_CLICK()
	EVENT_CUSTOM_ID("Myevent", eventidMyevent, Myevent, VTS_NONE)
	EVENT_CUSTOM_ID("MyEvent2", eventidMyEvent2, MyEvent2, VTS_BSTR)
END_EVENT_MAP()

// 属性页

// TODO:  按需要添加更多属性页。  请记住增加计数!
BEGIN_PROPPAGEIDS(CMFCActiveXControl控件Ctrl, 2)
	PROPPAGEID(CMFCActiveXControl控件PropPage::guid)
	PROPPAGEID(CLSID_CColorPropPage);
END_PROPPAGEIDS(CMFCActiveXControl控件Ctrl)

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CMFCActiveXControl控件Ctrl, "MFCACTIVEXCONTRO.MFCActiveXControCtrl.1",
	0x5d7fe87e, 0x11da, 0x4e62, 0x8b, 0x9c, 0x65, 0xa, 0x4e, 0xd9, 0xf, 0xda)

// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CMFCActiveXControl控件Ctrl, _tlid, _wVerMajor, _wVerMinor)

// 接口 ID

const IID IID_DMFCActiveXControl控件 = { 0x76028768, 0xB3C4, 0x4406, { 0xBB, 0x5F, 0x94, 0xB7, 0xC4, 0x13, 0x67, 0xFB } };
const IID IID_DMFCActiveXControl控件Events = { 0xBAD78B2F, 0x154B, 0x433F, { 0x8C, 0x1, 0x60, 0x46, 0x36, 0xF6, 0x1E, 0x96 } };

// 控件类型信息

static const DWORD _dwMFCActiveXControl控件OleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMFCActiveXControl控件Ctrl, IDS_MFCACTIVEXCONTROL, _dwMFCActiveXControl控件OleMisc)

// CMFCActiveXControl控件Ctrl::CMFCActiveXControl控件CtrlFactory::UpdateRegistry -
// 添加或移除 CMFCActiveXControl控件Ctrl 的系统注册表项

BOOL CMFCActiveXControl控件Ctrl::CMFCActiveXControl控件CtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO:  验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_MFCACTIVEXCONTROL,
			IDB_MFCACTIVEXCONTROL,
			afxRegApartmentThreading,
			_dwMFCActiveXControl控件OleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


// CMFCActiveXControl控件Ctrl::CMFCActiveXControl控件Ctrl - 构造函数

CMFCActiveXControl控件Ctrl::CMFCActiveXControl控件Ctrl()
: m_timer(0)
{
	InitializeIIDs(&IID_DMFCActiveXControl控件, &IID_DMFCActiveXControl控件Events);
	// TODO:  在此初始化控件的实例数据。
	m_timer = 0;
}

// CMFCActiveXControl控件Ctrl::~CMFCActiveXControl控件Ctrl - 析构函数

CMFCActiveXControl控件Ctrl::~CMFCActiveXControl控件Ctrl()
{
	// TODO:  在此清理控件的实例数据。
}

// CMFCActiveXControl控件Ctrl::OnDraw - 绘图函数

void CMFCActiveXControl控件Ctrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& /* rcInvalid */)
{
	if (!pdc)
		return;

	// TODO:  用您自己的绘图代码替换下面的代码。
	//pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	//pdc->Ellipse(rcBounds);

	CBrush brush(TranslateColor(GetBackColor()));
	pdc->FillRect(rcBounds,&brush);
	//if (pdc->SetBkColor(TranslateColor(GetBackColor())) == CLR_INVALID)
	//{
	//	AfxMessageBox(_T("设置背景色失败"));
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

// CMFCActiveXControl控件Ctrl::DoPropExchange - 持久性支持

void CMFCActiveXControl控件Ctrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO:  为每个持久的自定义属性调用 PX_ 函数。
	PX_Short(pPX, _T("Interal"), m_Interal, 1000);
}


// CMFCActiveXControl控件Ctrl::OnResetState - 将控件重置为默认状态

void CMFCActiveXControl控件Ctrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO:  在此重置任意其他控件状态。
}


// CMFCActiveXControl控件Ctrl::AboutBox - 向用户显示“关于”框

void CMFCActiveXControl控件Ctrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_MFCACTIVEXCONTROL);
	dlgAbout.DoModal();
}


// CMFCActiveXControl控件Ctrl 消息处理程序


int CMFCActiveXControl控件Ctrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	if (m_timer != 1)
	{
		m_timer = SetTimer(1, m_Interal, NULL);
	}
	
	return 0;
}


void CMFCActiveXControl控件Ctrl::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1&&AmbientUserMode())
		Invalidate();
	COleControl::OnTimer(nIDEvent);
}


void CMFCActiveXControl控件Ctrl::OncustomChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:  在此添加属性处理程序代码
	AfxMessageBox(_T("shuxing"));
	SetModifiedFlag();
}


//void CMFCActiveXControl控件Ctrl::OnMButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO:  在此添加消息处理程序代码和/或调用默认值
//	AfxMessageBox(_T("a"));
//
//	COleControl::OnMButtonDblClk(nFlags, point);
//}


void CMFCActiveXControl控件Ctrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	MyEvent2(_T("nihao "));
	AfxMessageBox(_T("dbclickk"));
	COleControl::OnLButtonDblClk(nFlags, point);
}


void CMFCActiveXControl控件Ctrl::MyMethod(LPCTSTR msg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	// TODO:  在此添加调度处理程序代码
	AfxMessageBox(msg);
}


VARIANT_BOOL CMFCActiveXControl控件Ctrl::GetmyProperty(VARIANT_BOOL mproperty)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:  在此添加调度处理程序代码
	AfxMessageBox(_T("get"));
	return VARIANT_TRUE;
}


void CMFCActiveXControl控件Ctrl::SetmyProperty(VARIANT_BOOL mproperty, VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:  在此添加属性处理程序代码
	AfxMessageBox(_T("set"));
	SetModifiedFlag();
}


VARIANT_BOOL CMFCActiveXControl控件Ctrl::Getmyproperty2(VARIANT_BOOL msg2)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:  在此添加调度处理程序代码

	return VARIANT_TRUE;
}


void CMFCActiveXControl控件Ctrl::Setmyproperty2(VARIANT_BOOL msg2, VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:  在此添加属性处理程序代码

	SetModifiedFlag();
}


BSTR CMFCActiveXControl控件Ctrl::GetmyProperty()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO:  在此添加调度处理程序代码

	return strResult.AllocSysString();
}


void CMFCActiveXControl控件Ctrl::SetmyProperty(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:  在此添加属性处理程序代码

	SetModifiedFlag();
}


BSTR CMFCActiveXControl控件Ctrl::Getm1(LPCTSTR msg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO:  在此添加调度处理程序代码

	return strResult.AllocSysString();
}


void CMFCActiveXControl控件Ctrl::Setm1(LPCTSTR msg, LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:  在此添加属性处理程序代码

	SetModifiedFlag();
}


void CMFCActiveXControl控件Ctrl::OnInteralChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:  在此添加属性处理程序代码
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


int CMFCActiveXControl控件Ctrl::MyMethod2()
{
	return 0;
}


int CMFCActiveXControl控件Ctrl::m2()
{
	return 0;
}


void CMFCActiveXControl控件Ctrl::hallo()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:  在此添加调度处理程序代码
	MessageBox(_T("hallo"));
}


void CMFCActiveXControl控件Ctrl::OnaaaChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:  在此添加属性处理程序代码

	SetModifiedFlag();
}
