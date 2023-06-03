#pragma once
#include "afxdialogex.h"


// DlgUSM 对话框

class DlgUSM : public CDialogEx
{
	DECLARE_DYNAMIC(DlgUSM)

public:
	DlgUSM(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlgUSM();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_weight;
};
