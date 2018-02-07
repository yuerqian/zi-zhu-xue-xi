
// ChatDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Chat.h"
#include "ChatDlg.h"
#include "afxdialogex.h"

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


// CChatDlg 对话框



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


// CChatDlg 消息处理程序

BOOL CChatDlg::OnInitDialog()
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
	InitSocket();
	RECVPARAM* pRecvParam = new RECVPARAM;
	pRecvParam->sock = m_socket;
	pRecvParam->hwnd = m_hWnd;
	HANDLE hThread=CreateThread(NULL, 0, RecvProc, pRecvParam, 0, NULL);
	CloseHandle(hThread);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChatDlg::OnPaint()
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
HCURSOR CChatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



// 初始化套接字
bool CChatDlg::InitSocket()
{
	m_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_socket == INVALID_SOCKET)
	{
		MessageBox("创建套接字失败");
		return FALSE;
	}
	sockaddr_in addrsock;
	addrsock.sin_addr.S_un.S_addr =INADDR_ANY;
	addrsock.sin_family = AF_INET;
	addrsock.sin_port = htons(6000);
	if (bind(m_socket, (SOCKADDR*)&addrsock, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		closesocket(m_socket);
		MessageBox("绑定失败");
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
		sprintf_s(tempBuf,"%s 说：%s", inet_ntoa(recvAddr.sin_addr),recvBuf);
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
	// TODO:  在此添加控件通知处理程序代码
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
//	// TODO:  在此添加控件通知处理程序代码
//	*pResult = 0;
//}


void CChatDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


BOOL CChatDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)//回车键
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_EDIT_SEND)//按下回车，如果当前焦点是在自己期望的控件上
		{
			// 你想做的事，如果按下回车时焦点在你想要的控件上
			CChatDlg::OnBnClickedBtnSend();
		}
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)//ESC键
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
