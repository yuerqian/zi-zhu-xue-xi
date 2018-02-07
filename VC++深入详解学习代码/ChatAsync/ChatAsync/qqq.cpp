// qqq.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatAsync.h"
#include "qqq.h"
#include "afxdialogex.h"
#include "resource.h"


// qqq 对话框

IMPLEMENT_DYNAMIC(qqq, CDialogEx)

qqq::qqq(CWnd* pParent /*=NULL*/)
	: CDialogEx(qqq::IDD, pParent)
{

}

qqq::~qqq()
{
}

void qqq::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(qqq, CDialogEx)
END_MESSAGE_MAP()


// qqq 消息处理程序
