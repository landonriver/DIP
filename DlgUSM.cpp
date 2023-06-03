// DlgUSM.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "DlgUSM.h"


// DlgUSM 对话框

IMPLEMENT_DYNAMIC(DlgUSM, CDialogEx)

DlgUSM::DlgUSM(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USM, pParent)
	, m_weight(0)
{

}

DlgUSM::~DlgUSM()
{
}

void DlgUSM::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_weight);
}


BEGIN_MESSAGE_MAP(DlgUSM, CDialogEx)
END_MESSAGE_MAP()


// DlgUSM 消息处理程序
