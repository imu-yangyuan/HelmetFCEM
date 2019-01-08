#pragma once


// MFCTabCtrlEx

class MFCTabCtrlEx : public CMFCTabCtrl
{
	DECLARE_DYNAMIC(MFCTabCtrlEx)

public:
	MFCTabCtrlEx();
	virtual ~MFCTabCtrlEx();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


