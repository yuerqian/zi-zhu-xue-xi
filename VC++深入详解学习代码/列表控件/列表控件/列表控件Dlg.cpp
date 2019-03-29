
// 列表控件Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "列表控件.h"
#include "列表控件Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// C列表控件Dlg dialog



C列表控件Dlg::C列表控件Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C列表控件Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C列表控件Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
}

BEGIN_MESSAGE_MAP(C列表控件Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_CMB_VIEW, &C列表控件Dlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BTN_ADD, &C列表控件Dlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DELETE, &C列表控件Dlg::OnBnClickedBtnDelete)
END_MESSAGE_MAP()


// C列表控件Dlg message handlers

BOOL C列表控件Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//添加表头
	m_List.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);//改变样式
	m_List.InsertColumn(0, "第一列", LVCFMT_LEFT,120);//添加列，1.是第几列，2.插入的列名称，3.对齐方式，4. 宽度
	m_List.InsertColumn(1, "第二列", LVCFMT_LEFT, 120);//添加列，1.是第几列，2.插入的列名称，3.对齐方式，4. 宽度
	//创建大小图片列表
	m_ImaLarge.Create(IDB_BMP_LARGE, 32, 1, RGB(255, 0, 0));
	m_ImaSmall.Create(IDB_BMP_SMALL, 16, 1, RGB(255, 0, 0));

	//将图标列表设置到表里
	m_List.SetImageList(&m_ImaLarge, LVSIL_NORMAL);//大图标
	m_List.SetImageList(&m_ImaSmall, LVSIL_SMALL);//小图标

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void C列表控件Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void C列表控件Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR C列表控件Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C列表控件Dlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
}


void C列表控件Dlg::OnBnClickedBtnAdd()
{
	// TODO: Add your control notification handler code here
	//获得原来有几行
	int nCount=m_List.GetItemCount();
	CString strText;
	//添加到列表控件里的文字
	strText.Format("第%d行，第1列", nCount + 1);
	m_List.InsertItem(nCount, strText, 0);//插入的是一整行，只能插入一次，1.第几行，2内容，3.使用序号是0的图标
	strText.Format("第%d行，第2列", nCount + 1);
	m_List.SetItemText(nCount, 1, strText);//设置第二列，1.第几行，2.第几列，3.内容



}


void C列表控件Dlg::OnBnClickedBtnDelete()
{
	// TODO: Add your control notification handler code here
	int nCount = m_List.GetItemCount();
	//从后面开始删除，避免出错
	for (int i = 0; i <= nCount; i++)
	{
		//获取某一行的状态，有没有被选中，如果被选中了，就把它删除
		if (m_List.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			m_List.DeleteItem(i);
		}

	}
}
