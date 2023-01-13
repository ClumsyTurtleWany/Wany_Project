#pragma once


// LandscapePaintingDlg 대화 상자

class LandscapePaintingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LandscapePaintingDlg)

public:
	LandscapePaintingDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~LandscapePaintingDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LandscapePaintingDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
