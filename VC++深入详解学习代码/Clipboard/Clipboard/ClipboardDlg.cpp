
// ClipboardDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Clipboard.h"
#include "ClipboardDlg.h"
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


// CClipboardDlg �Ի���



CClipboardDlg::CClipboardDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClipboardDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClipboardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CClipboardDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEND, &CClipboardDlg::OnBnClickedBtnSend)
	ON_BN_CLICKED(IDC_BTN_RECV, &CClipboardDlg::OnBnClickedBtnRecv)
END_MESSAGE_MAP()


// CClipboardDlg ��Ϣ�������

BOOL CClipboardDlg::OnInitDialog()
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

void CClipboardDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClipboardDlg::OnPaint()
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
HCURSOR CClipboardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClipboardDlg::OnBnClickedBtnSend()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (OpenClipboard())//�򿪼�����
	{
		CString str;//���淢�ͱ༭��ؼ��ϵ�����
		HANDLE hClip;//����GlobalAllo�����������ڴ������
		char* pBuf;//�������GlobalLock�����󷵻ص��ڴ��ַ
		EmptyClipboard();//��ռ�����
		GetDlgItemText(IDC_EDIT_SEND,str);
		hClip=GlobalAlloc(GMEM_MOVEABLE, str.GetLength() + 1);
		pBuf = (char*)GlobalLock(hClip);
		int len = str.GetLength() + 1;
		strcpy_s(pBuf,len, str.GetBuffer(len));
		GlobalUnlock(hClip);
		SetClipboardData(CF_TEXT,hClip);
		CloseClipboard();
		str.ReleaseBuffer();
	}
}


void CClipboardDlg::OnBnClickedBtnRecv()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (OpenClipboard())
	{
		if (IsClipboardFormatAvailable(CF_TEXT))//�жϼ������ϵ�����
		{
			HANDLE hClip;
			char* pBuf;
			hClip = GetClipboardData(CF_TEXT);
			pBuf=(char*)GlobalLock(hClip);
			GlobalUnlock(hClip);
			SetDlgItemText(IDC_EDIT_RECV,pBuf);
			
		}
		CloseClipboard();
	}
}
