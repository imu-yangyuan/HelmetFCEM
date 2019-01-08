// MFCTabCtrlEx.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HelmetFCEM.h"
#include "MFCTabCtrlEx.h"


// MFCTabCtrlEx

IMPLEMENT_DYNAMIC(MFCTabCtrlEx, CMFCTabCtrl)

MFCTabCtrlEx::MFCTabCtrlEx()
{

}

MFCTabCtrlEx::~MFCTabCtrlEx()
{
}


BEGIN_MESSAGE_MAP(MFCTabCtrlEx, CMFCTabCtrl)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// MFCTabCtrlEx ��Ϣ�������




void MFCTabCtrlEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CMFCTabCtrl::OnLButtonDown(nFlags, point);
	// ��ȡTab������
	int n = GetTabsNum();

	if (n == 0) return;

	CRect rc;

	// ��ȡ����Tab����
	CalcRectEdit(rc);
	GetTabsRect(rc);
	// ��ȡ��ǰѡ����ڵ�ָ��
	CWnd *pTabWnd = GetActiveWnd();
	pTabWnd->GetClientRect(rc);

	int sel;

	// ��ȡ��ǰѡ���Tab
	sel = GetActiveTab();

	// ��ȡ����Tab����
	GetTabRect(sel, rc);

	// ��ȡ����Tab�������
	int nWidth = GetTabMaxWidth();

	// ��ȡ�رհ�ť������
	CRect rcCloseBtn;
	rcCloseBtn = GetTabCloseButton();
	if (IsTabCloseButtonPressed()) {
		// �ر�Tabҳ��������   
		pTabWnd->SendMessage(WM_CLOSE);
		// ɾ��Tab  
		RemoveTab(sel);
	}
}
