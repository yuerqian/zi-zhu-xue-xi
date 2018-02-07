
// ParentView.h : CParentView ��Ľӿ�
//

#pragma once


class CParentView : public CView
{
protected: // �������л�����
	CParentView();
	DECLARE_DYNCREATE(CParentView)

// ����
public:
	CParentDoc* GetDocument() const;

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
	virtual ~CParentView();
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
	afx_msg void OnPipeRead();
	afx_msg void OnPipeCreate();
	afx_msg void OnPapeWrite();
private:
	HANDLE hWrite;
	// �ܵ������
	HANDLE hRead;
};

#ifndef _DEBUG  // ParentView.cpp �еĵ��԰汾
inline CParentDoc* CParentView::GetDocument() const
   { return reinterpret_cast<CParentDoc*>(m_pDocument); }
#endif

