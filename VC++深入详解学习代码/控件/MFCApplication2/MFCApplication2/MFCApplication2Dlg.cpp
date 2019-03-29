
// MFCApplication2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication2Dlg 对话框



CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	/*DDX_Control(pDX, IDC_MFCACTIVEXCONTROCTRL1, MyActiveDemo);*/
	DDX_Control(pDX, IDC_BUTTON1, m_MyMethodBotton);
	/*DDX_Control(pDX, IDC_MFCACTIVEXCONTROCTRL1, m_myControl);*/
	/*DDX_Control(pDX, IDC_MFCACTIVEXCONTROCTRL2, m_ActiveX2);*/
	/*DDX_Control(pDX, IDC_MFCACTIVEXCONTROCTRL1, m_ActveXcontrol);*/
	/*DDX_Control(pDX, IDC_MFCACTIVEXCONTROCTRL1, m_ActiveXControl);*/
	/*DDX_Control(pDX, IDC_MFCACTIVEXCONTROCTRL1, m_ActiveXControl);*/
	DDX_Control(pDX, IDC_MFCACTIVEXCONTROCTRL1, m_ActiveXControl);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication2Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCApplication2Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication2Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFCApplication2Dlg 消息处理程序

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_EVENTSINK_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_EVENT(CMFCApplication2Dlg, IDC_MFCACTIVEXCONTROCTRL1, DISPID_CLICK, CMFCApplication2Dlg::ClickMfcactivexcontroctrl1, VTS_NONE)
	ON_EVENT(CMFCApplication2Dlg, IDC_MFCACTIVEXCONTROCTRL1, 2, CMFCApplication2Dlg::MyEvent2Mfcactivexcontroctrl1, VTS_BSTR)
END_EVENTSINK_MAP()


void CMFCApplication2Dlg::ClickMfcactivexcontroctrl1()
{
	// TODO:  在此处添加消息处理程序代码
	/*AfxMessageBox(_T("test"));*/
	/*m_ActiveXControl.put_myProperty(true, true);*/
	/*m_ActiveXControl.get_myProperty(true);*/
	//m_ActiveXControl.Setcustom(20);
	//char m;
	//m=m_ActiveXControl.Getcustom();

	/*AfxMessageBox(m);*/
}


void CMFCApplication2Dlg::MyEvent2Mfcactivexcontroctrl1(LPCTSTR msg)
{
	// TODO:  在此处添加消息处理程序代码
	/*AfxMessageBox(msg);*/
}


void CMFCApplication2Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	/*MyActiveDemo.DoClick();*/
	CDialogEx::OnOK();
}


void CMFCApplication2Dlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CMFCApplication2Dlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	m_ActiveXControl.MyMethod(_T("你好"));
	
}
