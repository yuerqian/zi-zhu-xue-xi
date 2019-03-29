
// 内存映射-文件读写Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "内存映射-文件读写.h"
#include "内存映射-文件读写Dlg.h"
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


// C内存映射文件读写Dlg dialog



C内存映射文件读写Dlg::C内存映射文件读写Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C内存映射文件读写Dlg::IDD, pParent)
	, m_strText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C内存映射文件读写Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strText);
}

BEGIN_MESSAGE_MAP(C内存映射文件读写Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C内存映射文件读写Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// C内存映射文件读写Dlg message handlers

BOOL C内存映射文件读写Dlg::OnInitDialog()
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
	if (!LoadFile("test.txt"))
	{
		MessageBox("LoadFile ERROR!");
	}
	UpdateData(false);
	


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void C内存映射文件读写Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C内存映射文件读写Dlg::OnPaint()
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
HCURSOR C内存映射文件读写Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C内存映射文件读写Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	CDialogEx::OnOK();
}
BOOL C内存映射文件读写Dlg::LoadFile(CString strFileName)
{
	HANDLE hFile;//文件句柄
	HANDLE hMapping;//内存映射对象
	void *m_pMapviewfile;//指向映射的内存地址
	if ((hFile = CreateFile(strFileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, 0)) == INVALID_HANDLE_VALUE)//打开文件
	{
		MessageBox("CreateFile Error!");
		return FALSE;
	}
	if ((hMapping = CreateFileMapping(hFile, 0, PAGE_READONLY, 0, 0, NULL)) == INVALID_HANDLE_VALUE)//创建内存映射对象
	{
		MessageBox("CreateFileMapping Error!");
		CloseHandle(hFile);
		return FALSE;
	}
	if ((m_pMapviewfile = MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0)) == INVALID_HANDLE_VALUE)//映射内存地址空间
	{
		MessageBox("MapViewofFile Error!");
		CloseHandle(hMapping);
		CloseHandle(hFile);
		return FALSE;
	}	
	m_strText = (LPTSTR)m_pMapviewfile;

	UnmapViewOfFile(m_pMapviewfile);//取消内存地址映射
	CloseHandle(hMapping);//关闭映射对象句柄
	CloseHandle(hFile);//关闭文件句柄

	return TRUE;
}