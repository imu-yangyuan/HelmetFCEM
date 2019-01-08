#pragma once

#include "HelmetFCEMDoc.h"
#include "TransformPlus.h"
#include "UserCinQuota.h"
// DialogSetParam �Ի���

class DialogSetParam : public CDialogEx
{
	DECLARE_DYNAMIC(DialogSetParam)

public:
	CHelmetFCEMDoc *pDoc;
	int num;
	TransformPlus transTool;
	UserCinQuota *userCinQuota;
	UserCinQuota *userCinQuotaCopy;
	bool commit;
	DialogSetParam(CHelmetFCEMDoc *p,int n);
	DialogSetParam(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogSetParam();

// �Ի�������
	enum { IDD = IDD_SETPARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	double av(void);
	double aj(void);
	double ov(void);
	double oj(void);
	int m_page;  

	int GetScrollPos(int nBar, UINT nSBCode);  
	void ScrollClient(int nBar, int nPos) ;  
	void VScrool(int nBar, UINT nSBCode) ;  
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
