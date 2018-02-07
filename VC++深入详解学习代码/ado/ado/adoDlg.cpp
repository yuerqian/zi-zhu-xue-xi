
// adoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ado.h"
#include "adoDlg.h"
#include "afxdialogex.h"
#include "resource.h"

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


// CadoDlg 对话框



CadoDlg::CadoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CadoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CadoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CadoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_QUERY, &CadoDlg::OnBnClickedBtnQuery)
END_MESSAGE_MAP()


// CadoDlg 消息处理程序

BOOL CadoDlg::OnInitDialog()
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

void CadoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CadoDlg::OnPaint()
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
HCURSOR CadoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CadoDlg::OnBnClickedBtnQuery()
{
	// TODO:  在此添加控件通知处理程序代码
	//清空控件
	//((CListBox*)GetDlgItem(IDC_LIST2))->ResetContent();
	while (((CListBox*)GetDlgItem(IDC_LIST2))->GetCount())
	{
		((CListBox*)GetDlgItem(IDC_LIST2))->DeleteString(0);
	}

	CoInitialize(NULL);
	_ConnectionPtr pConn(__uuidof(Connection));//也可以创建连接实例pConn.CreateInstance(__uuidof(Connection))
	_RecordsetPtr pRst(__uuidof(Recordset));
	_CommandPtr pCmd(__uuidof(Command));
	//CString ConnectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data source=C:\\Users\\Andy\\Documents\\MY.mdb";
	pConn->ConnectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data source=C:\\Users\\Andy\\Documents\\MY.mdb";
	//if (SUCCEEDED(pConn->Open(_bstr_t(ConnectionString), "", "", adConnectUnspecified)))
	//{
	//	MessageBox("打开数据库成功");
	//}
	if (!SUCCEEDED(pConn->Open( "","", "", adConnectUnspecified)))
	{
		MessageBox("打开数据库失败");
	}
	//pRst = pConn->Execute("select * from 仓库1", NULL, adCmdText);//Connection方法获取数据
	//pRst->Open("select * from 仓库1", (_variant_t)((IDispatch*)pConn), adOpenDynamic, adLockOptimistic, adCmdText);//Recordset方法获取数据
	pCmd->put_ActiveConnection((_variant_t)((IDispatch*)pConn));//Command方法设置活动连接
	pCmd->CommandText = "select * from 仓库1";//Command方法设置SQL语句
	pRst = pCmd->Execute(NULL, NULL, adCmdText);//Command方法执行SQL语句
	while (!pRst->rsEOF)//rsEOF是导入com组件时重命名的名字
	{
		((CListBox*)GetDlgItem(IDC_LIST2))->AddString((_bstr_t)pRst->GetCollect("价格"));
		pRst->MoveNext();
	}
	pRst->Close();
	pConn->Close();
	pRst.Release();
	pConn.Release();
	pCmd.Release();
	CoUninitialize();
}
