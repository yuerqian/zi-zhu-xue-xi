
// �б�ؼ�Dlg.h : header file
//

#pragma once
#include "afxcmn.h"


// C�б�ؼ�Dlg dialog
class C�б�ؼ�Dlg : public CDialogEx
{
// Construction
public:
	C�б�ؼ�Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CImageList m_ImaLarge;
	CImageList m_ImaSmall;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	CListCtrl m_List;
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnDelete();
};
