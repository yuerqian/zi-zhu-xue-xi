
// AsyncChatDlg.h : 头文件
//

#pragma once

#define UM_SOCK WM_USER+1
// CAsyncChatDlg 对话框
class CAsyncChatDlg : public CDialogEx
{
// 构造
public:
	CAsyncChatDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ASYNCCHAT_DIALOG };

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
	afx_msg LRESULT OnSock(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
public:
	bool InitSocket();
private:
	SOCKET m_socket;
public:
	afx_msg void OnBnClickedBtnSend();
};
