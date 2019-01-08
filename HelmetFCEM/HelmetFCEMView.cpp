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

// HelmetFCEMView.cpp : CHelmetFCEMView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "HelmetFCEM.h"
#endif

#include "HelmetFCEMDoc.h"
#include "HelmetFCEMView.h"
#include "MainFrm.h"
#include "DialogSetParam.h"
#include "pdflib.h"
#pragma comment(lib, "PDFLib.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHelmetFCEMView

IMPLEMENT_DYNCREATE(CHelmetFCEMView, CScrollView)

BEGIN_MESSAGE_MAP(CHelmetFCEMView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHelmetFCEMView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON2, &CHelmetFCEMView::OnButton2)
	ON_COMMAND(ID_BUTTON3, &CHelmetFCEMView::OnButton3)
	ON_COMMAND(ID_BUTTON4, &CHelmetFCEMView::OnButton4)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_BUTTON9, &CHelmetFCEMView::OnButton9)
	ON_COMMAND(ID_BUTTONFIRST, &CHelmetFCEMView::OnButtonfirst)
	ON_UPDATE_COMMAND_UI(ID_EDIT2, &CHelmetFCEMView::OnUpdateEdit2)
	ON_COMMAND(ID_EDIT2, &CHelmetFCEMView::OnEdit2)
	ON_COMMAND(ID_BUTTON5, &CHelmetFCEMView::OnButton5)
	ON_COMMAND(ID_BUTTON6, &CHelmetFCEMView::OnButton6)
	ON_COMMAND(ID_BUTTON7, &CHelmetFCEMView::OnButton7)
	ON_COMMAND(ID_BUTTON8, &CHelmetFCEMView::OnButton8)
	ON_COMMAND(ID_BUTTONSHOWPIC, &CHelmetFCEMView::OnButtonshowpic)
	ON_COMMAND(ID_OUTPDF, &CHelmetFCEMView::OnOutpdf)
	ON_COMMAND(ID_SETSECOND, &CHelmetFCEMView::OnSetsecond)
	ON_COMMAND(ID_BUTTON11, &CHelmetFCEMView::OnButton11)
	ON_COMMAND(ID_BUTTON12, &CHelmetFCEMView::OnButton12)
	ON_COMMAND(ID_BUTTON13, &CHelmetFCEMView::OnButton13)
	ON_UPDATE_COMMAND_UI(ID_EDIT3, &CHelmetFCEMView::OnUpdateEdit3)
	ON_COMMAND(ID_EDIT3, &CHelmetFCEMView::OnEdit3)
	ON_COMMAND(ID_EDIT6, &CHelmetFCEMView::OnEdit6)
	ON_UPDATE_COMMAND_UI(ID_EDIT6, &CHelmetFCEMView::OnUpdateEdit6)
	ON_COMMAND(ID_EDIT7, &CHelmetFCEMView::OnEdit7)
	ON_COMMAND(ID_EDIT8, &CHelmetFCEMView::OnEdit8)
	ON_UPDATE_COMMAND_UI(ID_EDIT7, &CHelmetFCEMView::OnUpdateEdit7)
	ON_UPDATE_COMMAND_UI(ID_EDIT8, &CHelmetFCEMView::OnUpdateEdit8)
END_MESSAGE_MAP()

// CHelmetFCEMView 构造/析构

CHelmetFCEMView::CHelmetFCEMView()
{
	// TODO: 在此处添加构造代码
	setFirstQuotaCount = 0;
	setSecondQuotaCount = 0;
	setQuotaWeightCount = 0;
	setUserCinQuotaParaCount=0;


}

CHelmetFCEMView::~CHelmetFCEMView()
{
}

BOOL CHelmetFCEMView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CHelmetFCEMView 绘制

void CHelmetFCEMView::OnDraw(CDC* /*pDC*/)
{
	CHelmetFCEMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CHelmetFCEMView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	//pFrame->pTabbedBar->ShowPane(TRUE,FALSE,TRUE);
	pFrame->m_wndClassView.IsVisible();
	pFrame->m_wndClassView.ShowWindow(SW_SHOW);
	pFrame->m_wndClassView.IsWindowVisible();
	pFrame->m_wndOutput.IsVisible();
}


