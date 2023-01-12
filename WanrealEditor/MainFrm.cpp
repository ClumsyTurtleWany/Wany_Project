// 이 MFC 샘플 소스 코드는 MFC Microsoft Office Fluent 사용자 인터페이스("Fluent UI")를
// 사용하는 방법을 보여 주며, MFC C++ 라이브러리 소프트웨어에 포함된
// Microsoft Foundation Classes Reference 및 관련 전자 문서에 대해
// 추가적으로 제공되는 내용입니다.
// Fluent UI를 복사, 사용 또는 배포하는 데 대한 사용 약관은 별도로 제공됩니다.
// Fluent UI 라이선싱 프로그램에 대한 자세한 내용은
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "WanrealEditor.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()

	ON_COMMAND(ID_COMBO_MODE, OnComboChangeMode)
	ON_UPDATE_COMMAND_UI(ID_COMBO_MODE, OnUpdateComboChangeMode)
END_MESSAGE_MAP()

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!InitializeRibbonBar())
	{
		return -1;
	}

	if (!InitializeStatusBar())
	{
		return -1;
	}

	// Visual Studio 2005 스타일 도킹 창 동작을 활성화합니다.
	CDockingManager::SetDockingMode(DT_SMART);
	// Visual Studio 2005 스타일 도킹 창 자동 숨김 동작을 활성화합니다.
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 모든 사용자 인터페이스 요소를 그리는 데 사용하는 비주얼 관리자를 설정합니다.
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));


	if (!InitializeDockPane())
	{
		return -1;
	}


	return 0;
}

void CMainFrame::OnComboChangeMode()
{
	if (m_pMode != nullptr)
	{
		int idx = m_pMode->GetCurSel();
		if (idx == 0)
		{
			m_LandScapeDockPane.ShowPane(FALSE, FALSE, FALSE);
		}
		else if (idx == 1)
		{
			m_LandScapeDockPane.ShowPane(TRUE, FALSE, TRUE);
		}
		else
		{
			m_LandScapeDockPane.ShowPane(FALSE, FALSE, FALSE);
		}
	}
}

void CMainFrame::OnUpdateComboChangeMode(CCmdUI* pcmdui)
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

bool CMainFrame::InitializeRibbonBar()
{
	m_wndRibbonBar.Create(this);
	//m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	CMFCRibbonCategory* pCategoryMain = nullptr;
	CMFCRibbonPanel* pPanel = nullptr;

	pCategoryMain = m_wndRibbonBar.AddCategory(L"Main", NULL, NULL);
	pPanel = pCategoryMain->AddPanel(L"Main Panel");

	m_pMode = new CMFCRibbonComboBox(ID_COMBO_MODE, FALSE, -1, L"Test Combo Box", -1);
	m_pMode->AddItem(L"Select");
	m_pMode->AddItem(L"Landscape");
	m_pMode->AddItem(L"Test");
	m_pMode->SelectItem(2);

	pPanel->Add(m_pMode);

	//m_wndRibbonBar.AddToTabs(m_pMode);
	
	return true;
}

bool CMainFrame::InitializeStatusBar()
{
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return false;      // 만들지 못했습니다.
	}

	BOOL bNameValid;
	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	return true;
}

bool CMainFrame::InitializeDockPane()
{
	CString caption = L"Land Scape";
	DWORD dwstyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI;
	if (!m_LandScapeDockPane.Create(caption, this, CRect(0, 0, 200, 200), TRUE, ID_DOCKPANE_LANDSCAPE, dwstyle))
	{
		return false;
	}

	m_LandScapeDockPane.ShowPane(FALSE, FALSE, FALSE);
	m_LandScapeDockPane.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_LandScapeDockPane);
	m_LandScapeDockPane.ShowPane(TRUE, FALSE, TRUE);

	return true;
}
