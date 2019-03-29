
// �������ϵͳDlg.cpp : implementation file
//

#include "stdafx.h"
#include "�������ϵͳ.h"
#include "�������ϵͳDlg.h"
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


// C�������ϵͳDlg dialog



C�������ϵͳDlg::C�������ϵͳDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C�������ϵͳDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C�������ϵͳDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C�������ϵͳDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// C�������ϵͳDlg message handlers

BOOL C�������ϵͳDlg::OnInitDialog()
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
	//��ʼ�����ݿ�
	AfxOleInit();
	//��ʼ��list control�ؼ�
	LV_COLUMN listColumn;//�б�ؼ�
	char* listTittle[2] = { "ѧ��", "����" };
	int intColCx[2] = { 100, 120 };//ÿ��ռ��������
	listColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM; //�б�ؼ�����ʽ��LVCF_FMT

	//����access���ݿ����Ӷ���
	if (!SUCCEEDED(m_Connection.CreateInstance(__uuidof(Connection))))
	{
		m_Connection = NULL;
		AfxMessageBox("�������Ӷ���ʧ�ܣ�");
	}
	CString strConnect = "provider=Microsoft.Jet.OLEDB.4.0;Data source=C:\\Users\\Andy\\Documents\\MY.mdb";//ע�����ݿ��������б�ܣ�\���ģ�һ��Ҫת�壨��˫\\��
	try{
		m_Connection->Open(_bstr_t(strConnect), "", "", adConnectUnspecified);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
		m_Connection = NULL;
		return TRUE;
	}
	catch (...)
	{
		AfxMessageBox("δ֪����");
		m_Connection = NULL;
		return TRUE;
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void C�������ϵͳDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C�������ϵͳDlg::OnPaint()
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
HCURSOR C�������ϵͳDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

