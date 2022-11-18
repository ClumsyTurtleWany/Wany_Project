// CDlgMapCreate.cpp: 구현 파일
//

#include "pch.h"
#include "GameToolTest.h"
#include "CDlgMapCreate.h"
#include "afxdialogex.h"


// CDlgMapCreate 대화 상자

IMPLEMENT_DYNAMIC(CDlgMapCreate, CDialogEx)

CDlgMapCreate::CDlgMapCreate(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAP_CREATE, pParent)
	, CaptionSize(_T(""))
{

}

CDlgMapCreate::~CDlgMapCreate()
{
}

void CDlgMapCreate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MAP_CAPTION, CaptionSize);
	DDX_Control(pDX, IDC_COMBO_MAP_CAPTION, ComboCaptionSize);
}


BEGIN_MESSAGE_MAP(CDlgMapCreate, CDialogEx)
	//ON_UPDATE_COMMAND_UI(IDC_EDIT_MAP_CAPTION, CDlgMapCreate::)
	ON_BN_CLICKED(IDOK, &CDlgMapCreate::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgMapCreate 메시지 처리기


void CDlgMapCreate::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE); // 화면에 업데이트 된 값을 연결된 변수에 가져옴.(입력)

	int ComboIdx = ComboCaptionSize.GetCurSel();

	CDialogEx::OnOK();
}


BOOL CDlgMapCreate::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CaptionSize = L"123";

	ComboCaptionSize.AddString(L"1 X 1");
	ComboCaptionSize.AddString(L"2 X 2");
	ComboCaptionSize.AddString(L"4 X 4");
	ComboCaptionSize.SetCurSel(0);

	UpdateData(FALSE); // 연결된 변수 값을 화면에 업데이트.(출력)


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
