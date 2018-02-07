
// NamePipeCltView.cpp : CNamePipeCltView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CNamePipeCltView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_PIPE_CONNECT, &CNamePipeCltView::OnPipeConnect)
	ON_COMMAND(IDM_PIPE_READ, &CNamePipeCltView::OnPipeRead)
	ON_COMMAND(IDM_PIPE_WRITE, &CNamePipeCltView::OnPipeWrite)
END_MESSAGE_MAP()

// CNamePipeCltView 构造/析构

CNamePipeCltView::CNamePipeCltView()
{
	// TODO:  在此处添加构造代码
	hPipe = NULL;

}

CNamePipeCltView::~CNamePipeCltView()
{
	if (hPipe)
		CloseHandle(hPipe);
}

BOOL CNamePipeCltView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CNamePipeCltView 绘制

void CNamePipeCltView::OnDraw(CDC* /*pDC*/)
{
	CNamePipeCltDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CNamePipeCltView 打印


void CNamePipeCltView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CNamePipeCltView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CNamePipeCltView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CNamePipeCltView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
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


// CNamePipeCltView 诊断

#ifdef _DEBUG
void CNamePipeCltView::AssertValid() const
{
	CView::AssertValid();
}

void CNamePipeCltView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNamePipeCltDoc* CNamePipeCltView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNamePipeCltDoc)));
	return (CNamePipeCltDoc*)m_pDocument;
}
#endif //_DEBUG


// CNamePipeCltView 消息处理程序


void CNamePipeCltView::OnPipeConnect()
{
	// TODO:  在此添加命令处理程序代码
	//判断是否有可以利用的命名管道
	if (!WaitNamedPipe("\\\\.\\pipe\\MyPipe", NMPWAIT_USE_DEFAULT_WAIT))
	{
		MessageBox("当前没有可以利用的命名管道");
		return;
	}
	//打开可用的命名管道，并与服务器端进程进行通信
	hPipe = CreateFile("\\\\.\\pipe\\MyPipe", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hPipe == INVALID_HANDLE_VALUE)
	{
		MessageBox("打开管道失败！");
		hPipe = NULL;
		return;
	}
}


void CNamePipeCltView::OnPipeRead()
{
	// TODO:  在此添加命令处理程序代码
	char buf[1024];
	DWORD dwRead;
	if (!ReadFile(hPipe, buf, 1024, &dwRead, NULL))
	{
		MessageBox("读取数据失败！");
		return;
	}
	MessageBox(buf);
}


void CNamePipeCltView::OnPipeWrite()
{
	// TODO:  在此添加命令处理程序代码
	char buf[] = "Client is connect";
	DWORD dwWrite;
	if (!WriteFile(hPipe, buf, strlen(buf)+1, &dwWrite, NULL))
	{
		MessageBox("写入数据失败！");
		return;
	}

}
