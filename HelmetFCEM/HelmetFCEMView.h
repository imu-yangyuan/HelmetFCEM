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

// HelmetFCEMView.h : CHelmetFCEMView 类的接口
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
protected: // 仅从序列化创建
	CHelmetFCEMView();
	DECLARE_DYNCREATE(CHelmetFCEMView)

// 特性
public:
	CHelmetFCEMDoc* GetDocument() const;
	
// 操作
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
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CHelmetFCEMView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // HelmetFCEMView.cpp 中的调试版本
inline CHelmetFCEMDoc* CHelmetFCEMView::GetDocument() const
   { return reinterpret_cast<CHelmetFCEMDoc*>(m_pDocument); }
#endif

