
// �����View.cpp : C�����View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "�����.h"
#endif

#include "�����Doc.h"
#include "�����View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C�����View

IMPLEMENT_DYNCREATE(C�����View, CView)

BEGIN_MESSAGE_MAP(C�����View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &C�����View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// C�����View ����/����

C�����View::C�����View()
: m_strLine(_T(""))
, m_ptOrigin(0)
, m_nWidth(0)
{
	// TODO:  �ڴ˴���ӹ������
	m_strLine = "";
	m_ptOrigin = 0;
	m_nWidth = 0;

}

C�����View::~C�����View()
{
}

BOOL C�����View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// C�����View ����

void C�����View::OnDraw(CDC* pDC)
{
	C�����Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//CClientDC dc(this);
	//CFont font;
	//font.CreatePointFont(300, "����", NULL);
	//CFont *pOldFont = dc.SelectObject(&font);
	//CSize sz = dc.GetTextExtent(m_strLine);
	//CPoint pt;
	//pt.x = m_ptOrigin.x + sz.cx;//���û��ͨ����������趨�������m_ptOrigin.x������Ļ���m_ptOrigin.x��������ʵ�����ֵ������0
	//pt.y = m_ptOrigin.y;
	//TEXTMETRIC tm;
	//dc.GetTextMetrics(&tm);
	////���´���һ����ǰ��������߶ȵĲ����
	//CreateSolidCaret(tm.tmAveCharWidth / 8, tm.tmHeight);//���������
	//ShowCaret();//��ʾ�����
	////���ò������λ��
	//SetCaretPos(pt);
	//dc.TextOutA(m_ptOrigin.x, m_ptOrigin.y, m_strLine);


	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	//CString str="��ã���ӭ�����ҵ�����";
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


// C�����View ��ӡ


void C�����View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL C�����View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void C�����View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void C�����View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}

void C�����View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void C�����View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// C�����View ���

#ifdef _DEBUG
void C�����View::AssertValid() const
{
	CView::AssertValid();
}

void C�����View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C�����Doc* C�����View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C�����Doc)));
	return (C�����Doc*)m_pDocument;
}
#endif //_DEBUG


// C�����View ��Ϣ�������


int C�����View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CClientDC dc(this);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	CreateSolidCaret(tm.tmAveCharWidth/8, tm.tmHeight);//���������
	ShowCaret();//��ʾ�����

	SetTimer(1, 100, NULL);

	//m_bitmap.LoadBitmapA(IDB_BITMAP1);
	//CreateCaret(&m_bitmap);
	//ShowCaret();
	return 0;
}


void C�����View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SetCaretPos(point);
	
	m_strLine.Empty();
	m_ptOrigin = point;//������������

	CView::OnLButtonDown(nFlags, point);
}


void C�����View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC dc(this);
	//��������
	CFont font;
	font.CreatePointFont(300, "����", NULL);
	CFont *pOldFont=dc.SelectObject(&font);

	//��ȡ�豸��������ǰ����������
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);

	if (0x0d == nChar)//�س���
	{
		m_strLine.Empty();
		m_ptOrigin.y += tm.tmHeight;
	}
	else if (0x08 == nChar)//backspace��
	{
		COLORREF clr=dc.SetTextColor(dc.GetBkColor());
		dc.TextOutA(m_ptOrigin.x, m_ptOrigin.y, m_strLine);//��������ɫ���óɱ�����ɫ������ﵽ�������ֵ�Ч��
		m_strLine=m_strLine.Left(m_strLine.GetLength() - 1);//����������ּ�ȥһ���ַ�
		dc.SetTextColor(clr);
	}
	else
	{
		m_strLine += (char)nChar;
	}

	//��ȡ�����Ӧ��������λ��
	CSize sz=dc.GetTextExtent(m_strLine);
	CPoint pt;
	pt.x = m_ptOrigin.x + sz.cx;//���û��ͨ����������趨�������m_ptOrigin.x������Ļ���m_ptOrigin.x��������ʼ�����ֵ������0
	pt.y = m_ptOrigin.y;
	//���´���һ����ǰ��������߶ȵĲ����
	//CreateSolidCaret(tm.tmAveCharWidth / 8, tm.tmHeight);//���������
	//ShowCaret();//��ʾ�����
	//���ò������λ��
	

	//�Ļ�ԭ��������
	dc.SelectObject(&pOldFont);
	font.DeleteObject();

	//��ʾ
	dc.TextOutA(m_ptOrigin.x, m_ptOrigin.y, m_strLine);
	SetCaretPos(pt);


	CView::OnChar(nChar, nRepCnt, nFlags);
}


void C�����View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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

	//������̲�ѭ������
	CSize sz=dc.GetTextExtent(str);
	if (m_nWidth > sz.cx)
	{
		m_nWidth = 0;
		dc.SetTextColor(RGB(0, 255, 0));
		dc.TextOutA(0, 200, str);
	}


	CView::OnTimer(nIDEvent);
}
