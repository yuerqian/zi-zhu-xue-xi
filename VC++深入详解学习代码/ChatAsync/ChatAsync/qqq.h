#pragma once


// qqq 对话框

class qqq : public CDialogEx
{
	DECLARE_DYNAMIC(qqq)

public:
	qqq(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~qqq();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
