
// MFCApplication3_dailogDlg.h : ͷ�ļ�
//

#pragma once
#include"mfcactivexcontroctrl1.h"
// CMFCApplication3_dailogDlg �Ի���
class CMFCApplication3_dailogDlg : public CDialogEx
{
// ����
public:
	CMFCApplication3_dailogDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCAPPLICATION3_DAILOG_DIALOG };

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
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
//	CMFCActiveXControl�ؼ�Ctrl m_clock;
//	MFCACTIVEXCONTROCTRL2 m_Clock;
//	CMFCActiveXControl�ؼ�Ctrl m_clock;
	CMfcactivexcontroctrl1 m_ActiveX;
	CMfcactivexcontroctrl1 m_clock;
};
