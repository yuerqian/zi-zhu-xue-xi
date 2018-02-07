
// ChatDlg.h : 头文件
//

#pragma once

#define WM_RECVDATA (WM_USER+1)
// CChatDlg 对话框
class CChatDlg : public CDialogEx
{
// 构造
public:
	CChatDlg(CWnd* pParent = NULL);	// 标准构造函数

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
	afx_msg LRESULT OnRecvData(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	// 套接字描述符
	SOCKET m_socket;
public:
	// 初始化套接字
	bool InitSocket();
	static DWORD WINAPI RecvProc(LPVOID lpParam);
//	DWORD  RecvProc();
	afx_msg void OnBnClickedBtnSend();
//	afx_msg void OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

struct RECVPARAM
{
	SOCKET sock;//已创建的套接字
	HWND hwnd;//对话框句柄
};
