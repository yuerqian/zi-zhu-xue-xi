
// ChildView.h : CChildView ��Ľӿ�
//

#pragma once


class CChildView : public CView
{
protected: // �������л�����
	CChildView();
	DECLARE_DYNCREATE(CChildView)

// ����
public:
	CChildDoc* GetDocument() const;

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
	virtual ~CChildView();
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
	afx_msg void OnPipeWrite();
private:
	// �ܵ���ȡ���ݾ��
	HANDLE hRead;
	// д��ܵ����ݾ��
	HANDLE hWrite;
	LPOVERLAPPED_COMPLETION_ROUTINE CALLBACK AsynRead(DWORD dwErrorCode,
		DWORD dwNumberOfBytesTransfered,
		LPOVERLAPPED lpOverlapped);
public:
	virtual void OnInitialUpdate();
private:
	HANDLE g_Event;
};

#ifndef _DEBUG  // ChildView.cpp �еĵ��԰汾
inline CChildDoc* CChildView::GetDocument() const
   { return reinterpret_cast<CChildDoc*>(m_pDocument); }
#endif

