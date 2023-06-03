#pragma once
#include "afxdialogex.h"


// changeImgLight 对话框

class changeImgLight : public CDialogEx
{
	DECLARE_DYNAMIC(changeImgLight)

public:
	changeImgLight(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~changeImgLight();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_changeImgLight };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int delt;
	virtual BOOL OnInitDialog();
};
