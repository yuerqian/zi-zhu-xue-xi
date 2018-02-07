
// ChatDlg.h : ͷ�ļ�
//

#pragma once

#define WM_RECVDATA (WM_USER+1)
// CChatDlg �Ի���
class CChatDlg : public CDialogEx
{
// ����
public:
	CChatDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHAT_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnRecvData(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	// �׽���������
	SOCKET m_socket;
public:
	// ��ʼ���׽���
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
	SOCKET sock;//�Ѵ������׽���
	HWND hwnd;//�Ի�����
};
