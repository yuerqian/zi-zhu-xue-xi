
// ParentView.cpp : CParentView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Parent.h"
#endif

#include "ParentDoc.h"
#include "ParentView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CParentView

IMPLEMENT_DYNCREATE(CParentView, CView)

BEGIN_MESSAGE_MAP(CParentView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CParentView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_PIPE_READ, &CParentView::OnPipeRead)
	ON_COMMAND(IDM_PIPE_CREATE, &CParentView::OnPipeCreate)
	ON_COMMAND(IDM_PAPE_WRITE, &CParentView::OnPapeWrite)
END_MESSAGE_MAP()

// CParentView ����/����

CParentView::CParentView()
{
	// TODO:  �ڴ˴���ӹ������
	hWrite = NULL;
	hRead = NULL;

}

CParentView::~CParentView()
{
	if (hWrite)
		CloseHandle(hWrite);
	if (hRead)
		CloseHandle(hRead);

}

BOOL CParentView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CParentView ����

void CParentView::OnDraw(CDC* /*pDC*/)
{
	CParentDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CParentView ��ӡ


void CParentView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CParentView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CParentView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CParentView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}

void CParentView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CParentView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CParentView ���

#ifdef _DEBUG
void CParentView::AssertValid() const
{
	CView::AssertValid();
}

void CParentView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CParentDoc* CParentView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CParentDoc)));
	return (CParentDoc*)m_pDocument;
}
#endif //_DEBUG


// CParentView ��Ϣ�������


void CParentView::OnPipeRead()
{
	// TODO:  �ڴ���������������
	char Buf[100];
	DWORD dwRead;
	if (!ReadFile(hRead, Buf, 100, &dwRead, NULL))
	{
		MessageBox("��ȡ����ʧ�ܣ�");
		return;
	}
	MessageBox(Buf);
}


void CParentView::OnPipeCreate()
{
	// TODO:  �ڴ���������������
	SECURITY_ATTRIBUTES sa;
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))//�����ܵ�
	{
		MessageBox("���������ܵ�ʧ�ܣ�");
		return;
	}
	STARTUPINFO sui;
	PROCESS_INFORMATION pi;
	ZeroMemory(&sui,sizeof(STARTUPINFO));//��STARTUPINFO�ṹ������г�Ա��ʼ��Ϊ0���������ֵ����Ӱ��
	sui.cb = sizeof(STARTUPINFO);
	sui.dwFlags = STARTF_USESTDHANDLES;
	sui.hStdInput = hRead;
	sui.hStdOutput = hWrite;
	sui.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	if (!CreateProcess("..//..//Child//Debug//Child.exe", NULL, NULL, NULL, TRUE, 0, NULL, NULL, &sui, &pi))//�����ӽ���
	{
		CloseHandle(hRead);
		CloseHandle(hWrite);
		hRead = NULL;
		hWrite = NULL;//Ϊ�˱���ParentView������������ٴε���CloseHandle�����ر���Щ���������������ΪNULL
		MessageBox("�����ӽ���ʧ�ܣ�");
		return;
	}
	else
	{
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
}


void CParentView::OnPapeWrite()
{
	// TODO:  �ڴ���������������
	char buf[]="nihao";
	DWORD dwWrite;
	OVERLAPPED obWrite = { 0 };
	
	if (!WriteFile(hWrite, buf, strlen(buf) + 1, &dwWrite, NULL))
	{
		MessageBox("д������ʧ�ܣ�");
		return;
	}
}
