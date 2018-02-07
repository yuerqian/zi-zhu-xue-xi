
// MailslotView.cpp : CMailslotView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMailslotView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_MAILSLOT_RECV, &CMailslotView::OnMailslotRecv)
END_MESSAGE_MAP()

// CMailslotView 构造/析构

CMailslotView::CMailslotView()
{
	// TODO:  在此处添加构造代码

}

CMailslotView::~CMailslotView()
{
}

BOOL CMailslotView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMailslotView 绘制

void CMailslotView::OnDraw(CDC* /*pDC*/)
{
	CMailslotDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CMailslotView 打印


void CMailslotView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMailslotView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMailslotView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMailslotView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
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


// CMailslotView 诊断

#ifdef _DEBUG
void CMailslotView::AssertValid() const
{
	CView::AssertValid();
}

void CMailslotView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMailslotDoc* CMailslotView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMailslotDoc)));
	return (CMailslotDoc*)m_pDocument;
}
#endif //_DEBUG


// CMailslotView 消息处理程序


void CMailslotView::OnMailslotRecv()
{
	// TODO:  在此添加命令处理程序代码
	HANDLE hMailslot;
	hMailslot = CreateMailslot("\\\\.\\mailslot\\MyMaislot", 0, MAILSLOT_WAIT_FOREVER, NULL);
	if (hMailslot == INVALID_HANDLE_VALUE)
	{
		MessageBox("创建邮槽失败！");
		return;
	}
	char buf[100];
	DWORD dwRead;
	DWORD CMessage,cMessageNum;
	while (1)
	{
		if (!GetMailslotInfo(hMailslot, NULL, &CMessage, &cMessageNum, NULL))
		{
			MessageBox("获取邮槽消息错误！");
			return;
		}
		while (cMessageNum != 0)
		{
			if (!ReadFile(hMailslot, buf, 100, &dwRead, NULL))
			{
				MessageBox("读取数据失败");
				return;
			}
			if (!GetMailslotInfo(hMailslot, NULL, &CMessage, &cMessageNum, NULL))
			{
				MessageBox("获取邮槽消息错误！");
				return;
			}
			MessageBox(buf);
		}
	}
	CloseHandle(hMailslot);
}
