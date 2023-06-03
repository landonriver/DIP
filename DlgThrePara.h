#pragma once
#include "afxdialogex.h"
#include "MFCApplication1.h"
#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

// DlgThrePara 对话框

class DlgThrePara : public CDialogEx
{
	DECLARE_DYNAMIC(DlgThrePara)

public:
	DlgThrePara(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlgThrePara();
	// 当前鼠标拖动状态，TRUE表示正在拖动
	BOOL	m_bIsDraging;

	// 相应鼠标事件的矩形区域
	CRect	m_MouseRect;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDlgThrePara };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BYTE m_bThre;
	int m_intType;
	// 指向DIB象素指针
	LPSTR   lpDIBBits;
	CMFCApplication1Doc* pDoc;
	unsigned char* lpstartBits;
	long lSrcLineBytes;
	int     lpSrcBitCount;       //图像的位深
	int lWidth;
	int lHeight;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnKillfocusThre();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedRadio1();

	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio4();

	afx_msg void OnBnClickedcalculate();
	afx_msg void OnBnClickedButtonpre();
	afx_msg void OnBnClickedButton2rec();
};
