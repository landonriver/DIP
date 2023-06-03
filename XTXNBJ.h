#pragma once
#include "afxdialogex.h"


// XTXNBJ 对话框

class XTXNBJ : public CDialogEx
{
	DECLARE_DYNAMIC(XTXNBJ)

public:
	XTXNBJ(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~XTXNBJ();
	void UpdateEdit();//更新文本框状态
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_XTXNBJ };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nMode;
	int b_nMode = 0;
	CButton m_Control1;
	CButton m_Control2;
	CButton m_Control3;
	CButton m_Control4;
	CButton m_Control5;
	CButton m_Control6;
	CButton m_Control7;
	CButton m_Control8;
	CButton m_Control9;
	int m_nStructure1;
	int m_nStructure2;
	int m_nStructure3;
	int m_nStructure4;
	int m_nStructure5;
	int m_nStructure6;
	int m_nStructure7;
	int m_nStructure8;
	int m_nStructure9;

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio8();
	afx_msg void OnBnClickedRadio9();
	afx_msg void OnBnClickedRadio10();
	afx_msg void OnBnClickedRadio11();
	afx_msg void OnBnClickedRadio12();
	afx_msg void OnBnClickedRadio13();
	afx_msg void OnBnClickedRadio14();
	afx_msg void OnBnClickedRadio15();
	afx_msg void OnBnClickedRadio16();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
};
