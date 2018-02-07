
// BackupDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Backup.h"
#include "BackupDlg.h"
#include "afxdialogex.h"

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


// CBackupDlg �Ի���



CBackupDlg::CBackupDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBackupDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBackupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBackupDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BACKUP, &CBackupDlg::OnBnClickedBtnBackup)
END_MESSAGE_MAP()


// CBackupDlg ��Ϣ�������

BOOL CBackupDlg::OnInitDialog()
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

void CBackupDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBackupDlg::OnPaint()
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
HCURSOR CBackupDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBackupDlg::OnBnClickedBtnBackup()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString src = "E:\\codeText\\ado";
	CString dst = "E:\\text";
	Resu(dst, src);
}


void CBackupDlg::Resu(CString dst, CString src)
{
	CFileFind finder;
	CString strSrc;
	CString strDst;
	strSrc.Format(_T("%s//*.*"), src);
	int bWorking = finder.FindFile(strSrc); //�鿴Դ�ļ������Ƿ����ļ�
	while (bWorking)
	{
		bWorking = finder.FindNextFile(); //����������һ�ļ�
		if (finder.IsDots()) //����鵽�ļ�Ϊ[.]��[..]�����,ÿ��Ŀ¼�¶��������Ʒֱ�Ϊ[.]��[..]���ļ���
			continue;
		if (finder.IsDirectory()) //����鵽Ϊ�ļ���,��ݹ���ã��������ļ����е��ļ�
		{
			strSrc = finder.GetFilePath();
			strDst.Format(_T("%s//%s"), dst, finder.GetFileName());
			CreateDirectory(strDst, NULL); //�����Ŀ¼�����ڣ��򴴽���Ŀ¼
			Resu(strDst, strSrc); //�ݹ���ã��������ļ����е��ļ�
		}
		else{ //������ҵ������ļ�
			strSrc = finder.GetFilePath();
			strDst.Format(_T("%s//%s"), dst, finder.GetFileName());
			//if (ContrastFile(strDst, strSrc)) //�Ա�Ŀ���ļ������Ƿ�����Դ�ļ�����
				CopyFile(strSrc, strDst, 0); //����������Ϊ1����Ϊ����ʽ����
		}
	}
}