// CHelmetFCEMView 打印


void CHelmetFCEMView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHelmetFCEMView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CHelmetFCEMView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CHelmetFCEMView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CHelmetFCEMView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHelmetFCEMView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHelmetFCEMView 诊断

#ifdef _DEBUG
void CHelmetFCEMView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CHelmetFCEMView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CHelmetFCEMDoc* CHelmetFCEMView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHelmetFCEMDoc)));
	return (CHelmetFCEMDoc*)m_pDocument;
}
#endif //_DEBUG


// CHelmetFCEMView 消息处理程序

//建立一级指标
void CHelmetFCEMView::OnButton2()
{
	// TODO: 在此添加命令处理程序代码
	pDoc=GetDocument();
	pMF = (CMainFrame*)AfxGetMainWnd();
	pMF->m_wndClassView.showTree(pDoc);
}
//输入评价参数
void CHelmetFCEMView::OnButton3()
{
	// TODO: 在此添加命令处理程序代码
	pDoc = GetDocument();
	if(!pDoc->setUserCinQuotaNumTag||!pDoc->setQuotaWeightTag){
		MessageBox(_T("请设置要评价的人数或建立指标体系"));
		return;
	}
	pDoc->quotaParamcount++;
	if(pDoc->quotaParamcount<pDoc->CinParamPersonNum)
	{

		DialogSetParam *dialogSetParam = new DialogSetParam(pDoc,pDoc->quotaParamcount);
		dialogSetParam->Create(IDD_SETPARAM, &m_wndTabs);
		CString strTabName;
		strTabName.Format(_T("%d.设置指标阈值"),pDoc->quotaParamcount+1);
		m_wndTabs.AddTab(dialogSetParam, strTabName, pDoc->quotaParamcount, TRUE);
	}else{
		
		//MessageBox(_T(""));
	}
}

//设置指标权重
void CHelmetFCEMView::OnButton4()
{
	// TODO: 在此添加命令处理程序代码
	CHelmetFCEMDoc *pDoc = GetDocument();
	//int peopleNum = transTool.toInt(pDoc->peopleNum);
	if (pDoc->fistsetQuotaTag&&pDoc->sencondsetQuotaTag) {
	
		dialogSetQuotaWeight = new DialogSetQuotaWeight(pDoc, setQuotaWeightCount++);
		if (!dialogSetQuotaWeight->Create(IDD_SETWEIGHT))
		{
			TRACE0("未能创建对话框！");
			return;
		}
		dialogSetQuotaWeight->ShowWindow(SW_SHOW);
	}
	else {
		MessageBox(_T("请先设置一级指标和二级指标！"));
		return;
	}
	
}


int CHelmetFCEMView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CRect rectDummy;
	rectDummy.SetRectEmpty();
	GetClientRect(rectDummy);
	//rectDummy.bottom = 100;
	

	/*if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, 2, CMFCBaseTabCtrl::LOCATION_TOP))
	{
		TRACE0("未能创建Tab控件！");
		return -1;
	}*/
	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_3D_ONENOTE, rectDummy, this, 3000, CMFCTabCtrl::LOCATION_TOP))
	{
		return FALSE;
	}
	
	
	CArray<COLORREF, COLORREF> arColors;
	arColors.Add(RGB(121, 210, 231));
	arColors.Add(RGB(190, 218, 153));
	arColors.Add(RGB(255, 170, 100));
	m_wndTabs.EnableAutoColor(TRUE);
	m_wndTabs.SetAutoColors(arColors);

	//// 6.设置CMFCTabCtrl表头是否可以拖拽：
	m_wndTabs.EnableTabSwap(TRUE);//可以拖拽
	m_wndTabs.EnableActiveTabCloseButton();
	m_wndTabs.RecalcLayout ();
	m_wndTabs.RedrawWindow ();
	// 设置标签宽度
	m_wndTabs.SetTabMaxWidth(300);
	m_wndTabs.AutoSizeWindow();
	//ShowWindow(SW_MAXIMIZE);

	
	return 0;
}


void CHelmetFCEMView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	m_wndTabs.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}


