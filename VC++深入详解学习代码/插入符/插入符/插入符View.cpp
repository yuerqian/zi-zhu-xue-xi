
// 插入符View.cpp : C插入符View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "插入符.h"
#endif

#include "插入符Doc.h"
#include "插入符View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C插入符View

IMPLEMENT_DYNCREATE(C插入符View, CView)

BEGIN_MESSAGE_MAP(C插入符View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &C插入符View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// C插入符View 构造/析构

C插入符View::C插入符View()
: m_strLine(_T(""))
, m_ptOrigin(0)
, m_nWidth(0)
{
	// TODO:  在此处添加构造代码
	m_strLine = "";
	m_ptOrigin = 0;
	m_nWidth = 0;

}

C插入符View::~C插入符View()
{
}

BOOL C插入符View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// C插入符View 绘制

void C插入符View::OnDraw(CDC* pDC)
{
	C插入符Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//CClientDC dc(this);
	//CFont font;
	//font.CreatePointFont(300, "宋体", NULL);
	//CFont *pOldFont = dc.SelectObject(&font);
	//CSize sz = dc.GetTextExtent(m_strLine);
	//CPoint pt;
	//pt.x = m_ptOrigin.x + sz.cx;//如果没有通过鼠标重新设定插入符的m_ptOrigin.x的坐标的话，m_ptOrigin.x都等于其实坐标的值，即是0
	//pt.y = m_ptOrigin.y;
	//TEXTMETRIC tm;
	//dc.GetTextMetrics(&tm);
	////重新创建一个当前符合字体高度的插入符
	//CreateSolidCaret(tm.tmAveCharWidth / 8, tm.tmHeight);//创建插入符
	//ShowCaret();//显示插入符
	////设置插入符的位置
	//SetCaretPos(pt);
	//dc.TextOutA(m_ptOrigin.x, m_ptOrigin.y, m_strLine);


	// TODO:  在此处为本机数据添加绘制代码
	//CString str="你好，欢迎来到我的世界";
	///*pDC->TextOutA(50, 50, str);*/

	//CSize sz = pDC->GetTextExtent(str);
	////str.LoadStringA(IDS_STRINGWORLD);
	//pDC->TextOutA(100,100,str);

	//pDC->BeginPath();
	//pDC->Rectangle(100, 100, 100 + sz.cx, 100 + sz.cy);
	//pDC->EndPath();
	//pDC->SelectClipPath(RGN_DIFF);
	/*pDC->SelectClipPath(RGN_COPY);*/


	/*for (int i = 0; i < 300; i += 10)
	{
		pDC->MoveTo(0, i);
		pDC->LineTo(300, i);
		pDC->MoveTo(i, 0);
		pDC->LineTo(i, 300);
	}*/
}


// C插入符View 打印


void C插入符View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL C插入符View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void C插入符View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void C插入符View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}

void C插入符View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void C插入符View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// C插入符View 诊断

#ifdef _DEBUG
void C插入符View::AssertValid() const
{
	CView::AssertValid();
}

void C插入符View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C插入符Doc* C插入符View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C插入符Doc)));
	return (C插入符Doc*)m_pDocument;
}
#endif //_DEBUG


// C插入符View 消息处理程序


int C插入符View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CClientDC dc(this);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	CreateSolidCaret(tm.tmAveCharWidth/8, tm.tmHeight);//创建插入符
	ShowCaret();//显示插入符

	SetTimer(1, 100, NULL);

	//m_bitmap.LoadBitmapA(IDB_BITMAP1);
	//CreateCaret(&m_bitmap);
	//ShowCaret();
	return 0;
}


void C插入符View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	SetCaretPos(point);
	
	m_strLine.Empty();
	m_ptOrigin = point;//保存插入符坐标

	CView::OnLButtonDown(nFlags, point);
}


void C插入符View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	//设置字体
	CFont font;
	font.CreatePointFont(300, "宋体", NULL);
	CFont *pOldFont=dc.SelectObject(&font);

	//获取设备描述符当前的字体属性
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);

	if (0x0d == nChar)//回车键
	{
		m_strLine.Empty();
		m_ptOrigin.y += tm.tmHeight;
	}
	else if (0x08 == nChar)//backspace键
	{
		COLORREF clr=dc.SetTextColor(dc.GetBkColor());
		dc.TextOutA(m_ptOrigin.x, m_ptOrigin.y, m_strLine);//将文字颜色设置成背景颜色输出，达到隐藏文字的效果
		m_strLine=m_strLine.Left(m_strLine.GetLength() - 1);//将输出的文字减去一个字符
		dc.SetTextColor(clr);
	}
	else
	{
		m_strLine += (char)nChar;
	}

	//获取插入符应该跳到的位置
	CSize sz=dc.GetTextExtent(m_strLine);
	CPoint pt;
	pt.x = m_ptOrigin.x + sz.cx;//如果没有通过鼠标重新设定插入符的m_ptOrigin.x的坐标的话，m_ptOrigin.x都等于起始坐标的值，即是0
	pt.y = m_ptOrigin.y;
	//重新创建一个当前符合字体高度的插入符
	//CreateSolidCaret(tm.tmAveCharWidth / 8, tm.tmHeight);//创建插入符
	//ShowCaret();//显示插入符
	//设置插入符的位置
	

	//改回原来的字体
	dc.SelectObject(&pOldFont);
	font.DeleteObject();

	//显示
	dc.TextOutA(m_ptOrigin.x, m_ptOrigin.y, m_strLine);
	SetCaretPos(pt);


	CView::OnChar(nChar, nRepCnt, nFlags);
}


void C插入符View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_nWidth += 5;

	CClientDC dc(this);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	CRect rect;
	rect.left = 2000;
	rect.top = 200;
	rect.right = m_nWidth;
	rect.bottom = rect.top + tm.tmHeight;

	dc.SetTextColor(RGB(255, 0, 0));
	CString str;
	str.LoadStringA(IDS_STRINGWORLD);
	dc.DrawText(str, rect, DT_LEFT);

	//字体变绿并循环播放
	CSize sz=dc.GetTextExtent(str);
	if (m_nWidth > sz.cx)
	{
		m_nWidth = 0;
		dc.SetTextColor(RGB(0, 255, 0));
		dc.TextOutA(0, 200, str);
	}


	CView::OnTimer(nIDEvent);
}
