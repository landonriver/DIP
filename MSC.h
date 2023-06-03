#pragma once
#include "afxdialogex.h"


// MSC 对话框

class MSC : public CDialogEx
{
	DECLARE_DYNAMIC(MSC)

public:
	MSC(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MSC();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MSC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_ret;
};