//void CHelmetFCEMView::OnButtonshowtree()
//{
//	// TODO: 在此添加命令处理程序代码
//	pDoc=GetDocument();
//	pMF = (CMainFrame*)AfxGetMainWnd();
//	pMF->m_wndClassView.showTree(pDoc);
//}


//显示指标树
void CHelmetFCEMView::OnButton9()
{
	// TODO: 在此添加命令处理程序代码
	pDoc=GetDocument();
	pMF = (CMainFrame*)AfxGetMainWnd();
	pMF->pTabbedBar->ShowPane(TRUE,TRUE,TRUE);
	pMF->m_wndClassView.showTree(pDoc);
}

//设置一级指标
void CHelmetFCEMView::OnButtonfirst()
{
	// TODO: 在此添加命令处理程序代码
	pDoc = GetDocument();

	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	dialogFirstQuota = new DialogFirstQuota(pFrame,pDoc);
	if (!dialogFirstQuota->Create(IDD_FIRSTQUOTA))
	{
		TRACE0("未能创建对话框！");
	}
	dialogFirstQuota->ShowWindow(SW_SHOW);
}


void CHelmetFCEMView::OnUpdateEdit2(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}

//设置评价人数
void CHelmetFCEMView::OnEdit2()
{
	// TODO: 在此添加命令处理程序代码
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMFCRibbonEdit *edit = (CMFCRibbonEdit *)(pFrame->m_wndRibbonBar).FindByID(ID_EDIT2);
	ASSERT_VALID(edit);
	CString cstr = edit->GetEditText();
	int temp = transTool.toInt(cstr);
	if(temp<1||temp>30)
	{
		MessageBox(_T("参数输入错误！"));
		edit->SetEditText(_T(""));
	}
	else {
		pDoc = GetDocument();
		//	pDoc->percent= temp;
		//WritePrivateProfileString(_T("mainConfig"), _T("percent"), cstr, _T("./config//config.ini"));
		pDoc->CinParamPersonNum=temp;
		pDoc->setUserCinQuotaNumTag=true;
		int nn=pDoc->CinParamPersonNum;
		/*userCinQuota=new UserCinQuota*[temp];
		for (int i=0;i<temp;i++)
		{
			UserCinQuota[i]=new UserCinQuota[pDoc->quotaNum];
			for (int j=0;j<pDoc->quotaNum;j++)
			{
				((UserCinQuota*)userCinQuota[i])[j]->id=pDoc->finalQuota[i].id;
				((UserCinQuota*)userCinQuota[i])[j]->parentId=pDoc->finalQuota[i].parentId;
			}
		}*/
		pDoc->userCinQuotaResult=new double[temp];
		pDoc->setUserCinQuotaNumTag=true;
		MessageBox(_T("评价人数设置成功!"));
		(pFrame->m_wndOutput).alertMsg("评价人数设置成功!");
	}
}


//使用算子1
void CHelmetFCEMView::OnButton5()
{
	// TODO: 在此添加命令处理程序代码
	pDoc = GetDocument();
	pDoc->useWhatArithmeticTag=1;
}

