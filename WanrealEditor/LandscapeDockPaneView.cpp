// LandscapeDockPaneView.cpp: 구현 파일
//

#include "pch.h"
#include "WanrealEditor.h"
#include "LandscapeDockPaneView.h"


// LandscapeDockPaneView

IMPLEMENT_DYNCREATE(LandscapeDockPaneView, CFormView)

LandscapeDockPaneView::LandscapeDockPaneView()
	: CFormView(IDD_LandscapeDockPaneView)
{

}

LandscapeDockPaneView::~LandscapeDockPaneView()
{
}

void LandscapeDockPaneView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(LandscapeDockPaneView, CFormView)
END_MESSAGE_MAP()


// LandscapeDockPaneView 진단

#ifdef _DEBUG
void LandscapeDockPaneView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void LandscapeDockPaneView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// LandscapeDockPaneView 메시지 처리기
