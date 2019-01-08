// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// HelmetFCEMDoc.cpp : CHelmetFCEMDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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


// CHelmetFCEMDoc 构造/析构

CHelmetFCEMDoc::CHelmetFCEMDoc()
{
	// TODO: 在此添加一次性构造代码
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
	

	//优良中设置
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
			//设置最终的指标节点
			quota[i].id = i;
			quota[i].name = transTool.toString(quotaName[i]);
			quota[i].childNum = 0;
			quota[i].parentId = -1;
			quota[i].treeRank = -1;


		}
		//for (int i = 0; i < peopleNum; i++) {
		//	//初始化专家输入的指标节点
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
		CString strLine,strText;//一个存储文本一行内容一个存储所有的
		
		//char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
		//setlocale( LC_CTYPE, "chs" );//设定
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

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CHelmetFCEMDoc 序列化

void CHelmetFCEMDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CHelmetFCEMDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CHelmetFCEMDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
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

// CHelmetFCEMDoc 诊断

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


// CHelmetFCEMDoc 命令
