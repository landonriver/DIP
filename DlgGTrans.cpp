// DlgGTrans.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "DlgGTrans.h"


// DlgGTrans 对话框

IMPLEMENT_DYNAMIC(DlgGTrans, CDialogEx)

DlgGTrans::DlgGTrans(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DlgGTrans, pParent)
	, m_offX(0)
	, m_offY(0)
{

}

DlgGTrans::~DlgGTrans()
{
}

void DlgGTrans::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_GtransX, m_offX);
	DDX_Text(pDX, IDC_GtransY, m_offY);
}


BEGIN_MESSAGE_MAP(DlgGTrans, CDialogEx)
END_MESSAGE_MAP()


// DlgGTrans 消息处理程序
