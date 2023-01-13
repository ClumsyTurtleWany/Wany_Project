// LandscapeDockPaneFrame.cpp: 구현 파일
//

#include "pch.h"
#include "WanrealEditor.h"
#include "LandscapeDockPaneFrame.h"


// LandscapeDockPaneFrame

IMPLEMENT_DYNCREATE(LandscapeDockPaneFrame, CFrameWndEx)

LandscapeDockPaneFrame::LandscapeDockPaneFrame()
{

}

LandscapeDockPaneFrame::~LandscapeDockPaneFrame()
{
}


BEGIN_MESSAGE_MAP(LandscapeDockPaneFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// LandscapeDockPaneFrame 메시지 처리기


int LandscapeDockPaneFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


void LandscapeDockPaneFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWndEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
