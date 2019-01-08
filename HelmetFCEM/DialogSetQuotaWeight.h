#pragma once
#include "HelmetFCEMDoc.h"
#include "TransformPlus.h"
#include "Quota.h"
#include "MainFrm.h"

// DialogSetQuotaWeight �Ի���

class DialogSetQuotaWeight : public CDialogEx
{
	DECLARE_DYNAMIC(DialogSetQuotaWeight)

public:
	DialogSetQuotaWeight(CHelmetFCEMDoc * p,int n);
	Quota *expertCinquotaWeight;
	TransformPlus transTool;
	CHelmetFCEMDoc *pDoc;
	int num;
	DialogSetQuotaWeight(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogSetQuotaWeight();

// �Ի�������
	enum { IDD = IDD_SETWEIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	//ͷ�ļ�������������ݣ�m_page�ǵó�ʼ��  
	int m_page;  

	int GetScrollPos(int nBar, UINT nSBCode);  
	void ScrollClient(int nBar, int nPos) ;  
	void VScrool(int nBar, UINT nSBCode) ;  
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
