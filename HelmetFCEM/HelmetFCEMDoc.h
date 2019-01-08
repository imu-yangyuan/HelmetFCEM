// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// HelmetFCEMDoc.h : CHelmetFCEMDoc ��Ľӿ�
//


#pragma once
#include "TransformPlus.h"
#include "Quota.h"
#include "UserCinQuota.h"

class CHelmetFCEMDoc : public CDocument
{
protected: // �������л�����
	CHelmetFCEMDoc();
	DECLARE_DYNCREATE(CHelmetFCEMDoc)

// ����
public:

// ����
public:
	//ָ������Ŀ
	int quotaNum;

	//ר������ȷ����ָ������
	Quota *quota;
	//ʹ��ʱ���õ�ָ������
	Quota *finalQuota;
	////ר�������ָ������
	//Quota **expertQuotaCinData;
	int firstQutaNum;
	int secondQutaNum;
	CString quotaName[100];
	TransformPlus transTool;

	//ָ�������¼
	//CString quotaParam[100][100];
	int quotaParamcount;
	// �ж�ר���Ƿ�������ָ��
	bool peopleNumTag;
	int userCanCinParamNum;
	//��¼�û��������ֵ�Ĵ���
	int userCinParaNum;
	//int av, ov, aj, oj;
	int treesave;//��һ��������ָ�����Ƿ񱣴�ı�־
	int sencontQuotauseTag;
	double result;
	int useWhatArithmeticTag;

	bool fistsetQuotaTag;
	bool sencondsetQuotaTag;
	bool setQuotaWeightTag;
	//��������
	int CinParamPersonNum;
	int CinParamPersonCount;
	//UserCinQuota **userCinQuota;
	//������¼�û������ֵ����������ս��
	double *userCinQuotaResult;
	bool setUserCinQuotaNumTag;
	//��¼Ҫ���Ƶ�ͼ������
	bool canPicture;
	int useWhatPicture;

	double you;
	double liang;
	double zhong;
	bool youTag;
	bool liangTag;
	bool zhongTag;
	int ToPicresult[4];
// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CHelmetFCEMDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
