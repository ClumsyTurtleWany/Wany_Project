#include "pch.h"
#include "VisualManagerEx.h"
#include "resource.h"

//IMPLEMENT_DYNCREATE(VisualManagerEx, CMFCVisualManagerOffice2007)
//IMPLEMENT_DYNCREATE(VisualManagerEx, CMFCVisualManagerVS2008)
IMPLEMENT_DYNCREATE(VisualManagerEx, CMFCVisualManagerWindows7)

VisualManagerEx::VisualManagerEx()
{
}

VisualManagerEx::~VisualManagerEx()
{
}

void VisualManagerEx::OnDrawRibbonCaption(CDC* pDC, CMFCRibbonBar* pBar, CRect rect, CRect rectText)
{
	ASSERT_VALID(pBar);

	CWnd* pWnd = pBar->GetParent();
	ASSERT_VALID(pWnd);

	const BOOL bGlass = pBar->IsTransparentCaption();
	const DWORD dwStyleEx = pWnd->GetExStyle();
	const BOOL bIsRTL = (dwStyleEx & WS_EX_LAYOUTRTL) == WS_EX_LAYOUTRTL;
	BOOL bTextCenter = TRUE;

	ASSERT_VALID(pDC);

	// Å¸ÀÌÆ² Ä¸¼ÇÀÌ¶û ¹öÆ° »ö»ó¸¸ ¹Ù²ñ.
	//CBrush br(RGB(0, 255, 0));
	//pDC->FillRect(rect, &br);

	if ((pBar->GetHideFlags() & AFX_RIBBONBAR_HIDE_ALL) == AFX_RIBBONBAR_HIDE_ALL)
	{
		HICON hIcon = afxGlobalUtils.GetWndIcon(pWnd);

		if (hIcon != NULL)
		{
			CSize szIcon(::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
			CRect rectIcon(rect.TopLeft(), CSize(min(::GetSystemMetrics(SM_CYCAPTION), rect.Height()), rect.Height()));

			long x = rect.left + max((long)0, (long)(rectIcon.Width() - szIcon.cx) / 2);
			long y = rect.top + max((long)0, (long)(rectIcon.Height() - szIcon.cy) / 2);

			::DrawIconEx(pDC->GetSafeHdc(), x, y, hIcon, szIcon.cx, szIcon.cy, 0, NULL, DI_NORMAL);

			if (rectText.left < rectIcon.right)
			{
				rectText.left = rectIcon.right;
			}
		}

		bTextCenter = TRUE;
	}

	//CFont* pOldFont = pDC->SelectObject(&(GetGlobalData()->fontDefaultGUIBold));
	CFont m_fntApplication;
	m_fntApplication.CreateFont(24, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, _T("segoe ui"));
	CFont* pOldFont = pDC->SelectObject(&m_fntApplication);
	ENSURE(pOldFont != NULL);

	int nOldMode = pDC->SetBkMode(TRANSPARENT);

	CString strCaption;
	pWnd->GetWindowText(strCaption);

	DWORD dwTextStyle = DT_END_ELLIPSIS | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | (bIsRTL ? DT_RTLREADING | DT_RIGHT : 0);

	int widthFull = rectText.Width();
	int width = pDC->GetTextExtent(strCaption).cx;

	if (bTextCenter && width < widthFull)
	{
		rectText.left += (widthFull - width) / 2;
	}

	rectText.right = min(rectText.left + width, rectText.right);

	if (rectText.right > rectText.left)
	{
		/*if (bGlass)
		{
		DrawTextOnGlass(pDC, strCaption, rectText, dwTextStyle, 100);
		}
		else
		{
		COLORREF clrOldText = pDC->SetTextColor(clrText);
		pDC->DrawText(strCaption, rectText, dwTextStyle);
		pDC->SetTextColor(clrOldText);
		}*/

		BOOL bRes = GetGlobalData()->DrawTextOnGlass(m_hThemeButton, pDC, 0, 0, strCaption, rectText, dwTextStyle, 0, COLOR_TITLE_TEXT);
	}

	//CBrush br(RGB(255, 0, 0));
	//pDC->FillRect(rect, &br);
	pDC->SetBkMode(nOldMode);
	pDC->SelectObject(pOldFont);
}

COLORREF VisualManagerEx::OnDrawRibbonTabsFrame(CDC* pDC, CMFCRibbonBar* pWndRibbonBar, CRect rectTab)
{
	CBrush br(COLOR_TITLE_BAR);
	pDC->FillRect(rectTab, &br);
	return RGB(0, 0, 0);
}

void VisualManagerEx::OnFillBarBackground(CDC* pDC, CBasePane* pBar, CRect rectClient, CRect rectClip, BOOL bNCArea)
{
	CBrush br(COLOR_TITLE_BAR);
	pDC->FillRect(rectClip, &br);
	br.DeleteObject();
}

COLORREF VisualManagerEx::OnDrawRibbonPanel(CDC* pDC, CMFCRibbonPanel* pPanel, CRect rectPanel, CRect rectCaption)
{
	//CBrush br(RGB(0, 0, 255));
	CBrush br(RGB(255, 255, 255));
	pDC->FillRect(rectPanel, &br);
	return RGB(0, 255, 0);
}

void VisualManagerEx::OnDrawRibbonCategory(CDC* pDC, CMFCRibbonCategory* pCategory, CRect rectCategory)
{
	//CBrush br(RGB(255, 0, 0));
	CBrush br(RGB(36, 36, 36));
	pDC->FillRect(rectCategory, &br);
}

COLORREF VisualManagerEx::OnDrawRibbonCategoryTab(CDC* pDC, CMFCRibbonTab* pTab, BOOL bIsActive)
{
	CString strText = pTab->GetText();

	CRect rc = pTab->GetRect();
	if (bIsActive)
	{
		rc.bottom += 2;
		CBrush br(RGB(36, 36, 36));
		pDC->FillRect(rc, &br);
		return RGB(255, 255, 255);
	}
	else
	{
		rc.top += 4;
		rc.bottom += 2;
		CBrush br(RGB(100, 100, 100));
		pDC->FillRect(rc, &br);
	}
	return RGB(255, 255, 255);
}

