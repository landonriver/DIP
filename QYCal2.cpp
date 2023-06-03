// QYCal2.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "QYCal2.h"


// QYCal2 对话框

IMPLEMENT_DYNAMIC(QYCal2, CDialogEx)

QYCal2::QYCal2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_QYCal2, pParent)
	, m_Num(0)
	, m_mSquare(0)
	, m_mCmeter(0)
	, m_circle(0)
	, m_square(0)
	, m_x(0)
	, m_y(0)
{

}

QYCal2::~QYCal2()
{
}

void QYCal2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Num);
	DDX_Text(pDX, IDC_EDIT2, m_mSquare);
	DDX_Text(pDX, IDC_EDIT3, m_mCmeter);
	DDX_Text(pDX, IDC_EDIT4, m_circle);
	DDX_Text(pDX, IDC_EDIT5, m_square);
	DDX_Text(pDX, IDC_EDIT6, m_x);
	DDX_Text(pDX, IDC_EDIT7, m_y);
}


BEGIN_MESSAGE_MAP(QYCal2, CDialogEx)
END_MESSAGE_MAP()


// QYCal2 消息处理程序
