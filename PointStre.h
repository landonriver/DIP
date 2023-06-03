#pragma once
#include "afxdialogex.h"
#include "MFCApplication1.h"
#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

// PointStre 对话框

class PointStre : public CDialogEx
{
	DECLARE_DYNAMIC(PointStre)

public:
	PointStre(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~PointStre();
	// 当前鼠标拖动状态，0表示未拖动，1表示正在拖动第一点，2表示正在拖动第二点。
	int		m_iIsDraging;

	// 相应鼠标事件的矩形区域
	CRect	m_MouseRect;

	// 标识是否已经绘制橡皮筋线
	BOOL	m_bDrawed;

	// 保存鼠标左键单击时的位置
	CPoint	m_p1;

	// 保存鼠标拖动时的位置
	CPoint	m_p2;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PointStre };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BYTE m_bX1;
	BYTE m_bY1;
	BYTE m_bX2;
	BYTE m_bY2;
	// 指向DIB象素指针
	LPSTR   lpDIBBits;
	CMFCApplication1Doc* pDoc;
	unsigned char* lpstartBits;
	long lSrcLineBytes;
	int  lpSrcBitCount;       //图像的位深
	int lWidth;
	int lHeight;
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnEnKillfocusbx1();
	afx_msg void OnEnKillfocusbx2();
	afx_msg void OnEnKillfocusby1();
	afx_msg void OnEnKillfocusby2();
	virtual void OnOK();


	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
