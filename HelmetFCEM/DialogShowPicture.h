#pragma once

#include "HelmetFCEMDoc.h"
#include "TransformPlus.h"
#include "afxwin.h"
// DialogShowPicture 对话框

class DialogShowPicture : public CDialogEx
{
	DECLARE_DYNAMIC(DialogShowPicture)

public:
	TransformPlus transTool;
	CHelmetFCEMDoc *pDoc;
	DialogShowPicture(CHelmetFCEMDoc *p);
	DialogShowPicture(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogShowPicture();

// 对话框数据
	enum { IDD = IDD_SHOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	CStatic staticZhu;
	CStatic staticBing;
	afx_msg void OnStnClickedStaticbing();
};
