// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// HelmetFCEMDoc.cpp : CHelmetFCEMDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "HelmetFCEM.h"
#endif

#include "HelmetFCEMDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHelmetFCEMDoc

IMPLEMENT_DYNCREATE(CHelmetFCEMDoc, CDocument)

BEGIN_MESSAGE_MAP(CHelmetFCEMDoc, CDocument)
END_MESSAGE_MAP()


// CHelmetFCEMDoc ����/����

CHelmetFCEMDoc::CHelmetFCEMDoc()
{
	// TODO: �ڴ����һ���Թ������
	CString peopleNum_cs;
	CString quotaNum_cs;
	CString percent_cs;
	CString setQuotaWeightTag_cs;
	setQuotaWeightTag = false;
	GetPrivateProfileString(_T("mainConfig"), _T("peopleNum"), _T(""), peopleNum_cs.GetBuffer(MAX_PATH), MAX_PATH, _T("./config//config.ini"));
	GetPrivateProfileString(_T("mainConfig"), _T("quotaNum"), _T(""), quotaNum_cs.GetBuffer(MAX_PATH), MAX_PATH, _T("./config//config.ini"));
	GetPrivateProfileString(_T("mainConfig"), _T("percent"), _T(""), percent_cs.GetBuffer(MAX_PATH), MAX_PATH, _T("./config//config.ini"));
	GetPrivateProfileString(_T("mainConfig"), _T("setQuotaWeightTag"), _T(""), setQuotaWeightTag_cs.GetBuffer(MAX_PATH), MAX_PATH, _T("./config//config.ini"));

	int setQuotaWeightTag_int=transTool.toInt(setQuotaWeightTag_cs);
	if (setQuotaWeightTag_int==1)
	{
		setQuotaWeightTag=true;
	}
	if (!peopleNum_cs.IsEmpty() || peopleNum_cs.GetLength() == 0) {
		//zhibiaoNum = _T("0");
	}
	//peopleNum = transTool.toInt(peopleNum_cs);
	quotaNum = transTool.toInt(quotaNum_cs);
	//percent = transTool.toDouble(percent_cs);
	peopleNumTag = false;
	fistsetQuotaTag = false;
	sencondsetQuotaTag = false;
	
	canPicture=false;
	quotaParamcount = -1;
	CinParamPersonNum=1;
	CinParamPersonCount=0;
	useWhatPicture=2;
	useWhatArithmeticTag=0;
	setUserCinQuotaNumTag=false;
	finalQuota = new Quota[quotaNum];
	

	//����������
	 you=0.9;
	 liang=0.8;
	 zhong=0.6;
	 youTag=false;
	 liangTag=false;
	 zhongTag=false;
	 for (int i=0;i<4;i++)
	 { ToPicresult[i]=0;
	 }
	//setfirstQutaNum = 0;
	//setsecondQutaNum = 0;
	if (quotaNum != 0) {
		quota = new Quota[quotaNum];
		//	expertQuotaCinData = new Quota *[quotaNum];

		for (int i = 0; i < quotaNum; i++) {
			GetPrivateProfileString(_T("quotaName"), transTool.toCString(i), _T(""), (quotaName[i]).GetBuffer(MAX_PATH), MAX_PATH, _T("./config//config.ini"));
			//�������յ�ָ��ڵ�
			quota[i].id = i;
			quota[i].name = transTool.toString(quotaName[i]);
			quota[i].childNum = 0;
			quota[i].parentId = -1;
			quota[i].treeRank = -1;


		}
		//for (int i = 0; i < peopleNum; i++) {
		//	//��ʼ��ר�������ָ��ڵ�
		//	expertQuotaCinData[i] = new Quota[quotaNum];
		//	for (int j = 0; j < quotaNum; j++) {
		//		expertQuotaCinData[i][j].id = quota[j].id;
		//		expertQuotaCinData[i][j].name = quota[j].name;
		//		expertQuotaCinData[i][j].childNum = 0;
		//		expertQuotaCinData[i][j].treeRank = -1;
		//		expertQuotaCinData[i][j].parentId = -1;
		//	}
		//}
	}

	/////////////////////
	if (setQuotaWeightTag)
	{
		CStdioFile File;
	File.Open(_T(".//config//data.txt"), CFile::modeRead);
	for (int i = 0; i <quotaNum; i++) {
		CString strLine,strText;//һ���洢�ı�һ������һ���洢���е�
		
		//char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
		//setlocale( LC_CTYPE, "chs" );//�趨
		File.ReadString(strLine);
		CStringArray strResult;
		//CString strLine = _T("1++2+3+4");

		CString strGap = _T("#");
		int nPos = strLine.Find(strGap);

		CString strLeft = _T("");
		while(0 <= nPos)
		{
			strLeft = strLine.Left(nPos);
			if (!strLeft.IsEmpty())
				strResult.Add(strLeft);

			strLine = strLine.Right(strLine.GetLength() - nPos - 1);
			nPos = strLine.Find(strGap);
		}

		if (!strLine.IsEmpty()) {
			strResult.Add(strLine);
		}
		//int nSize = strResult.GetSize();
		for (int j = 0; j < 5; j++)
		{
			CString temp=strResult.GetAt(j);
			switch(j){
			case 0:{
				finalQuota[i].id=transTool.toInt(temp);
				break;};
				case 1:{
					finalQuota[i].parentId=transTool.toInt(temp);break;};
					case 2:{
						finalQuota[i].weight=transTool.toDouble(temp);
						break;};
						case 3:{
							finalQuota[i].treeRank=transTool.toInt(temp);
							break;};
						case 4:{
							finalQuota[i].childNum=transTool.toInt(temp);
								break;};
						
			}
			
		}
		finalQuota[i].name=quota[i].name;
	}
	/*for (int i=0;i<quotaNum;i++)
	{
		int n=finalQuota[i].id;
		double wei=finalQuota[i].weight;
	}*/
	File.Close();
	}
	
}

CHelmetFCEMDoc::~CHelmetFCEMDoc()
{
}

BOOL CHelmetFCEMDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CHelmetFCEMDoc ���л�

void CHelmetFCEMDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CHelmetFCEMDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CHelmetFCEMDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CHelmetFCEMDoc::SetSearchContent(const CString& value)
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

// CHelmetFCEMDoc ���

#ifdef _DEBUG
void CHelmetFCEMDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHelmetFCEMDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CHelmetFCEMDoc ����
