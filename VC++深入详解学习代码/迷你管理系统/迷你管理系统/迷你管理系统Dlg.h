
// �������ϵͳDlg.h : header file
//

#pragma once

#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","rsEOF")

// C�������ϵͳDlg dialog
class C�������ϵͳDlg : public CDialogEx
{
// Construction
public:
	C�������ϵͳDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	_ConnectionPtr m_Connection;
	_RecordsetPtr m_Recordset;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
