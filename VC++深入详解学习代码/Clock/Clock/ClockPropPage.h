#pragma once

// ClockPropPage.h : CClockPropPage ����ҳ���������


// CClockPropPage : �й�ʵ�ֵ���Ϣ������� ClockPropPage.cpp��

class CClockPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CClockPropPage)
	DECLARE_OLECREATE_EX(CClockPropPage)

// ���캯��
public:
	CClockPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_CLOCK };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

