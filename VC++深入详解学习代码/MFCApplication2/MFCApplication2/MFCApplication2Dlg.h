
// MFCApplication2Dlg.h : ͷ�ļ�
//

#pragma once
#include "mfcactivexcontroctrl1.h"
#include "afxwin.h"


// CMFCApplication2Dlg �Ի���
class CMFCApplication2Dlg : public CDialogEx
{
// ����
public:
	CMFCApplication2Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG };

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
	DECLARE_EVENTSINK_MAP()
	void ClickMfcactivexcontroctrl1();
	void MyEvent2Mfcactivexcontroctrl1(LPCTSTR msg);
	/*CMfcactivexcontroctrl1 MyActiveDemo;*/
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CButton m_MyMethodBotton;
	afx_msg void OnBnClickedButton1();
	/*CMfcactivexcontroctrl1 m_myControl;*/
	/*CMfcactivexcontroctrl1 m_ActiveX2;*/
	/*CMfcactivexcontroctrl1 m_ActveXcontrol;*/
	/*CMfcactivexcontroctrl1 m_ActiveXControl;*/
	/*CMfcactivexcontroctrl1 m_ActiveXControl;*/
	CMfcactivexcontroctrl1 m_ActiveXControl;
};
