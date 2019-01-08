// DialogSetParam.cpp : 实现文件
//

#include "stdafx.h"
#include "HelmetFCEM.h"
#include "DialogSetParam.h"
#include "afxdialogex.h"
#include "pdflib.h"
#pragma comment(lib, "PDFLib.lib")

// DialogSetParam 对话框
#define IDC_CEDIT    (0x2000) // 控件的ID号
IMPLEMENT_DYNAMIC(DialogSetParam, CDialogEx)

DialogSetParam::DialogSetParam(CWnd* pParent /*=NULL*/)
	: CDialogEx(DialogSetParam::IDD, pParent)
{

}
DialogSetParam::DialogSetParam(CHelmetFCEMDoc * p,int n) : CDialogEx(IDD_SETPARAM)
{
	pDoc = p;
	num=n;
	userCinQuota = new UserCinQuota[pDoc->quotaNum];
	userCinQuotaCopy=new UserCinQuota[pDoc->quotaNum];
	for (int i = 0; i < pDoc->quotaNum;i++) {
		userCinQuota[i].id = pDoc->finalQuota[i].id;
		userCinQuota[i].parentId = pDoc->finalQuota[i].parentId;
		userCinQuotaCopy[i].id = pDoc->finalQuota[i].id;
		userCinQuotaCopy[i].parentId = pDoc->finalQuota[i].parentId;
	}
}
DialogSetParam::~DialogSetParam()
{
}

void DialogSetParam::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogSetParam, CDialogEx)
	ON_BN_CLICKED(IDOK, &DialogSetParam::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &DialogSetParam::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &DialogSetParam::OnBnClickedButton2)
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// DialogSetParam 消息处理程序


void DialogSetParam::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


