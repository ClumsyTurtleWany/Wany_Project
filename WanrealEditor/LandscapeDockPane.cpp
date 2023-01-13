// LandscapeDockPane.cpp: 구현 파일
//

#include "pch.h"
#include "WanrealEditor.h"
#include "LandscapeDockPane.h"
#include "LandscapeDockPaneFrame.h"


// LandscapeDockPane

IMPLEMENT_DYNAMIC(LandscapeDockPane, CDockablePane)

LandscapeDockPane::LandscapeDockPane()
{

}

LandscapeDockPane::~LandscapeDockPane()
{
}

BEGIN_MESSAGE_MAP(LandscapeDockPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// LandscapeDockPane 메시지 처리기

int LandscapeDockPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;



	/*CRect rectPane;
	this->GetClientRect(rectPane);

	CCreateContext cc;

	CView* pView = (CView*)RUNTIME_CLASS(LandscapeDockPaneView)->CreateObject();
	ZeroMemory(&cc, sizeof(cc));
	pView->Create(nullptr, nullptr, WS_CHILD, rectPane, this, IDD_LandscapeDockPaneView, &cc);
	pView->OnInitialUpdate();
	m_FormView = pView;


	CFrameWndEx* pWnd = (CFrameWndEx*)RUNTIME_CLASS(LandscapeDockPaneFrame)->CreateObject();
	pWnd->Create(nullptr, nullptr, WS_CHILD, rectPane, this);
	pWnd.oninit

		m_FrameWnd


	DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP;
	if (!m_RibbonBar.Create(m_FormView, dwStyle, ID_RIBBON_BAR_LANDSCAPE))
	{
		return -1;
	}*/







	CRect rectTab;
	this->GetWindowRect(rectTab);
	ScreenToClient(rectTab);
	if (!m_TabCtrl.Create(CMFCTabCtrl::STYLE_3D_ROUNDED, rectTab, this, 1, CMFCTabCtrl::LOCATION_TOP))
	{
		return -1;
	}

	if (!m_LandscapeManagementDlg.Create(IDD_LandscapeManagementDlg, &m_TabCtrl))
	{
		return -1;
	}
	//m_LandscapeManagementDlg.ShowWindow(SW_SHOW);

	if (!m_LandscapeSculptingDlg.Create(IDD_LandscapeSculptingDlg, &m_TabCtrl))
	{
		return -1;
	}
	//m_LandscapeSculptingDlg.ShowWindow(SW_SHOW);

	if (!m_LandscapePaintingDlg.Create(IDD_LandscapePaintingDlg, &m_TabCtrl))
	{
		return -1;
	}
	//m_LandscapePaintingDlg.ShowWindow(SW_SHOW);

	m_TabCtrl.AddTab(&m_LandscapeManagementDlg, L"Management", 0, FALSE);
	m_TabCtrl.AddTab(&m_LandscapeSculptingDlg, L"Sculpting", 1, FALSE);
	m_TabCtrl.AddTab(&m_LandscapePaintingDlg, L"Painting", 2, FALSE);


	m_TabCtrl.SetImageList(IDR_MAINFRAME, 32, RGB(255, 0, 0));
	for (int tabIdx = 0; tabIdx < m_TabCtrl.GetTabsNum(); tabIdx++)
	{
		m_TabCtrl.SetTabBkColor(tabIdx, RGB(21, 21, 21));
		m_TabCtrl.SetTabTextColor(tabIdx, RGB(255, 255, 255));
		m_TabCtrl.SetTabIcon(tabIdx, tabIdx);
	}

	m_TabCtrl.SetActiveTabTextColor(RGB(255, 0, 0));
	m_TabCtrl.SetActiveTabColor(RGB(255, 36, 36));
	m_TabCtrl.SetActiveTabBoldFont(0);

	m_TabCtrl.RecalcLayout();
	m_TabCtrl.RedrawWindow();

	return 0;
}

void LandscapeDockPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	m_TabCtrl.SetWindowPos(nullptr, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	//m_LandscapeManagementDlg.SetWindowPos(nullptr, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	
}
