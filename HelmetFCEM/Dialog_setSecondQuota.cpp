// Dialog_setSecondQuota.cpp : ʵ���ļ�
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


// Dialog_setSecondQuota �Ի���
#include "SelectQuota.h"


// DialogSetSecondQuota �Ի���
CImageList m_imagelist;
//��¼�������нڵ㣬���ڷּ���Ȩ
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


// Dialog_setSecondQuota ��Ϣ�������


void Dialog_setSecondQuota::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (pDoc->sencontQuotauseTag == 0) {
		//MessageBox(_T("����ָ���������"));
		pDoc->sencondsetQuotaTag = true;
		OnOK();
	}
	else {
		MessageBox(_T("���ж���ָ��û�������꣬�������������ύ��"));
		return;
	}
	CDialogEx::OnOK();
}


BOOL Dialog_setSecondQuota::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//HBITMAP hBitmap = NULL;
	////hBitmap = ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP75));
	//EnableToolTips(TRUE);//enable use it

	m_imagelist.Create(16, 16, ILC_COLOR, 2, 2);//����ͼ���б��ֱ�������أ���ɫ��ͼƬ���������ͼƬ����
	CBitmap bm;//λͼ��װ����
	bm.LoadBitmap(IDB_BITMAP16);//����Bitmap��Դ
	m_imagelist.Add(&bm, RGB(0, 0, 0));//��ӵ�ͼ���б�
	bm.DeleteObject();
	bm.LoadBitmap(IDB_BITMAP15);
	m_imagelist.Add(&bm, RGB(0, 0, 0));
	int *i = new int();
	quotaTree.SetImageList(&m_imagelist, LVSIL_NORMAL);//Ϊ���οؼ����ͼ���б�

	//�����½ڵ�
	hroot = quotaTree.InsertItem((_bstr_t)"ָ��", 1, 0, TVI_ROOT);//��Ӷ����ڵ�
	quotaTree.SetBkColor(RGB(255, 255, 255));//�������οؼ��ı���ɫ
	quotaTree.SetTextColor(RGB(0, 0, 0));//�����ı�����ɫ
	quotaTree.Select(h1, TVGN_CARET);
	for (int i = 0; i <pDoc->quotaNum; i++) {
		if(1==pDoc->quota[i].treeRank)
			h1 = quotaTree.InsertItem(transTool.toCString(pDoc->quota[i].name), 1, 0, hroot);//��Ӷ����ڵ�
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
	// �쳣: OCX ����ҳӦ���� FALSE
}




void Dialog_setSecondQuota::OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPoint point;
	GetCursorPos(&point); // ��ǰ�������
	CPoint PointInTree = point;
	quotaTree.ScreenToClient(&PointInTree);
	CMenu menu;
	CMenu *ptrMenu;
	CBitmap m_bitmap1, m_bitmap2, m_bitmap3;
	m_bitmap1.LoadBitmap(IDB_BITMAP13);

	HTREEITEM Item;
	UINT nFlag = TVHT_ONITEM; // ���� Item ���һ�ʱ
	Item = quotaTree.HitTest(PointInTree, &nFlag);
	CString roadname = quotaTree.GetItemText(Item);
	int nLength = roadname.GetLength();
	CString b = roadname.Right(3);

	if (Item != NULL&&quotaTree.GetParentItem(Item) == hroot)//�ܸ��ڵ� �����½�һ���ڵ�
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
	// TODO: �ڴ���������������
	// TODO: �ڴ���������������
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
