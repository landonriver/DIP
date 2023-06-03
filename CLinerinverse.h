#pragma once
#include "afxdialogex.h"


// CLinerinverse 对话框

class CLinerinverse : public CDialogEx
{
	DECLARE_DYNAMIC(CLinerinverse)

public:
	CLinerinverse(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLinerinverse();
	// 标识是否已经绘制橡皮筋线
	BOOL	m_bDrawed5;

	// 保存鼠标左键单击时的位置
	CPoint	m_p1;

	// 保存鼠标拖动时的位置
	CPoint	m_p2;

	// 当前鼠标拖动状态，TRUE表示正在拖动。
	BOOL	m_bIsDraging5;

	// 相应鼠标事件的矩形区域
	CRect	m_MouseRect5;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Linertrans };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_Fa;
	float m_Fb;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnKillfocusEditA();
	afx_msg void OnEnKillfocusEditB();

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
};
