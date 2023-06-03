// MSC.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "MSC.h"


// MSC 对话框

IMPLEMENT_DYNAMIC(MSC, CDialogEx)

MSC::MSC(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MSC, pParent)
	, m_ret(0)
{

}

MSC::~MSC()
{
}

void MSC::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_ret);
}


BEGIN_MESSAGE_MAP(MSC, CDialogEx)
END_MESSAGE_MAP()


// MSC 消息处理程序
