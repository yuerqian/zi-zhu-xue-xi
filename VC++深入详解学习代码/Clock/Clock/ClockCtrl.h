#pragma once

// ClockCtrl.h : CClockCtrl ActiveX �ؼ����������


// CClockCtrl : �й�ʵ�ֵ���Ϣ������� ClockCtrl.cpp��

class CClockCtrl : public COleControl
{
	DECLARE_DYNCREATE(CClockCtrl)

// ���캯��
public:
	CClockCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~CClockCtrl();

	DECLARE_OLECREATE_EX(CClockCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CClockCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CClockCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CClockCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
public:
	enum {
	};
};

