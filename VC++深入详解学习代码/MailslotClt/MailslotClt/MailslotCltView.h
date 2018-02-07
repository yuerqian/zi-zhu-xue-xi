
// MailslotCltView.h : CMailslotCltView ��Ľӿ�
//

#pragma once


class CMailslotCltView : public CView
{
protected: // �������л�����
	CMailslotCltView();
	DECLARE_DYNCREATE(CMailslotCltView)

// ����
public:
	CMailslotCltDoc* GetDocument() const;

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
	virtual ~CMailslotCltView();
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
	afx_msg void OnMailslotSend();
};

#ifndef _DEBUG  // MailslotCltView.cpp �еĵ��԰汾
inline CMailslotCltDoc* CMailslotCltView::GetDocument() const
   { return reinterpret_cast<CMailslotCltDoc*>(m_pDocument); }
#endif

