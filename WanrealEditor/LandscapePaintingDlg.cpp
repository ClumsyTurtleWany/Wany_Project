// LandscapePaintingDlg.cpp: 구현 파일
//

#include "pch.h"
#include "WanrealEditor.h"
#include "LandscapePaintingDlg.h"
#include "afxdialogex.h"


// LandscapePaintingDlg 대화 상자

IMPLEMENT_DYNAMIC(LandscapePaintingDlg, CDialogEx)

LandscapePaintingDlg::LandscapePaintingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LandscapePaintingDlg, pParent)
{

}

LandscapePaintingDlg::~LandscapePaintingDlg()
{
}

void LandscapePaintingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LandscapePaintingDlg, CDialogEx)
END_MESSAGE_MAP()


// LandscapePaintingDlg 메시지 처리기
