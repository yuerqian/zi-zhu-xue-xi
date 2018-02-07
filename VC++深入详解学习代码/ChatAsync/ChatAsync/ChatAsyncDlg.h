
// ChatAsyncDlg.h : ͷ�ļ�
//

#pragma once

#define UM_SOCK WM_USER+1
// CChatAsyncDlg �Ի���
class CChatAsyncDlg : public CDialogEx
{
// ����
public:
	CChatAsyncDlg(CWnd* pParent = NULL);	// ��׼���캯��

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



