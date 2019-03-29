
// �ڴ�ӳ��-�ļ���дDlg.cpp : implementation file
//

#include "stdafx.h"
#include "�ڴ�ӳ��-�ļ���д.h"
#include "�ڴ�ӳ��-�ļ���дDlg.h"
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


// C�ڴ�ӳ���ļ���дDlg dialog



C�ڴ�ӳ���ļ���дDlg::C�ڴ�ӳ���ļ���дDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C�ڴ�ӳ���ļ���дDlg::IDD, pParent)
	, m_strText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C�ڴ�ӳ���ļ���дDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strText);
}

BEGIN_MESSAGE_MAP(C�ڴ�ӳ���ļ���дDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C�ڴ�ӳ���ļ���дDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// C�ڴ�ӳ���ļ���дDlg message handlers

BOOL C�ڴ�ӳ���ļ���дDlg::OnInitDialog()
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

void C�ڴ�ӳ���ļ���дDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C�ڴ�ӳ���ļ���дDlg::OnPaint()
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
HCURSOR C�ڴ�ӳ���ļ���дDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C�ڴ�ӳ���ļ���дDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	CDialogEx::OnOK();
}
BOOL C�ڴ�ӳ���ļ���дDlg::LoadFile(CString strFileName)
{
	HANDLE hFile;//�ļ����
	HANDLE hMapping;//�ڴ�ӳ�����
	void *m_pMapviewfile;//ָ��ӳ����ڴ��ַ
	if ((hFile = CreateFile(strFileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, 0)) == INVALID_HANDLE_VALUE)//���ļ�
	{
		MessageBox("CreateFile Error!");
		return FALSE;
	}
	if ((hMapping = CreateFileMapping(hFile, 0, PAGE_READONLY, 0, 0, NULL)) == INVALID_HANDLE_VALUE)//�����ڴ�ӳ�����
	{
		MessageBox("CreateFileMapping Error!");
		CloseHandle(hFile);
		return FALSE;
	}
	if ((m_pMapviewfile = MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0)) == INVALID_HANDLE_VALUE)//ӳ���ڴ��ַ�ռ�
	{
		MessageBox("MapViewofFile Error!");
		CloseHandle(hMapping);
		CloseHandle(hFile);
		return FALSE;
	}	
	m_strText = (LPTSTR)m_pMapviewfile;

	UnmapViewOfFile(m_pMapviewfile);//ȡ���ڴ��ַӳ��
	CloseHandle(hMapping);//�ر�ӳ�������
	CloseHandle(hFile);//�ر��ļ����

	return TRUE;
}