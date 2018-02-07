
// FileView.cpp : CFileView ���ʵ��
//

#include "stdafx.h"
#include<fstream>
using namespace std;
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "File.h"
#endif

#include "FileDoc.h"
#include "FileView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileView

IMPLEMENT_DYNCREATE(CFileView, CView)

BEGIN_MESSAGE_MAP(CFileView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFileView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_FILE_WRITE, &CFileView::OnFileWrite)
	ON_COMMAND(IDM_FILE_READ, &CFileView::OnFileRead)
	ON_COMMAND(IDM_REG_WRITE, &CFileView::OnRegWrite)
	ON_COMMAND(IDM_REG_READ, &CFileView::OnRegRead)
END_MESSAGE_MAP()

// CFileView ����/����

CFileView::CFileView()
{
	// TODO:  �ڴ˴���ӹ������

}

CFileView::~CFileView()
{
}

BOOL CFileView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CFileView ����

void CFileView::OnDraw(CDC* /*pDC*/)
{
	CFileDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CFileView ��ӡ


void CFileView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CFileView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CFileView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CFileView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}

void CFileView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFileView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CFileView ���

#ifdef _DEBUG
void CFileView::AssertValid() const
{
	CView::AssertValid();
}

void CFileView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFileDoc* CFileView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFileDoc)));
	return (CFileDoc*)m_pDocument;
}
#endif //_DEBUG


// CFileView ��Ϣ�������


void CFileView::OnFileWrite()
{
	//FILE *pFile = fopen("1.txt", "wb");
	//TCHAR a[19]="http://sunxin.org";
	///*int aa = strlen(a);
	//a[aa] = '\0';*/
	///*fwrite(a, 1, strlen(a)+1, pFile);*/
	//fwrite("http://sunxin.org", 1, strlen("http://sunxin.org")+1, pFile);

	///*fseek(pFile, 0x0012, SEEK_SET);*/
	//int aaaa = 123;
	//char aaa[100] = { 0 };
	//_itoa(aaaa, aaa, 10);
	//fwrite(aaa, sizeof(char), strlen(aaa), pFile);
	///*fprintf(pFile, "%s %d", a, aaaa);*/

	///*char b[] = "adfa13jfal";
	//int len = strlen(b);
	//char *bb;
	//bb = new char[len + 1];
	//int i = 0;
	//int j = 0;
	//for (i = 0; i<len; i++)
	//{
	//	if (b[i] >=48&&b[i]<=57)
	//	{
	//		bb[j] = b[i];
	//		j++;
	//	}

	//}
	//fwrite(bb, 1, j, pFile);*/
	//fclose(pFile);

	/*FILE *File2 = fopen("1.txt", "a");
	fwrite("��ӭ����", 1, strlen("��ӭ����"), File2);
	fclose(File2);*/

	/*FILE *pFile = fopen("2.txt", "wb");
	char ch[3];
	ch[0] = 'a';
	ch[1] = 10;
	ch[2] = 'b';
	fwrite(ch, 1, 3, pFile);
	fclose(pFile);*/

	//FILE *pFile = fopen("3.txt", "w");
	//int i = 98341;
	/*fwrite(&i, 4, 1, pFile);*/
	//fprintf(pFile, "%d", i);
	//fclose(pFile);
	
	/*ofstream ofs("4.txt",ios::binary);
	ofs.write("http://sunxin.org", strlen("http://sunxin.org"));
	ofs.close();*/

	//win API
	/*HANDLE hFile;
	hFile = CreateFile("5.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox("�ļ��򴴽�/�򿪿�����");
		return;
	}
	DWORD dwWrites;
	WriteFile(hFile, "http://sunxin.org", strlen("http://sunxin.org")+1, &dwWrites, NULL);
	WriteFile(hFile, "123", strlen("123"), &dwWrites, NULL);
	CloseHandle(hFile);*/
	//char a[100];
	//_ultoa(dwWrites, a, 100);
	//MessageBox(a);

	//MFC
	/*CFile file("6.txt", CFile::modeCreate | CFile::modeWrite);
	file.Write("http://sunxin.org", strlen("http://sunxin.org")+1);
	file.Write("123", strlen("123"));
	file.Close();*/
	
	/*CFileDialog fileDlg(false);
	fileDlg.m_ofn.lpstrTitle = "�ҵ��ļ�����";
	fileDlg.m_ofn.lpstrFilter = "Dat File(*.dat)\0*.dat\0All File(*.*)\0*.*\0Text File(*.txt)\0*.txt\0\0";
	fileDlg.m_ofn.lpstrDefExt = "txt";
	if (fileDlg.DoModal()==IDOK)
	{
		CFile file(fileDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);
		file.Write("http://sunxin.org", strlen("http://sunxin.org") + 1);
		file.Write("123", strlen("123"));
		file.Close();
	}*/

	/*WritePrivateProfileString("http://sunxin.org", "admin", "zhang", "E:\\\codeText\\File\\File\\7.ini");*/

	/*CFile File("8.txt", CFile::modeCreate|CFile::modeWrite);
	CArchive Ar(&File, CArchive::store);
	int i = 4;
	char ch = 'a';
	float f = 1.3f;
	CString str("http://sunxin.org");
	Ar << i << ch << f << str;*/
	CFileh ff;
	CFile File("8.txt", CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&File, CArchive::store);
	ff.Serialize(ar);
	
}


