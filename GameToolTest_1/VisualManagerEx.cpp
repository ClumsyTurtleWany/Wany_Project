#include "pch.h"
#include "VisualManagerEx.h"
#include "resource.h"

//IMPLEMENT_DYNCREATE(VisualManagerEx, CMFCVisualManagerOffice2007)
IMPLEMENT_DYNCREATE(VisualManagerEx, CMFCVisualManagerVS2008)

VisualManagerEx::VisualManagerEx()
{
}

VisualManagerEx::~VisualManagerEx()
{
}

void VisualManagerEx::OnUpdateSystemColors()
{

}

COLORREF VisualManagerEx::OnDrawRibbonPanel(CDC* pDC, CMFCRibbonPanel* pPanel, CRect rectPanel, CRect rectCaption)
{
	//CBrush br(RGB(0, 0, 255));
	CBrush br(RGB(0, 0, 0));
	pDC->FillRect(rectPanel, &br);
	return RGB(0, 255, 0);
}

void VisualManagerEx::OnDrawRibbonCategory(CDC* pDC, CMFCRibbonCategory* pCategory, CRect rectCategory)
{
	//CBrush br(RGB(255, 0, 0));
	CBrush br(RGB(0, 0, 0));
	pDC->FillRect(rectCategory, &br);
}

