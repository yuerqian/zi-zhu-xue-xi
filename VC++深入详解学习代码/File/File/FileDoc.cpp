
// FileDoc.cpp : CFileDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


// CFileDoc ����/����

CFileDoc::CFileDoc()
{
	// TODO:  �ڴ����һ���Թ������

}

CFileDoc::~CFileDoc()
{
}

BOOL CFileDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	SetTitle("http://sunxin.org");


	return TRUE;
}




// CFileDoc ���л�

void CFileDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  �ڴ���Ӵ洢����
		//CFileh ff;
		//ff.Serialize(ar);
		//int i = 0;
		//ar << i;

	}
	else
	{
		// TODO:  �ڴ���Ӽ��ش���
		//CFileh ff;
		//ff.Serialize(ar);
		//int i = 0;
		//ar >> i;
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CFileDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CFileDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CFileDoc ���

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


// CFileDoc ����

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

