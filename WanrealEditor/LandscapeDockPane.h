#pragma once

#include "LandscapeManagementDlg.h"
#include "LandscapeSculptingDlg.h"
#include "LandscapePaintingDlg.h"

#include "LandscapeDockPaneView.h"

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
	CFrameWndEx*			m_FrameWnd;
	CView*					m_FormView;
	CMFCRibbonBar			m_RibbonBar;
	CMFCTabCtrl				m_TabCtrl;
	LandscapeManagementDlg	m_LandscapeManagementDlg;
	LandscapeSculptingDlg	m_LandscapeSculptingDlg;
	LandscapePaintingDlg	m_LandscapePaintingDlg;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

public:
	
};


