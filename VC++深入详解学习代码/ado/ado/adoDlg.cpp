
// adoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ado.h"
#include "adoDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CadoDlg �Ի���



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


// CadoDlg ��Ϣ�������

BOOL CadoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CadoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CadoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CadoDlg::OnBnClickedBtnQuery()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//��տؼ�
	//((CListBox*)GetDlgItem(IDC_LIST2))->ResetContent();
	while (((CListBox*)GetDlgItem(IDC_LIST2))->GetCount())
	{
		((CListBox*)GetDlgItem(IDC_LIST2))->DeleteString(0);
	}

	CoInitialize(NULL);
	_ConnectionPtr pConn(__uuidof(Connection));//Ҳ���Դ�������ʵ��pConn.CreateInstance(__uuidof(Connection))
	_RecordsetPtr pRst(__uuidof(Recordset));
	_CommandPtr pCmd(__uuidof(Command));
	//CString ConnectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data source=C:\\Users\\Andy\\Documents\\MY.mdb";
	pConn->ConnectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data source=C:\\Users\\Andy\\Documents\\MY.mdb";
	//if (SUCCEEDED(pConn->Open(_bstr_t(ConnectionString), "", "", adConnectUnspecified)))
	//{
	//	MessageBox("�����ݿ�ɹ�");
	//}
	if (!SUCCEEDED(pConn->Open( "","", "", adConnectUnspecified)))
	{
		MessageBox("�����ݿ�ʧ��");
	}
	//pRst = pConn->Execute("select * from �ֿ�1", NULL, adCmdText);//Connection������ȡ����
	//pRst->Open("select * from �ֿ�1", (_variant_t)((IDispatch*)pConn), adOpenDynamic, adLockOptimistic, adCmdText);//Recordset������ȡ����
	pCmd->put_ActiveConnection((_variant_t)((IDispatch*)pConn));//Command�������û����
	pCmd->CommandText = "select * from �ֿ�1";//Command��������SQL���
	pRst = pCmd->Execute(NULL, NULL, adCmdText);//Command����ִ��SQL���
	while (!pRst->rsEOF)//rsEOF�ǵ���com���ʱ������������
	{
		((CListBox*)GetDlgItem(IDC_LIST2))->AddString((_bstr_t)pRst->GetCollect("�۸�"));
		pRst->MoveNext();
	}
	pRst->Close();
	pConn->Close();
	pRst.Release();
	pConn.Release();
	pCmd.Release();
	CoUninitialize();
}