BOOL DialogSetParam::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	commit=false;
	// TODO:  在此添加额外的初始化
	CEdit* pEdit = NULL;
	CStatic *pStatic = NULL;
	CString strText(_T(""));
	/*pStatic = new CStatic;
	pStatic->Create(_T("hello world"), WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(50, 80, 150, 150), this);*/
	CONST UINT WIDTH = 50; // 定义CheckBox的宽度
	CONST UINT HEIGHT = 20; // 定义CheckBox的高度
	CONST UINT X_GAP = 30; // 定义CheckBox之间的水平间隔距离
	CONST UINT Y_GAP = 20; // 定义CheckBox之间的垂直间隔距离
	CONST UINT MAX_STATIC_WIDTH = 250;//静态文本框宽度
	CRect rect;
	rect.SetRectEmpty();

	rect.top = 100;
	int childNum = 0;
	int firstQuotaCount=0;
	for (int i = 0; i < pDoc->quotaNum; ++i)
	{
		if (pDoc->finalQuota[i].treeRank ==1&&pDoc->finalQuota[i].childNum != 0) {
			childNum = 0;
			rect.left = 10;
			rect.right = rect.left + MAX_STATIC_WIDTH;
			rect.bottom = rect.top + HEIGHT;
			pStatic = new CStatic;
			ASSERT(NULL != pStatic);
			CString cstr;
			firstQuotaCount++;
			cstr.Format(_T("%d.%s"), firstQuotaCount, pDoc->quotaName[i]);
			pStatic->Create(cstr, WS_CHILD | WS_VISIBLE, rect, this);
			rect.top = rect.bottom + Y_GAP;
			rect.right = 20;
			rect.left = 50;
			for (int j = 0; j < pDoc->quotaNum; j++) {
				if (pDoc->finalQuota[i].id == pDoc->finalQuota[j].parentId) {
					if (childNum % 3 == 0)
					{
						rect.left = 50;
						rect.top = rect.bottom + Y_GAP;
					}
					else
					{
						rect.left = rect.right + X_GAP;
					}
					childNum++;
					rect.right = rect.left + MAX_STATIC_WIDTH;
					rect.bottom = rect.top + HEIGHT;
					pStatic = new CStatic;
					ASSERT(NULL != pStatic);
					CString cstr;
					cstr.Format(_T("%s"), pDoc->quotaName[j]);
					pStatic->Create(cstr, WS_CHILD | WS_VISIBLE , rect, this);

					rect.left = rect.right + X_GAP;
					rect.right = rect.left + WIDTH;
					strText = pDoc->quotaName[i];
					pEdit = new CEdit;
					ASSERT(NULL != pEdit);
					pEdit->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rect, this, IDC_CEDIT + pDoc->quota[j].id);
				}
			}
			rect.top = rect.bottom + Y_GAP + Y_GAP;
			
		}else if(pDoc->finalQuota[i].treeRank ==1&&pDoc->finalQuota[i].childNum == 0){
				rect.top = rect.bottom + Y_GAP + Y_GAP;
				rect.left = 10;
				rect.right = rect.left + MAX_STATIC_WIDTH;
				rect.bottom = rect.top + HEIGHT;
				pStatic = new CStatic;
				ASSERT(NULL != pStatic);
				CString cstr;
				firstQuotaCount++;
				cstr.Format(_T("%d.%s"), firstQuotaCount, pDoc->quotaName[i]);
				pStatic->Create(cstr, WS_CHILD | WS_VISIBLE , rect, this);

				rect.left = rect.right + X_GAP;
				rect.right = rect.left + WIDTH;
				CString CStemp;
				strText.Format(_T("%d."), firstQuotaCount);
				CStemp = pDoc->quotaName[i];
				cstr=strText;
				strText.Format(_T("%s%s"), cstr, CStemp);
				pEdit = new CEdit;
				ASSERT(NULL != pEdit);
				pEdit->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rect, this, IDC_CEDIT + pDoc->quota[i].id);
				
		}

	}
	ShowWindow(SW_NORMAL);
	CRect rtDesk;
	CRect rtDlg;
	::GetWindowRect(::GetDesktopWindow(),&rtDesk);
	GetWindowRect(&rtDlg);
	int iXpos=rtDesk.Width()/2-rtDlg.Width()/2;
	int iYpos=rtDesk.Height()/2-rtDlg.Height()/2;
	SetWindowPos(NULL,iXpos,iYpos,0,0,SWP_NOOWNERZORDER|SWP_NOSIZE|SWP_NOZORDER);

	//////////////////////////////////////////////////////////////////////////
	//竖直滚动
	CRect rc;    
	GetClientRect(&rc);    

	const SIZE sz = { rc.right - rc.left, rc.bottom - rc.top };    

	SCROLLINFO si;    
	si.cbSize = sizeof(SCROLLINFO);    
	si.fMask = SIF_PAGE | SIF_POS | SIF_RANGE;    
	si.nPos = si.nMin = 1;    

	si.nMax = sz.cy*m_page;    
	si.nPage = sz.cy;    
	SetScrollInfo(SB_VERT, &si, FALSE);  //此函数将产生一个垂直滚动条  
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

