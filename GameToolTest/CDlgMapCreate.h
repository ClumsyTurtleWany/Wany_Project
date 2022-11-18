#pragma once


// CDlgMapCreate 대화 상자

class CDlgMapCreate : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMapCreate)

public:
	CDlgMapCreate(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgMapCreate();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAP_CREATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CString CaptionSize;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CComboBox ComboCaptionSize;
};
