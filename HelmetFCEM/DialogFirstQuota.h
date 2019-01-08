#pragma once

#include "TransformPlus.h"
#include "HelmetFCEMDoc.h"
#include"MainFrm.h"
// DialogFirstQuota 对话框

class DialogFirstQuota : public CDialogEx
{
	DECLARE_DYNAMIC(DialogFirstQuota)

public:
	TransformPlus transformPlus;
	CHelmetFCEMDoc *pDoc;
	CMainFrame *pFrame;
	DialogFirstQuota(CMainFrame *pF,CHelmetFCEMDoc * p);
	DialogFirstQuota(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogFirstQuota();

// 对话框数据
	enum { IDD = IDD_FIRSTQUOTA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
