
// ChatAsyncDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatAsync.h"
#include "ChatAsyncDlg.h"
#include "afxdialogex.h"
#include"qqq.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX, };

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


// CChatAsyncDlg 对话框



CChatAsyncDlg::CChatAsyncDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatAsyncDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatAsyncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CChatAsyncDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_SOCK, OnSock)
	ON_BN_CLICKED(IDC_BTN_SEND, &CChatAsyncDlg::OnBnClickedBtnSend)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CChatAsyncDlg 消息处理程序

BOOL CChatAsyncDlg::OnInitDialog()
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
	GetDlgItem(IDC_BTN_SEND)->SetFocus();

	//缩放对话框的所有控件
	CRect rectWnd;
	GetWindowRect(&rectWnd);//得到当前对话框的坐标
	listRect.AddTail(&rectWnd);//将坐标添加到链表listRect的末尾

	CWnd *pWndChild = GetWindow(GW_CHILD);// 寻找源窗口的第一个子窗口
	while (pWndChild)//依次得到对话框上控件的坐标，并将所有的控件坐标存储在链表中
	{
		pWndChild->GetWindowRect(&rectWnd);
		listRect.AddTail(&rectWnd);//由于依次将控件坐标添加到链表末尾，所以开头的坐标是对话框的坐标
		pWndChild = pWndChild->GetNextWindow();
	}
	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChatAsyncDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChatAsyncDlg::OnPaint()
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
HCURSOR CChatAsyncDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CChatAsyncDlg::InitSocket()
{
	m_socket = WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0, 0);
	if (m_socket == INVALID_SOCKET)
	{
		AfxMessageBox("创建套接字失败");
		return FALSE;
	}
	sockaddr_in sockaddr;
	sockaddr.sin_addr.S_un.S_addr = INADDR_ANY;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(6000);
	if (bind(m_socket, (SOCKADDR*)&sockaddr, sizeof(SOCKADDR))==SOCKET_ERROR)
	{
		AfxMessageBox("绑定套接字失败");
		return FALSE;
	}
	if (WSAAsyncSelect(m_socket, m_hWnd, UM_SOCK, FD_READ) == SOCKET_ERROR)
	{
		AfxMessageBox("注册网络读取事件失败");
		return FALSE;
	}
	return TRUE;
}

LRESULT CChatAsyncDlg::OnSock(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(lParam))
	{
	case FD_READ:
	{
					WSABUF wsabuf;
					wsabuf.buf = new char[200];
					wsabuf.len = 200;
					DWORD dwRead;
					DWORD flag=0;
					SOCKADDR_IN addrFrom;
					int len = sizeof(SOCKADDR);
					CString str;
					CString strtemp;
					if (WSARecvFrom(m_socket, &wsabuf, 1, &dwRead, &flag, (SOCKADDR*)&addrFrom, &len, NULL, NULL) == SOCKET_ERROR)
					{
						MessageBox("接收数据失败");
						delete[] wsabuf.buf;
						return FALSE;
					}
					str.Format("%s说：%s", inet_ntoa(addrFrom.sin_addr), wsabuf.buf);
					str += "\r\n";
					GetDlgItemText(IDC_EDIT_RECV, strtemp);
					str += strtemp;
					SetDlgItemText(IDC_EDIT_RECV, str);
					delete[] wsabuf.buf;
					break;
	}
	default:
	{
			   AfxMessageBox("接收未知网络事件");
			   break;
	}
		
	}
}

void CChatAsyncDlg::OnBnClickedBtnSend()
{
	// TODO:  在此添加控件通知处理程序代码
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
	addrto.sin_port = htons(6000);
	addrto.sin_family = AF_INET;
	
	GetDlgItemText(IDC_EDIT_SEND, strsend);
	
	len = strsend.GetLength();
	wsabuf.buf = strsend.GetBuffer(len);
	wsabuf.len = len + 1;

	
	if (WSASendTo(m_socket, &wsabuf, 1, &dwsend, 0,(SOCKADDR*)&addrto, sizeof(SOCKADDR), NULL, NULL) == SOCKET_ERROR)
	{
		MessageBox("发送数据失败！");
		return;
	}
	SetDlgItemText(IDC_EDIT_SEND, "");

	/*qqq dlg1;
	dlg1.DoModal();*/

}


BOOL CChatAsyncDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_RETURN)
	{
		GetDlgItem(IDC_BTN_SEND)->SetFocus();//聚焦到发送键上
		if (GetFocus()->GetDlgCtrlID() == IDC_BTN_SEND)
		{
			CChatAsyncDlg::OnBnClickedBtnSend();
		}
		return true;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
CChatAsyncDlg::~CChatAsyncDlg()
{
	if (m_socket)
		closesocket(m_socket);
}


void CChatAsyncDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	if (listRect.GetCount()>0)//看链表是否为空
	{
		CRect rectDlgNow;
		GetWindowRect(&rectDlgNow);//得到当前对话框的坐标
		POSITION mp = listRect.GetHeadPosition();//取得存储在链表中的头元素，其实就是前边的对话框坐标
		CRect rectDlgSaved;
		rectDlgSaved = listRect.GetNext(mp);
		ScreenToClient(rectDlgNow);
		float fRateScaleX = (float)(rectDlgNow.right - rectDlgNow.left) / (rectDlgSaved.right - rectDlgSaved.left);//拖拉后的窗口大小与原来窗口大小的比例
		float fRateScaleY = (float)(rectDlgNow.bottom - rectDlgNow.top) / (rectDlgSaved.bottom - rectDlgSaved.top);
		ClientToScreen(rectDlgNow);
		CRect rectChildSaved;
		CWnd *pWndChild = GetWindow(GW_CHILD);
		int n = 1;  //当前处理缩放控件的TAB值
		while (pWndChild)
		{
			rectChildSaved = listRect.GetNext(mp);
			rectChildSaved.left = rectDlgNow.left + (int)((rectChildSaved.left - rectDlgSaved.left)*fRateScaleX);
			rectChildSaved.top = rectDlgNow.top + (int)((rectChildSaved.top - rectDlgSaved.top)*fRateScaleY);
			rectChildSaved.right = rectDlgNow.right + (int)((rectChildSaved.right - rectDlgSaved.right)*fRateScaleX);
			if ( n == 79)  //根据控件Tab值判定控件执行循序，进而判定是否为下拉菜单控件
			{
				//判定是下拉菜单的控件其高度增加100
				rectChildSaved.bottom = rectDlgNow.bottom + (int)((rectChildSaved.bottom - rectDlgSaved.bottom)*fRateScaleY) + 100;
			}
			else
			{
				rectChildSaved.bottom = rectDlgNow.bottom + (int)((rectChildSaved.bottom - rectDlgSaved.bottom)*fRateScaleY);
			}
			ScreenToClient(rectChildSaved);
			pWndChild->MoveWindow(rectChildSaved);
			pWndChild = pWndChild->GetNextWindow();
			n++;
		}
	}
	Invalidate(); //强制重绘窗口
}
