#pragma once
#include "afxdialogex.h"


// CDLinverse 对话框

class CDLinverse : public CDialogEx
{
	DECLARE_DYNAMIC(CDLinverse)

public:
	CDLinverse(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDLinverse();
	int temp3;
	//响应鼠标的区域
	CRect m_MouseRect3;
	//标识是否拖动
	BOOL m_bIsDrawing3;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLinverse };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_sol3;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnEnKillfocusThreshold();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
