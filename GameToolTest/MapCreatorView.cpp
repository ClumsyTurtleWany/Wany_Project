﻿// MapCreatorView.cpp: 구현 파일
//

#include "pch.h"
#include "GameToolTest.h"
#include "MapCreatorView.h"


// MapCreatorView

IMPLEMENT_DYNAMIC(MapCreatorView, CDockablePane)

MapCreatorView::MapCreatorView()
{
}

MapCreatorView::~MapCreatorView()
{
}


BEGIN_MESSAGE_MAP(MapCreatorView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()



// MapCreatorView 메시지 처리기




int MapCreatorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CString TitleLabelName = L"Title Label";
	RECT TitleLabelPosition;
	TitleLabelPosition.left = this->GetPaneRect().left + 10;
	TitleLabelPosition.right = TitleLabelPosition.left + 100;
	TitleLabelPosition.top = this->GetPaneRect().top + 10;
	TitleLabelPosition.bottom = TitleLabelPosition.top + 100;
	if (!TitleLabel.Create(TitleLabelName, WS_CHILD | WS_VISIBLE | SS_LEFT, TitleLabelPosition, this, ID_STATIC_MAPCREATOR_LABEL))
	{
		int a = 0;
	}

	RECT EditBox1Position;
	EditBox1Position.left = TitleLabelPosition.left + 10;
	EditBox1Position.right = EditBox1Position.left + 50;
	EditBox1Position.top = TitleLabelPosition.top + 10;
	EditBox1Position.bottom = EditBox1Position.top + 20;
	if (!EditBox1.Create(WS_VISIBLE, EditBox1Position, TitleLabel.GetWindow(0), ID_EDIT_MAPCREATOR_WIDTH))
	{
		int a = 0;
	}
	

	return 0;
}


//void MapCreatorView::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
//					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
//					   // 그리기 메시지에 대해서는 CDockablePane::OnPaint()을(를) 호출하지 마십시오.
//
//	CRect DockPaneRect;
//	this->GetWindowRect(DockPaneRect);
//	CBrush br;
//	br.CreateSolidBrush(RGB(255, 255, 255));
//	dc.FillRect(DockPaneRect, &br);
//
//	CRect TitleLabelRect;
//	TitleLabel.GetWindowRect(TitleLabelRect);
//	ScreenToClient(TitleLabelRect);
//
//	TitleLabelRect.InflateRect(1, 1);
//	dc.Draw3dRect(TitleLabelRect, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
//}


void MapCreatorView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	AdjustLayout();
}
