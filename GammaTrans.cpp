// GammaTrans.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "GammaTrans.h"


// GammaTrans 对话框

IMPLEMENT_DYNAMIC(GammaTrans, CDialogEx)

GammaTrans::GammaTrans(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAMMAtrans, pParent)
	, m_fGamma(0)
{

}

GammaTrans::~GammaTrans()
{
}

void GammaTrans::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GAMMA, m_fGamma);
}


BEGIN_MESSAGE_MAP(GammaTrans, CDialogEx)
END_MESSAGE_MAP()


// GammaTrans 消息处理程序