//打印pdf
void DialogSetParam::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (commit)
	{
		remove("D:\\报告单.pdf");
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
		if (PDF_begin_document(p, "D:\\报告单.pdf", 0, "") == -1)
		{
			strTemp.Format(_T("Error: %s＼n"), PDF_get_errmsg(p));
			MessageBox(strTemp);

		}
		PDF_set_info(p, "Creator", "pdflib_cs3.c");
		PDF_set_info(p, "Author", "myi@pdflib.com");
		PDF_set_info(p, "Title", "the report of grade");
		/* Start a new page. */
		PDF_begin_page_ext(p, a4_width, a4_height, "");
		Font_E = PDF_load_font(p, "Helvetica-Bold", 0, "winansi", "");
		Font_CS = PDF_load_font(p, "STSong-Light", 0, "UniGB-UCS2-H", "");
		Font_CS2 = PDF_load_font(p, "STSong-Light", 0, "GB-EUC-H", "");
		PDF_setfont(p, Font_CS2, 22);
		PDF_set_text_pos(p, Left+200, Top);
		PDF_show(p, "报告单");
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
				 firstQuotaCount++;
				strTemp.Format(_T("%d.%s"),firstQuotaCount,pDoc->quotaName[i]);
				Top-=30;
				Left=5;
				PDF_set_text_pos(p, Left, Top);
				PDF_continue_text2(p,(LPSTR)(LPCTSTR)strTemp,strTemp.GetLength()*2);
				int count=0;
				for (int j=0;j<pDoc->quotaNum;j++)
				{
					
					if (pDoc->finalQuota[i].id==userCinQuotaCopy[j].parentId&&userCinQuotaCopy[j].parentId!=-1)
					{
						if(count%3==0)
						{
							Top-=20;
							Left=25;
						}
						count++;
						PDF_set_text_pos(p, Left, Top);
						strTemp.Format(_T("%d.%s: %.2f"),count,pDoc->quotaName[j],userCinQuotaCopy[j].data);
						PDF_continue_text2(p,(LPSTR)(LPCTSTR)strTemp,strTemp.GetLength()*2);
						Left+=150;
					}
				}
			}
			else if(pDoc->finalQuota[i].treeRank==1&&pDoc->finalQuota[i].childNum==0){
				Top-=25;
				Left=5;
				firstQuotaCount++;
				strTemp.Format(_T("%d.%s: %.2f"),firstQuotaCount,pDoc->quotaName[i],userCinQuotaCopy[i].data);
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
	ShellExecute(NULL,_T("open"),_T("D:\\报告单.pdf"),NULL,NULL,SW_SHOW);
	return;
	}else{
		MessageBox(_T("请先提交"));
}
}

//提交
void DialogSetParam::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int zhibiaoNum = transTool.toInt(pDoc->quotaNum);
	//int peopleNum = tranTool.toInt(pDoc->peopleNum);
	CString cstr;
	CString msg;
	bool tag = false;
	int canCinQuotaNumCount=0;
	for (int i = 0; i < zhibiaoNum; i++) {
		if (pDoc->finalQuota[i].treeRank == 2 || (pDoc->finalQuota[i].childNum == 0 && pDoc->finalQuota[i].treeRank == 1)) {
			CEdit* pEdit = (CEdit*)GetDlgItem(IDC_CEDIT + i);
			pEdit->GetWindowText(cstr);
			double param = transTool.toDouble(cstr);
			if (param-0.00 < 0.001 || param-1> 0.001) {
				MessageBox(_T("阈值输入不正确！"));
				return;
			}
			else {
				for (int j = 0; j < pDoc->quotaNum; j++) {
					if (userCinQuota[j].id == pDoc->finalQuota[i].id) {
						userCinQuota[j].data = param;
					}
				}
			}
		}

	}
	for (int i = 0; i < pDoc->quotaNum;i++) {
		userCinQuotaCopy[i].data= userCinQuota[i].data;
	}
	double result=0;
	switch (pDoc->useWhatArithmeticTag)
	{
	case 1: {result = oj(); break; }
	case 2: {result = aj(); break; }
	case 3: {result = ov(); break; }
	case 4: {result = av(); break; }
	default: {MessageBox(_T("请先设置要使用的算子")); return;}

	}
	pDoc->userCinQuotaResult[num]=result;
	commit=true;
	if (num==pDoc->CinParamPersonNum-1)
	{
		pDoc->canPicture=true;
	}
	CString tempcs;
	CString grade;
	if (result>=pDoc->you)
	{
		grade=_T("优");
	}else if (result>=pDoc->liang)
	{
		grade=_T("良");
	}else if (result>=pDoc->zhong)
	{
		grade=_T("中");
	}else
	{
		grade=_T("差");
	}
	tempcs.Format(_T("第%d个已提交结果为%.2f\n评价等级: %s"),num+1,result,grade);
	MessageBox(tempcs);
}

