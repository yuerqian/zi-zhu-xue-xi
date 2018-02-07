// ActiveXPropPage.cpp : CActiveXPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "ActiveX.h"
#include "ActiveXPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CActiveXPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CActiveXPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CActiveXPropPage, "ACTIVEX.ActiveXPropPage.1",
	0x4050254a, 0x4ac5, 0x4560, 0xaa, 0xe0, 0x73, 0xc3, 0x37, 0x64, 0x7c, 0x69)



// CActiveXPropPage::CActiveXPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CActiveXPropPage ��ϵͳע�����

BOOL CActiveXPropPage::CActiveXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_ACTIVEX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CActiveXPropPage::CActiveXPropPage - ���캯��

CActiveXPropPage::CActiveXPropPage() :
	COlePropertyPage(IDD, IDS_ACTIVEX_PPG_CAPTION)
{
}



// CActiveXPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CActiveXPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CActiveXPropPage ��Ϣ�������
