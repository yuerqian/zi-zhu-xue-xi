
// MailslotView.cpp : CMailslotView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Mailslot.h"
#endif

#include "MailslotDoc.h"
#include "MailslotView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMailslotView

IMPLEMENT_DYNCREATE(CMailslotView, CView)

BEGIN_MESSAGE_MAP(CMailslotView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMailslotView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_MAILSLOT_RECV, &CMailslotView::OnMailslotRecv)
END_MESSAGE_MAP()

// CMailslotView ����/����

CMailslotView::CMailslotView()
{
	// TODO:  �ڴ˴���ӹ������

}

CMailslotView::~CMailslotView()
{
}

BOOL CMailslotView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMailslotView ����

void CMailslotView::OnDraw(CDC* /*pDC*/)
{
	CMailslotDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMailslotView ��ӡ


void CMailslotView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMailslotView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMailslotView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMailslotView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}

void CMailslotView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMailslotView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMailslotView ���

#ifdef _DEBUG
void CMailslotView::AssertValid() const
{
	CView::AssertValid();
}

void CMailslotView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMailslotDoc* CMailslotView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMailslotDoc)));
	return (CMailslotDoc*)m_pDocument;
}
#endif //_DEBUG


// CMailslotView ��Ϣ�������


void CMailslotView::OnMailslotRecv()
{
	// TODO:  �ڴ���������������
	HANDLE hMailslot;
	hMailslot = CreateMailslot("\\\\.\\mailslot\\MyMaislot", 0, MAILSLOT_WAIT_FOREVER, NULL);
	if (hMailslot == INVALID_HANDLE_VALUE)
	{
		MessageBox("�����ʲ�ʧ�ܣ�");
		return;
	}
	char buf[100];
	DWORD dwRead;
	DWORD CMessage,cMessageNum;
	while (1)
	{
		if (!GetMailslotInfo(hMailslot, NULL, &CMessage, &cMessageNum, NULL))
		{
			MessageBox("��ȡ�ʲ���Ϣ����");
			return;
		}
		while (cMessageNum != 0)
		{
			if (!ReadFile(hMailslot, buf, 100, &dwRead, NULL))
			{
				MessageBox("��ȡ����ʧ��");
				return;
			}
			if (!GetMailslotInfo(hMailslot, NULL, &CMessage, &cMessageNum, NULL))
			{
				MessageBox("��ȡ�ʲ���Ϣ����");
				return;
			}
			MessageBox(buf);
		}
	}
	CloseHandle(hMailslot);
}