//使用算子2
void CHelmetFCEMView::OnButton6()
{
	// TODO: 在此添加命令处理程序代码
	pDoc = GetDocument();
	pDoc->useWhatArithmeticTag=2;
}
	//使用算子3
	void CHelmetFCEMView::OnButton7()
	{
		// TODO: 在此添加命令处理程序代码
		pDoc = GetDocument();
		pDoc->useWhatArithmeticTag=3;
	}

	//使用算子4
	void CHelmetFCEMView::OnButton8()
	{
		// TODO: 在此添加命令处理程序代码
		pDoc = GetDocument();
		pDoc->useWhatArithmeticTag=4;
	}

	//显示扇形和柱状图和折线图参数
	void CHelmetFCEMView::OnButtonshowpic()
	{
		// TODO: 在此添加命令处理程序代码
		pDoc=GetDocument();
	/*	dialogShowPicture=new DialogShowPicture(pDoc);
		if (!dialogShowPicture->Create(IDD_SHOW))
		{
			TRACE0("未能创建对话框！");
		}
		dialogShowPicture->ShowWindow(SW_SHOW);*/
		if(pDoc->canPicture){
			dialogShowPicture=new DialogShowPicture(pDoc);
			if (!dialogShowPicture->Create(IDD_SHOW))
			{
				TRACE0("未能创建对话框！");
			}
			dialogShowPicture->ShowWindow(SW_SHOW);
		}else{
			MessageBox(_T("请先设置完评价参数"));
		}
	}

	//打印权重
	void CHelmetFCEMView::OnOutpdf()
	{
		// TODO: 在此添加命令处理程序代码
		remove("D:\\指标权重报告单.pdf");
	pDoc = GetDocument();
	if(!pDoc->setQuotaWeightTag){
		MessageBox(_T("请先设置权重"));
		return;
	}
	CString strTemp;
	PDF         *p = NULL;
	int         i = 0, j = 0, Left = 50, Top = 800, Right = 545;
	int         Font_E = 0, Font_CS = 0, Font_CS2 = 0, TextFlow = 0;
	char        TextUnicode[] = "＼x80＼x7B＼x53＼x4F＼x2D＼x4E＼x87＼x65";
	char        TextCpArray36[] = "＼xBC＼xF2＼xCC＼xE5＼xD6＼xD0＼xCE＼xC4";
	/* create a new PDFlib object */
	if ((p = PDF_new()) == (PDF *) 0)
	{
		MessageBox(_T("Couldn’t create PDFlib object (out of memory)!＼n"));
		return;
	}
	PDF_TRY(p) {
		PDF_set_parameter(p, "license", "X600605-009100-4E7661-329E0C");//去除水印。将注册号写入。
		PDF_set_parameter(p,"hypertextencoding","host");
		if (PDF_begin_document(p, "D:\\指标权重报告单.pdf", 0, "") == -1)
		{
			strTemp.Format(_T("Error: %s＼n"), PDF_get_errmsg(p));
			MessageBox(strTemp);

		}
		//PDF_set_info(p, "Creator", "pdflib_cs3.c");
		//PDF_set_info(p, "Author", "myi@pdflib.com");
		//PDF_set_info(p, "Title", "the report of grade");
		/* Start a new page. */
		PDF_begin_page_ext(p, a4_width, a4_height, "");
		Font_E = PDF_load_font(p, "Helvetica-Bold", 0, "winansi", "");
		Font_CS = PDF_load_font(p, "STSong-Light", 0, "UniGB-UCS2-H", "");
		Font_CS2 = PDF_load_font(p, "STSong-Light", 0, "GB-EUC-H", "");
		PDF_setfont(p, Font_CS2, 22);
		PDF_set_text_pos(p, Left+200, Top);
		PDF_show(p, "指标权重报告单");
		Top-=30;
		PDF_setfont(p, Font_CS, 10);	
	for(int i=0;i<pDoc->quotaNum;i++){
		//if(pDoc->finalQuota[i].childNum==0)
			//MessageBox(transTool.toCString(userCinQuotaCopy[i].data) );
		}
	/*	for(int i=0;i<pDoc->quotaNum;i++)
		{
			PDF_set_text_pos(p, Left, Top);
				if(i%3==0){
							Top-=20;
						}
				if(pDoc->finalQuota[i].childNum==0)
					strTemp.Format(_T("%s:%s"),pDoc->quotaName[i],transTool.toCString(userCinQuotaCopy[i].data));
					PDF_continue_text2(p,(LPSTR)(LPCTSTR)strTemp,strTemp.GetLength()*2);
					Left+=50;
		
		}*/
	Left=5;
	int firstQuotaCount=0;
		for (int i=0;i<pDoc->quotaNum;i++)
		{
			if(pDoc->finalQuota[i].treeRank==1&&pDoc->finalQuota[i].childNum!=0){
				CString cstrtt;
				firstQuotaCount++;
				strTemp.Format(_T("%d.%s%.2f"),firstQuotaCount,pDoc->quotaName[i],pDoc->finalQuota[i].weight);
				Top-=30;
				Left=5;
				PDF_set_text_pos(p, Left, Top);
				PDF_continue_text2(p,(LPSTR)(LPCTSTR)strTemp,strTemp.GetLength()*2);
				int count=0;
				for (int j=0;j<pDoc->quotaNum;j++)
				{
					
					if (pDoc->finalQuota[i].id==pDoc->finalQuota[j].parentId&&pDoc->finalQuota[j].parentId!=-1)
					{
						if(count%3==0)
						{
							Top-=20;
							Left=30;
						}
						count++;
						PDF_set_text_pos(p, Left, Top);
						strTemp.Format(_T("%d.%s: %.2f"),count,pDoc->quotaName[j],pDoc->finalQuota[j].weight);
						PDF_continue_text2(p,(LPSTR)(LPCTSTR)strTemp,strTemp.GetLength()*2);
						Left+=150;
					}
				}
			}
			else if(pDoc->finalQuota[i].treeRank==1&&pDoc->finalQuota[i].childNum==0){
				Top-=30;
				Left=5;
				firstQuotaCount++;
				strTemp.Format(_T("%d.%s: %.2f"),firstQuotaCount,pDoc->quotaName[i],pDoc->finalQuota[i].weight);
				PDF_set_text_pos(p, Left, Top);
				PDF_continue_text2(p,(LPSTR)(LPCTSTR)strTemp,strTemp.GetLength()*2);
			}
			
			
		}
		
		
		
		/*int len=details.GetLength();
		for (int i=0;i<len;i=i+50)
		{
			strTemp=details.Left(50);
			details.Delete(0,50);
			PDF_continue_text2(p,(LPSTR)(LPCTSTR)strTemp,strTemp.GetLength()*2);
			Top-=30;
		}*/
		PDF_end_page_ext(p, "");
		PDF_end_document(p, "");
	}
	PDF_CATCH(p) {

		PDF_get_errnum(p), PDF_get_apiname(p), PDF_get_errmsg(p);
		PDF_delete(p);

	}
	PDF_delete(p);
	MessageBox(_T("打印完毕！PDF成绩单已保存到D盘下！"));
	ShellExecute(NULL,_T("open"),_T("D:\\指标权重报告单.pdf"),NULL,NULL,SW_SHOW);
	return;
	}



	//设置二级指标
	void CHelmetFCEMView::OnSetsecond()
	{
		// TODO: 在此添加命令处理程序代码
		CHelmetFCEMDoc *pDoc = GetDocument();
		//int peopleNum = transTool.toInt(pDoc->peopleNum);
		CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
		if (!pDoc->fistsetQuotaTag) {
			MessageBox(_T("请先设置一级指标！"));
			return;
		}
		if(pDoc->sencondsetQuotaTag){
			MessageBox(_T("已经设置好二级指标！"));
			return;
		}
		dialog_setSecondQuota = new Dialog_setSecondQuota(pFrame,pDoc);
		if (!dialog_setSecondQuota->Create(IDD_SECONDQUOTA))
		{
			TRACE0("未能创建对话框！");
			return;
		}
		dialog_setSecondQuota->ShowWindow(SW_SHOW);
	}



	//柱状图

	void CHelmetFCEMView::OnButton11()
	{
		// TODO: 在此添加命令处理程序代码
		pDoc=GetDocument();
		pDoc->useWhatPicture=1;
	}

	//饼图

	void CHelmetFCEMView::OnButton12()
	{
		// TODO: 在此添加命令处理程序代码
		pDoc=GetDocument();
		pDoc->useWhatPicture=2;
	}

	//打开计算器
	void CHelmetFCEMView::OnButton13()
	{
		// TODO: 在此添加命令处理程序代码
		ShellExecute(this->m_hWnd, _T("open"),_T("calc.exe"), _T(""), _T(""), SW_SHOW);

	}


	void CHelmetFCEMView::OnUpdateEdit3(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		pCmdUI->Enable(TRUE);
	}

