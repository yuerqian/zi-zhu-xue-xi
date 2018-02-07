
// NamePipeSrvView.cpp : CNamePipeSrvView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "NamePipeSrv.h"
#endif

#include "NamePipeSrvDoc.h"
#include "NamePipeSrvView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNamePipeSrvView

IMPLEMENT_DYNCREATE(CNamePipeSrvView, CView)

BEGIN_MESSAGE_MAP(CNamePipeSrvView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CNamePipeSrvView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_PIPE_CREATE, &CNamePipeSrvView::OnPipeCreate)
	ON_COMMAND(IDM_PIPE_READ, &CNamePipeSrvView::OnPipeRead)
	ON_COMMAND(IDM_PIPE_WRITE, &CNamePipeSrvView::OnPipeWrite)
END_MESSAGE_MAP()

// CNamePipeSrvView ����/����

CNamePipeSrvView::CNamePipeSrvView()
{
	// TODO:  �ڴ˴���ӹ������
	hPipe = NULL;
}

CNamePipeSrvView::~CNamePipeSrvView()
{
	if (hPipe)
		CloseHandle(hPipe);
}

BOOL CNamePipeSrvView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CNamePipeSrvView ����

void CNamePipeSrvView::OnDraw(CDC* /*pDC*/)
{
	CNamePipeSrvDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CNamePipeSrvView ��ӡ


void CNamePipeSrvView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CNamePipeSrvView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CNamePipeSrvView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CNamePipeSrvView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}

void CNamePipeSrvView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CNamePipeSrvView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CNamePipeSrvView ���

#ifdef _DEBUG
void CNamePipeSrvView::AssertValid() const
{
	CView::AssertValid();
}

void CNamePipeSrvView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNamePipeSrvDoc* CNamePipeSrvView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNamePipeSrvDoc)));
	return (CNamePipeSrvDoc*)m_pDocument;
}
#endif //_DEBUG


// CNamePipeSrvView ��Ϣ�������


void CNamePipeSrvView::OnPipeCreate()
{
	// TODO:  �ڴ���������������
	//���������ܵ�

	hPipe=CreateNamedPipe("\\\\.\\pipe\\Mypipe", PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED, 0, 1, 1024, 1024, 0, NULL);
	if (hPipe == INVALID_HANDLE_VALUE)
	{
		MessageBox("���������ܵ�ʧ�ܣ�");
		hPipe = NULL;
		return;
	}
	//�����������˹������¼�
	HANDLE hEvent;
	hEvent=CreateEvent(NULL, TRUE, FALSE, NULL);
	if (!hEvent)
	{
		MessageBox("�����˹������¼�ʧ�ܣ�");
		CloseHandle(hEvent);
		hPipe = NULL;
		return;
	}
	//�ȴ��ͻ�����ĵ���
	OVERLAPPED ovlap;
	ZeroMemory(&ovlap,sizeof(OVERLAPPED));
	ovlap.hEvent = hEvent;
	if (!ConnectNamedPipe(hPipe, &ovlap))
	{
		if (GetLastError() != ERROR_IO_PENDING)
		{
			MessageBox("�ȴ��ͻ�����ʧ�ܣ�");
			CloseHandle(hPipe);//��ʾ���������ʹ�ã��þ������ָ��CreateNamedPipe
			CloseHandle(hEvent);
			hPipe = NULL;//��ʾ�������ʹ�ã�ָ����ǿ�ֵ,ͬʱ��������������ʱ�ٴιرա�
			return;
		}
	}

	if (WaitForSingleObject(hEvent, INFINITE) == WAIT_FAILED)
	{
		MessageBox("�ȴ�����ʧ��");
		CloseHandle(hPipe);
		CloseHandle(hEvent);
		hPipe = NULL;
		return;
	}
	CloseHandle(hEvent);

}


void CNamePipeSrvView::OnPipeRead()
{
	// TODO:  �ڴ���������������
	char buf[1024];
	DWORD readnum;
	if (!ReadFile(hPipe, buf, 1024, &readnum, NULL))
	{
		MessageBox("��ȡ����ʧ�ܣ�");
		return;
	}
	MessageBox(buf);
}


void CNamePipeSrvView::OnPipeWrite()
{
	// TODO:  �ڴ���������������
	char buf[] = "���";
	DWORD WriteNum;
	if (!WriteFile(hPipe, buf, strlen(buf)+1, &WriteNum, NULL))
	{
		MessageBox("д������ʧ�ܣ�");
		return;
	}
}
