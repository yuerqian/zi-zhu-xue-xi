
// ChildView.cpp : CChildView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CChildView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_PIPE_READ, &CChildView::OnPipeRead)
	ON_COMMAND(IDM_PIPE_WRITE, &CChildView::OnPipeWrite)
END_MESSAGE_MAP()

// CChildView 构造/析构

CChildView::CChildView()
{
	// TODO:  在此处添加构造代码
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
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CChildView 绘制

void CChildView::OnDraw(CDC* /*pDC*/)
{
	CChildDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CChildView 打印


void CChildView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CChildView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CChildView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CChildView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
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


// CChildView 诊断

#ifdef _DEBUG
void CChildView::AssertValid() const
{
	CView::AssertValid();
}

void CChildView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChildDoc* CChildView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChildDoc)));
	return (CChildDoc*)m_pDocument;
}
#endif //_DEBUG


// CChildView 消息处理程序
LPOVERLAPPED_COMPLETION_ROUTINE CALLBACK CChildView::AsynRead(DWORD dwErrorCode,
	DWORD dwNumberOfBytesTransfered,
	LPOVERLAPPED lpOverlapped)
{
	LPOVERLAPPED_COMPLETION_ROUTINE aa={0};
	MessageBox("回调函数");
	return aa;
}

void CChildView::OnPipeRead()
{
	// TODO:  在此添加命令处理程序代码
	char Buf[100];
	DWORD dwRead;
	OVERLAPPED obRead = { 0 };
	DWORD FF = { 0 };
	DWORD dwNumread;
	obRead.hEvent = NULL;
	//WaitForSingleObject(g_Event, INFINITE);
	if (!ReadFileEx(hRead, Buf, 100, &obRead,AsynRead(FF, 100, &obRead)))
	{
		MessageBox("读取数据失败！");
		return;
	}
	GetOverlappedResult(hRead, &obRead, &dwNumread, true);
	if (strlen(Buf)>0)
	   MessageBox(Buf);
}


void CChildView::OnPipeWrite()
{
	// TODO:  在此添加命令处理程序代码
	char buf[] = "匿名管道测试";
	DWORD dwWrite = { 0 };
	OVERLAPPED odWrite = { 0 };
	if (!WriteFileEx(hWrite, buf, strlen(buf) + 1, &odWrite, NULL))
	{
		MessageBox("写入数据！");
		return;
	}
}


void CChildView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	hRead = GetStdHandle(STD_INPUT_HANDLE);
	hWrite = GetStdHandle(STD_OUTPUT_HANDLE);
	g_Event=CreateEvent(NULL, FALSE, TRUE, "HALLO");
}


