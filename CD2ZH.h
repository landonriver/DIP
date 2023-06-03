#pragma once
#include "afxdialogex.h"


// CD2ZH 对话框

class CD2ZH : public CDialogEx
{
	DECLARE_DYNAMIC(CD2ZH)

public:
	CD2ZH(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CD2ZH();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_2ZH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	int delt;
	virtual BOOL OnInitDialog();
};
