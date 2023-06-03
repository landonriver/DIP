#pragma once
#include "afxdialogex.h"


// PointInverse 对话框

class PointInverse : public CDialogEx
{
	DECLARE_DYNAMIC(PointInverse)

public:
	PointInverse(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~PointInverse();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PointInverse };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
