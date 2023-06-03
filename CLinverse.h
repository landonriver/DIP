#pragma once
#include "afxdialogex.h"


// CLinverse 对话框

class CLinverse : public CDialogEx
{
	DECLARE_DYNAMIC(CLinverse)

public:
	CLinverse(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLinverse();
	int temp4;
	//响应鼠标的区域
	CRect m_MouseRect4;
	//标识是否拖动
	BOOL m_bIsDrawing4;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Linverse };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_sol4;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnEnKillfocusThreshold();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
