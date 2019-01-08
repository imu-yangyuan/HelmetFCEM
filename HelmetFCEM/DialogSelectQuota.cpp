// DialogSelectQuota.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HelmetFCEM.h"
#include "DialogSelectQuota.h"
#include "afxdialogex.h"
#define IDC_CHECKBOX    (0x3000) // �ؼ���ID��

// DialogSelectQuota �Ի���

IMPLEMENT_DYNAMIC(DialogSelectQuota, CDialogEx)

DialogSelectQuota::DialogSelectQuota(CWnd* pParent /*=NULL*/)
	: CDialogEx(DialogSelectQuota::IDD, pParent)
{

}
DialogSelectQuota::DialogSelectQuota(CHelmetFCEMDoc *p, SelectQuota *sq,int id)
	: CDialogEx(IDD_SELECTQUOTA)
{
	selectQuota = sq;
	pDoc = p;
	parentId = id;
}
DialogSelectQuota::~DialogSelectQuota()
{
}

void DialogSelectQuota::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogSelectQuota, CDialogEx)
	ON_BN_CLICKED(IDOK, &DialogSelectQuota::OnBnClickedOk)
END_MESSAGE_MAP()


// DialogSelectQuota ��Ϣ�������


BOOL DialogSelectQuota::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CButton* pButton = NULL;
	CString strText(_T(""));

	CONST UINT MAX_CHECKBOX_WIDTH = 350; // ����CheckBox�Ŀ��
	CONST UINT MAX_CHECKBOX_HEIGHT = 20; // ����CheckBox�ĸ߶�

	CONST UINT MAX_CHECKBOX_X_GAP = 30; // ����CheckBox֮���ˮƽ�������
	CONST UINT MAX_CHECKBOX_Y_GAP = 20; // ����CheckBox֮��Ĵ�ֱ�������
	CRect rect;
	rect.SetRectEmpty();
	int count=0;
	for (int i = 0; i < pDoc->secondQutaNum; ++i)
	{
		if (selectQuota[i].isSelect==0) {
			if (0 == (count % 4))
			{
				rect.left = 10;
				rect.top = rect.bottom + MAX_CHECKBOX_Y_GAP;
			}
			else
			{
				rect.left = rect.right + MAX_CHECKBOX_X_GAP;
			}
			rect.right = rect.left + MAX_CHECKBOX_WIDTH;
			rect.bottom = rect.top + MAX_CHECKBOX_HEIGHT;
			CString CStemp,CStemp1;
			strText.Format(_T("%d."), i + 1);
			CStemp1=strText;
			CStemp = transTool.toCString(selectQuota[i].quotaName);
			strText.Format(_T("%s%s"), CStemp1, CStemp);
			//strText+= CStemp;
			count++;
			pButton = new CButton;
			ASSERT(NULL != pButton);
			VERIFY(pButton->Create(strText, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, rect, this, IDC_CHECKBOX + i));
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
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void DialogSelectQuota::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for (int i = 0; i < pDoc->secondQutaNum; ++i)
	{
		if (selectQuota[i].isSelect == 0) {
			CButton* pbtn = (CButton*)GetDlgItem(IDC_CHECKBOX + i);
			if (pbtn->GetCheck() == 1 && pbtn->IsWindowEnabled() == true) {
				int id = selectQuota[i].id;
				pDoc->quota[id].treeRank = 2;
				pDoc->quota[id].parentId = parentId;
				pDoc->quota[parentId].childNum++;
				selectQuota[i].isSelect = 1;
				pDoc->sencontQuotauseTag--;
			}
		}

	}
	CDialogEx::OnOK();
}
