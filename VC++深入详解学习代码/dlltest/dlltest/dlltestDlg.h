
// dlltestDlg.h : ͷ�ļ�
//

#pragma once
//#include"dll.h"
//_declspec(dllimport) int add(int a, int b);
//extern"C" _declspec(dllimport) int subtract(int a, int b);
extern class Point
{
public:
	void  output(int x, int y);
};

// CdlltestDlg �Ի���
class CdlltestDlg : public CDialogEx
{
// ����
public:
	CdlltestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DLLTEST_DIALOG };

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
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnSubtrace();
	afx_msg void OnBnClickedBtnOutput();
};
