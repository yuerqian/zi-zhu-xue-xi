#pragma once


// qqq �Ի���

class qqq : public CDialogEx
{
	DECLARE_DYNAMIC(qqq)

public:
	qqq(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~qqq();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
