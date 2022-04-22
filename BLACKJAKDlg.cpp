
// BLACKJAKDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "BLACKJAK.h"
#include "BLACKJAKDlg.h"
#include "afxdialogex.h"
#include "Card.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <cstdio>
#include "probility.h"
#ifdef _DEBUG
#define new DEBUG_NEW

#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
Card card[52];
int Mymoney = 1000; // 초기 돈
int Betting_Money = 0; // 베팅 된 금액
int Card_sum = 0;  // 카드의 합 (A 가 1일때)
int Dealer_Card_Sum = 0; // 딜러 카드의 합 (A가 1일때)
int Card_sum2 = 0;//카드의 합 (A가 11일때)
int Dealer_Card_Sum2 = 0; // 딜러 카드의 합(A가 11일때)
int Card_Split_Sum;  // 스플릿카드의 합 (A가 1일때)
int Card_Split_Sum2;// 스플릿카드의 합(A가 11일때)
int Split_state = 0;// 스플릿 상태의 판별
int controlnumber = 0; // 버튼 컨트롤 하는 값
CString Card_image;  // 카드 이미지를 올리기 위한 변수
CString Card_Split_image;//스플릿 경우 카드 이미지 올리기 위한 변수
CString Dealer_Card_image; // 딜러 카드의 이미지
int DealerNumber = 0;
int PlayerNumber = 0;
int Stoi(CString str, int number)
{
	number = _ttoi(str);
	return number;
}
CString Itos(int number, CString str)
{
	CString cstr;
	cstr.Format(_T("%d"), number);
	return cstr;
}

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBLACKJAKDlg 대화 상자



CBLACKJAKDlg::CBLACKJAKDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BLACKJAK_DIALOG, pParent)
	, Bet_Money(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	Result = 0;
	//  Probability = 0.0f;
	Result1 = 0;
	Result3 = 1;
}

void CBLACKJAKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Bet_Money);
	DDX_Control(pDX, IDC_Information, BettingInformation);
	DDX_Control(pDX, IDC_CardImage, Card_Image);
	DDX_Control(pDX, IDC_Sum, Sum);
	//  DDX_Control(pDX, IDC_DealerCard, DealerCard);
	DDX_Control(pDX, IDC_DealerSum, DealerSum);
	DDX_Control(pDX, IDC_SplitSum, SplitSum);
	DDX_Control(pDX, IDC_DealerImage, m_DealerImage);
	DDX_Control(pDX, IDC_DealerImage2, m_DealerImage2);
	DDX_Control(pDX, IDC_PlayerImage, m_PlayerImage);
	DDX_Control(pDX, IDC_PlayerImage2, m_PlayerImage2);
	DDX_Control(pDX, IDC_DealerImage3, m_DealerImage3);
	DDX_Control(pDX, IDC_PlayerImage3, m_PlayerImage3);
	DDX_Control(pDX, IDC_PlayerImage4, m_PlayerImage4);
	DDX_Control(pDX, IDC_PlayerImage5, m_PlayerImage5);
	DDX_Control(pDX, IDC_DealerImage4, m_DealerImage4);
	DDX_Control(pDX, IDC_DealerImage5, m_DealerImage5);
}

BEGIN_MESSAGE_MAP(CBLACKJAKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CBLACKJAKDlg::OnBnClickedGAMESTART)
//	ON_COMMAND(IDC_STATIC, &CBLACKJAKDlg::OnStatic)
	ON_BN_CLICKED(IDC_BUTTON2, &CBLACKJAKDlg::OnClickedBettingButton)
	ON_BN_CLICKED(IDC_BUTTON1, &CBLACKJAKDlg::OnClickedHit)
	ON_BN_CLICKED(IDC_BUTTON3, &CBLACKJAKDlg::OnClickedStand)
ON_BN_CLICKED(IDC_BUTTON4, &CBLACKJAKDlg::OnClickedDealerHIT)
ON_BN_CLICKED(IDC_BUTTON5, &CBLACKJAKDlg::OnClickedDealerStand)
ON_BN_CLICKED(IDC_BUTTON6, &CBLACKJAKDlg::OnClickedPlayerDouble)
ON_BN_CLICKED(IDC_BUTTON7, &CBLACKJAKDlg::OnClickedPlayerSplrit)
ON_BN_CLICKED(IDC_BUTTON10, &CBLACKJAKDlg::OnClickedPlayerSplitHit)
ON_BN_CLICKED(IDC_BUTTON11, &CBLACKJAKDlg::OnClickedPlayerSplitStand)
ON_BN_CLICKED(IDC_BUTTON8, &CBLACKJAKDlg::OnBnClickedButton8)
//ON_STN_CLICKED(IDC_CardImage, &CBLACKJAKDlg::OnStnClickedCardimage)
END_MESSAGE_MAP()


// CBLACKJAKDlg 메시지 처리기

