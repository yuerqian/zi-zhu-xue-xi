// ClockPropPage.cpp : CClockPropPage 属性页类的实现。

#include "stdafx.h"
#include "Clock.h"
#include "ClockPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CClockPropPage, COlePropertyPage)

// 消息映射

BEGIN_MESSAGE_MAP(CClockPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CClockPropPage, "CLOCK.ClockPropPage.1",
	0xddeae91d, 0xe8d0, 0x49ec, 0x85, 0xa9, 0xfb, 0x1, 0x2f, 0xca, 0x5d, 0x9f)

// CClockPropPage::CClockPropPageFactory::UpdateRegistry -
// 添加或移除 CClockPropPage 的系统注册表项

BOOL CClockPropPage::CClockPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_CLOCK_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

// CClockPropPage::CClockPropPage - 构造函数

CClockPropPage::CClockPropPage() :
	COlePropertyPage(IDD, IDS_CLOCK_PPG_CAPTION)
{
}

// CClockPropPage::DoDataExchange - 在页和属性间移动数据

void CClockPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CClockPropPage 消息处理程序
