
// AsyncChatDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AsyncChat.h"
#include "AsyncChatDlg.h"
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


// CAsyncChatDlg �Ի���



CAsyncChatDlg::CAsyncChatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAsyncChatDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAsyncChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAsyncChatDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_MESSAGE(UM_SOCK, OnSock)
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEND, &CAsyncChatDlg::OnBnClickedBtnSend)
END_MESSAGE_MAP()


// CAsyncChatDlg ��Ϣ�������

BOOL CAsyncChatDlg::OnInitDialog()
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
	InitSocket();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CAsyncChatDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAsyncChatDlg::OnPaint()
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
HCURSOR CAsyncChatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



bool CAsyncChatDlg::InitSocket()
{
	m_socket = WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0, 0);
	if (m_socket == INVALID_SOCKET)
	{
		AfxMessageBox("�����׽���ʧ��");
		return FALSE;
	}
	sockaddr_in sockaddr;
	sockaddr.sin_addr.S_un.S_addr = INADDR_ANY;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(6000);
	if (bind(m_socket, (SOCKADDR*)&sockaddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		AfxMessageBox("���׽���ʧ��");
		return FALSE;
	}
	if (WSAAsyncSelect(m_socket, m_hWnd, UM_SOCK, FD_READ) == SOCKET_ERROR)
	{
		AfxMessageBox("ע�������ȡ�¼�ʧ��");
		return FALSE;
	}
	return true;
}
LRESULT CAsyncChatDlg::OnSock(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(lParam))
	{
	case FD_READ:
	{
					WSABUF wsabuf;
					wsabuf.buf = new char[200];
					wsabuf.len = 200;
					DWORD dwRead;
					DWORD flag = 0;
					SOCKADDR_IN addrFrom;
					int len = sizeof(SOCKADDR);
					CString str;
					CString strtemp;
					if (WSARecvFrom(m_socket, &wsabuf, 1, &dwRead, &flag, (SOCKADDR*)&addrFrom, &len, NULL, NULL) == SOCKET_ERROR)
					{
						MessageBox("��������ʧ��");
						delete[] wsabuf.buf;
						return FALSE;
					}
					str.Format("%s˵��%s", inet_ntoa(addrFrom.sin_addr), wsabuf.buf);
					str += "\r\n";
					GetDlgItemText(IDC_EDIT_RECV, strtemp);
					str += strtemp;
					SetDlgItemText(IDC_EDIT_RECV, str);
					delete[] wsabuf.buf;
					break;
	}
	default:
	{
			   AfxMessageBox("û���յ������¼�");
			   break;
	}
		
	}
}

void CAsyncChatDlg::OnBnClickedBtnSend()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DWORD dwIP;
	sockaddr_in addrto;
	CString strsend;
	int len;
	WSABUF wsabuf;
	DWORD dwsend;
	CString strhostname;
	HOSTENT* pHost;

	if (GetDlgItemText(IDC_EDIT_HOSTNAME, strhostname), strhostname == "")
	{
		((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1))->GetAddress(dwIP);
		addrto.sin_addr.S_un.S_addr = htonl(dwIP);
	}
	else
	{
		pHost = gethostbyname(strhostname);
		addrto.sin_addr.S_un.S_addr = *((DWORD*)pHost->h_addr_list[0]);
	}
	//((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1))->GetAddress(dwIP);
	//addrto.sin_addr.S_un.S_addr = htonl(dwIP);
	addrto.sin_port = htons(6000);
	addrto.sin_family = AF_INET;

	GetDlgItemText(IDC_EDIT_SEND, strsend);

	len = strsend.GetLength();
	wsabuf.buf = strsend.GetBuffer(len);
	wsabuf.len = len + 1;


	if (WSASendTo(m_socket, &wsabuf, 1, &dwsend, 0, (SOCKADDR*)&addrto, sizeof(SOCKADDR), NULL, NULL) == SOCKET_ERROR)
	{
		MessageBox("��������ʧ�ܣ�");
		return;
	}
	SetDlgItemText(IDC_EDIT_SEND, "");
}
