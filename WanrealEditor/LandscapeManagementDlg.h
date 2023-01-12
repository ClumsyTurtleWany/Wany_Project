#pragma once


// LandscapeManagementDlg 대화 상자

class LandscapeManagementDlg : public CDialog
{
	DECLARE_DYNAMIC(LandscapeManagementDlg)

public:
	LandscapeManagementDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~LandscapeManagementDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LandscapeManagementDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
