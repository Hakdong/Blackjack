
// BLACKJAKDlg.h: 헤더 파일
//

#pragma once


// CBLACKJAKDlg 대화 상자
class CBLACKJAKDlg : public CDialogEx
{
// 생성입니다.
public:
	CBLACKJAKDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BLACKJAK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int Bet_Money;
	afx_msg void OnBnClickedGAMESTART();
//	afx_msg void OnStatic();
	CStatic BettingInformation;
	CStatic Card_Image;
	afx_msg void OnClickedBettingButton();
	CStatic Sum;
	afx_msg void OnClickedHit();
//	CStatic DealerCard;
	CStatic DealerSum;
	afx_msg void OnClickedStand();
	void PlayerProcess();
	void DealerProcess();
	void Win();
	void Draw();
	void Lose();
	afx_msg void OnClickedDealerHIT();
	afx_msg void OnClickedDealerStand();
	int Result=0;
	afx_msg void OnClickedPlayerDouble();
	afx_msg void OnClickedPlayerSplrit();
	void ButtonControl(char Find_Number[14]);
	afx_msg void OnClickedPlayerSplitHit();
	afx_msg void OnClickedPlayerSplitStand();
	int Result1 = 0;
	int Result3 = 1;
	CStatic SplitSum;
	void initialization();
	afx_msg void OnBnClickedButton8();
	int CardImageInsert(CString Card_number,CString Card_Shape);
	CStatic m_DealerImage;
	CImage m_CardImage;
//	CStatic IDC_DealerImage2;
	CStatic m_DealerImage2;
	CStatic m_PlayerImage;
	CStatic m_PlayerImage2;
	int CardImageInSert2(CString Card_number, CString Card_Shape);
//	afx_msg void OnStnClickedCardimage();
	CStatic m_DealerImage3;
	CStatic m_PlayerImage3;
	CStatic m_PlayerImage4;
	CStatic m_PlayerImage5;
	CStatic m_DealerImage4;
	CStatic m_DealerImage5;
};
