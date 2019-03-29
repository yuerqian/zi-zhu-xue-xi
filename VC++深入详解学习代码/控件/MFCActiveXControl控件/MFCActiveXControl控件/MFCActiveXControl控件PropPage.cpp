// MFCActiveXControl控件PropPage.cpp : CMFCActiveXControl控件PropPage 属性页类的实现。

#include "stdafx.h"
#include "MFCActiveXControl控件.h"
#include "MFCActiveXControl控件PropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMFCActiveXControl控件PropPage, COlePropertyPage)

// 消息映射

BEGIN_MESSAGE_MAP(CMFCActiveXControl控件PropPage, COlePropertyPage)
END_MESSAGE_MAP()

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CMFCActiveXControl控件PropPage, "MFCACTIVEXCONT.MFCActiveXContPropPage.1",
	0xbb04f957, 0xe33e, 0x48a8, 0xb8, 0x75, 0x89, 0x72, 0x1f, 0x51, 0x4e, 0x1)

// CMFCActiveXControl控件PropPage::CMFCActiveXControl控件PropPageFactory::UpdateRegistry -
// 添加或移除 CMFCActiveXControl控件PropPage 的系统注册表项

BOOL CMFCActiveXControl控件PropPage::CMFCActiveXControl控件PropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_MFCACTIVEXCONTROL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

// CMFCActiveXControl控件PropPage::CMFCActiveXControl控件PropPage - 构造函数

CMFCActiveXControl控件PropPage::CMFCActiveXControl控件PropPage() :
	COlePropertyPage(IDD, IDS_MFCACTIVEXCONTROL_PPG_CAPTION)
	, m_UpdateInterval(0)
{
}

// CMFCActiveXControl控件PropPage::DoDataExchange - 在页和属性间移动数据

void CMFCActiveXControl控件PropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_Text(pDX, IDC_EDIT1_INTERVAL, m_UpdateInterval, _T("Interal"));
	DDX_Text(pDX, IDC_EDIT1_INTERVAL, m_UpdateInterval);
	DDP_PostProcessing(pDX);
	//  DDX_Text(pDX, IDC_EDIT1_INTERVAL, m_UpdateInterval);
	//  DDX_Text(pDX, IDC_EDIT1_INTERVAL, m_UpdateInterval);
}

// CMFCActiveXControl控件PropPage 消息处理程序
