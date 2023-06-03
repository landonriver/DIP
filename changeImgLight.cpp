// changeImgLight.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "changeImgLight.h"


// changeImgLight 对话框

IMPLEMENT_DYNAMIC(changeImgLight, CDialogEx)

changeImgLight::changeImgLight(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_changeImgLight, pParent)
	, delt(0)
{

}

changeImgLight::~changeImgLight()
{
}

void changeImgLight::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_cgLight, delt);
}


BEGIN_MESSAGE_MAP(changeImgLight, CDialogEx)
END_MESSAGE_MAP()


// changeImgLight 消息处理程序


BOOL changeImgLight::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
