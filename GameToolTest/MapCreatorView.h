#pragma once


// MapCreatorView

class MapCreatorView : public CDockablePane
{
	DECLARE_DYNAMIC(MapCreatorView)

public:
	MapCreatorView();
	virtual ~MapCreatorView();

protected:
	DECLARE_MESSAGE_MAP()

public:
	CStatic TitleLabel;
	CEdit	EditBox1;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

