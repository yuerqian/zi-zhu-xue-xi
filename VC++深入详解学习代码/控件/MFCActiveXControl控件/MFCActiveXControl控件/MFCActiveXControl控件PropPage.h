#pragma once

// MFCActiveXControl�ؼ�PropPage.h : CMFCActiveXControl�ؼ�PropPage ����ҳ���������


// CMFCActiveXControl�ؼ�PropPage : �й�ʵ�ֵ���Ϣ������� MFCActiveXControl�ؼ�PropPage.cpp��

class CMFCActiveXControl�ؼ�PropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CMFCActiveXControl�ؼ�PropPage)
	DECLARE_OLECREATE_EX(CMFCActiveXControl�ؼ�PropPage)

// ���캯��
public:
	CMFCActiveXControl�ؼ�PropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_MFCACTIVEXCONTROL };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
public:
//	short m_UpdateInterval;
//	short m_UpdateInterval;
	short m_UpdateInterval;
};

