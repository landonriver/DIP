#pragma once
#include "afxdialogex.h"
#include "MFCApplication1.h"
#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

// DlgStyleFilter 对话框

class DlgStyleFilter : public CDialogEx
{
	DECLARE_DYNAMIC(DlgStyleFilter)

public:
	DlgStyleFilter(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlgStyleFilter();
	//模板元素数组指针
	FLOAT* m_fpArray;
	void UpdateEdit();//更新文本框状态

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DlgStyleFilter };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_intType;
	int m_nMode;
	int m_SThre;
	float m_c;

	virtual BOOL OnInitDialog();


	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedRadio8();
	afx_msg void OnBnClickedRadio9();
	afx_msg void OnBnClickedRadio10();
	afx_msg void OnBnClickedRadio11();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedButtonsave();
	afx_msg void OnBnClickedButtonload();
	afx_msg void OnBnClickedButtonpreview();
	afx_msg void OnBnClickedButtonrecover();


	long    lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	CMFCApplication1Doc* pDoc;
	unsigned char* lpstartBits;
};
