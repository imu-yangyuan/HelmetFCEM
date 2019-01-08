#pragma once
#include "SelectQuota.h"
#include "HelmetFCEMDoc.h"
#include "TransformPlus.h"

// DialogSelectQuota 对话框

class DialogSelectQuota : public CDialogEx
{
	DECLARE_DYNAMIC(DialogSelectQuota)

public:
	DialogSelectQuota(CHelmetFCEMDoc *p,SelectQuota *sq, int id);
	DialogSelectQuota(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogSelectQuota();

// 对话框数据
	enum { IDD = IDD_SELECTQUOTA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	SelectQuota *selectQuota;
	CHelmetFCEMDoc *pDoc;
	TransformPlus transTool;
	int parentId;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
