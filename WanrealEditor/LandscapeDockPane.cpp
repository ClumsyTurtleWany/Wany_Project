// LandscapeDockPane.cpp: 구현 파일
//

#include "pch.h"
#include "WanrealEditor.h"
#include "LandscapeDockPane.h"


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
	ON_WM_SETFOCUS()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// LandscapeDockPane 메시지 처리기

int LandscapeDockPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_LandscapeManagementDlg.Create(IDD_TestDlg, this);
	m_LandscapeManagementDlg.ShowWindow(SW_SHOW);

	//InitializeRibbonBar();

	return 0;
}

void LandscapeDockPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	if (m_LandscapeManagementDlg.GetSafeHwnd())
	{
		int nLeft = ::GetSystemMetrics(SM_XVIRTUALSCREEN);  // 제일 왼쪽 모니터 X 좌표
		int nTop = ::GetSystemMetrics(SM_YVIRTUALSCREEN); // 제일 위쪽 모니터 Y 좌표
		int nWidth = ::GetSystemMetrics(SM_CXSCREEN); // 현재 모니터 전체 넓이
		int nHeight = ::GetSystemMetrics(SM_CYSCREEN); // 현재 모니터 전체 높이
		m_LandscapeManagementDlg.MoveWindow(0 + nLeft, 0 + nTop, cx, cy);
		//m_LandscapeManagementDlg.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOZORDER);
	}
}

//void LandscapeDockPane::OnSetFocus(CWnd* pOldWnd)
//{
//	CDockablePane::OnSetFocus(pOldWnd);
//
//	m_LandscapeManagementDlg.SetFocus();
//	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
//}


void LandscapeDockPane::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDockablePane::OnPaint()을(를) 호출하지 마십시오.

	CRect rectPane;
	this->GetWindowRect(rectPane);
	ScreenToClient(rectPane);

	CRect rectDlg;
	m_LandscapeManagementDlg.GetWindowRect(rectDlg);
	
	int nLeft = ::GetSystemMetrics(SM_XVIRTUALSCREEN);  // 제일 왼쪽 모니터 X 좌표
	int nTop = ::GetSystemMetrics(SM_YVIRTUALSCREEN); // 제일 위쪽 모니터 Y 좌표
	rectDlg.left += nLeft;
	rectDlg.top += nTop;
	rectDlg.right += nLeft;
	rectDlg.bottom += nTop;
	ScreenToClient(rectDlg);

	rectDlg.InflateRect(1, 1);

	//dc.Draw3dRect(rectDlg, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
	dc.Draw3dRect(rectPane, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void LandscapeDockPane::InitializeRibbonBar()
{
	/*m_RibbonBar.Create(this);
	
	CMFCRibbonCategory* pCategoryManagement = nullptr;
	CMFCRibbonPanel* pPanel = nullptr;

	pCategoryManagement = m_RibbonBar.AddCategory(L"Management", NULL, NULL);
	pPanel = pCategoryManagement->AddPanel(L"TestPanel");
	pPanel->Add(new CMFCRibbonLabel(L"Test Panel Label"));*/

}
