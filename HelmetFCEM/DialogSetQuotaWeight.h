#pragma once
#include "HelmetFCEMDoc.h"
#include "TransformPlus.h"
#include "Quota.h"
#include "MainFrm.h"

// DialogSetQuotaWeight 对话框

class DialogSetQuotaWeight : public CDialogEx
{
	DECLARE_DYNAMIC(DialogSetQuotaWeight)

public:
	DialogSetQuotaWeight(CHelmetFCEMDoc * p,int n);
	Quota *expertCinquotaWeight;
	TransformPlus transTool;
	CHelmetFCEMDoc *pDoc;
	int num;
	DialogSetQuotaWeight(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogSetQuotaWeight();

// 对话框数据
	enum { IDD = IDD_SETWEIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	//头文件中添加如下内容，m_page记得初始化  
	int m_page;  

	int GetScrollPos(int nBar, UINT nSBCode);  
	void ScrollClient(int nBar, int nPos) ;  
	void VScrool(int nBar, UINT nSBCode) ;  
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
