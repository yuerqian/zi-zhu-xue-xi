#pragma once

// ActiveXPropPage.h : CActiveXPropPage ����ҳ���������


// CActiveXPropPage : �й�ʵ�ֵ���Ϣ������� ActiveXPropPage.cpp��

class CActiveXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CActiveXPropPage)
	DECLARE_OLECREATE_EX(CActiveXPropPage)

// ���캯��
public:
	CActiveXPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_ACTIVEX };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

