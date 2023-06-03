#pragma once
#include "afxdialogex.h"


// QYCal2 对话框

class QYCal2 : public CDialogEx
{
	DECLARE_DYNAMIC(QYCal2)

public:
	QYCal2(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~QYCal2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_QYCal2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_Num;
	int m_mSquare;
	int m_mCmeter;
	double m_circle;
	double m_square;
	int m_x;
	int m_y;
};
