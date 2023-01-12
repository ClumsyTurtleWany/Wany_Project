// LandscapeManagementDlg.cpp: 구현 파일
//

#include "pch.h"
#include "WanrealEditor.h"
#include "LandscapeManagementDlg.h"
#include "afxdialogex.h"


// LandscapeManagementDlg 대화 상자

IMPLEMENT_DYNAMIC(LandscapeManagementDlg, CDialog)

LandscapeManagementDlg::LandscapeManagementDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_LandscapeManagementDlg, pParent)
{

}

LandscapeManagementDlg::~LandscapeManagementDlg()
{
}

void LandscapeManagementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LandscapeManagementDlg, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// LandscapeManagementDlg 메시지 처리기


void LandscapeManagementDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
