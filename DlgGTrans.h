#pragma once
#include "afxdialogex.h"


// DlgGTrans 对话框

class DlgGTrans : public CDialogEx
{
	DECLARE_DYNAMIC(DlgGTrans)

public:
	DlgGTrans(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlgGTrans();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DlgGTrans };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	LONG m_offX;
	LONG m_offY;
};
