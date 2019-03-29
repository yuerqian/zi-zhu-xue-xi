// ActiveXCtrl.cpp : CActiveXCtrl ActiveX �ؼ����ʵ�֡�

#include "stdafx.h"
#include "ActiveX.h"
#include "ActiveXCtrl.h"
#include "ActiveXPropPage.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CActiveXCtrl, COleControl)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CActiveXCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()



// ����ӳ��

BEGIN_DISPATCH_MAP(CActiveXCtrl, COleControl)
	DISP_FUNCTION_ID(CActiveXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()



// �¼�ӳ��

BEGIN_EVENT_MAP(CActiveXCtrl, COleControl)
END_EVENT_MAP()



// ����ҳ

// TODO: ����Ҫ��Ӹ�������ҳ�����ס���Ӽ���!
BEGIN_PROPPAGEIDS(CActiveXCtrl, 1)
	PROPPAGEID(CActiveXPropPage::guid)
END_PROPPAGEIDS(CActiveXCtrl)



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CActiveXCtrl, "ACTIVEX.ActiveXCtrl.1",
	0xd33f6026, 0xff75, 0x4769, 0x8e, 0xeb, 0xbb, 0xc9, 0xc8, 0x8f, 0xee, 0x3)



// ����� ID �Ͱ汾

IMPLEMENT_OLETYPELIB(CActiveXCtrl, _tlid, _wVerMajor, _wVerMinor)



// �ӿ� ID

const IID IID_DActiveX = { 0x3F4DA7D3, 0x959C, 0x486E, { 0x95, 0xAF, 0xDA, 0x7F, 0xE3, 0xD8, 0xD2, 0xB4 } };
const IID IID_DActiveXEvents = { 0x1E70B72B, 0xCD4E, 0x4C04, { 0xA8, 0x3C, 0x75, 0x1F, 0x38, 0xCE, 0xC8, 0x7 } };


// �ؼ�������Ϣ

static const DWORD _dwActiveXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CActiveXCtrl, IDS_ACTIVEX, _dwActiveXOleMisc)



// CActiveXCtrl::CActiveXCtrlFactory::UpdateRegistry -
// ��ӻ��Ƴ� CActiveXCtrl ��ϵͳע�����

BOOL CActiveXCtrl::CActiveXCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: ��֤���Ŀؼ��Ƿ���ϵ�Ԫģ���̴߳������
	// �йظ�����Ϣ����ο� MFC ����˵�� 64��
	// ������Ŀؼ������ϵ�Ԫģ�͹�����
	// �����޸����´��룬��������������
	// afxRegApartmentThreading ��Ϊ 0��

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_ACTIVEX,
			IDB_ACTIVEX,
			afxRegApartmentThreading,
			_dwActiveXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CActiveXCtrl::CActiveXCtrl - ���캯��

CActiveXCtrl::CActiveXCtrl()
{
	InitializeIIDs(&IID_DActiveX, &IID_DActiveXEvents);
	// TODO: �ڴ˳�ʼ���ؼ���ʵ�����ݡ�
}



// CActiveXCtrl::~CActiveXCtrl - ��������

CActiveXCtrl::~CActiveXCtrl()
{
	// TODO: �ڴ�����ؼ���ʵ�����ݡ�
}



// CActiveXCtrl::OnDraw - ��ͼ����

void CActiveXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: �����Լ��Ļ�ͼ�����滻����Ĵ��롣
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}



// CActiveXCtrl::DoPropExchange - �־���֧��

void CActiveXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Ϊÿ���־õ��Զ������Ե��� PX_ ������
}



// CActiveXCtrl::OnResetState - ���ؼ�����ΪĬ��״̬

void CActiveXCtrl::OnResetState()
{
	COleControl::OnResetState();  // ���� DoPropExchange ���ҵ���Ĭ��ֵ

	// TODO: �ڴ��������������ؼ�״̬��
}



// CActiveXCtrl::AboutBox - ���û���ʾ�����ڡ���

void CActiveXCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_ACTIVEX);
	dlgAbout.DoModal();
}



// CActiveXCtrl ��Ϣ�������
