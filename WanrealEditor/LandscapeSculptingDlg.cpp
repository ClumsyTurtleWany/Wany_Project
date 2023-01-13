// LandscapeSculptingDlg.cpp: 구현 파일
//

#include "pch.h"
#include "WanrealEditor.h"
#include "LandscapeSculptingDlg.h"
#include "afxdialogex.h"


// LandscapeSculptingDlg 대화 상자

IMPLEMENT_DYNAMIC(LandscapeSculptingDlg, CDialogEx)

LandscapeSculptingDlg::LandscapeSculptingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LandscapeSculptingDlg, pParent)
{

}

LandscapeSculptingDlg::~LandscapeSculptingDlg()
{
}

void LandscapeSculptingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LandscapeSculptingDlg, CDialogEx)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// LandscapeSculptingDlg 메시지 처리기


int LandscapeSculptingDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


void LandscapeSculptingDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
