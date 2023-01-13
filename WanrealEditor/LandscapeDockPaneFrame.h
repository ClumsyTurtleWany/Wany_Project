#pragma once


// LandscapeDockPaneFrame 프레임

class LandscapeDockPaneFrame : public CFrameWndEx
{
	DECLARE_DYNCREATE(LandscapeDockPaneFrame)
protected:
	LandscapeDockPaneFrame();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~LandscapeDockPaneFrame();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


