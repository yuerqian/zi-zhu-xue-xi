
// ChatDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chat.h"
#include "ChatDlg.h"
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


// CChatDlg �Ի���



CChatDlg::CChatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CChatDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_RECVDATA, OnRecvData)
	ON_BN_CLICKED(IDC_BTN_SEND, &CChatDlg::OnBnClickedBtnSend)
//	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS1, &CChatDlg::OnIpnFieldchangedIpaddress1)
ON_BN_CLICKED(IDCANCEL, &CChatDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CChatDlg ��Ϣ�������

BOOL CChatDlg::OnInitDialog()
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
	RECVPARAM* pRecvParam = new RECVPARAM;
	pRecvParam->sock = m_socket;
	pRecvParam->hwnd = m_hWnd;
	HANDLE hThread=CreateThread(NULL, 0, RecvProc, pRecvParam, 0, NULL);
	CloseHandle(hThread);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CChatDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChatDlg::OnPaint()
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
HCURSOR CChatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



// ��ʼ���׽���
bool CChatDlg::InitSocket()
{
	m_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_socket == INVALID_SOCKET)
	{
		MessageBox("�����׽���ʧ��");
		return FALSE;
	}
	sockaddr_in addrsock;
	addrsock.sin_addr.S_un.S_addr =INADDR_ANY;
	addrsock.sin_family = AF_INET;
	addrsock.sin_port = htons(6000);
	if (bind(m_socket, (SOCKADDR*)&addrsock, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		closesocket(m_socket);
		MessageBox("��ʧ��");
		return FALSE;
	}
	return TRUE;
}


//DWORD  CChatDlg::RecvProc()
//{
//	return 0;
//}

DWORD WINAPI CChatDlg::RecvProc(LPVOID lpParam)
{
	SOCKET sock = ((RECVPARAM*)lpParam)->sock;
	HWND hWnd = ((RECVPARAM*)lpParam)->hwnd;
	delete lpParam;
	char recvBuf[100];
	char tempBuf[100];
	sockaddr_in recvAddr;
	int len;
	int retval;
	len = sizeof(SOCKADDR);
	while (TRUE)
	{
		retval = recvfrom(sock, recvBuf, 100, 0, (SOCKADDR*)&recvAddr, &len);
		if (retval == SOCKET_ERROR)
			break;
		sprintf_s(tempBuf,"%s ˵��%s", inet_ntoa(recvAddr.sin_addr),recvBuf);
		::PostMessage(hWnd, WM_RECVDATA, 0,(LPARAM)tempBuf);
	}
	return 0;
}
LRESULT CChatDlg::OnRecvData(WPARAM wParam, LPARAM lParam)
{
	CString str = (char*)lParam;
	CString strTemp = 0;
	GetDlgItemText(IDC_EDIT_RECV, strTemp);
	str += "\r\n";
	strTemp += str;
	SetDlgItemText(IDC_EDIT_RECV, strTemp);
	return 0;
}

void CChatDlg::OnBnClickedBtnSend()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DWORD IPAddress;
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1))->GetAddress(IPAddress);
	sockaddr_in addrto;
	addrto.sin_addr.S_un.S_addr = htonl(IPAddress);
	addrto.sin_family = AF_INET;
	addrto.sin_port = htons(6000);

	CString strSend;
	GetDlgItemText(IDC_EDIT_SEND, strSend);
	sendto(m_socket, strSend, strSend.GetLength()+1, 0, (SOCKADDR*)&addrto, sizeof(SOCKADDR));
	SetDlgItemText(IDC_EDIT_SEND, "");
}


//void CChatDlg::OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	*pResult = 0;
//}


void CChatDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


BOOL CChatDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)//�س���
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_EDIT_SEND)//���»س��������ǰ���������Լ������Ŀؼ���
		{
			// ���������£�������»س�ʱ����������Ҫ�Ŀؼ���
			CChatDlg::OnBnClickedBtnSend();
		}
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)//ESC��
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
