// MFCActiveXControl�ؼ�PropPage.cpp : CMFCActiveXControl�ؼ�PropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "MFCActiveXControl�ؼ�.h"
#include "MFCActiveXControl�ؼ�PropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMFCActiveXControl�ؼ�PropPage, COlePropertyPage)

// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CMFCActiveXControl�ؼ�PropPage, COlePropertyPage)
END_MESSAGE_MAP()

// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CMFCActiveXControl�ؼ�PropPage, "MFCACTIVEXCONT.MFCActiveXContPropPage.1",
	0xbb04f957, 0xe33e, 0x48a8, 0xb8, 0x75, 0x89, 0x72, 0x1f, 0x51, 0x4e, 0x1)

// CMFCActiveXControl�ؼ�PropPage::CMFCActiveXControl�ؼ�PropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CMFCActiveXControl�ؼ�PropPage ��ϵͳע�����

BOOL CMFCActiveXControl�ؼ�PropPage::CMFCActiveXControl�ؼ�PropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_MFCACTIVEXCONTROL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

// CMFCActiveXControl�ؼ�PropPage::CMFCActiveXControl�ؼ�PropPage - ���캯��

CMFCActiveXControl�ؼ�PropPage::CMFCActiveXControl�ؼ�PropPage() :
	COlePropertyPage(IDD, IDS_MFCACTIVEXCONTROL_PPG_CAPTION)
	, m_UpdateInterval(0)
{
}

// CMFCActiveXControl�ؼ�PropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CMFCActiveXControl�ؼ�PropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_Text(pDX, IDC_EDIT1_INTERVAL, m_UpdateInterval, _T("Interal"));
	DDX_Text(pDX, IDC_EDIT1_INTERVAL, m_UpdateInterval);
	DDP_PostProcessing(pDX);
	//  DDX_Text(pDX, IDC_EDIT1_INTERVAL, m_UpdateInterval);
	//  DDX_Text(pDX, IDC_EDIT1_INTERVAL, m_UpdateInterval);
}

// CMFCActiveXControl�ؼ�PropPage ��Ϣ�������
