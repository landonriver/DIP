// CD2ZH.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "CD2ZH.h"


// CD2ZH 对话框

IMPLEMENT_DYNAMIC(CD2ZH, CDialogEx)

CD2ZH::CD2ZH(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_2ZH, pParent)
	, delt(0)
{

}

CD2ZH::~CD2ZH()
{
}

void CD2ZH::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_delt, delt);
}


BEGIN_MESSAGE_MAP(CD2ZH, CDialogEx)
	ON_EN_CHANGE(IDC_delt, &CD2ZH::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CD2ZH 消息处理程序


void CD2ZH::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

BOOL CD2ZH::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}