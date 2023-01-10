#pragma once

#define COLOR_TITLE_TEXT	RGB(255, 0, 0)
#define COLOR_TITLE_BAR		RGB(21, 21, 21)
#define COLOR_RIBBON_BAR	RGB(36, 36, 36)

class VisualManagerEx : public CMFCVisualManagerWindows7
//class VisualManagerEx : public CMFCVisualManagerVS2008
{
public:
	VisualManagerEx();
	virtual ~VisualManagerEx();

	DECLARE_DYNCREATE(VisualManagerEx)

	/////////////////////////////////////////////////////
	// Ribbon Bar
	/////////////////////////////////////////////////////
	
	// Title Text
	void OnDrawRibbonCaption(CDC* pDC, CMFCRibbonBar* pBar, CRect rect, CRect rectText);

	// Ribbon & Status Bar Background
	COLORREF OnDrawRibbonTabsFrame(CDC* pDC, CMFCRibbonBar* pWndRibbonBar, CRect rectTab);
	void OnFillBarBackground(CDC* pDC, CBasePane* pBar, CRect rectClient, CRect rectClip, BOOL bNCArea);
	// Ribbon Panel
	virtual COLORREF OnDrawRibbonPanel(CDC* pDC, CMFCRibbonPanel* pPanel, CRect rectPanel, CRect rectCaption);
	// Ribbon Panel Tab
	COLORREF OnDrawRibbonCategoryTab(CDC* pDC, CMFCRibbonTab* pTab, BOOL bIsActive);
	// Ribbon Panel's Category
	virtual void OnDrawRibbonCategory(CDC* pDC, CMFCRibbonCategory* pCategory, CRect rectCategory);

};