//添加指标
	void CHelmetFCEMView::OnEdit3()
	{
		// TODO: 在此添加命令处理程序代码
		CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
		CMFCRibbonEdit *edit = (CMFCRibbonEdit *)(pFrame->m_wndRibbonBar).FindByID(ID_EDIT3);
		ASSERT_VALID(edit);
		CString cstr = edit->GetEditText();
		pDoc = GetDocument();
		pDoc->quotaNum++;
		if (cstr.IsEmpty()) {
			MessageBox(_T("请输入正确的指标名！"));

		}
		else {
			WritePrivateProfileString(_T("quotaName"), transTool.toCString(pDoc->quotaNum-1), cstr, _T("./config//config.ini"));
			WritePrivateProfileString(_T("mainConfig"), _T("setQuotaWeightTag"), _T("0"), _T("./config//config.ini"));
			WritePrivateProfileString(_T("mainConfig"), _T("quotaNum"), transTool.toCString(pDoc->quotaNum), _T("./config//config.ini"));
			pDoc->quota = new Quota[pDoc->quotaNum];
			//	expertQuotaCinData = new Quota *[quotaNum];
			pDoc->finalQuota = new Quota[pDoc->quotaNum];
			for (int i = 0; i < pDoc->quotaNum; i++) {
				GetPrivateProfileString(_T("quotaName"), transTool.toCString(i), _T(""), (pDoc->quotaName[i]).GetBuffer(MAX_PATH), MAX_PATH, _T("./config//config.ini"));
				//设置最终的指标节点
				pDoc->quota[i].id = i;
				pDoc->quota[i].name = transTool.toString(pDoc->quotaName[i]);
				pDoc->quota[i].childNum = 0;
				pDoc->quota[i].parentId = -1;
				pDoc->quota[i].treeRank = -1;


			}
			MessageBox(_T("指标添加成功！"));
			(pFrame->m_wndOutput).alertMsg("添加成功!");
		}

	}





	void CHelmetFCEMView::OnUpdateEdit6(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		pCmdUI->Enable(TRUE);
	}

	void CHelmetFCEMView::OnUpdateEdit7(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		pCmdUI->Enable(TRUE);
	}


	void CHelmetFCEMView::OnUpdateEdit8(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
		pCmdUI->Enable(TRUE);
	}
	//优
	void CHelmetFCEMView::OnEdit6()
	{
		// TODO: 在此添加命令处理程序代码
		CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMFCRibbonEdit *edit = (CMFCRibbonEdit *)(pFrame->m_wndRibbonBar).FindByID(ID_EDIT6);
	ASSERT_VALID(edit);
	CString cstr = edit->GetEditText();
	double temp = transTool.toDouble(cstr);
	if(temp<0.01||temp>1.00)
	{
		MessageBox(_T("参数输入错误！"));
		edit->SetEditText(_T(""));
	}
	else {
		pDoc = GetDocument();
		pDoc->you=temp;
		MessageBox(_T("设置成功!"));
		(pFrame->m_wndOutput).alertMsg("设置成功!");
	}
	}
	//良
	void CHelmetFCEMView::OnEdit7()
	{
		// TODO: 在此添加命令处理程序代码
		CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
		CMFCRibbonEdit *edit = (CMFCRibbonEdit *)(pFrame->m_wndRibbonBar).FindByID(ID_EDIT6);
		ASSERT_VALID(edit);
		CString cstr = edit->GetEditText();
		double temp = transTool.toDouble(cstr);
		if(temp<0.01||temp>1.00)
		{
			MessageBox(_T("参数输入错误！"));
			edit->SetEditText(_T(""));
		}
		else {
			pDoc = GetDocument();
			pDoc->liang=temp;
			MessageBox(_T("设置成功!"));
			(pFrame->m_wndOutput).alertMsg("设置成功!");
		}
	}

	//中
	void CHelmetFCEMView::OnEdit8()
	{
		// TODO: 在此添加命令处理程序代码
		CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
		CMFCRibbonEdit *edit = (CMFCRibbonEdit *)(pFrame->m_wndRibbonBar).FindByID(ID_EDIT6);
		ASSERT_VALID(edit);
		CString cstr = edit->GetEditText();
		double temp = transTool.toDouble(cstr);
		if(temp<0.01||temp>1.00)
		{
			MessageBox(_T("参数输入错误！"));
			edit->SetEditText(_T(""));
		}
		else {
			pDoc = GetDocument();
			pDoc->zhong=temp;
			MessageBox(_T("设置成功!"));
			(pFrame->m_wndOutput).alertMsg("设置成功!");
		}
	}


