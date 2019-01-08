// DialogSetQuotaWeight.cpp : 实现文件
//

#include "stdafx.h"
#include "HelmetFCEM.h"
#include "DialogSetQuotaWeight.h"
#include "afxdialogex.h"
#include <math.h>

#define IDC_CEDIT    (0x2000) // 控件的ID号

// DialogSetQuotaWeight 对话框

IMPLEMENT_DYNAMIC(DialogSetQuotaWeight, CDialogEx)

DialogSetQuotaWeight::DialogSetQuotaWeight(CWnd* pParent /*=NULL*/)
	: CDialogEx(DialogSetQuotaWeight::IDD, pParent)
{

}
DialogSetQuotaWeight::DialogSetQuotaWeight(CHelmetFCEMDoc * p,int n) : CDialogEx(IDD_SETWEIGHT)
{
	pDoc = p;
	num = n;
}
DialogSetQuotaWeight::~DialogSetQuotaWeight()
{
}

void DialogSetQuotaWeight::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogSetQuotaWeight, CDialogEx)
	ON_BN_CLICKED(IDOK, &DialogSetQuotaWeight::OnBnClickedOk)
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// DialogSetQuotaWeight 消息处理程序


BOOL DialogSetQuotaWeight::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
		expertCinquotaWeight = new Quota[pDoc->quotaNum];
	for (int i = 0; i < pDoc->quotaNum; i++) {
		expertCinquotaWeight[i].childNum = pDoc->quota[i].childNum;
		expertCinquotaWeight[i].id = pDoc->quota[i].id;
		expertCinquotaWeight[i].name = pDoc->quota[i].name;
		expertCinquotaWeight[i].parentId = pDoc->quota[i].parentId;
		expertCinquotaWeight[i].treeRank = pDoc->quota[i].treeRank;
		expertCinquotaWeight[i].weight = pDoc->quota[i].weight;
	}
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
	int firstQuotacount=0;
	for (int i = 0; i < pDoc->quotaNum; i++)
	{
		if (pDoc->quota[i].treeRank == 1&&pDoc->quota[i].childNum != 0) {
			childNum = 0;
			rect.left = 10;
			rect.right = rect.left + MAX_STATIC_WIDTH;
			rect.bottom = rect.top + HEIGHT;
			pStatic = new CStatic;
			ASSERT(NULL != pStatic);
			CString cstr;
			firstQuotacount++;
			cstr.Format(_T("%d."), firstQuotacount);
			CString str=cstr;
			cstr.Format(_T("%s%s"), str, pDoc->quotaName[i]);
			pStatic->Create(cstr, WS_CHILD | WS_VISIBLE, rect, this);
			rect.left = rect.right + X_GAP;
			rect.right = rect.left + WIDTH;
			strText = pDoc->quotaName[i];
			pEdit = new CEdit;
			ASSERT(NULL != pEdit);
			pEdit->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rect, this, IDC_CEDIT + pDoc->quota[i].id);
			rect.top = rect.bottom + Y_GAP;
			rect.right = 20;
			rect.left = 50;
			for (int j = 0; j < pDoc->quotaNum; j++) {
				if (pDoc->quota[i].id == pDoc->quota[j].parentId) {
					
					if (childNum%3==0)
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
					cstr.Format(_T("%d.%s"),  childNum,pDoc->quotaName[j]);
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
			
			
		}else if(pDoc->quota[i].treeRank == 1&&pDoc->quota[i].childNum == 0){
			rect.left = 10;
			rect.right = rect.left + MAX_STATIC_WIDTH;
			rect.bottom = rect.top + HEIGHT;
			pStatic = new CStatic;
			ASSERT(NULL != pStatic);
			CString cstr;
			firstQuotacount++;
			cstr.Format(_T("%d.%s"), firstQuotacount, pDoc->quotaName[i]);
			pStatic->Create(cstr, WS_CHILD | WS_VISIBLE, rect, this);

			rect.left = rect.right + X_GAP;
			rect.right = rect.left + WIDTH;
			CString CStemp;
			
			strText.Format(_T("%d."), firstQuotacount);
			CStemp = pDoc->quotaName[i];
			CString str=strText;
			strText.Format(_T("%s%s"), strText,CStemp);
			pEdit = new CEdit;
			ASSERT(NULL != pEdit);
			pEdit->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rect, this, IDC_CEDIT + pDoc->quota[i].id);
			rect.top = rect.bottom + Y_GAP + Y_GAP;

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


void DialogSetQuotaWeight::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	int zhibiaoNum = transTool.toInt(pDoc->quotaNum);
	//int peopleNum = tranTool.toInt(pDoc->peopleNum);
	CString cstr;
	CString msg;
	bool tag = false;
	for (int i = 0; i < zhibiaoNum; i++) {
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_CEDIT + i);
		pEdit->GetWindowText(cstr);
		//MessageBox(cstr);
		double param = transTool.toDouble(cstr);
		//double paramTwo = mathRound(param,2);
		if ((param - 0.00) < 0.001 || (param - 1.00) > 0.001) {
			MessageBox(_T("参数输入不正确！"));
			return;
		}
		else {
			expertCinquotaWeight[i].weight = param;
		}


	}
	double count = 0.0;
	double secondquotaweightcount = 0;
	for (int i = 0; i < pDoc->quotaNum; i++) {
		secondquotaweightcount = 0;
		if (expertCinquotaWeight[i].treeRank == 1&&expertCinquotaWeight[i].childNum!=0) {

			for (int j = 0; j < pDoc->quotaNum; j++) {
				if (expertCinquotaWeight[i].id == expertCinquotaWeight[j].parentId) {
					secondquotaweightcount += expertCinquotaWeight[j].weight;
				}
			}
			if (abs(secondquotaweightcount - 1.0) < 0.01) {
				for (int j = 0; j < pDoc->quotaNum; j++) {
					if (expertCinquotaWeight[i].id == expertCinquotaWeight[j].parentId) {
						pDoc->quota[expertCinquotaWeight[j].id].weight = expertCinquotaWeight[j].weight;
					}
				}

			}
			else {
				CString temp = pDoc->quotaName[i];
				temp.Format(_T("%s%s"),temp,_T("下的二级指标和不为1！请重新输入"));
				MessageBox(temp);
				return;
			}
		}
		if (expertCinquotaWeight[i].treeRank == 1) {
			count += expertCinquotaWeight[i].weight;
		}

	}
	if (abs(count - 1.0) < 0.001) {
		for (int j = 0; j < pDoc->quotaNum; j++) {
			if (pDoc->quota[j].treeRank==1) {
				pDoc->quota[j].weight = expertCinquotaWeight[j].weight;
			}
		}
		for (int i = 0; i < pDoc->quotaNum; i++) {
			//MessageBox(transTool.toCString(pDoc->quota[i].weight));
		}
		pDoc->userCanCinParamNum=0;
		//计算可输入的指标数
		for (int i = 0; i < pDoc->quotaNum; i++) {
			if ((pDoc->quota[i].treeRank == 1 && pDoc->quota[i].childNum == 0) || pDoc->quota[i].treeRank == 2) {
				pDoc->userCanCinParamNum++;
			}
		}
		CStdioFile File;
		File.Open(_T(".//config//data.txt"), CFile::modeCreate || CFile::modeWrite);
		for (int i = 0; i < pDoc->quotaNum; i++) {
			CString strText = transTool.toCString(pDoc->quota[i].id);
			File.WriteString(strText);
			File.WriteString(_T("#"));
			strText = transTool.toCString(pDoc->quota[i].parentId);
			File.WriteString(strText);
			File.WriteString(_T("#"));
			strText.Format(_T("%.2f"), pDoc->quota[i].weight);
			File.WriteString(strText);
			File.WriteString(_T("#"));
			strText = transTool.toCString(pDoc->quota[i].treeRank);
			File.WriteString(strText);
			File.WriteString(_T("#"));
			strText = transTool.toCString(pDoc->quota[i].childNum);
			File.WriteString(strText);
			File.WriteString(_T("\n"));
			pDoc->finalQuota[i].weight = pDoc->quota[i].weight;
			pDoc->finalQuota[i].id = pDoc->quota[i].id;
			pDoc->finalQuota[i].parentId = pDoc->quota[i].parentId;
			pDoc->finalQuota[i].childNum = pDoc->quota[i].childNum;
			pDoc->finalQuota[i].treeRank = pDoc->quota[i].treeRank;
		}
		File.Close();
		WritePrivateProfileString(_T("mainConfig"), _T("setQuotaWeightTag"), _T("1"), _T("./config//config.ini"));
		MessageBox(_T("指标权重设置成功!"));
		pDoc->setQuotaWeightTag = true;
		OnOK();
	}
	else {
		MessageBox(_T("一级指标和不唯一！"));
		return;
	}

	//if (i == zhibiaoNum) {
	//	msg.Format(_T("第%d个设置成功"), num + 1);

	//	MessageBox(msg);
	//}
	//if (num + 1 == peopleNum) {
	//	int cout = 0;
	//	int Notag[50];
	//	for (int i = 0; i < peopleNum; i++) {
	//		if (pDoc->setQuotaWeightTag[i]==false) {
	//			Notag[cout++] = i + 1;
	//		}
	//	}
	//	if (cout != 0) {
	//		string temp_string = "还有第";
	//		for (int i = 0; i < cout; i++) {
	//			if (i == cout - 1)
	//			{
	//				temp_string.append(tranTool.toString(Notag[i]));
	//			}
	//			else {
	//				temp_string.append(tranTool.toString(Notag[i]));
	//				temp_string.append(",");
	//			}
	//		}
	//		temp_string.append("个没有设置,请先设置完");
	//		MessageBox(tranTool.toCString(temp_string));
	//	}
	//	else {
	//		int sum;
	//		for (int j = 0; j < zhibiaoNum; j++) {
	//			sum = 0;
	//			for (int i = 0; i < peopleNum; i++) {
	//				// sum = sum+tranTool.toInt(pDoc->zhibiaoWeight[i][j]);
	//			}
	//			double weight = sum / (peopleNum*100*1.0);
	//			CString csf;
	//			csf.Format(_T("%.3lf"), weight);
	//			WritePrivateProfileString(_T("zhibiaoWeight"), tranTool.toCString(j), csf, _T("./config//config.ini"));
	//		}
	//		MessageBox(_T("指标权重设置成功"));
	//	}


	//}
}
void DialogSetQuotaWeight::ScrollClient(int nBar, int nPos)    
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
int DialogSetQuotaWeight::GetScrollPos(int nBar, UINT nSBCode)    
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
void DialogSetQuotaWeight::VScrool(int nBar, UINT nSBCode)    
{    
	const int scrollPos = GetScrollPos(nBar,nSBCode);    

	if(scrollPos == -1)    
		return;    

	SetScrollPos(nBar, scrollPos, TRUE);    
	ScrollClient(nBar, scrollPos);    
}  

void DialogSetQuotaWeight::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	VScrool(SB_VERT,nSBCode);
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}
