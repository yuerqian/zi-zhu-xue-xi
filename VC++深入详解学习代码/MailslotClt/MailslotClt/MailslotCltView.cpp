
// MailslotCltView.cpp : CMailslotCltView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MailslotClt.h"
#endif

#include "MailslotCltDoc.h"
#include "MailslotCltView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMailslotCltView

IMPLEMENT_DYNCREATE(CMailslotCltView, CView)

BEGIN_MESSAGE_MAP(CMailslotCltView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMailslotCltView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_MAILSLOT_SEND, &CMailslotCltView::OnMailslotSend)
END_MESSAGE_MAP()

// CMailslotCltView ����/����

CMailslotCltView::CMailslotCltView()
{
	// TODO:  �ڴ˴���ӹ������

}

CMailslotCltView::~CMailslotCltView()
{
}

BOOL CMailslotCltView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMailslotCltView ����

void CMailslotCltView::OnDraw(CDC* /*pDC*/)
{
	CMailslotCltDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMailslotCltView ��ӡ


void CMailslotCltView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMailslotCltView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMailslotCltView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMailslotCltView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}

void CMailslotCltView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMailslotCltView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMailslotCltView ���

#ifdef _DEBUG
void CMailslotCltView::AssertValid() const
{
	CView::AssertValid();
}

void CMailslotCltView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMailslotCltDoc* CMailslotCltView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMailslotCltDoc)));
	return (CMailslotCltDoc*)m_pDocument;
}
#endif //_DEBUG


// CMailslotCltView ��Ϣ�������


void CMailslotCltView::OnMailslotSend()
{
	// TODO:  �ڴ���������������
	HANDLE hMailslot;
	hMailslot=CreateFile("\\\\.\\mailslot\\MyMaislot", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hMailslot == INVALID_HANDLE_VALUE)
	{
		MessageBox("���ʲ�ʧ�ܣ�");
		return;
	}
	char buf[] = "nihao1";
	DWORD dwWrite;
	if (!WriteFile(hMailslot, buf, strlen(buf) + 1, &dwWrite, NULL))
	{
		MessageBox("д������ʧ�ܣ�");
		return;
	}
	char buf1[] = "hallo";
	strcpy_s(buf,strlen(buf)+1, buf1);
	if (!WriteFile(hMailslot, buf, strlen(buf) + 1, &dwWrite, NULL))//����д�룬����������Ϣ���ڷ����ͨ��GetMailslotInfo��ȡ��Ϣ������ÿһ��WriteFile�ʲ۵���Ϣ������1��ͨ����Ϣ������ζ�ȡ����
	{
		MessageBox("д������ʧ�ܣ�");
		return;
	}
	CloseHandle(hMailslot);
}
