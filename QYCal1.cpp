// QYCal1.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "QYCal1.h"


// QYCal1 对话框

IMPLEMENT_DYNAMIC(QYCal1, CDialogEx)

QYCal1::QYCal1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_QYcal1, pParent)
{

}

QYCal1::~QYCal1()
{
}

void QYCal1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(QYCal1, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &QYCal1::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &QYCal1::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &QYCal1::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &QYCal1::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &QYCal1::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_CHECK1, &QYCal1::OnBnClickedCheck1)

END_MESSAGE_MAP()


// QYCal1 消息处理程序


void QYCal1::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_foreground = 0;
}


void QYCal1::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_foreground = 1;
}


void QYCal1::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_foreground = 2;
}


void QYCal1::OnBnClickedRadio4()
{
	m_link = 1;
}


void QYCal1::OnBnClickedRadio5()
{
	m_link = 0;
}


void QYCal1::OnBnClickedCheck1()
{
	m_forecolor = 1;
}