//主因素突出型M(∧,∨)正确
double DialogSetParam::av()
{

	double secondRank = 0;
	double firstRank = 0;
	for (int i = 0; i < pDoc->quotaNum; i++) {
		secondRank = 0;
		if (pDoc->finalQuota[i].treeRank == 1 && pDoc->finalQuota[i].childNum != 0) {
			for (int j = 0; j < pDoc->quotaNum; j++) {
				if (pDoc->finalQuota[i].id == userCinQuota[j].parentId&&userCinQuota[j].parentId != -1) {
					if (pDoc->finalQuota[j].weight - userCinQuota[j].data > 0.001) {
						userCinQuota[j].data = userCinQuota[j].data;
					}
					else {
						userCinQuota[j].data = pDoc->finalQuota[j].weight;
					}
					if (userCinQuota[j].data - secondRank > 0.001) {
						secondRank = userCinQuota[j].data;
					}
				}
			}
			/*for (int m = 0; m < pDoc->quotaNum; m++) {
				if (pDoc->finalQuota[i].id == userCinQuota[m].parentId) {
					if (secondRank-userCinQuota[m].data >0.001 ) {
						secondRank = userCinQuota[m].data;
					}
				}
			}*/
			userCinQuota[i].data = secondRank;
		}
	}
	for (int n = 0; n < pDoc->quotaNum; n++) {
		if (pDoc->finalQuota[n].treeRank == 1) {
			if (pDoc->finalQuota[n].weight - userCinQuota[n].data > 0.001) {
				
			}
			else {
				userCinQuota[n].data = pDoc->finalQuota[n].weight;
			}
			if (userCinQuota[n].data - firstRank > 0.001) {
				firstRank = userCinQuota[n].data;
			}
		}
	}
	return firstRank;
}


//主因素突出型M(·,∨)//正确
double DialogSetParam::ov()
{
	double secondRank = 0;
	double firstRank = 0;
	for (int i = 0; i < pDoc->quotaNum; i++) {
		secondRank = 0;
		if (pDoc->finalQuota[i].treeRank == 1 && pDoc->finalQuota[i].childNum != 0) {
			for (int j = 0; j < pDoc->quotaNum; j++) {

				if (pDoc->finalQuota[i].id == userCinQuota[j].parentId&&userCinQuota[j].parentId != -1) {
					if(pDoc->finalQuota[j].weight-userCinQuota[j].data>0.001)
					userCinQuota[j].data = pDoc->finalQuota[j].weight;
				}
			}
			for (int m = 0; m < pDoc->quotaNum; m++) {
				if (pDoc->finalQuota[i].id == userCinQuota[m].parentId) {
					if (userCinQuota[m].data - secondRank>0.001) {
						secondRank = userCinQuota[m].data;
					}
				}
			}
			userCinQuota[i].data = secondRank;
		}
	}
	for (int n = 0; n < pDoc->quotaNum; n++) {
		if (pDoc->finalQuota[n].treeRank == 1) {
			if (pDoc->finalQuota[n].weight - userCinQuota[n].data>0.001) {
				firstRank = pDoc->finalQuota[n].weight;
			}
			else {
				firstRank = userCinQuota[n].data;
			}
			
			}
	}
	return firstRank;
}

