// LandscapeManagementDlg.cpp: 구현 파일
//

#include "pch.h"
#include "WanrealEditor.h"
#include "LandscapeManagementDlg.h"
#include "afxdialogex.h"


// LandscapeManagementDlg 대화 상자

IMPLEMENT_DYNAMIC(LandscapeManagementDlg, CDialogEx)

LandscapeManagementDlg::LandscapeManagementDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LandscapeManagementDlg, pParent)
{

}

LandscapeManagementDlg::~LandscapeManagementDlg()
{
}

void LandscapeManagementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LandscapeManagementDlg, CDialogEx)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// LandscapeManagementDlg 메시지 처리기


int LandscapeManagementDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CRect rectTab;
	this->GetWindowRect(rectTab);
	ScreenToClient(rectTab);
	if (!m_TabCtrl.Create(CMFCTabCtrl::STYLE_3D_ROUNDED, rectTab, this, 1, CMFCTabCtrl::LOCATION_TOP))
	{
		return -1;
	}

	if (!m_LandscapeManagementAddDlg.Create(IDD_LandscapeManagementAddDlg, &m_TabCtrl))
	{
		return -1;
	}
	m_LandscapeManagementAddDlg.ShowWindow(SW_SHOW);

	m_TabCtrl.AddTab(&m_LandscapeManagementAddDlg, L"Add", 0, FALSE);

	return 0;
}


void LandscapeManagementDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
