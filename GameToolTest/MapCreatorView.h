#pragma once


// MapCreatorView

class MapCreatorView : public CDockablePane
{
	DECLARE_DYNAMIC(MapCreatorView)

public:
	MapCreatorView();
	virtual ~MapCreatorView();

protected:
	CStatic TitleLabel;
	CEdit	EditBox1;

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};


