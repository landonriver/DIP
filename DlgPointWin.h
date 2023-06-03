#pragma once
#include "afxdialogex.h"
#include "MFCApplication1.h"
#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"


// DlgPointWin 对话框

class DlgPointWin : public CDialogEx
{
	DECLARE_DYNAMIC(DlgPointWin)

public:
	DlgPointWin(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlgPointWin();
	// 当前鼠标拖动状态，0表示未拖动，1表示正在拖动下限，2表示正在拖动上限。
	int		m_iIsDraging;

	// 相应鼠标事件的矩形区域
	CRect	m_MouseRect;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DlgPointWin };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BYTE m_bUp;
	BYTE m_bLow;
	// 指向DIB象素指针
	LPSTR   lpDIBBits;
	CMFCApplication1Doc* pDoc;
	unsigned char* lpstartBits;
	long lSrcLineBytes;
	int  lpSrcBitCount;       //图像的位深
	int lWidth;
	int lHeight;
	virtual void OnOK();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnEnKillfocusEditLow();
	afx_msg void OnEnKillfocusEditUp();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
