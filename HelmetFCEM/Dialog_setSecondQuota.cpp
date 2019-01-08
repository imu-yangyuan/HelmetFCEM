// Dialog_setSecondQuota.cpp : 实现文件
//

#include "stdafx.h"
#include "HelmetFCEM.h"
#include "Dialog_setSecondQuota.h"
#include "afxdialogex.h"
#include "TransformPlus.h"
#include"MainFrm.h"
#include "HelmetFCEMDoc.h"
#include "DialogSelectQuota.h"
#include "SelectQuota.h"


// Dialog_setSecondQuota 对话框
#include "SelectQuota.h"


// DialogSetSecondQuota 对话框
CImageList m_imagelist;
//记录树的所有节点，用于分级赋权
SelectQuota *selectQuota;
HTREEITEM 
	hroot, delitem = NULL, h1, delitem1 = NULL, h2, reitem = NULL, reitem1 = NULL, yijiitem, erjiitem, sanjiitem;
IMPLEMENT_DYNAMIC(Dialog_setSecondQuota, CDialogEx)

	Dialog_setSecondQuota::Dialog_setSecondQuota(CWnd* pParent /*=NULL*/)
	: CDialogEx(Dialog_setSecondQuota::IDD, pParent)
{

}
Dialog_setSecondQuota::Dialog_setSecondQuota(CMainFrame *pF, CHelmetFCEMDoc * p) : CDialogEx(IDD_SECONDQUOTA)
{
	pFrame = pF;
	pDoc = p;
}
Dialog_setSecondQuota::~Dialog_setSecondQuota()
{
}

void Dialog_setSecondQuota::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, quotaTree);
}


BEGIN_MESSAGE_MAP(Dialog_setSecondQuota, CDialogEx)
	ON_BN_CLICKED(IDOK, &Dialog_setSecondQuota::OnBnClickedOk)
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, &Dialog_setSecondQuota::OnNMRClickTree1)
	ON_COMMAND(ID_32779, &Dialog_setSecondQuota::On32779)
END_MESSAGE_MAP()


// Dialog_setSecondQuota 消息处理程序


void Dialog_setSecondQuota::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (pDoc->sencontQuotauseTag == 0) {
		//MessageBox(_T("二级指标设置完成"));
		pDoc->sencondsetQuotaTag = true;
		OnOK();
	}
	else {
		MessageBox(_T("还有二级指标没有设置完，请先设置完再提交！"));
		return;
	}
	CDialogEx::OnOK();
}


BOOL Dialog_setSecondQuota::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	int secondcount = 0;
	selectQuota = new SelectQuota[pDoc->secondQutaNum];
	pDoc->sencontQuotauseTag = pDoc->secondQutaNum;
	for (int i = 0; i < pDoc->quotaNum; i++) {
		if (pDoc->quota[i].treeRank != 1) {
			selectQuota[secondcount].id = pDoc->quota[i].id;
			selectQuota[secondcount].quotaName = pDoc->quota[i].name;
			secondcount++;
		}
	}
	// TODO:  在此添加额外的初始化
	//HBITMAP hBitmap = NULL;
	////hBitmap = ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP75));
	//EnableToolTips(TRUE);//enable use it

	m_imagelist.Create(16, 16, ILC_COLOR, 2, 2);//建立图像列表，分别代表像素，颜色，图片列数，最大图片列数
	CBitmap bm;//位图封装容器
	bm.LoadBitmap(IDB_BITMAP16);//载入Bitmap资源
	m_imagelist.Add(&bm, RGB(0, 0, 0));//添加到图像列表
	bm.DeleteObject();
	bm.LoadBitmap(IDB_BITMAP15);
	m_imagelist.Add(&bm, RGB(0, 0, 0));
	int *i = new int();
	quotaTree.SetImageList(&m_imagelist, LVSIL_NORMAL);//为树形控件添加图像列表

	//插入新节点
	hroot = quotaTree.InsertItem((_bstr_t)"指标", 1, 0, TVI_ROOT);//添加二级节点
	quotaTree.SetBkColor(RGB(255, 255, 255));//设置树形控件的背景色
	quotaTree.SetTextColor(RGB(0, 0, 0));//设置文本背景色
	quotaTree.Select(h1, TVGN_CARET);
	for (int i = 0; i <pDoc->quotaNum; i++) {
		if(1==pDoc->quota[i].treeRank)
			h1 = quotaTree.InsertItem(transTool.toCString(pDoc->quota[i].name), 1, 0, hroot);//添加二级节点
	}
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




void Dialog_setSecondQuota::OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CPoint point;
	GetCursorPos(&point); // 当前鼠标坐标
	CPoint PointInTree = point;
	quotaTree.ScreenToClient(&PointInTree);
	CMenu menu;
	CMenu *ptrMenu;
	CBitmap m_bitmap1, m_bitmap2, m_bitmap3;
	m_bitmap1.LoadBitmap(IDB_BITMAP13);

	HTREEITEM Item;
	UINT nFlag = TVHT_ONITEM; // 当在 Item 上右击时
	Item = quotaTree.HitTest(PointInTree, &nFlag);
	CString roadname = quotaTree.GetItemText(Item);
	int nLength = roadname.GetLength();
	CString b = roadname.Right(3);

	if (Item != NULL&&quotaTree.GetParentItem(Item) == hroot)//总根节点 可以新建一级节点
	{
		quotaTree.SelectItem(Item);
		menu.LoadMenu(IDR_MENU1);
		ptrMenu = menu.GetSubMenu(0);
		ptrMenu->SetMenuItemBitmaps(0, MF_BYPOSITION, &m_bitmap1, &m_bitmap1);
		ptrMenu->TrackPopupMenu
			(
			TPM_LEFTALIGN | TPM_RIGHTBUTTON,
			point.x,
			point.y,
			this,
			NULL);

	}
	*pResult = 0;
}


void Dialog_setSecondQuota::On32779()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
	CString temp = quotaTree.GetItemText(quotaTree.GetSelectedItem());
	int parentId;
	for (int i = 0; i < pDoc->quotaNum; i++) {
		if (temp == transTool.toCString(pDoc->quota[i].name))
		{
			parentId = pDoc->quota[i].id;
			break;
		}
	}
	DialogSelectQuota *selectDialog=new DialogSelectQuota(pDoc, selectQuota, parentId);
	selectDialog->DoModal();

	for (int i = 0; i < pDoc->quotaNum; i++) {
		if(2==pDoc->quota[i].treeRank)
			if (parentId == pDoc->quota[i].parentId) 
			{
				for (int j = 0; j < pDoc->secondQutaNum; j++) {
					if (pDoc->quota[i].id == selectQuota[j].id) {
						if (selectQuota[j].isAddParent == 0) {
							selectQuota[j].isAddParent = 1;
							quotaTree.InsertItem(transTool.toCString(pDoc->quota[i].name), 1, 0, quotaTree.GetSelectedItem());

						}

					}
				}					
			}
	}
	delete selectDialog;
}
