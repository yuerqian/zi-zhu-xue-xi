
// FileDoc.cpp : CFileDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "File.h"
#endif

#include "FileDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFileDoc

IMPLEMENT_DYNCREATE(CFileDoc, CDocument)
IMPLEMENT_SERIAL(CFileh, CFileDoc, 2)
BEGIN_MESSAGE_MAP(CFileDoc, CDocument)
END_MESSAGE_MAP()


// CFileDoc 构造/析构

CFileDoc::CFileDoc()
{
	// TODO:  在此添加一次性构造代码

}

CFileDoc::~CFileDoc()
{
}

BOOL CFileDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	SetTitle("http://sunxin.org");


	return TRUE;
}




// CFileDoc 序列化

void CFileDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
		//CFileh ff;
		//ff.Serialize(ar);
		//int i = 0;
		//ar << i;

	}
	else
	{
		// TODO:  在此添加加载代码
		//CFileh ff;
		//ff.Serialize(ar);
		//int i = 0;
		//ar >> i;
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CFileDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CFileDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CFileDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CFileDoc 诊断

#ifdef _DEBUG
void CFileDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFileDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFileDoc 命令

CFileh::CFileh()
{
	
}
void CFileh::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		int i = 4;
		char ch = 'a';
		float f = 1.3f;
		CString str("http://sunxin.org");
		ar << i << ch << f << str;
	}
	else
	{
		int i;
		char ch;
		float f;
		CString str;
		CString StrResult;
		ar >> i >> ch >> f >> str;
		StrResult.Format("%d,%c,%f,%s", i, ch, f, str);
		AfxMessageBox(StrResult);
	}
}

