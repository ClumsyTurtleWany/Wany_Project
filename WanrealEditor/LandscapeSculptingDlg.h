#pragma once


// LandscapeSculptingDlg 대화 상자

class LandscapeSculptingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LandscapeSculptingDlg)

public:
	LandscapeSculptingDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~LandscapeSculptingDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LandscapeSculptingDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
