#pragma once
#include "SelectQuota.h"
#include "HelmetFCEMDoc.h"
#include "TransformPlus.h"

// DialogSelectQuota �Ի���

class DialogSelectQuota : public CDialogEx
{
	DECLARE_DYNAMIC(DialogSelectQuota)

public:
	DialogSelectQuota(CHelmetFCEMDoc *p,SelectQuota *sq, int id);
	DialogSelectQuota(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogSelectQuota();

// �Ի�������
	enum { IDD = IDD_SELECTQUOTA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	SelectQuota *selectQuota;
	CHelmetFCEMDoc *pDoc;
	TransformPlus transTool;
	int parentId;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
