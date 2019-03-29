
// 菜单View.h : C菜单View 类的接口
//

#pragma once


class C菜单View : public CView
{
protected: // 仅从序列化创建
	C菜单View();
	DECLARE_DYNCREATE(C菜单View)

// 特性
public:
	C菜单Doc* GetDocument() const;

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
	virtual ~C菜单View();
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
	afx_msg void OnTest();
//	afx_msg void OnUpdateViewStatusBar(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // 菜单View.cpp 中的调试版本
inline C菜单Doc* C菜单View::GetDocument() const
   { return reinterpret_cast<C菜单Doc*>(m_pDocument); }
#endif

