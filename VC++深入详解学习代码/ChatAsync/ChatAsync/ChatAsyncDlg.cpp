
// ChatAsyncDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatAsync.h"
#include "ChatAsyncDlg.h"
#include "afxdialogex.h"
#include"qqq.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX, };

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


// CChatAsyncDlg �Ի���



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


// CChatAsyncDlg ��Ϣ�������

BOOL CChatAsyncDlg::OnInitDialog()
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
	GetDlgItem(IDC_BTN_SEND)->SetFocus();

	//���ŶԻ�������пؼ�
	CRect rectWnd;
	GetWindowRect(&rectWnd);//�õ���ǰ�Ի��������
	listRect.AddTail(&rectWnd);//��������ӵ�����listRect��ĩβ

	CWnd *pWndChild = GetWindow(GW_CHILD);// Ѱ��Դ���ڵĵ�һ���Ӵ���
	while (pWndChild)//���εõ��Ի����Ͽؼ������꣬�������еĿؼ�����洢��������
	{
		pWndChild->GetWindowRect(&rectWnd);
		listRect.AddTail(&rectWnd);//�������ν��ؼ�������ӵ�����ĩβ�����Կ�ͷ�������ǶԻ��������
		pWndChild = pWndChild->GetNextWindow();
	}
	return FALSE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChatAsyncDlg::OnPaint()
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
HCURSOR CChatAsyncDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CChatAsyncDlg::InitSocket()
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
	if (bind(m_socket, (SOCKADDR*)&sockaddr, sizeof(SOCKADDR))==SOCKET_ERROR)
	{
		AfxMessageBox("���׽���ʧ��");
		return FALSE;
	}
	if (WSAAsyncSelect(m_socket, m_hWnd, UM_SOCK, FD_READ) == SOCKET_ERROR)
	{
		AfxMessageBox("ע�������ȡ�¼�ʧ��");
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
			   AfxMessageBox("����δ֪�����¼�");
			   break;
	}
		
	}
}

void CChatAsyncDlg::OnBnClickedBtnSend()
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
	addrto.sin_port = htons(6000);
	addrto.sin_family = AF_INET;
	
	GetDlgItemText(IDC_EDIT_SEND, strsend);
	
	len = strsend.GetLength();
	wsabuf.buf = strsend.GetBuffer(len);
	wsabuf.len = len + 1;

	
	if (WSASendTo(m_socket, &wsabuf, 1, &dwsend, 0,(SOCKADDR*)&addrto, sizeof(SOCKADDR), NULL, NULL) == SOCKET_ERROR)
	{
		MessageBox("��������ʧ�ܣ�");
		return;
	}
	SetDlgItemText(IDC_EDIT_SEND, "");

	/*qqq dlg1;
	dlg1.DoModal();*/

}


BOOL CChatAsyncDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_RETURN)
	{
		GetDlgItem(IDC_BTN_SEND)->SetFocus();//�۽������ͼ���
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

	// TODO:  �ڴ˴������Ϣ����������
	if (listRect.GetCount()>0)//�������Ƿ�Ϊ��
	{
		CRect rectDlgNow;
		GetWindowRect(&rectDlgNow);//�õ���ǰ�Ի��������
		POSITION mp = listRect.GetHeadPosition();//ȡ�ô洢�������е�ͷԪ�أ���ʵ����ǰ�ߵĶԻ�������
		CRect rectDlgSaved;
		rectDlgSaved = listRect.GetNext(mp);
		ScreenToClient(rectDlgNow);
		float fRateScaleX = (float)(rectDlgNow.right - rectDlgNow.left) / (rectDlgSaved.right - rectDlgSaved.left);//������Ĵ��ڴ�С��ԭ�����ڴ�С�ı���
		float fRateScaleY = (float)(rectDlgNow.bottom - rectDlgNow.top) / (rectDlgSaved.bottom - rectDlgSaved.top);
		ClientToScreen(rectDlgNow);
		CRect rectChildSaved;
		CWnd *pWndChild = GetWindow(GW_CHILD);
		int n = 1;  //��ǰ�������ſؼ���TABֵ
		while (pWndChild)
		{
			rectChildSaved = listRect.GetNext(mp);
			rectChildSaved.left = rectDlgNow.left + (int)((rectChildSaved.left - rectDlgSaved.left)*fRateScaleX);
			rectChildSaved.top = rectDlgNow.top + (int)((rectChildSaved.top - rectDlgSaved.top)*fRateScaleY);
			rectChildSaved.right = rectDlgNow.right + (int)((rectChildSaved.right - rectDlgSaved.right)*fRateScaleX);
			if ( n == 79)  //���ݿؼ�Tabֵ�ж��ؼ�ִ��ѭ�򣬽����ж��Ƿ�Ϊ�����˵��ؼ�
			{
				//�ж��������˵��Ŀؼ���߶�����100
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
	Invalidate(); //ǿ���ػ洰��
}
