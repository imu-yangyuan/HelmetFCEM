#pragma once

#include "TransformPlus.h"
#include "HelmetFCEMDoc.h"
#include"MainFrm.h"
// DialogFirstQuota �Ի���

class DialogFirstQuota : public CDialogEx
{
	DECLARE_DYNAMIC(DialogFirstQuota)

public:
	TransformPlus transformPlus;
	CHelmetFCEMDoc *pDoc;
	CMainFrame *pFrame;
	DialogFirstQuota(CMainFrame *pF,CHelmetFCEMDoc * p);
	DialogFirstQuota(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogFirstQuota();

// �Ի�������
	enum { IDD = IDD_FIRSTQUOTA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
