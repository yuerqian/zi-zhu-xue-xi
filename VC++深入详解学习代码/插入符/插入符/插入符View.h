
// 插入符View.h : C插入符View 类的接口
//

#pragma once
#include "afxwin.h"
#include "atltypes.h"


class C插入符View : public CView
{
protected: // 仅从序列化创建
	C插入符View();
	DECLARE_DYNCREATE(C插入符View)

// 特性
public:
	C插入符Doc* GetDocument() const;

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
	virtual ~C插入符View();
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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
	CBitmap m_bitmap;
public:
	CString m_strLine;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	CPoint m_ptOrigin;
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_nWidth;
};

#ifndef _DEBUG  // 插入符View.cpp 中的调试版本
inline C插入符Doc* C插入符View::GetDocument() const
   { return reinterpret_cast<C插入符Doc*>(m_pDocument); }
#endif

