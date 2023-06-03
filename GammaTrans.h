#pragma once
#include "afxdialogex.h"


// GammaTrans 对话框

class GammaTrans : public CDialogEx
{
	DECLARE_DYNAMIC(GammaTrans)

public:
	GammaTrans(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~GammaTrans();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMMAtrans };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_fGamma;
};
