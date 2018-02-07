
// NamePipeCltView.cpp : CNamePipeCltView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "NamePipeClt.h"
#endif

#include "NamePipeCltDoc.h"
#include "NamePipeCltView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNamePipeCltView

IMPLEMENT_DYNCREATE(CNamePipeCltView, CView)

BEGIN_MESSAGE_MAP(CNamePipeCltView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CNamePipeCltView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_PIPE_CONNECT, &CNamePipeCltView::OnPipeConnect)
	ON_COMMAND(IDM_PIPE_READ, &CNamePipeCltView::OnPipeRead)
	ON_COMMAND(IDM_PIPE_WRITE, &CNamePipeCltView::OnPipeWrite)
END_MESSAGE_MAP()

// CNamePipeCltView ����/����

CNamePipeCltView::CNamePipeCltView()
{
	// TODO:  �ڴ˴���ӹ������
	hPipe = NULL;

}

CNamePipeCltView::~CNamePipeCltView()
{
	if (hPipe)
		CloseHandle(hPipe);
}

BOOL CNamePipeCltView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CNamePipeCltView ����

void CNamePipeCltView::OnDraw(CDC* /*pDC*/)
{
	CNamePipeCltDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CNamePipeCltView ��ӡ


void CNamePipeCltView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CNamePipeCltView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CNamePipeCltView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CNamePipeCltView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}

void CNamePipeCltView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CNamePipeCltView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CNamePipeCltView ���

#ifdef _DEBUG
void CNamePipeCltView::AssertValid() const
{
	CView::AssertValid();
}

void CNamePipeCltView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNamePipeCltDoc* CNamePipeCltView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNamePipeCltDoc)));
	return (CNamePipeCltDoc*)m_pDocument;
}
#endif //_DEBUG


// CNamePipeCltView ��Ϣ�������


void CNamePipeCltView::OnPipeConnect()
{
	// TODO:  �ڴ���������������
	//�ж��Ƿ��п������õ������ܵ�
	if (!WaitNamedPipe("\\\\.\\pipe\\MyPipe", NMPWAIT_USE_DEFAULT_WAIT))
	{
		MessageBox("��ǰû�п������õ������ܵ�");
		return;
	}
	//�򿪿��õ������ܵ�������������˽��̽���ͨ��
	hPipe = CreateFile("\\\\.\\pipe\\MyPipe", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hPipe == INVALID_HANDLE_VALUE)
	{
		MessageBox("�򿪹ܵ�ʧ�ܣ�");
		hPipe = NULL;
		return;
	}
}


void CNamePipeCltView::OnPipeRead()
{
	// TODO:  �ڴ���������������
	char buf[1024];
	DWORD dwRead;
	if (!ReadFile(hPipe, buf, 1024, &dwRead, NULL))
	{
		MessageBox("��ȡ����ʧ�ܣ�");
		return;
	}
	MessageBox(buf);
}


void CNamePipeCltView::OnPipeWrite()
{
	// TODO:  �ڴ���������������
	char buf[] = "Client is connect";
	DWORD dwWrite;
	if (!WriteFile(hPipe, buf, strlen(buf)+1, &dwWrite, NULL))
	{
		MessageBox("д������ʧ�ܣ�");
		return;
	}

}
