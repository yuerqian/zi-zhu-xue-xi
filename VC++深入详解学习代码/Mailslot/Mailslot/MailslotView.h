
// MailslotView.h : CMailslotView ��Ľӿ�
//

#pragma once


class CMailslotView : public CView
{
protected: // �������л�����
	CMailslotView();
	DECLARE_DYNCREATE(CMailslotView)

// ����
public:
	CMailslotDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMailslotView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMailslotRecv();
};

#ifndef _DEBUG  // MailslotView.cpp �еĵ��԰汾
inline CMailslotDoc* CMailslotView::GetDocument() const
   { return reinterpret_cast<CMailslotDoc*>(m_pDocument); }
#endif

