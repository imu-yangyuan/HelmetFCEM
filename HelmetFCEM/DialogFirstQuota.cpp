// DialogFirstQuota.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HelmetFCEM.h"
#include "DialogFirstQuota.h"
#include "afxdialogex.h"

#include <cstring>
#include <string>
#define eps 1e-8 
#define MAX_COUNT        (33) // CheckBox���ܸ���
#define MAX_ROW            (5)  // һ������2��CheckBox
#define IDC_CHECKBOX    (0x2000) // �ؼ���ID��
// DialogFirstQuota �Ի���

IMPLEMENT_DYNAMIC(DialogFirstQuota, CDialogEx)

DialogFirstQuota::DialogFirstQuota(CWnd* pParent /*=NULL*/)
	: CDialogEx(DialogFirstQuota::IDD, pParent)
{

}
DialogFirstQuota::DialogFirstQuota(CMainFrame *pF, CHelmetFCEMDoc * p)
	: CDialogEx(IDD_FIRSTQUOTA)
{
	pFrame = pF;
	pDoc = p;

}
DialogFirstQuota::~DialogFirstQuota()
{
}

void DialogFirstQuota::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogFirstQuota, CDialogEx)
	ON_BN_CLICKED(IDOK, &DialogFirstQuota::OnBnClickedOk)
END_MESSAGE_MAP()


// DialogFirstQuota ��Ϣ�������


void DialogFirstQuota::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int zhibiaoNum = transformPlus.toInt(pDoc->quotaNum);
	int count = 0;
	for (int i = 0; i < zhibiaoNum; ++i)
	{
		CButton* pbtn = (CButton*)GetDlgItem(IDC_CHECKBOX + i);
		if (pbtn->GetCheck() == 1 && pbtn->IsWindowEnabled() == true) {
			pDoc->quota[i].treeRank = 1;

			count++;
		}
	}
	pDoc->firstQutaNum = count;
	pDoc->secondQutaNum = pDoc->quotaNum - count;
	pDoc->fistsetQuotaTag = true;
	//MessageBox(_T("һ��ָ���Ѿ�������ɣ�"));
	CDialogEx::OnOK();
}


BOOL DialogFirstQuota::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CButton* pButton = NULL;
	CString strText(_T(""));

	CONST UINT MAX_CHECKBOX_WIDTH = 250; // ����CheckBox�Ŀ��
	CONST UINT MAX_CHECKBOX_HEIGHT = 20; // ����CheckBox�ĸ߶�

	CONST UINT MAX_CHECKBOX_X_GAP = 30; // ����CheckBox֮���ˮƽ�������
	CONST UINT MAX_CHECKBOX_Y_GAP = 20; // ����CheckBox֮��Ĵ�ֱ�������
	CRect rect;
	rect.SetRectEmpty();	
	int temp = transformPlus.toInt(pDoc->quotaNum);
	for (int i = 0; i < temp; ++i)
	{
		if (0 == (i %5))
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
		CString CStemp;
		strText.Format(_T("%d."), i + 1);

		CStemp = pDoc->quotaName[i];
		CString cstr=strText;
		strText.Format(_T("%s%s"), cstr, CStemp);
		//strText+= CStemp;

		pButton = new CButton;
		ASSERT(NULL != pButton);
		VERIFY(pButton->Create(strText, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, rect, this, IDC_CHECKBOX + i));
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
