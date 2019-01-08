#pragma once

#include "TransformPlus.h"
#include "HelmetFCEMDoc.h"
#include"MainFrm.h"
#include "afxcmn.h"
// Dialog_setSecondQuota �Ի���

class Dialog_setSecondQuota : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog_setSecondQuota)

public:
	TransformPlus transTool;
	CHelmetFCEMDoc *pDoc;
	CMainFrame *pFrame;
	Dialog_setSecondQuota(CMainFrame *pF,CHelmetFCEMDoc * p);
	Dialog_setSecondQuota(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dialog_setSecondQuota();

	// �Ի�������
	enum { IDD = IDD_SECONDQUOTA };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl quotaTree;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void On32776();
	afx_msg void OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void On32779();
};
