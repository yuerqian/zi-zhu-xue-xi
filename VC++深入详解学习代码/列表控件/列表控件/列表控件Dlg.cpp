
// �б�ؼ�Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "�б�ؼ�.h"
#include "�б�ؼ�Dlg.h"
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


// C�б�ؼ�Dlg dialog



C�б�ؼ�Dlg::C�б�ؼ�Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C�б�ؼ�Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C�б�ؼ�Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
}

BEGIN_MESSAGE_MAP(C�б�ؼ�Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_CMB_VIEW, &C�б�ؼ�Dlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BTN_ADD, &C�б�ؼ�Dlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DELETE, &C�б�ؼ�Dlg::OnBnClickedBtnDelete)
END_MESSAGE_MAP()


// C�б�ؼ�Dlg message handlers

BOOL C�б�ؼ�Dlg::OnInitDialog()
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
	//��ӱ�ͷ
	m_List.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);//�ı���ʽ
	m_List.InsertColumn(0, "��һ��", LVCFMT_LEFT,120);//����У�1.�ǵڼ��У�2.����������ƣ�3.���뷽ʽ��4. ���
	m_List.InsertColumn(1, "�ڶ���", LVCFMT_LEFT, 120);//����У�1.�ǵڼ��У�2.����������ƣ�3.���뷽ʽ��4. ���
	//������СͼƬ�б�
	m_ImaLarge.Create(IDB_BMP_LARGE, 32, 1, RGB(255, 0, 0));
	m_ImaSmall.Create(IDB_BMP_SMALL, 16, 1, RGB(255, 0, 0));

	//��ͼ���б����õ�����
	m_List.SetImageList(&m_ImaLarge, LVSIL_NORMAL);//��ͼ��
	m_List.SetImageList(&m_ImaSmall, LVSIL_SMALL);//Сͼ��

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void C�б�ؼ�Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C�б�ؼ�Dlg::OnPaint()
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
HCURSOR C�б�ؼ�Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C�б�ؼ�Dlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
}


void C�б�ؼ�Dlg::OnBnClickedBtnAdd()
{
	// TODO: Add your control notification handler code here
	//���ԭ���м���
	int nCount=m_List.GetItemCount();
	CString strText;
	//��ӵ��б�ؼ��������
	strText.Format("��%d�У���1��", nCount + 1);
	m_List.InsertItem(nCount, strText, 0);//�������һ���У�ֻ�ܲ���һ�Σ�1.�ڼ��У�2���ݣ�3.ʹ�������0��ͼ��
	strText.Format("��%d�У���2��", nCount + 1);
	m_List.SetItemText(nCount, 1, strText);//���õڶ��У�1.�ڼ��У�2.�ڼ��У�3.����



}


void C�б�ؼ�Dlg::OnBnClickedBtnDelete()
{
	// TODO: Add your control notification handler code here
	int nCount = m_List.GetItemCount();
	//�Ӻ��濪ʼɾ�����������
	for (int i = 0; i <= nCount; i++)
	{
		//��ȡĳһ�е�״̬����û�б�ѡ�У������ѡ���ˣ��Ͱ���ɾ��
		if (m_List.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			m_List.DeleteItem(i);
		}

	}
}