BOOL CBLACKJAKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SetDlgItemText(IDC_Information,_T("블랙잭에 오신걸 환영합니다.\n 최소배팅 금액은 100원입니다."));
	
	int k = 0;
	ButtonControl("");
	for (int i = 0; i < 13; i++)  // 카드의 52장에 대해 그림과 속성을 부여한다.
	{

		for (int j = 0; j < 4; j++)
		{
			if (i == 0)card[k].number = "A";
			else if (i == 1)card[k].number = "2";
			else if (i == 2)card[k].number = "3";
			else if (i == 3)card[k].number = "4";
			else if (i == 4)card[k].number = "5";
			else if (i == 5)card[k].number = "6";
			else if (i == 6)card[k].number = "7";
			else if (i == 7)card[k].number = "8";
			else if (i == 8)card[k].number = "9";
			else if (i == 9)card[k].number = "10";
			else if (i == 10)card[k].number = "J";
			else if (i == 11)card[k].number = "Q";
			else if (i == 12)card[k].number = "K";
			if (j == 0)	card[k].Shape = "♠";
			else if (j == 1)	card[k].Shape = "♣";
			else if (j == 2)	card[k].Shape = "◆";
			else if (j == 3) card[k].Shape = "♥";

			k++;
		}
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CBLACKJAKDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CBLACKJAKDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CBLACKJAKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBLACKJAKDlg::initialization()	// 각종 변수 초기화
{
	// TODO: 여기에 구현 코드 추가.
	Result =0;
	Result1 = 0;
	Result3 = 1;
	Card_sum = 0;
	Card_sum2 = 0;
	Dealer_Card_Sum = 0;
	Dealer_Card_Sum2 = 0;
	Card_image = " ";
	Card_Split_image = " ";
	Dealer_Card_image = " ";
	controlnumber = 0;
	ButtonControl("");
	Split_state = 0;
	 DealerNumber = 0;
	 PlayerNumber = 0;

}
void CBLACKJAKDlg::OnBnClickedGAMESTART() // 시작과 동시에 카드 2장씩을 랜덤으로 받는다.
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CStatic*)GetDlgItem(IDC_PlayerImage))->SetBitmap(0);
	((CStatic*)GetDlgItem(IDC_PlayerImage2))->SetBitmap(0);
	((CStatic*)GetDlgItem(IDC_PlayerImage3))->SetBitmap(0);
	((CStatic*)GetDlgItem(IDC_PlayerImage4))->SetBitmap(0);
	((CStatic*)GetDlgItem(IDC_PlayerImage5))->SetBitmap(0);
	((CStatic*)GetDlgItem(IDC_DealerImage))->SetBitmap(0);
	((CStatic*)GetDlgItem(IDC_DealerImage2))->SetBitmap(0);
	((CStatic*)GetDlgItem(IDC_DealerImage3))->SetBitmap(0);
	((CStatic*)GetDlgItem(IDC_DealerImage4))->SetBitmap(0);
	((CStatic*)GetDlgItem(IDC_DealerImage5))->SetBitmap(0);

	ButtonControl("on23456");
	srand(time(NULL));
	PlayerProcess();
	Sleep(1000);
	DealerProcess();
	Sleep(1000);
	PlayerProcess();
	Sleep(1000);
	DealerProcess();
}
//void CBLACKJAKDlg::OnStatic()
//{
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//
//
//}
void CBLACKJAKDlg::OnClickedBettingButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(true);
	
	if (Bet_Money >= 100)
	{
		Mymoney -= Bet_Money;
		Betting_Money += Bet_Money;
		Bet_Money = 0;
	}
	CString cstr;
	cstr = Itos(Mymoney, cstr);
	SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
	UpdateData(false);
	if (Betting_Money >= 100)  	//베팅머니가 100원 이상일 때 시작 할 수 있다.
	{
		ButtonControl("on1");
	}
}
void CBLACKJAKDlg::PlayerProcess()
{
	// TODO: 여기에 구현 코드 추가.
	srand(time(NULL));// 카드 52장 중에 랜덤으로 받기 위해 사용
	int index = rand() % 52;
	int Card_Number = 0;

	Card_Number = Stoi(card[index].number, Card_Number);
	if (card[index].number == "J" || card[index].number == "K" || card[index].number == "Q")  // J,K,Q 는 숫자 10으로 사용한다.
	{
		Card_Number = 10;
	}
	if (card[index].number == "A")  // A의 1 또는 11을 적용하기 위해 변수를 하나 더 지정하고 각각에 변수에 다른 값을 넣어 표현
	{
		Card_sum += 1;
		Card_sum2 += 11;
	}
	if (Card_sum == Card_Number) // 스플릿이 될때 조건
	{
		ButtonControl("on7");
	}


	if (Split_state == 0)  // 숫자가 21이 넘어가면 패배(스플릿이 없는 경우)
	{
		if (Card_sum > 21) Lose();
	}

	if (Split_state == 1)// 숫자가 21이 넘어가면 패배(스플릿이 있는 경우)
	{
		if (Card_sum > 21)
		{
			ButtonControl("off2");
			int* Result_pointer = &Result;
			*Result_pointer = 1;
		}

	}


	Card_sum += Card_Number;
	Card_sum2 += Card_Number;

	CardImageInSert2(card[index].number, card[index].Shape);

	// 출력을 위해 CString 으로 변환.
	CString Card_Sum_Print;
	Card_Sum_Print = Itos(Card_sum, Card_Sum_Print);  // int를 CString 으로 변환하기 위해 사용
	CString Card_Sum_Print2;
	Card_Sum_Print2 = Itos(Card_sum2, Card_Sum_Print2);
	CString Card_Split_Sum_Print;
	Card_Split_Sum_Print = Itos(Card_Split_Sum, Card_Split_Sum_Print);
	CString Card_Split_Sum_Print2;
	Card_Split_Sum_Print2 = Itos(Card_Split_Sum2, Card_Split_Sum_Print2);
	CString cstr;
	cstr = Itos(Mymoney, cstr);
	if (Split_state == 0) // 스플릿이 없는 경우
	{
		if (Card_sum2 > 21) // a의 변수로 인해 Card_sum2가 21이 넘어가는 경우에는 하나의 경우만 보이게 설정하였다.
		{
			SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
			SetDlgItemText(IDC_CardImage, Card_image);
			SetDlgItemText(IDC_Sum, _T("PLAYER 현재 합계 :") + Card_Sum_Print);
		}
		else if (Card_sum2 <= 21)
		{
			SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
			SetDlgItemText(IDC_CardImage, Card_image);
			SetDlgItemText(IDC_Sum, _T("PLAYER 현재 합계 :") + Card_Sum_Print + _T("or") + Card_Sum_Print2);
		}
	}
	else if (Split_state == 1) // 스플릿이 있는 경우
	{
		if (Card_sum2 > 21) // a의 변수로 인해 Card_sum2가 21이 넘어가는 경우에는 하나의 경우만 보이게 설정하였다.
		{
			SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
			SetDlgItemText(IDC_CardImage, Card_image);
			SetDlgItemText(IDC_Sum, _T("PLAYER 현재 합계 :") + Card_Sum_Print);
		}
		else if (Card_sum2 <= 21)
		{
			SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
			SetDlgItemText(IDC_CardImage, Card_image);
			SetDlgItemText(IDC_Sum, _T("PLAYER 현재 합계 :") + Card_Sum_Print + _T("or") + Card_Sum_Print2);
		}
		if (Card_Split_Sum2 > 21)// 스플릿이 있는 경우에도 추가한다.
		{
			SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
			SetDlgItemText(IDC_CardImage, Card_image + _T("\n") + Card_Split_image);
			SetDlgItemText(IDC_Sum, _T("PLAYER 현재 합계 :") + Card_Sum_Print + _T("or") + Card_Sum_Print2 );
			SetDlgItemText(IDC_SplitSum, _T("PLAYER 현재 합계 :") + Card_Split_Sum_Print);
		}
		else if (Card_Split_Sum2 <= 21)
		{
			SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
			SetDlgItemText(IDC_CardImage, Card_image + _T("\n") + Card_Split_image);
			SetDlgItemText(IDC_Sum, _T("PLAYER 현재 합계 :") + Card_Sum_Print + _T("or") + Card_Sum_Print2 );
			SetDlgItemText(IDC_SplitSum, _T("PLAYER 현재 합계 :") + Card_Split_Sum_Print + _T("or") + Card_Split_Sum_Print2);
		}
		if (Card_Split_Sum2 > 21 && Card_sum2 > 21) // 둘다 넘는 경우를 추가한다.
		{
			SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
			SetDlgItemText(IDC_CardImage, Card_image + _T("\n") + Card_Split_image);
			SetDlgItemText(IDC_Sum, _T("PLAYER 현재 합계 :") + Card_Sum_Print );
			SetDlgItemText(IDC_SplitSum, _T("PLAYER 현재 합계 :") + Card_Split_Sum_Print);
		}
	}
}
void CBLACKJAKDlg::DealerProcess()
{
	// TODO: 여기에 구현 코드 추가.
	srand(time(NULL));
	int Dealerindex = rand() % 52;
	int Dealer_Card_Number = 0;
	Dealer_Card_Number = Stoi(card[Dealerindex].number, Dealer_Card_Number);
	if (card[Dealerindex].number == "J" || card[Dealerindex].number == "K" || card[Dealerindex].number == "Q")
	{
		Dealer_Card_Number = 10;
	}
	if (card[Dealerindex].number == "A")
	{
		Dealer_Card_Sum += 1;
		Dealer_Card_Sum2 += 11;
	}
	Dealer_Card_Sum += Dealer_Card_Number;
	Dealer_Card_Sum2 += Dealer_Card_Number;
	

	CardImageInsert(card[Dealerindex].number, card[Dealerindex].Shape);

	CString cstr;
	cstr = Itos(Mymoney, cstr);
	CString Card_Sum_Print;
	Card_Sum_Print = Itos(Dealer_Card_Sum, Card_Sum_Print);
	CString Card_Sum_Print2;
	Card_Sum_Print2 = Itos(Dealer_Card_Sum2, Card_Sum_Print2);

	if (Dealer_Card_Sum2 > 21)
	{
		SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
		SetDlgItemText(IDC_DealerCard, Dealer_Card_image);
		SetDlgItemText(IDC_DealerSum, _T("Dealer 현재 합계 :") + Card_Sum_Print);
	}
	else if (Dealer_Card_Sum2 <= 21)
	{
		SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
		SetDlgItemText(IDC_DealerCard, Dealer_Card_image);
		SetDlgItemText(IDC_DealerSum, _T("PLAYER 현재 합계 :") + Card_Sum_Print + _T("or") + Card_Sum_Print2);
	}
}
void CBLACKJAKDlg::OnClickedHit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	PlayerProcess();//플레이어 카드 함수
	if (Split_state == 0) // 스플릿이 없는 경우
	{
		if (Card_sum > 21)  // 숫자의 합이 21이 넘어가는 경우 패배한다.
		{
			Lose();
		}
	}
	if (Split_state == 1) // 스플릿이 있는 경우에는 버튼이 눌러지지 않게 한다. 패배처리하면 하나만 져도 바로 게임이 끝나기에 하지 않는다.
	{
		if (Card_sum > 21)
		{
			ButtonControl("off2");
			SetDlgItemText(IDC_Sum, _T("패배하였습니다."));
		}
	}
}
void CBLACKJAKDlg::OnClickedStand()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (Card_sum2 <= 21) Card_sum = Card_sum2; // Card_sum2 가 21보다 작은 경우 자동으로 21근처인 Card_sum2를 선택한다.

	Result = 1;
	ButtonControl("off23");
	if (Split_state == 0)
	{
		if (Result == 1 && Result1 == 1 && Result3 == 1) // 모두가 스탠드를 눌러야지 계산되게 하기 위해 사용
		{
			if (Dealer_Card_Sum < Card_sum)
			{
				Win();
			}
			else if (Dealer_Card_Sum > Card_sum)
			{
				Lose();
			}
			else if (Dealer_Card_Sum == Card_sum)
			{
				Draw();
			}
		}
	}
	if (Split_state == 1)
	{
		if (Result == 1 && Result1 == 1 && Result3 == 1) // 모두가 스탠드를 눌러야지 계산되게 하기 위해 사용
		{
			// 각각의 승리조건을 만든 다음 변수에 값을 넣어서 저장하여 승부를 계산
			int state = 0;
			int split_state = 0;
			if ((Dealer_Card_Sum < Card_sum && Card_sum <= 21) || Dealer_Card_Sum > 21) // 승리 조건
			{
				state = 1;
			}
			else if (Dealer_Card_Sum == Card_sum) // 무승부 조건
			{
				state = 2;
			}
			else if ((Dealer_Card_Sum > Card_sum && Dealer_Card_Sum <= 21) || Card_sum > 21) // 패배 조건
			{
				state = 3;
			}

			if ((Dealer_Card_Sum < Card_Split_Sum && Card_Split_Sum <= 21) || Dealer_Card_Sum > 21) // 승리 조건
			{
				split_state = 1;
			}
			else if (Dealer_Card_Sum == Card_Split_Sum) // 무승부 조건
			{
				split_state = 2;
			}
			else if ((Dealer_Card_Sum > Card_Split_Sum && Dealer_Card_Sum <= 21) || Card_Split_Sum > 21) // 패배 조건
			{
				split_state = 3;
			}
			if (state == 1 && split_state == 1) // 숫자가 21보다 작거나 같면서 딜러보다 커야함
			{
				Win();
			}
			else if (state == 3 && split_state == 3)
			{
				Lose();
			}
			else if (state == 1 && split_state == 2) // 승부 조건값과 돈과 멘트가 맞지 않기 때문에 함수를 사용하지 않는다.
			{
				UpdateData(true);
				SetDlgItemText(IDC_Sum, _T("비겼습니다.\n 최소 배팅 금액은 100원입니다."));
				SetDlgItemText(IDC_SplitSum, _T(" 패배하였습니다."));
				Mymoney += (Betting_Money * 0.5);
				Betting_Money = 0;
				CString cstr;
				cstr = Itos(Mymoney, cstr);
				SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
				initialization();

				UpdateData(false);
			}
			else if (state == 2 && split_state == 1)
			{
				UpdateData(true);
				SetDlgItemText(IDC_Sum, _T("패배하였습니다.\n 최소 배팅 금액은 100원입니다."));
				SetDlgItemText(IDC_SplitSum, _T(" 비겼습니다."));
				Mymoney += (Betting_Money * 0.5);
				Betting_Money = 0;
				CString cstr;
				cstr = Itos(Mymoney, cstr);
				SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
				initialization();
				UpdateData(false);
			}
			else if (state == 3 && split_state == 2)
			{
				UpdateData(true);
				SetDlgItemText(IDC_Sum, _T("비겼습니다.\n 최소 배팅 금액은 100원입니다."));
				SetDlgItemText(IDC_SplitSum, _T(" 승리하였습니다. 베팅 금액 2배를 얻습니다."));
				Mymoney += (Betting_Money * 1.5);
				Betting_Money = 0;
				CString cstr;
				cstr = Itos(Mymoney, cstr);
				SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
				initialization();
				UpdateData(false);
			}
			else if (state == 2 && split_state == 3)
			{
				UpdateData(true);
				SetDlgItemText(IDC_Sum, _T("승리하였습니다. 베팅 금액 2배를 얻습니다.\n 최소 배팅 금액은 100원입니다."));
				SetDlgItemText(IDC_SplitSum, _T(" 비겼습니다."));
				Mymoney += (Betting_Money * 1.5);
				Betting_Money = 0;
				CString cstr;
				cstr = Itos(Mymoney, cstr);
				SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
				initialization();
				UpdateData(false);
			}

			else
			{
				Draw();
			}
		}
	}


	

}
void CBLACKJAKDlg::Win()
{
	// TODO: 여기에 구현 코드 추가.
	UpdateData(true);
	if (Split_state == 0) 
	{
		SetDlgItemText(IDC_Sum, _T("승리하였습니다. 베팅 금액 2배를 얻습니다.\n 최소 배팅 금액은 100원입니다."));
		Mymoney += (Betting_Money * 2); // 배팅 금액의 2배로 설정
		Betting_Money = 0;
		CString cstr;
		cstr = Itos(Mymoney, cstr);
		SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
		controlnumber = 0; 
		ButtonControl("");// 모든 버튼을 초기화 시킨다.
	}
	if (Split_state == 1)
	{
		SetDlgItemText(IDC_Sum, _T("승리하였습니다. 베팅 금액 2배를 얻습니다.\n 최소 배팅 금액은 100원입니다."));
		SetDlgItemText(IDC_SplitSum, _T(" "));
		Mymoney += (Betting_Money * 2);
		Betting_Money = 0;
		CString cstr;
		cstr = Itos(Mymoney, cstr);
		SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
		controlnumber = 0;
		ButtonControl("");
	}
	initialization();
	UpdateData(false);

	
}
void CBLACKJAKDlg::Draw()
{
	// TODO: 여기에 구현 코드 추가.
	UpdateData(true);
	SetDlgItemText(IDC_Sum, _T("무승부입니다.\n 최소 배팅 금액은 100원입니다."));
	SetDlgItemText(IDC_SplitSum, _T(" "));
	Mymoney += Betting_Money;// 무승부 인 경우 다시 돈을 돌려주기 위해 사용
	Betting_Money = 0;
	CString cstr;
	cstr = Itos(Mymoney, cstr);
	SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
	initialization();
	UpdateData(false);
}
void CBLACKJAKDlg::Lose()
{
	// TODO: 여기에 구현 코드 추가.
	UpdateData(true);
	SetDlgItemText(IDC_Sum, _T("패배하였습니다. 베팅 금액을 회수하겠습니다.\n 최소 배팅 금액은 100원입니다."));
	SetDlgItemText(IDC_SplitSum, _T(" "));
	controlnumber = 0;
	ButtonControl("");
	Betting_Money = 0; // 베팅 금액을 초기화한다.
	CString cstr;
	cstr = Itos(Mymoney, cstr);
	SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
	initialization();
	UpdateData(false);
}
void CBLACKJAKDlg::OnClickedDealerHIT()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DealerProcess(); //딜러 카드함수
	if (Dealer_Card_Sum > 21)
	{
		Win();
	}


}
void CBLACKJAKDlg::OnClickedDealerStand()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (Dealer_Card_Sum2 <= 21) Dealer_Card_Sum = Dealer_Card_Sum2;

	Result1 = 1;


	ButtonControl("off45");
	if (Split_state == 0)
	{
		if (Result == 1 && Result1 == 1 && Result3 == 1)
		{
			if (Dealer_Card_Sum < Card_sum)
			{
				Win();
			}
			else if (Dealer_Card_Sum > Card_sum)
			{
				Lose();
			}
			else if (Dealer_Card_Sum == Card_sum)
			{
				Draw();
			}
		}
	}
	else if (Split_state == 1)
	{
		if (Result == 1 && Result1 == 1 && Result3 == 1) // 모두가 스탠드를 눌러야지 계산되게 하기 위해 사용
		{
		
			int state = 0;
			int split_state = 0;
			if ((Dealer_Card_Sum < Card_sum && Card_sum <= 21) || Dealer_Card_Sum > 21) // 승리 조건
			{
				state = 1;
			}
			else if (Dealer_Card_Sum == Card_sum) // 무승부 조건
			{
				state = 2;
			}
			else if ((Dealer_Card_Sum > Card_sum && Dealer_Card_Sum <= 21) || Card_sum > 21) // 패배 조건
			{
				state = 3;
			}

			if ((Dealer_Card_Sum < Card_Split_Sum && Card_Split_Sum <= 21) || Dealer_Card_Sum > 21) // 승리 조건
			{
				split_state = 1;
			}
			else if (Dealer_Card_Sum == Card_Split_Sum) // 무승부 조건
			{
				split_state = 2;
			}
			else if ((Dealer_Card_Sum > Card_Split_Sum && Dealer_Card_Sum <= 21) || Card_Split_Sum > 21) // 패배 조건
			{
				split_state = 3;
			}

			if (state == 1 && split_state == 1) // 각각 스플릿 승부의 조건
			{
				Win();
			}
			else if (state == 3 && split_state == 3)
			{
				Lose();
			}
			else if (state == 1 && split_state == 2)
			{
				UpdateData(true);
				SetDlgItemText(IDC_Sum, _T("비겼습니다.\n 최소 배팅 금액은 100원입니다."));
				SetDlgItemText(IDC_SplitSum, _T(" 패배하였습니다."));
				Mymoney += (Betting_Money * 0.5);
				Betting_Money = 0;
				CString cstr;
				cstr = Itos(Mymoney, cstr);
				SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
				initialization();

				UpdateData(false);
			}
			else if (state == 2 && split_state == 1)
			{
				UpdateData(true);
				SetDlgItemText(IDC_Sum, _T("패배하였습니다.\n 최소 배팅 금액은 100원입니다."));
				SetDlgItemText(IDC_SplitSum, _T(" 비겼습니다."));
				Mymoney += (Betting_Money * 0.5);
				Betting_Money = 0;
				CString cstr;
				cstr = Itos(Mymoney, cstr);
				SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
				initialization();
				UpdateData(false);
			}
			else if (state == 3 && split_state == 2)
			{
				UpdateData(true);
				SetDlgItemText(IDC_Sum, _T("비겼습니다.\n 최소 배팅 금액은 100원입니다."));
				SetDlgItemText(IDC_SplitSum, _T(" 승리하였습니다. 베팅 금액 2배를 얻습니다."));
				Mymoney += (Betting_Money * 1.5);
				Betting_Money = 0;
				CString cstr;
				cstr = Itos(Mymoney, cstr);
				SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
				initialization();
				UpdateData(false);
			}
			else if (state == 2 && split_state == 3)
			{
				UpdateData(true);
				SetDlgItemText(IDC_Sum, _T("승리하였습니다. 베팅 금액 2배를 얻습니다.\n 최소 배팅 금액은 100원입니다."));
				SetDlgItemText(IDC_SplitSum, _T(" 비겼습니다."));
				Mymoney += (Betting_Money * 1.5);
				Betting_Money = 0;
				CString cstr;
				cstr = Itos(Mymoney, cstr);
				SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
				initialization();
				UpdateData(false);
			}
			else
			{
				Draw();
			}
		}
	}

}
void CBLACKJAKDlg::OnClickedPlayerDouble() // 카드 한장만 추가로 받는 대신에 배팅 금액을 2배로 건다.
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	Mymoney -= Betting_Money;
	Betting_Money *= 2;
	ButtonControl("off236");
	CString cstr;
	cstr = Itos(Mymoney, cstr);
	SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
	PlayerProcess();
	UpdateData(false);
}
void CBLACKJAKDlg::OnClickedPlayerSplrit() //같은 카드가 나왔을 때 각각 카드를 나누어 승부한다.
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Split_state = 1;
	ButtonControl("off7"); // 스플릿 버튼 비활성화
	ButtonControl("on89"); // 스플릿 히트 스탠드를 활성화.
	Card_sum /= 2;
	Card_sum2 /= 2;
	Card_Split_Sum = Card_sum;
	Card_Split_Sum2 = Card_sum2;
	CString temp;
	temp += Card_image[0];
	temp += Card_image[1];
	Card_Split_image += Card_image[2];
	Card_Split_image += Card_image[3];
	Mymoney -= Betting_Money;
	Betting_Money *= 2;
	Card_image = temp;
	// 카드의 속성을 나누어 저장한다.
	CString cstr;
	cstr = Itos(Mymoney, cstr);
	CString Card_Sum_Print;
	Card_Sum_Print = Itos(Card_Split_Sum, Card_Sum_Print);
	CString Card_Sum_Print2;
	Card_Sum_Print2 = Itos(Card_sum2, Card_Sum_Print2);
	CString Card_Split_Sum_Print;
	Card_Split_Sum_Print = Itos(Card_Split_Sum, Card_Split_Sum_Print);
	CString Card_Split_Sum_Print2;
	Card_Split_Sum_Print2 = Itos(Card_Split_Sum2, Card_Split_Sum_Print2);
	SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
	SetDlgItemText(IDC_Sum, _T("PLAYER 현재 합계 :") + Card_Sum_Print+ _T("or") + Card_Sum_Print2 );
	SetDlgItemText(IDC_SplitSum, _T("PLAYER 현재 합계 :") + Card_Split_Sum_Print + _T("or") + Card_Split_Sum_Print2);
	SetDlgItemText(IDC_CardImage, Card_image + _T("\n") + Card_Split_image);
	Result3 = 0; // Result3 값을 0으로 하여 결과값이 안나오게 만듬

}
void CBLACKJAKDlg::ButtonControl(char Find_Number[14])
{
	// TODO: 여기에 구현 코드 추가.
	// 처음에는 문자열에서 찾아서 버튼을 끄는 경우로 만들었으나 하나씩 컨트롤 하는 경우가 쉬워
	// 버튼 컨트롤이라는 변수를 비트처럼 활용하여 버튼 하나만 조작하여 할 수 있게 적용

	if (strstr(Find_Number, "on"))
	{
		for (int i = 1; i < 10; i++)
		{
			if(strchr(Find_Number, i+48))
				controlnumber |= (1 << i-1);
		}


	}
	else if (strstr(Find_Number, "off"))
	{
		for (int i = 1; i < 10; i++)
		{
			if (strchr(Find_Number, i + 48))
				controlnumber &= ~(1 << i - 1);
		}
	}
	if (controlnumber & 0x01)
	{
		CButton* pBtn = (CButton*)GetDlgItem(IDOK);
		pBtn->EnableWindow(true);
	}
	else
	{
		CButton* pBtn = (CButton*)GetDlgItem(IDOK);
		pBtn->EnableWindow(false);
	}
	if (controlnumber & 0x02)
	{
		CButton* pBtn2 = (CButton*)GetDlgItem(IDC_BUTTON1);
		pBtn2->EnableWindow(true);
	}
	else
	{
		CButton* pBtn2 = (CButton*)GetDlgItem(IDC_BUTTON1);
		pBtn2->EnableWindow(false);
	}
	if (controlnumber & 0x04)
	{
		CButton* pBtn3 = (CButton*)GetDlgItem(IDC_BUTTON3);
		pBtn3->EnableWindow(true);
	}
	else
	{
		CButton* pBtn3 = (CButton*)GetDlgItem(IDC_BUTTON3);
		pBtn3->EnableWindow(false);
	}
	if (controlnumber & 0x08)
	{
		CButton* pBtn4 = (CButton*)GetDlgItem(IDC_BUTTON4);
		pBtn4->EnableWindow(true);
	}
	else
	{
		CButton* pBtn4 = (CButton*)GetDlgItem(IDC_BUTTON4);
		pBtn4->EnableWindow(false);
	}
	if (controlnumber & 0x10)
	{
		CButton* pBtn5 = (CButton*)GetDlgItem(IDC_BUTTON5);
		pBtn5->EnableWindow(true);
	}
	else
	{
		CButton* pBtn5 = (CButton*)GetDlgItem(IDC_BUTTON5);
		pBtn5->EnableWindow(false);
	}
	if (controlnumber & 0x20)
	{
		CButton* pBtn6 = (CButton*)GetDlgItem(IDC_BUTTON6);
		pBtn6->EnableWindow(true);
	}
	else
	{
		CButton* pBtn6 = (CButton*)GetDlgItem(IDC_BUTTON6);
		 pBtn6->EnableWindow(false);
	}
	if (controlnumber & 0x40)
	{
		CButton* pBtn7 = (CButton*)GetDlgItem(IDC_BUTTON7);
		pBtn7->EnableWindow(true);
	}
	else
	{
		CButton* pBtn7 = (CButton*)GetDlgItem(IDC_BUTTON7);
		pBtn7->EnableWindow(false);
	}
	if (controlnumber & 0x80)
	{
		CButton* pBtn10 = (CButton*)GetDlgItem(IDC_BUTTON10);
		pBtn10->EnableWindow(true);
	}
	else
	{
		CButton* pBtn10 = (CButton*)GetDlgItem(IDC_BUTTON10);
		pBtn10->EnableWindow(false);
	}
	if (controlnumber & 0x100)
	{
		CButton* pBtn11 = (CButton*)GetDlgItem(IDC_BUTTON11);
		pBtn11->EnableWindow(true);
	}
	else
	{
		CButton* pBtn11 = (CButton*)GetDlgItem(IDC_BUTTON11);
		pBtn11->EnableWindow(false);
	}
}
void CBLACKJAKDlg::OnClickedPlayerSplitHit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		// TODO: 여기에 구현 코드 추가.
	srand(time(NULL));// Player 변수 처리
	int index = rand() % 52;
	int Card_Number = 0;

	Card_Number = Stoi(card[index].number, Card_Number); 
	if (card[index].number == "J" || card[index].number == "K" || card[index].number == "Q")
	{
		Card_Number = 10;
	}
	if (card[index].number == "A")
	{
		Card_Split_Sum += 1;
		Card_Split_Sum2 += 11;
	}
	Card_Split_Sum += Card_Number;
	Card_Split_Sum2 += Card_Number;
	Card_Split_image += card[index].Shape;
	Card_Split_image += card[index].number;
	if (Card_Split_Sum > 21) // 스플릿 카드가 21이 넘는 경우 패배
	{
		ButtonControl("off8");
		SetDlgItemText(IDC_SplitSum, _T("패배하였습니다."));
	}
	CString Card_Sum_Print;
	Card_Sum_Print = Itos(Card_sum, Card_Sum_Print);
	CString Card_Sum_Print2;
	Card_Sum_Print2 = Itos(Card_sum2, Card_Sum_Print2);
	CString Card_Split_Sum_Print;
	Card_Split_Sum_Print = Itos(Card_Split_Sum, Card_Split_Sum_Print);
	CString Card_Split_Sum_Print2;
	Card_Split_Sum_Print2 = Itos(Card_Split_Sum2, Card_Split_Sum_Print2);
	CString cstr;
	cstr = Itos(Mymoney, cstr);

	SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr + _T("\n승리 확률 :"));
	SetDlgItemText(IDC_CardImage, Card_image + _T("\n") + Card_Split_image);
	SetDlgItemText(IDC_Sum, _T("PLAYER 현재 합계 :") + Card_Sum_Print + _T("or") + Card_Sum_Print2);
	SetDlgItemText(IDC_SplitSum, _T("\nPLAYER 현재 합계 :") + Card_Split_Sum_Print + _T("or") + Card_Split_Sum_Print2);
}
void CBLACKJAKDlg::OnClickedPlayerSplitStand()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	Result3 = 1;

	if (Card_Split_Sum2 <= 21) Card_Split_Sum = Card_Split_Sum2;
	ButtonControl("off89");
	if (Result == 1 && Result1 == 1 && Result3 == 1)
	{
		int state = 0;
		int split_state = 0;
		if ((Dealer_Card_Sum < Card_sum && Card_sum <= 21) || Dealer_Card_Sum>21) // 승리 조건
		{
			state = 1; 
		}
		else if (Dealer_Card_Sum == Card_sum ) // 무승부 조건
		{
			state = 2; 
		}
		else if ((Dealer_Card_Sum > Card_sum && Dealer_Card_Sum <= 21) || Card_sum>21) // 패배 조건
		{
			state = 3;
		}

		if ((Dealer_Card_Sum < Card_Split_Sum && Card_Split_Sum <= 21) || Dealer_Card_Sum > 21) // 승리 조건
		{
			split_state = 1;
		}
		else if (Dealer_Card_Sum == Card_Split_Sum) // 무승부 조건
		{
			split_state = 2;
		}
		else if ((Dealer_Card_Sum > Card_Split_Sum && Dealer_Card_Sum <= 21) || Card_Split_Sum > 21) // 패배 조건
		{
			split_state = 3;
		}
		if (state == 1 && split_state == 1) // 숫자가 21보다 작거나 같면서 딜러보다 커야함
		{
			Win();
		}
		else if (state == 3 && split_state == 3)
		{
			Lose();
		}
		else if (state ==1 && split_state == 2)
		{
			UpdateData(true);
			SetDlgItemText(IDC_Sum, _T("비겼습니다.\n 최소 배팅 금액은 100원입니다."));
			SetDlgItemText(IDC_SplitSum, _T(" 패배하였습니다."));
			Mymoney += (Betting_Money * 0.5);
			Betting_Money = 0;
			CString cstr;
			cstr = Itos(Mymoney, cstr);
			SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
			initialization();

			UpdateData(false);
		}
		else if (state == 2 && split_state == 1)
		{
			UpdateData(true);
			SetDlgItemText(IDC_Sum, _T("패배하였습니다.\n 최소 배팅 금액은 100원입니다."));
			SetDlgItemText(IDC_SplitSum, _T(" 비겼습니다."));
			Mymoney += (Betting_Money * 0.5);
			Betting_Money = 0;
			CString cstr;
			cstr = Itos(Mymoney, cstr);
			SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
			initialization();
			UpdateData(false);
		}
		else if (state == 3 && split_state == 2)
		{
			UpdateData(true);
			SetDlgItemText(IDC_Sum, _T("비겼습니다.\n 최소 배팅 금액은 100원입니다."));
			SetDlgItemText(IDC_SplitSum, _T(" 승리하였습니다. 베팅 금액 2배를 얻습니다."));
			Mymoney += (Betting_Money * 1.5);
			Betting_Money = 0;
			CString cstr;
			cstr = Itos(Mymoney, cstr);
			SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
			initialization();
			UpdateData(false);
		}
		else if (state == 2 && split_state == 3)
		{
			UpdateData(true);
			SetDlgItemText(IDC_Sum, _T("승리하였습니다. 베팅 금액 2배를 얻습니다.\n 최소 배팅 금액은 100원입니다."));
			SetDlgItemText(IDC_SplitSum, _T(" 비겼습니다."));
			Mymoney += (Betting_Money * 1.5);
			Betting_Money = 0;
			CString cstr;
			cstr = Itos(Mymoney, cstr);
			SetDlgItemText(IDC_Information, _T("현재 보유하고 있는 돈 :") + cstr);
			initialization();
			UpdateData(false);
		}
		else
		{
			Draw();
		}
	}
	
}
void CBLACKJAKDlg::OnBnClickedButton8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	probility* child = new probility();

	child->Create(IDD_DIALOG1, this);
	child->ShowWindow(SW_SHOW);

	int count[20] = { 0 };
	float data[20] = { 0 };
	int trial = 100000;
	CString cstr[20];
	for (int k = 0; k < trial; k++) // 2장의 합계는 통계로 계산한다. 10만번 수행
	{
		// 카드 52장 중에 랜덤으로 받기 위해 사용
		int index = rand() % 52;
		int Card_Number = 0;

		Card_Number = Stoi(card[index].number, Card_Number);
		if (card[index].number == "J" || card[index].number == "K" || card[index].number == "Q")  // J,K,Q 는 숫자 10으로 사용한다.
		{
			Card_Number = 10;
		}
		if (card[index].number == "A")  // A의 1 또는 11을 적용하기 위해 변수를 하나 더 지정하고 각각에 변수에 다른 값을 넣어 표현
		{
			Card_sum += 1;
			//Card_sum2 += 11;
		}

		Card_sum += Card_Number;
		//Card_sum2 += Card_Number;

		//if (Card_sum2 <= 21) Card_sum = Card_sum2;

		if (k % 2 == 1)
		{
			for (int i = 2; i < 22; i++)
			{
				if (Card_sum == i)
				{
					count[i - 2]++;
					Card_sum = 0;
					Card_sum2 = 0;
				}
			}
		}
	}
	for (int i = 0; i < 20; i++)
	{

		data[i] = ((float)count[i]*100) / trial;
		cstr[i].Format(_T("%f"), data[i]);
		child->ReceiveText(cstr[i]);
	}


}
int CBLACKJAKDlg::CardImageInsert(CString Card_number, CString Card_Shape)
{
	// TODO: 여기에 구현 코드 추가.
	int ImageNumber = 0;
	if (DealerNumber == 0) ImageNumber = 1022;
	if (DealerNumber == 1) ImageNumber = 1023;
	if (DealerNumber == 2) ImageNumber = 1028;
	if (DealerNumber == 3) ImageNumber = 1030;
	if (DealerNumber == 4) ImageNumber = 1031;
	if (m_CardImage.IsNull())
	{		
		if (Card_Shape == "♠")
		{
			if (Card_number == 'A')
			{
				m_CardImage.Load(L"스페이드 A.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '2')
			{
				m_CardImage.Load(L"스페이드 2.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '3')
			{
				m_CardImage.Load(L"스페이드 3.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '4')
			{
				m_CardImage.Load(L"스페이드 4.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '5')
			{
				m_CardImage.Load(L"스페이드 5.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '6')
			{
				m_CardImage.Load(L"스페이드 6.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '7')
			{
				m_CardImage.Load(L"스페이드 7.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '8')
			{
				m_CardImage.Load(L"스페이드 8.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '9')
			{
				m_CardImage.Load(L"스페이드 9.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == "10")
			{
				m_CardImage.Load(L"스페이드 10.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == 'J')
			{
				m_CardImage.Load(L"스페이드 J.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == 'Q')
			{
				m_CardImage.Load(L"스페이드 Q.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == 'K')
			{
				m_CardImage.Load(L"스페이드 K.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else
			{
				m_CardImage.Detach();
			}

		}
		if (Card_Shape == "♣")
		{
			if (Card_number == 'A')
			{
				m_CardImage.Load(L"클로버 A.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '2')
			{
				m_CardImage.Load(L"클로버 2.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '3')
			{
				m_CardImage.Load(L"클로버 3.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '4')
			{
				m_CardImage.Load(L"클로버 4.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '5')
			{
				m_CardImage.Load(L"클로버 5.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '6')
			{
				m_CardImage.Load(L"클로버 6.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '7')
			{
				m_CardImage.Load(L"클로버 7.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '8')
			{
				m_CardImage.Load(L"클로버 8.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '9')
			{
				m_CardImage.Load(L"클로버 9.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == "10")
			{
				m_CardImage.Load(L"클로버 10.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == 'J')
			{
				m_CardImage.Load(L"클로버 J.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == 'Q')
			{
				m_CardImage.Load(L"클로버 Q.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == 'K')
			{
				m_CardImage.Load(L"클로버 K.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else
			{
				m_CardImage.Detach();
			}
		}
		if (Card_Shape == "◆")
		{
			if (Card_number == 'A')
			{
				m_CardImage.Load(L"다이아 A.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '2')
			{
				m_CardImage.Load(L"다이아 2.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '3')
			{
				m_CardImage.Load(L"다이아 3.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '4')
			{
				m_CardImage.Load(L"다이아 4.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '5')
			{
				m_CardImage.Load(L"다이아 5.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '6')
			{
				m_CardImage.Load(L"다이아 6.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '7')
			{
				m_CardImage.Load(L"다이아 7.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '8')
			{
				m_CardImage.Load(L"다이아 8.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '9')
			{
				m_CardImage.Load(L"다이아 9.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == "10")
			{
				m_CardImage.Load(L"다이아 10.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == 'J')
			{
				m_CardImage.Load(L"다이아 J.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == 'Q')
			{
				m_CardImage.Load(L"다이아 Q.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == 'K')
			{
				m_CardImage.Load(L"다이아 K.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else
			{
				m_CardImage.Detach();
			}
		}
		if (Card_Shape == "♥")
		{
			if (Card_number == 'A')
			{
				m_CardImage.Load(L"하트 A.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '2')
			{
				m_CardImage.Load(L"하트 2.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '3')
			{
				m_CardImage.Load(L"하트 3.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '4')
			{
				m_CardImage.Load(L"하트 4.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '5')
			{
				m_CardImage.Load(L"하트 5.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '6')
			{
				m_CardImage.Load(L"하트 6.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '7')
			{
				m_CardImage.Load(L"하트 7.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '8')
			{
				m_CardImage.Load(L"하트 8.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '9')
			{
				m_CardImage.Load(L"하트 9.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == "10")
			{
				m_CardImage.Load(L"하트 10.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == 'J')
			{
				m_CardImage.Load(L"하트 J.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == 'Q')
			{
				m_CardImage.Load(L"하트 Q.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == 'K')
			{
				m_CardImage.Load(L"하트 K.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else
			{
				m_CardImage.Detach();
			}
		}
		DealerNumber++;
		
	}
	m_CardImage.Detach();
	return 0;
}
int CBLACKJAKDlg::CardImageInSert2(CString Card_number, CString Card_Shape)
{
	// TODO: 여기에 구현 코드 추가.
	int ImageNumber = 0;
	if (PlayerNumber == 0) ImageNumber = 1024;
	if (PlayerNumber == 1) ImageNumber = 1025;
	if (PlayerNumber == 2) ImageNumber = 1029;
	if (PlayerNumber == 3) ImageNumber = 1032;
	if (PlayerNumber == 4) ImageNumber = 1033;
	if (m_CardImage.IsNull())
	{

		if (Card_Shape == "♠")
		{
			if (Card_number == 'A')
			{
				m_CardImage.Load(L"스페이드 A.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '2')
			{
				m_CardImage.Load(L"스페이드 2.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '3')
			{
				m_CardImage.Load(L"스페이드 3.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '4')
			{
				m_CardImage.Load(L"스페이드 4.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '5')
			{
				m_CardImage.Load(L"스페이드 5.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '6')
			{
				m_CardImage.Load(L"스페이드 6.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '7')
			{
				m_CardImage.Load(L"스페이드 7.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '8')
			{
				m_CardImage.Load(L"스페이드 8.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '9')
			{
				m_CardImage.Load(L"스페이드 9.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == "10")
			{
				m_CardImage.Load(L"스페이드 10.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == 'J')
			{
				m_CardImage.Load(L"스페이드 J.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == 'Q')
			{
				m_CardImage.Load(L"스페이드 Q.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == 'K')
			{
				m_CardImage.Load(L"스페이드 K.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else
			{
				m_CardImage.Detach();
			}

		}
		if (Card_Shape == "♣")
		{
			if (Card_number == 'A')
			{
				m_CardImage.Load(L"클로버 A.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '2')
			{
				m_CardImage.Load(L"클로버 2.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '3')
			{
				m_CardImage.Load(L"클로버 3.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '4')
			{
				m_CardImage.Load(L"클로버 4.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '5')
			{
				m_CardImage.Load(L"클로버 5.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '6')
			{
				m_CardImage.Load(L"클로버 6.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '7')
			{
				m_CardImage.Load(L"클로버 7.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '8')
			{
				m_CardImage.Load(L"클로버 8.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '9')
			{
				m_CardImage.Load(L"클로버 9.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == "10")
			{
				m_CardImage.Load(L"클로버 10.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == 'J')
			{
				m_CardImage.Load(L"클로버 J.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == 'Q')
			{
				m_CardImage.Load(L"클로버 Q.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == 'K')
			{
				m_CardImage.Load(L"클로버 K.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else
			{
				m_CardImage.Detach();
			}
		}
		if (Card_Shape == "◆")
		{
			if (Card_number == 'A')
			{
				m_CardImage.Load(L"다이아 A.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '2')
			{
				m_CardImage.Load(L"다이아 2.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '3')
			{
				m_CardImage.Load(L"다이아 3.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '4')
			{
				m_CardImage.Load(L"다이아 4.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '5')
			{
				m_CardImage.Load(L"다이아 5.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '6')
			{
				m_CardImage.Load(L"다이아 6.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '7')
			{
				m_CardImage.Load(L"다이아 7.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '8')
			{
				m_CardImage.Load(L"다이아 8.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '9')
			{
				m_CardImage.Load(L"다이아 9.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == "10")
			{
				m_CardImage.Load(L"다이아 10.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == 'J')
			{
				m_CardImage.Load(L"다이아 J.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == 'Q')
			{
				m_CardImage.Load(L"다이아 Q.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == 'K')
			{
				m_CardImage.Load(L"다이아 K.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else
			{
				m_CardImage.Detach();
			}
		}
		if (Card_Shape == "♥")
		{
			if (Card_number == 'A')
			{
				m_CardImage.Load(L"하트 A.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '2')
			{
				m_CardImage.Load(L"하트 2.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '3')
			{
				m_CardImage.Load(L"하트 3.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '4')
			{
				m_CardImage.Load(L"하트 4.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '5')
			{
				m_CardImage.Load(L"하트 5.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '6')
			{
				m_CardImage.Load(L"하트 6.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '7')
			{
				m_CardImage.Load(L"하트 7.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '8')
			{
				m_CardImage.Load(L"하트 8.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == '9')
			{
				m_CardImage.Load(L"하트 9.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == "10")
			{
				m_CardImage.Load(L"하트 10.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == 'J')
			{
				m_CardImage.Load(L"하트 J.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == 'Q')
			{
				m_CardImage.Load(L"하트 Q.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else if (Card_number == 'K')
			{
				m_CardImage.Load(L"하트 K.bmp");
				((CStatic*)GetDlgItem(ImageNumber))->SetBitmap(m_CardImage);
			}
			else
			{
				m_CardImage.Detach();
			}
		}
		PlayerNumber++;
	}

	m_CardImage.Detach();
	return 0;
}


//void CBLACKJAKDlg::OnStnClickedCardimage()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}
