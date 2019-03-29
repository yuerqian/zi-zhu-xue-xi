
// 菜单View.cpp : C菜单View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "菜单.h"
#endif

#include "菜单Doc.h"
#include "菜单View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C菜单View

IMPLEMENT_DYNCREATE(C菜单View, CView)

BEGIN_MESSAGE_MAP(C菜单View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &C菜单View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_TEST, &C菜单View::OnTest)
//	ON_UPDATE_COMMAND_UI(ID_VIEW_STATUS_BAR, &C菜单View::OnUpdateViewStatusBar)
END_MESSAGE_MAP()

// C菜单View 构造/析构

C菜单View::C菜单View()
{
	// TODO:  在此处添加构造代码

}

C菜单View::~C菜单View()
{
}

BOOL C菜单View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// C菜单View 绘制

void C菜单View::OnDraw(CDC* /*pDC*/)
{
	C菜单Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// C菜单View 打印


void C菜单View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL C菜单View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void C菜单View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void C菜单View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}

void C菜单View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void C菜单View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// C菜单View 诊断

#ifdef _DEBUG
void C菜单View::AssertValid() const
{
	CView::AssertValid();
}

void C菜单View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C菜单Doc* C菜单View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C菜单Doc)));
	return (C菜单Doc*)m_pDocument;
}
#endif //_DEBUG


// C菜单View 消息处理程序


void C菜单View::OnTest()
{

	// TODO:  在此添加命令处理程序代码
	//CMenu mu;
	//mu.LoadMenuA(IDR_MAINFRAME);//加载菜单
	//CPoint point;
	//GetCursorPos(&point);//获取鼠标位置
	//mu.GetSubMenu(0)->TrackPopupMenu(0, point.x, point.y, this);//mu.GetSubMenu(0)获取索引号为0的子菜单句柄，TrackPopupMenu弹出菜单项
	/*MessageBox("你好啊！", 0, 0);*/

}


//void C菜单View::OnUpdateViewStatusBar(CCmdUI *pCmdUI)
//{
//	// TODO:  在此添加命令更新用户界面处理程序代码
//	
//
//}
