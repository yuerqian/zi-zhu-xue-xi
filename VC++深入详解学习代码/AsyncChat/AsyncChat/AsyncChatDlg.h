
// AsyncChatDlg.h : ͷ�ļ�
//

#pragma once

#define UM_SOCK WM_USER+1
// CAsyncChatDlg �Ի���
class CAsyncChatDlg : public CDialogEx
{
// ����
public:
	CAsyncChatDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ASYNCCHAT_DIALOG };

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
	afx_msg LRESULT OnSock(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
public:
	bool InitSocket();
private:
	SOCKET m_socket;
public:
	afx_msg void OnBnClickedBtnSend();
};
