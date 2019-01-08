// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// HelmetFCEMDoc.h : CHelmetFCEMDoc 类的接口
//


#pragma once
#include "TransformPlus.h"
#include "Quota.h"
#include "UserCinQuota.h"

class CHelmetFCEMDoc : public CDocument
{
protected: // 仅从序列化创建
	CHelmetFCEMDoc();
	DECLARE_DYNCREATE(CHelmetFCEMDoc)

// 特性
public:

// 操作
public:
	//指标总数目
	int quotaNum;

	//专家最终确定的指标数据
	Quota *quota;
	//使用时所用的指标数据
	Quota *finalQuota;
	////专家输入的指标数据
	//Quota **expertQuotaCinData;
	int firstQutaNum;
	int secondQutaNum;
	CString quotaName[100];
	TransformPlus transTool;

	//指标参数记录
	//CString quotaParam[100][100];
	int quotaParamcount;
	// 判断专家是否输入了指标
	bool peopleNumTag;
	int userCanCinParamNum;
	//记录用户输入的阈值的次数
	int userCinParaNum;
	//int av, ov, aj, oj;
	int treesave;//第一步建立的指标树是否保存的标志
	int sencontQuotauseTag;
	double result;
	int useWhatArithmeticTag;

	bool fistsetQuotaTag;
	bool sencondsetQuotaTag;
	bool setQuotaWeightTag;
	//评价人数
	int CinParamPersonNum;
	int CinParamPersonCount;
	//UserCinQuota **userCinQuota;
	//用来记录用户输入的值算出来的最终结果
	double *userCinQuotaResult;
	bool setUserCinQuotaNumTag;
	//记录要绘制的图形类型
	bool canPicture;
	int useWhatPicture;

	double you;
	double liang;
	double zhong;
	bool youTag;
	bool liangTag;
	bool zhongTag;
	int ToPicresult[4];
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CHelmetFCEMDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
