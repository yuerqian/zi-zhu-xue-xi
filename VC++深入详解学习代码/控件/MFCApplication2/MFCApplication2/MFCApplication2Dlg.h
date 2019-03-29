
// MFCApplication2Dlg.h : 头文件
//

#pragma once
#include "mfcactivexcontroctrl1.h"
#include "afxwin.h"


// CMFCApplication2Dlg 对话框
class CMFCApplication2Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication2Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void ClickMfcactivexcontroctrl1();
	void MyEvent2Mfcactivexcontroctrl1(LPCTSTR msg);
	/*CMfcactivexcontroctrl1 MyActiveDemo;*/
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CButton m_MyMethodBotton;
	afx_msg void OnBnClickedButton1();
	/*CMfcactivexcontroctrl1 m_myControl;*/
	/*CMfcactivexcontroctrl1 m_ActiveX2;*/
	/*CMfcactivexcontroctrl1 m_ActveXcontrol;*/
	/*CMfcactivexcontroctrl1 m_ActiveXControl;*/
	/*CMfcactivexcontroctrl1 m_ActiveXControl;*/
	CMfcactivexcontroctrl1 m_ActiveXControl;
};
