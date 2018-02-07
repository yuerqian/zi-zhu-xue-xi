
// MFCApplication3_dailogDlg.h : 头文件
//

#pragma once
#include"mfcactivexcontroctrl1.h"
// CMFCApplication3_dailogDlg 对话框
class CMFCApplication3_dailogDlg : public CDialogEx
{
// 构造
public:
	CMFCApplication3_dailogDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCAPPLICATION3_DAILOG_DIALOG };

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
	afx_msg void OnBnClickedButton1();
//	CMFCActiveXControl控件Ctrl m_clock;
//	MFCACTIVEXCONTROCTRL2 m_Clock;
//	CMFCActiveXControl控件Ctrl m_clock;
	CMfcactivexcontroctrl1 m_ActiveX;
	CMfcactivexcontroctrl1 m_clock;
};
