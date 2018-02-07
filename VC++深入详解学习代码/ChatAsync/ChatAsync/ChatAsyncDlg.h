
// ChatAsyncDlg.h : 头文件
//

#pragma once

#define UM_SOCK WM_USER+1
// CChatAsyncDlg 对话框
class CChatAsyncDlg : public CDialogEx
{
// 构造
public:
	CChatAsyncDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CHAT_DIALOG };

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
private:
	SOCKET m_socket;
	CList<CRect, CRect> listRect;
public:
	BOOL InitSocket();
	afx_msg void OnBnClickedBtnSend();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	~CChatAsyncDlg();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
#pragma once



