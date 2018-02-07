
// ChildView.cpp : CChildView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Child.h"
#endif

#include "ChildDoc.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

IMPLEMENT_DYNCREATE(CChildView, CView)

BEGIN_MESSAGE_MAP(CChildView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CChildView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_PIPE_READ, &CChildView::OnPipeRead)
	ON_COMMAND(IDM_PIPE_WRITE, &CChildView::OnPipeWrite)
END_MESSAGE_MAP()

// CChildView ����/����

CChildView::CChildView()
{
	// TODO:  �ڴ˴���ӹ������
	hRead = NULL;
	hWrite = NULL;

}

CChildView::~CChildView()
{
	if (hRead)
		CloseHandle(hRead);
	if (hWrite)
		CloseHandle(hWrite);
}

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CChildView ����

void CChildView::OnDraw(CDC* /*pDC*/)
{
	CChildDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CChildView ��ӡ


void CChildView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CChildView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CChildView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CChildView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}

void CChildView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CChildView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CChildView ���

#ifdef _DEBUG
void CChildView::AssertValid() const
{
	CView::AssertValid();
}

void CChildView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChildDoc* CChildView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChildDoc)));
	return (CChildDoc*)m_pDocument;
}
#endif //_DEBUG


// CChildView ��Ϣ�������
LPOVERLAPPED_COMPLETION_ROUTINE CALLBACK CChildView::AsynRead(DWORD dwErrorCode,
	DWORD dwNumberOfBytesTransfered,
	LPOVERLAPPED lpOverlapped)
{
	LPOVERLAPPED_COMPLETION_ROUTINE aa={0};
	MessageBox("�ص�����");
	return aa;
}

void CChildView::OnPipeRead()
{
	// TODO:  �ڴ���������������
	char Buf[100];
	DWORD dwRead;
	OVERLAPPED obRead = { 0 };
	DWORD FF = { 0 };
	DWORD dwNumread;
	obRead.hEvent = NULL;
	//WaitForSingleObject(g_Event, INFINITE);
	if (!ReadFileEx(hRead, Buf, 100, &obRead,AsynRead(FF, 100, &obRead)))
	{
		MessageBox("��ȡ����ʧ�ܣ�");
		return;
	}
	GetOverlappedResult(hRead, &obRead, &dwNumread, true);
	if (strlen(Buf)>0)
	   MessageBox(Buf);
}


void CChildView::OnPipeWrite()
{
	// TODO:  �ڴ���������������
	char buf[] = "�����ܵ�����";
	DWORD dwWrite = { 0 };
	OVERLAPPED odWrite = { 0 };
	if (!WriteFileEx(hWrite, buf, strlen(buf) + 1, &odWrite, NULL))
	{
		MessageBox("д�����ݣ�");
		return;
	}
}


void CChildView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���
	hRead = GetStdHandle(STD_INPUT_HANDLE);
	hWrite = GetStdHandle(STD_OUTPUT_HANDLE);
	g_Event=CreateEvent(NULL, FALSE, TRUE, "HALLO");
}