//加权平均型M(∧,+)
double DialogSetParam::aj()
{
	double secondRank = 0;
	double firstRank = 0;
	for (int i = 0; i < pDoc->quotaNum; i++) {
		secondRank = 0;
		if (pDoc->finalQuota[i].treeRank == 1 && pDoc->finalQuota[i].childNum != 0) {
			for (int j = 0; j < pDoc->quotaNum; j++) {

				if (pDoc->finalQuota[i].id == userCinQuota[j].parentId&&userCinQuota[j].parentId != -1) {
					if (userCinQuota[j].data-pDoc->finalQuota[j].weight >0.001)
						userCinQuota[j].data = pDoc->finalQuota[j].weight;
				}
			}
			for (int m = 0; m < pDoc->quotaNum; m++) {
				if (pDoc->finalQuota[i].id == userCinQuota[m].parentId) {
					secondRank += userCinQuota[m].data;
				}
			}
			if (secondRank - 1.00 > 0.001)
			{
				userCinQuota[i].data = 1;
			}
			else {
				userCinQuota[i].data = secondRank;
			}
		}
	}
	for (int n = 0; n < pDoc->quotaNum; n++) {
		if (pDoc->finalQuota[n].treeRank == 1) {
			if (pDoc->finalQuota[n].weight - userCinQuota[n].data>0.001) {
				firstRank += userCinQuota[n].data;
			}
			else {
				firstRank += pDoc->finalQuota[n].weight;
			}

		}
	}
	if (firstRank - 1.0 > 0.001) {
		firstRank = 1;
	}
	return firstRank;
}
//加权平均型M(·,+)
double DialogSetParam::oj()
{
	double secondRank = 0;
	double firstRank = 0;
	for (int i = 0; i < pDoc->quotaNum; i++) {
		secondRank = 0;
		if (pDoc->finalQuota[i].treeRank == 1 && pDoc->finalQuota[i].childNum != 0) {
			for (int j = 0; j < pDoc->quotaNum; j++) {

				if (pDoc->finalQuota[i].id == userCinQuota[j].parentId&&userCinQuota[j].parentId != -1) {
					secondRank += userCinQuota[j].data * pDoc->finalQuota[j].weight;
				}
			}
			/*for (int m = 0; m < pDoc->quotaNum; m++) {
				if (pDoc->finalQuota[i].id == userCinQuota[m].parentId) {
					secondRank += userCinQuota[m].data;
				}
			}*/
			if (secondRank - 1.00 > 0.001)
			{
				userCinQuota[i].data = 1;
			}
			else {
				userCinQuota[i].data = secondRank;
			}
		}
	}
	for (int n = 0; n < pDoc->quotaNum; n++) {
		if (pDoc->finalQuota[n].treeRank == 1) {
			firstRank += pDoc->finalQuota[n].weight *userCinQuota[n].data;
		}
	}
	if (firstRank - 1.0 > 0.001) {
		firstRank = 1;
	}
	return firstRank;
}
void DialogSetParam::ScrollClient(int nBar, int nPos)    
{    
	static int s_prevx = 1;    
	static int s_prevy = 1;    

	int cx = 0;    
	int cy = 0;    

	int& delta = cy;    
	int& prev = s_prevy;  

	delta = prev - nPos;    
	prev = nPos;    

	if(cx || cy)    
	{    
		ScrollWindow(cx, cy, NULL, NULL);    
	}    
}   
int DialogSetParam::GetScrollPos(int nBar, UINT nSBCode)    
{    
	SCROLLINFO si;    
	si.cbSize = sizeof(SCROLLINFO);    
	si.fMask = SIF_PAGE | SIF_POS | SIF_RANGE | SIF_TRACKPOS;    
	GetScrollInfo(nBar, &si);    

	const int minPos = si.nMin;    
	const int maxPos = si.nMax - (si.nPage - 1);    

	int result = -1;    

	switch(nSBCode)    
	{    
	case SB_LINEUP /*SB_LINELEFT*/:    
		result = max(si.nPos - 1, minPos);    
		break;    
	case SB_LINEDOWN /*SB_LINERIGHT*/:    
		result = min(si.nPos + 1, maxPos);    
		break;    
	case SB_PAGEUP /*SB_PAGELEFT*/:    
		result = max(si.nPos - 400, minPos);    
		break;    
	case SB_PAGEDOWN /*SB_PAGERIGHT*/:    
		result = min(si.nPos + 400, maxPos);    
		break;    
	case SB_THUMBPOSITION:    
		// do nothing     
		break;    
	case SB_THUMBTRACK:    
		result = si.nTrackPos;    
		break;    
	case SB_TOP /*SB_LEFT*/:    
		result = minPos;    
		break;    
	case SB_BOTTOM /*SB_RIGHT*/:    
		result = maxPos;    
		break;    
	case SB_ENDSCROLL:    
		// do nothing     
		break;    
	}    

	return result;    
}    
void DialogSetParam::VScrool(int nBar, UINT nSBCode)    
{    
	const int scrollPos = GetScrollPos(nBar,nSBCode);    

	if(scrollPos == -1)    
		return;    

	SetScrollPos(nBar, scrollPos, TRUE);    
	ScrollClient(nBar, scrollPos);    
}  

void DialogSetParam::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	VScrool(SB_VERT,nSBCode);
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}
