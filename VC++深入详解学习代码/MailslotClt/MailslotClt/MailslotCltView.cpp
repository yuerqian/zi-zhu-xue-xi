
// MailslotCltView.cpp : CMailslotCltView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMailslotCltView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_MAILSLOT_SEND, &CMailslotCltView::OnMailslotSend)
END_MESSAGE_MAP()

// CMailslotCltView 构造/析构

CMailslotCltView::CMailslotCltView()
{
	// TODO:  在此处添加构造代码

}

CMailslotCltView::~CMailslotCltView()
{
}

BOOL CMailslotCltView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMailslotCltView 绘制

void CMailslotCltView::OnDraw(CDC* /*pDC*/)
{
	CMailslotCltDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CMailslotCltView 打印


void CMailslotCltView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMailslotCltView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMailslotCltView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMailslotCltView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
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


// CMailslotCltView 诊断

#ifdef _DEBUG
void CMailslotCltView::AssertValid() const
{
	CView::AssertValid();
}

void CMailslotCltView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMailslotCltDoc* CMailslotCltView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMailslotCltDoc)));
	return (CMailslotCltDoc*)m_pDocument;
}
#endif //_DEBUG


// CMailslotCltView 消息处理程序


void CMailslotCltView::OnMailslotSend()
{
	// TODO:  在此添加命令处理程序代码
	HANDLE hMailslot;
	hMailslot=CreateFile("\\\\.\\mailslot\\MyMaislot", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hMailslot == INVALID_HANDLE_VALUE)
	{
		MessageBox("打开邮槽失败！");
		return;
	}
	char buf[] = "nihao1";
	DWORD dwWrite;
	if (!WriteFile(hMailslot, buf, strlen(buf) + 1, &dwWrite, NULL))
	{
		MessageBox("写入数据失败！");
		return;
	}
	char buf1[] = "hallo";
	strcpy_s(buf,strlen(buf)+1, buf1);
	if (!WriteFile(hMailslot, buf, strlen(buf) + 1, &dwWrite, NULL))//两次写入，产生两个消息，在服务端通过GetMailslotInfo获取消息数量，每一个WriteFile邮槽的消息数量加1，通过消息数量多次读取数据
	{
		MessageBox("写入数据失败！");
		return;
	}
	CloseHandle(hMailslot);
}
