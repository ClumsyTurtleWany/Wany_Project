#pragma once

//class VisualManagerEx : public CMFCVisualManagerWindows7
class VisualManagerEx : public CMFCVisualManagerVS2008
{
public:
	VisualManagerEx();
	virtual ~VisualManagerEx();

	DECLARE_DYNCREATE(VisualManagerEx)

	virtual void OnUpdateSystemColors();
	virtual COLORREF OnDrawRibbonPanel(CDC* pDC, CMFCRibbonPanel* pPanel, CRect rectPanel, CRect rectCaption);
	virtual void OnDrawRibbonCategory(CDC* pDC, CMFCRibbonCategory* pCategory, CRect rectCategory);
};