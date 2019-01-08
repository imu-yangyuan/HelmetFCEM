// DialogShowPicture.cpp : 实现文件
//

#include "stdafx.h"
#include "HelmetFCEM.h"
#include "DialogShowPicture.h"
#include "afxwin.h"
#include "afxdialogex.h"
CString s1 ("        ");
CString s2 ("                ");
CString s3 ("       ");

// DialogShowPicture 对话框

IMPLEMENT_DYNAMIC(DialogShowPicture, CDialogEx)

DialogShowPicture::DialogShowPicture(CWnd* pParent /*=NULL*/)
	: CDialogEx(DialogShowPicture::IDD, pParent)
{

}
DialogShowPicture::DialogShowPicture(CHelmetFCEMDoc *p)
	: CDialogEx(IDD_SHOW)
{
	pDoc=p;
}
DialogShowPicture::~DialogShowPicture()
{
}

void DialogShowPicture::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATICZHU, staticZhu);
	DDX_Control(pDX, IDC_STATICBING, staticBing);
}


BEGIN_MESSAGE_MAP(DialogShowPicture, CDialogEx)
	ON_BN_CLICKED(IDOK, &DialogShowPicture::OnBnClickedOk)
	ON_WM_PAINT()



	ON_STN_CLICKED(IDC_STATICBING, &DialogShowPicture::OnStnClickedStaticbing)
END_MESSAGE_MAP()


// DialogShowPicture 消息处理程序


void DialogShowPicture::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void DialogShowPicture::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()

	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	
	float ToPicResultDouble[4];
	int ToPocCount[4];
	for (int i=0;i<4;i++)
	{
		ToPicResultDouble[i]=0;
		ToPocCount[i]=0;
	}
	for (int i=0;i<pDoc->CinParamPersonNum;i++)
	{
		if (pDoc->userCinQuotaResult[i]>=pDoc->you)
		{
			ToPocCount[0]++;
		}else if (pDoc->userCinQuotaResult[i]>=pDoc->liang)
		{
			ToPocCount[1]++;
		}else if (pDoc->userCinQuotaResult[i]>=pDoc->zhong)
		{
			ToPocCount[2]++;
		}else if (pDoc->userCinQuotaResult[i]>=0)
		{
			ToPocCount[3]++;
		}
	}
	for (int i=0;i<4;i++)
	{
		MessageBox(transTool.toCString(ToPocCount[i]));
		ToPicResultDouble[i]=double(ToPocCount[i]/1.0)/pDoc->CinParamPersonNum;
	}
	/*float ToPicResultDouble[4];
	ToPicResultDouble[0]=0.33;
	ToPicResultDouble[1]=0.0;
	ToPicResultDouble[2]=0.33;
	ToPicResultDouble[3]=0.34;*/
	if (pDoc->useWhatPicture == 0)
	{	
		for (int i = 0; i <pDoc->CinParamPersonNum; i++)
		{
			
			if (i == 0)
			{
				int hight = 400 * pDoc->userCinQuotaResult[i];
				dc.MoveTo(90 * i + 80, 400 - hight);
				
			}
			else
			{
				
				int hight = 400 * pDoc->userCinQuotaResult[i];
				dc.LineTo(90 + 80*i, 400 - hight);
				dc.MoveTo(90 + 80*i, 400 - hight);
				
			}
			//	edit1.SetWindowTextA((_bstr_t)shili1); MessageBox((_bstr_t)shili1);
		}
	staticZhu.HideCaret();
		UpdateData(false);

	}
	//柱状图
	else if (pDoc->useWhatPicture == 1)
	{
		for (int i = 0; i < 4; i++)
		{
			if (i == 0)
			{ 
				//shili1 = addCString(s2, treeitem1[i]);
			}
			else
			{
				//shili1 = addCString(shili1, s3);
				//shili1 = addCString(shili1, treeitem1[i]);
			}
			
			int hight = 600 * ToPicResultDouble[i];
			dc.Rectangle(45 + 80 * i, 600 - hight, 45 + 80 * i+ 80, 600);
			
		}
		UpdateData(false);
		staticBing.ShowWindow(SW_HIDE);
	}
	//饼图
	else
	{

		int x0 = 400, y0 = 300;
		float sum = 0,presum, pi = 3.14f, angle = 0,sum1=0;
		int x1, x2, y1, y2;
		/*for (int i = 0; i < 4; i++)
		{
			sum1 += pDoc->userCinQuotaResult[i];
		}*/
		bool tag=false;
		for (int t = 0; t < 4; t++)
		{ 
		
			CBrush brush2(RGB(255 - t * 140, t * 200, 255 - t * 100)), *oldbrush2;
			oldbrush2 = dc.SelectObject(&brush2);
			dc.Rectangle(600, 200 + t * 50, 610, 200 + t * 50 + 10);
			presum=sum;
			sum += ToPicResultDouble[t];
			if (presum==sum)
			{
				continue;
			}
			//float aa=sum;
			if (t == 0)
			{
				dc.SelectObject(&brush2);
				x1 = (x0 - 300)*cos(sum*3.14 * 2) + (y0 - 300)*sin(sum*3.14 * 2) + 300;
				y1 = (y0 - 300)*cos(sum*3.14 * 2) - (x0 - 300)*sin(sum*3.14 * 2) + 300;
				dc.Pie(200, 200, 400, 400, 400, 300, x1, y1);
			}
			else
			{
				if (sum!=1)
				{
					dc.SelectObject(&brush2);
					x2 = (x0 - 300)*cos(sum*3.14 * 2) + (y0 - 300)*sin(sum*3.14 * 2) + 300;
					y2 = (y0 - 300)*cos(sum*3.14 * 2) - (x0 - 300)*sin(sum*3.14 * 2) + 300;
					dc.Pie(200, 200, 400, 400, x1, y1, x2, y2);
					x1 = x2;
					y1 = y2;
				}else{
					if (!tag)
					{
						tag=true;
						dc.SelectObject(&brush2);
						x2 = (x0 - 300)*cos(sum*3.14 * 2) + (y0 - 300)*sin(sum*3.14 * 2) + 300;
						y2 = (y0 - 300)*cos(sum*3.14 * 2) - (x0 - 300)*sin(sum*3.14 * 2) + 300;
						dc.Pie(200, 200, 400, 400, x1, y1, x2, y2);
						x1 = x2;
						y1 = y2;
					}else{
						break;
					}
				}
			}
			dc.SelectObject(&oldbrush2);
			UpdateData(false);
		}
	staticZhu.ShowWindow(SW_HIDE);		
	}
}

//
void DialogShowPicture::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	OnPaint();
}




BOOL DialogShowPicture::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ShowWindow(SW_NORMAL);
	CRect rtDesk;
	CRect rtDlg;
	::GetWindowRect(::GetDesktopWindow(),&rtDesk);
	GetWindowRect(&rtDlg);
	int iXpos=rtDesk.Width()/2-rtDlg.Width()/2;
	int iYpos=rtDesk.Height()/2-rtDlg.Height()/2;
	SetWindowPos(NULL,iXpos,iYpos,0,0,SWP_NOOWNERZORDER|SWP_NOSIZE|SWP_NOZORDER);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void DialogShowPicture::OnStnClickedStaticbing()
{
	// TODO: 在此添加控件通知处理程序代码
}
