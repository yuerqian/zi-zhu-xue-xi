#pragma once

// ActiveXCtrl.h : CActiveXCtrl ActiveX �ؼ����������


// CActiveXCtrl : �й�ʵ�ֵ���Ϣ������� ActiveXCtrl.cpp��

class CActiveXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CActiveXCtrl)

// ���캯��
public:
	CActiveXCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~CActiveXCtrl();

	DECLARE_OLECREATE_EX(CActiveXCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CActiveXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CActiveXCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CActiveXCtrl)		// �������ƺ�����״̬

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