void CFileView::OnFileRead()
{
	// TODO:  �ڴ���������������
	//FILE *pFile = fopen("1.txt", "r+");
	//char fRead[100] = { 0 };
	//char fRead11[100] = { 0 };
	//int fRead2=0;
	///*memset(fRead, 0, 100);*/
	//fseek(pFile, 0, SEEK_END);
	//int len = ftell(pFile);
	//char* fput;
	//fput = new char[len + 1];
	///*memset(fput, 0, len + 1);*/
	///*while (!feof(pFile))
	//{
	//	fscanf(pFile, "%s %d", fput, &fRead2);
	//}*/
	///*fseek(pFile, 0, SEEK_SET);*/
	//rewind(pFile);
	//fread(fput, 1, len, pFile);
	//fput[len] = 0;
	//fclose(pFile);
	//MessageBoxA(fput);
	//_itoa(len, fRead, 10);
	//MessageBoxA(fRead);

	//FILE *pFile = fopen("2.txt", "r");
	//char ch[100];
	//fread(ch, 1, 3, pFile);
	//ch[3] = 0;
	//fclose(pFile);
	//MessageBox(ch);

	//FILE *pFile = fopen("3.txt", "r");
	//int i=0;
	//char a[100];
	//fscanf(pFile, "%d", &i);
	//fclose(pFile);
	//memset(a, 0, 100);
	//_itoa(i, a, 10);
	//MessageBox(a);

	/*ifstream ifs("4.txt");
	char ch[100];
	memset(ch, 0, 100);
	ifs.read(ch, 100);
	ifs.close();
	MessageBox(ch);*/

	/*HANDLE hFile;
	hFile = CreateFile("5.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox("�ļ�������ʧ��");
	}
	char* ch;
	DWORD LenFile=GetFileSize(hFile, NULL);
	ch = new char[LenFile + 1];
	DWORD dwRead;
	char ch2[3];
	char ch3[100];
	ReadFile(hFile, ch3, 100, &dwRead, NULL);
	SetFilePointer(hFile, -4, NULL, FILE_END);
	ReadFile(hFile, ch2, 3, &dwRead, NULL);
	ch[LenFile] = '\0';
	CloseHandle(hFile);
	MessageBox(ch3);
	MessageBox(ch2);*/

	/*CFile file("6.txt", CFile::modeRead);
	char* pBuf;
	char aa[100] = { 0 };
	DWORD lenFile=file.GetLength();
	pBuf = new char[lenFile + 1];
	pBuf[lenFile] = 0;
	file.Read(aa, 100);
	file.Close();
	MessageBox(pBuf);*/

	//CFileDialog fileOpen(true);
	//fileOpen.m_ofn.lpstrTitle = "�ҵ��ļ���";
	//fileOpen.m_ofn.lpstrFilter = "File Text(.txt)\0*.txt\0All File(*.*)\0*.*\0\0";
	//fileOpen.m_ofn.lpstrDefExt = "txt";
	//if (fileOpen.DoModal() == IDOK)
	//{
	//	CFile file(fileOpen.GetPathName(), CFile::modeRead);
	//	char* pBuf;
	//	DWORD Len = file.GetLength();
	//	pBuf = new char[Len + 1];
	//	memset(pBuf, 0, Len + 1);
	//	file.Read(pBuf, Len);
	//	file.Close();
	//	MessageBox(pBuf);
	//	delete[] pBuf;
	//}
	
	//CFile File("8.txt", CFile::modeRead);
	//CArchive Ar(&File, CArchive::load);
	//int i;
	//char ch;
	//float f;
	//CString str;
	//CString StrResult;
	//Ar >> i >> ch >> f >> str;
	//StrResult.Format("%d,%c,%f,%s", i, ch, f, str);
	//MessageBox(StrResult);
	//File.Close();
	CFileh ff;
    CFile File("8.txt", CFile::modeRead);
    CArchive ar(&File, CArchive::load);
	ff.Serialize(ar);

}


void CFileView::OnRegWrite()
{
	// TODO:  �ڴ���������������
	HKEY hKey;
	if(ERROR_SUCCESS!=RegCreateKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\http://sunxin.org\\admin", &hKey))
	{
		AfxMessageBox("������α�ʧ��");
		return;
	}
	if (ERROR_SUCCESS != RegSetValue(hKey, NULL, REG_SZ, "zhangsan", strlen("zhangsan")))
	{
		AfxMessageBox("����ע���ֵʧ��");
		return;
	}
	DWORD dwAge = 30;
	if (ERROR_SUCCESS != RegSetValueEx(hKey, "age", 0,REG_DWORD, (const BYTE*)&dwAge, 4))
	{
		AfxMessageBox("����ע���ֵʧ��");
		return;
	}
	RegCloseKey(hKey);

}


void CFileView::OnRegRead()
{
	// TODO:  �ڴ���������������
	/*long lValue;
	RegQueryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\http://sunxin.org\\admin", NULL, &lValue);
	char* pBuf = new char[lValue];
	RegQueryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\http://sunxin.org\\admin", pBuf, &lValue);
	MessageBox(pBuf);
	delete[] pBuf;*/
	HKEY hKey;
	RegOpenKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\http://sunxin.org\\admin", &hKey);
	DWORD dwType;
	DWORD dwAge;
	DWORD lValue;
	RegQueryValueEx(hKey, "age", 0, &dwType, (LPBYTE)&dwAge, &lValue);
	CString str;
	str.Format("age=%d", dwAge);
	MessageBox(str);
	RegCloseKey(hKey);

}

