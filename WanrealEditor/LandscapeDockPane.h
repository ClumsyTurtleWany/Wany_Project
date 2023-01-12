#pragma once

#include "LandscapeManagementDlg.h"
#include "TestDlg.h"
// LandscapeDockPane

class LandscapeDockPane : public CDockablePane
{
	DECLARE_DYNAMIC(LandscapeDockPane)

public:
	LandscapeDockPane();
	virtual ~LandscapeDockPane();

protected:
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnShowControlBarMenu(CPoint pt) { return TRUE; }

private:
	TestDlg m_LandscapeManagementDlg;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnPaint();

public:
	void InitializeRibbonBar();
};


