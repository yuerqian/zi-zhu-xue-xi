
// �ڴ�ӳ��-�ļ���дDlg.h : header file
//

#pragma once


// C�ڴ�ӳ���ļ���дDlg dialog
class C�ڴ�ӳ���ļ���дDlg : public CDialogEx
{
// Construction
public:
	C�ڴ�ӳ���ļ���дDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	BOOL LoadFile(CString strFileName);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_strText;
};
