
// NamePipeCltView.h : CNamePipeCltView ��Ľӿ�
//

#pragma once


class CNamePipeCltView : public CView
{
protected: // �������л�����
	CNamePipeCltView();
	DECLARE_DYNCREATE(CNamePipeCltView)

// ����
public:
	CNamePipeCltDoc* GetDocument() const;

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
	virtual ~CNamePipeCltView();
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
private:
	HANDLE hPipe;
public:
	afx_msg void OnPipeConnect();
	afx_msg void OnPipeRead();
	afx_msg void OnPipeWrite();
};

#ifndef _DEBUG  // NamePipeCltView.cpp �еĵ��԰汾
inline CNamePipeCltDoc* CNamePipeCltView::GetDocument() const
   { return reinterpret_cast<CNamePipeCltDoc*>(m_pDocument); }
#endif

