// probility.cpp: 구현 파일
//

#include "pch.h"
#include "BLACKJAK.h"
#include "probility.h"
#include "afxdialogex.h"


// probility 대화 상자

IMPLEMENT_DYNAMIC(probility, CDialogEx)

probility::probility(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

probility::~probility()
{
}

void probility::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, Probility);
}


BEGIN_MESSAGE_MAP(probility, CDialogEx)
END_MESSAGE_MAP()


// probility 메시지 처리기


BOOL probility::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	UpdateData(true);
	Probility.InsertColumn(0, _T("1장"), LVCFMT_CENTER, 110);
	Probility.InsertColumn(1, _T("확률"), LVCFMT_CENTER, 110);
	Probility.InsertColumn(2, _T("2장"), LVCFMT_CENTER, 110);
	Probility.InsertColumn(3, _T("확률"), LVCFMT_CENTER, 110);
	for(int i=0 ; i<20 ; i++)	Probility.InsertItem(i, _T(" "));
	Probility.SetItem(0, 0, LVIF_TEXT, _T("1의 확률"), 0, 0, 0, 0);
	Probility.SetItem(0, 1, LVIF_TEXT, _T("7.69%"), 0, 0, 0, 0);
	Probility.SetItem(1, 0, LVIF_TEXT, _T("2의 확률"), 0, 0, 0, 0);
	Probility.SetItem(1, 1, LVIF_TEXT, _T("7.69%"), 0, 0, 0, 0);
	Probility.SetItem(2, 0, LVIF_TEXT, _T("3의 확률"), 0, 0, 0, 0);
	Probility.SetItem(2, 1, LVIF_TEXT, _T("7.69%"), 0, 0, 0, 0);
	Probility.SetItem(3, 0, LVIF_TEXT, _T("4의 확률"), 0, 0, 0, 0);
	Probility.SetItem(3, 1, LVIF_TEXT, _T("7.69%"), 0, 0, 0, 0);
	Probility.SetItem(4, 0, LVIF_TEXT, _T("5의 확률"), 0, 0, 0, 0);
	Probility.SetItem(4, 1, LVIF_TEXT, _T("7.69%"), 0, 0, 0, 0);
	Probility.SetItem(5, 0, LVIF_TEXT, _T("6의 확률"), 0, 0, 0, 0);
	Probility.SetItem(5, 1, LVIF_TEXT, _T("7.69%"), 0, 0, 0, 0);
	Probility.SetItem(6, 0, LVIF_TEXT, _T("7의 확률"), 0, 0, 0, 0);
	Probility.SetItem(6, 1, LVIF_TEXT, _T("7.69%"), 0, 0, 0, 0);
	Probility.SetItem(7, 0, LVIF_TEXT, _T("8의 확률"), 0, 0, 0, 0);
	Probility.SetItem(7, 1, LVIF_TEXT, _T("7.69%"), 0, 0, 0, 0);
	Probility.SetItem(8, 0, LVIF_TEXT, _T("9의 확률"), 0, 0, 0, 0);
	Probility.SetItem(8, 1, LVIF_TEXT, _T("7.69%"), 0, 0, 0, 0);
	Probility.SetItem(9, 0, LVIF_TEXT, _T("10의 확률"), 0, 0, 0, 0);
	Probility.SetItem(9, 1, LVIF_TEXT, _T("30.77%"), 0, 0, 0, 0);

	Probility.SetItem(0, 2, LVIF_TEXT, _T("2의 확률"), 0, 0, 0, 0);
	Probility.SetItem(1, 2, LVIF_TEXT, _T("3의 확률"), 0, 0, 0, 0);
	Probility.SetItem(2, 2, LVIF_TEXT, _T("4의 확률"), 0, 0, 0, 0);
	Probility.SetItem(3, 2, LVIF_TEXT, _T("5의 확률"), 0, 0, 0, 0);
	Probility.SetItem(4, 2, LVIF_TEXT, _T("6의 확률"), 0, 0, 0, 0);
	Probility.SetItem(5, 2, LVIF_TEXT, _T("7의 확률"), 0, 0, 0, 0);
	Probility.SetItem(6, 2, LVIF_TEXT, _T("8의 확률"), 0, 0, 0, 0);
	Probility.SetItem(7, 2, LVIF_TEXT, _T("9의 확률"), 0, 0, 0, 0);
	Probility.SetItem(8, 2, LVIF_TEXT, _T("10의 확률"), 0, 0, 0, 0);
	Probility.SetItem(9, 2, LVIF_TEXT, _T("11의 확률"), 0, 0, 0, 0);
	Probility.SetItem(10, 2, LVIF_TEXT, _T("12의 확률"), 0, 0, 0, 0);
	Probility.SetItem(11, 2, LVIF_TEXT, _T("13의 확률"), 0, 0, 0, 0);
	Probility.SetItem(12, 2, LVIF_TEXT, _T("14의 확률"), 0, 0, 0, 0);
	Probility.SetItem(13, 2, LVIF_TEXT, _T("15의 확률"), 0, 0, 0, 0);
	Probility.SetItem(14, 2, LVIF_TEXT, _T("16의 확률"), 0, 0, 0, 0);
	Probility.SetItem(15, 2, LVIF_TEXT, _T("17의 확률"), 0, 0, 0, 0);
	Probility.SetItem(16, 2, LVIF_TEXT, _T("18의 확률"), 0, 0, 0, 0);
	Probility.SetItem(17, 2, LVIF_TEXT, _T("19의 확률"), 0, 0, 0, 0);
	Probility.SetItem(18, 2, LVIF_TEXT, _T("20의 확률"), 0, 0, 0, 0);
	Probility.SetItem(19, 2, LVIF_TEXT, _T("21의 확률"), 0, 0, 0, 0);

	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

int q = 0;
void probility::ReceiveText(CString str)
{
	// TODO: 여기에 구현 코드 추가.
	UpdateData(true);
	Probility.SetItem(q, 3, LVIF_TEXT, (LPCTSTR)str, 0, 0, 0, 0);
	q++;
	if (q >= 20) q = 0;
	UpdateData(false);
}
