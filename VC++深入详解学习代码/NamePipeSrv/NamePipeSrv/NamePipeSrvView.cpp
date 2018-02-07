
// NamePipeSrvView.cpp : CNamePipeSrvView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CNamePipeSrvView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_PIPE_CREATE, &CNamePipeSrvView::OnPipeCreate)
	ON_COMMAND(IDM_PIPE_READ, &CNamePipeSrvView::OnPipeRead)
	ON_COMMAND(IDM_PIPE_WRITE, &CNamePipeSrvView::OnPipeWrite)
END_MESSAGE_MAP()

// CNamePipeSrvView 构造/析构

CNamePipeSrvView::CNamePipeSrvView()
{
	// TODO:  在此处添加构造代码
	hPipe = NULL;
}

CNamePipeSrvView::~CNamePipeSrvView()
{
	if (hPipe)
		CloseHandle(hPipe);
}

BOOL CNamePipeSrvView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CNamePipeSrvView 绘制

void CNamePipeSrvView::OnDraw(CDC* /*pDC*/)
{
	CNamePipeSrvDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CNamePipeSrvView 打印


void CNamePipeSrvView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CNamePipeSrvView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CNamePipeSrvView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CNamePipeSrvView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
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


// CNamePipeSrvView 诊断

#ifdef _DEBUG
void CNamePipeSrvView::AssertValid() const
{
	CView::AssertValid();
}

void CNamePipeSrvView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNamePipeSrvDoc* CNamePipeSrvView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNamePipeSrvDoc)));
	return (CNamePipeSrvDoc*)m_pDocument;
}
#endif //_DEBUG


// CNamePipeSrvView 消息处理程序


void CNamePipeSrvView::OnPipeCreate()
{
	// TODO:  在此添加命令处理程序代码
	//创建命名管道

	hPipe=CreateNamedPipe("\\\\.\\pipe\\Mypipe", PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED, 0, 1, 1024, 1024, 0, NULL);
	if (hPipe == INVALID_HANDLE_VALUE)
	{
		MessageBox("创建命名管道失败！");
		hPipe = NULL;
		return;
	}
	//创建匿名的人工重置事件
	HANDLE hEvent;
	hEvent=CreateEvent(NULL, TRUE, FALSE, NULL);
	if (!hEvent)
	{
		MessageBox("创建人工重置事件失败！");
		CloseHandle(hEvent);
		hPipe = NULL;
		return;
	}
	//等待客户请求的到来
	OVERLAPPED ovlap;
	ZeroMemory(&ovlap,sizeof(OVERLAPPED));
	ovlap.hEvent = hEvent;
	if (!ConnectNamedPipe(hPipe, &ovlap))
	{
		if (GetLastError() != ERROR_IO_PENDING)
		{
			MessageBox("等待客户连接失败！");
			CloseHandle(hPipe);//表示句柄不能再使用，该句柄还是指向CreateNamedPipe
			CloseHandle(hEvent);
			hPipe = NULL;//表示句柄可以使用，指向的是空值,同时避免在析构函数时再次关闭。
			return;
		}
	}

	if (WaitForSingleObject(hEvent, INFINITE) == WAIT_FAILED)
	{
		MessageBox("等待对象失败");
		CloseHandle(hPipe);
		CloseHandle(hEvent);
		hPipe = NULL;
		return;
	}
	CloseHandle(hEvent);

}


void CNamePipeSrvView::OnPipeRead()
{
	// TODO:  在此添加命令处理程序代码
	char buf[1024];
	DWORD readnum;
	if (!ReadFile(hPipe, buf, 1024, &readnum, NULL))
	{
		MessageBox("读取数据失败！");
		return;
	}
	MessageBox(buf);
}


void CNamePipeSrvView::OnPipeWrite()
{
	// TODO:  在此添加命令处理程序代码
	char buf[] = "你好";
	DWORD WriteNum;
	if (!WriteFile(hPipe, buf, strlen(buf)+1, &WriteNum, NULL))
	{
		MessageBox("写入数据失败！");
		return;
	}
}
