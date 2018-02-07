
// FileView.h : CFileView ��Ľӿ�
//

#pragma once


class CFileView : public CView
{
protected: // �������л�����
	CFileView();
	DECLARE_DYNCREATE(CFileView)

// ����
public:
	CFileDoc* GetDocument() const;

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
	virtual ~CFileView();
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
	afx_msg void OnFileWrite();
	afx_msg void OnFileRead();
	afx_msg void OnRegWrite();
	afx_msg void OnRegRead();
};

#ifndef _DEBUG  // FileView.cpp �еĵ��԰汾
inline CFileDoc* CFileView::GetDocument() const
   { return reinterpret_cast<CFileDoc*>(m_pDocument); }
#endif


