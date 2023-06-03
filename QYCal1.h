﻿#pragma once
#include "afxdialogex.h"


// QYCal1 对话框

class QYCal1 : public CDialogEx
{
	DECLARE_DYNAMIC(QYCal1)

public:
	QYCal1(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~QYCal1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_QYcal1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	int m_forecolor;
	int m_foreground;
	int m_link;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedCheck1();

};
