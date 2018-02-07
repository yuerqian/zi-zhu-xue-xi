#pragma once

// MFCActiveXControl控件PropPage.h : CMFCActiveXControl控件PropPage 属性页类的声明。


// CMFCActiveXControl控件PropPage : 有关实现的信息，请参阅 MFCActiveXControl控件PropPage.cpp。

class CMFCActiveXControl控件PropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CMFCActiveXControl控件PropPage)
	DECLARE_OLECREATE_EX(CMFCActiveXControl控件PropPage)

// 构造函数
public:
	CMFCActiveXControl控件PropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_MFCACTIVEXCONTROL };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
public:
//	short m_UpdateInterval;
//	short m_UpdateInterval;
	short m_UpdateInterval;
};

