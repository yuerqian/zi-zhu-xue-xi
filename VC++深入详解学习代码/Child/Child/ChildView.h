
// ChildView.h : CChildView 类的接口
//

#pragma once


class CChildView : public CView
{
protected: // 仅从序列化创建
	CChildView();
	DECLARE_DYNCREATE(CChildView)

// 特性
public:
	CChildDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CChildView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPipeRead();
	afx_msg void OnPipeWrite();
private:
	// 管道读取数据句柄
	HANDLE hRead;
	// 写入管道数据句柄
	HANDLE hWrite;
	LPOVERLAPPED_COMPLETION_ROUTINE CALLBACK AsynRead(DWORD dwErrorCode,
		DWORD dwNumberOfBytesTransfered,
		LPOVERLAPPED lpOverlapped);
public:
	virtual void OnInitialUpdate();
private:
	HANDLE g_Event;
};

#ifndef _DEBUG  // ChildView.cpp 中的调试版本
inline CChildDoc* CChildView::GetDocument() const
   { return reinterpret_cast<CChildDoc*>(m_pDocument); }
#endif

