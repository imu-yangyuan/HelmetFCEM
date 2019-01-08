// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// HelmetFCEMView.h : CHelmetFCEMView ��Ľӿ�
//

#pragma once
#include "TransformPlus.h"
#include "MFCTabCtrlEx.h"
#include "DialogFirstQuota.h"
#include "Dialog_setSecondQuota.h"
#include "Dialog_setSecondQuota.h"
#include "DialogSetQuotaWeight.h"
#include "DialogShowPicture.h"
#include "MainFrm.h"

class CHelmetFCEMView : public CScrollView
{
protected: // �������л�����
	CHelmetFCEMView();
	DECLARE_DYNCREATE(CHelmetFCEMView)

// ����
public:
	CHelmetFCEMDoc* GetDocument() const;
	
// ����
public:
	int setFirstQuotaCount;
	int setSecondQuotaCount;
	int setQuotaWeightCount;
	TransformPlus transTool;
	CMainFrame *pMF;
	CHelmetFCEMDoc *pDoc;
	MFCTabCtrlEx m_wndTabs;
	DialogFirstQuota *dialogFirstQuota;
	Dialog_setSecondQuota *dialog_setSecondQuota;
	DialogSetQuotaWeight *dialogSetQuotaWeight;
	DialogShowPicture *dialogShowPicture;
	int setUserCinQuotaParaCount;
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CHelmetFCEMView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButtonshowtree();
	afx_msg void OnButton9();
	afx_msg void OnButtonfirst();
	afx_msg void OnUpdateEdit2(CCmdUI *pCmdUI);
	afx_msg void OnEdit2();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButtonshowpic();
	afx_msg void OnOutpdf();
	afx_msg void OnSetsecond();
	afx_msg void OnButtonzhu();
	afx_msg void OnButton11();
	afx_msg void OnButton12();
	afx_msg void OnButton13();
	afx_msg void OnUpdateEdit3(CCmdUI *pCmdUI);
	afx_msg void OnEdit3();
	afx_msg void OnEdit6();
	afx_msg void OnUpdateEdit6(CCmdUI *pCmdUI);
	afx_msg void OnEdit7();
	afx_msg void OnEdit8();
	afx_msg void OnUpdateEdit7(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEdit8(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // HelmetFCEMView.cpp �еĵ��԰汾
inline CHelmetFCEMDoc* CHelmetFCEMView::GetDocument() const
   { return reinterpret_cast<CHelmetFCEMDoc*>(m_pDocument); }
#endif

