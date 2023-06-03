// CDXTXBH.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "CDXTXBH.h"


// CDXTXBH 对话框

IMPLEMENT_DYNAMIC(CDXTXBH, CDialogEx)

CDXTXBH::CDXTXBH(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_XTXBH, pParent)
	, m_nMode(0)
	, m_nStructure1(0)
	, m_nStructure2(0)
	, m_nStructure3(0)
	, m_nStructure4(1)
	, m_nStructure5(1)
	, m_nStructure6(1)
	, m_nStructure7(0)
	, m_nStructure8(0)
	, m_nStructure9(0)
{

}

CDXTXBH::~CDXTXBH()
{
}

void CDXTXBH::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_nMode);
	DDX_Control(pDX, IDC_RADIO8, m_Control1);
	DDX_Control(pDX, IDC_RADIO9, m_Control2);
	DDX_Control(pDX, IDC_RADIO10, m_Control3);
	DDX_Control(pDX, IDC_RADIO11, m_Control4);
	DDX_Control(pDX, IDC_RADIO12, m_Control5);
	DDX_Control(pDX, IDC_RADIO13, m_Control6);
	DDX_Control(pDX, IDC_RADIO14, m_Control7);
	DDX_Control(pDX, IDC_RADIO15, m_Control8);
	DDX_Control(pDX, IDC_RADIO16, m_Control9);
	DDX_Radio(pDX, IDC_RADIO8, m_nStructure1);
	DDX_Radio(pDX, IDC_RADIO9, m_nStructure2);
	DDX_Radio(pDX, IDC_RADIO10, m_nStructure3);
	DDX_Radio(pDX, IDC_RADIO11, m_nStructure4);
	DDX_Radio(pDX, IDC_RADIO12, m_nStructure5);
	DDX_Radio(pDX, IDC_RADIO13, m_nStructure6);
	DDX_Radio(pDX, IDC_RADIO14, m_nStructure7);
	DDX_Radio(pDX, IDC_RADIO15, m_nStructure8);
	DDX_Radio(pDX, IDC_RADIO16, m_nStructure9);
}


BEGIN_MESSAGE_MAP(CDXTXBH, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &CDXTXBH::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDXTXBH::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CDXTXBH::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO8, &CDXTXBH::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_RADIO9, &CDXTXBH::OnBnClickedRadio9)
	ON_BN_CLICKED(IDC_RADIO10, &CDXTXBH::OnBnClickedRadio10)
	ON_BN_CLICKED(IDC_RADIO11, &CDXTXBH::OnBnClickedRadio11)
	ON_BN_CLICKED(IDC_RADIO12, &CDXTXBH::OnBnClickedRadio12)
	ON_BN_CLICKED(IDC_RADIO13, &CDXTXBH::OnBnClickedRadio13)
	ON_BN_CLICKED(IDC_RADIO14, &CDXTXBH::OnBnClickedRadio14)
	ON_BN_CLICKED(IDC_RADIO15, &CDXTXBH::OnBnClickedRadio15)
	ON_BN_CLICKED(IDC_RADIO16, &CDXTXBH::OnBnClickedRadio16)
	ON_BN_CLICKED(IDC_RADIO4, &CDXTXBH::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CDXTXBH::OnBnClickedRadio5)
END_MESSAGE_MAP()


// CDXTXBH 消息处理程序
// CDXTXBH 消息处理程序
void CDXTXBH::UpdateEdit()
{
	BOOL	bEnable;

	// 循环变量
	int		i = 0;
	int		j = 0;

	// 判断是不是自定义模板
	if (m_nMode == 2)
	{
		bEnable = TRUE;
	}
	else
	{
		bEnable = FALSE;
	}

	// 设置文本框不可编辑
	m_Control1.EnableWindow(bEnable);
	m_Control2.EnableWindow(bEnable);
	m_Control3.EnableWindow(bEnable);
	m_Control4.EnableWindow(bEnable);
	m_Control5.EnableWindow(bEnable);
	m_Control6.EnableWindow(bEnable);
	m_Control7.EnableWindow(bEnable);
	m_Control8.EnableWindow(bEnable);
	m_Control9.EnableWindow(bEnable);


}


void CDXTXBH::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nMode = 0;

	m_nStructure4 = 1;
	m_nStructure6 = 1;
	m_nStructure5 = 1;
	m_nStructure1 = 0;
	m_nStructure2 = 0;
	m_nStructure3 = 0;
	m_nStructure7 = 0;
	m_nStructure8 = 0;
	m_nStructure9 = 0;
	// 更新文本框状态
	UpdateEdit();

	// 更新
	UpdateData(FALSE);
}


void CDXTXBH::OnBnClickedRadio2()
{
	m_nMode = 1;
	m_nStructure2 = 1;
	m_nStructure5 = 1;
	m_nStructure8 = 1;
	m_nStructure4 = 0;
	m_nStructure3 = 0;
	m_nStructure1 = 0;
	m_nStructure6 = 0;
	m_nStructure7 = 0;
	m_nStructure9 = 0;
	// 更新文本框状态
	UpdateEdit();

	// 更新
	UpdateData(FALSE);
}


void CDXTXBH::OnBnClickedRadio3()
{
	m_nMode = 2;
	m_nStructure2 = 0;
	m_nStructure5 = 0;
	m_nStructure8 = 0;
	m_nStructure4 = 0;
	m_nStructure3 = 0;
	m_nStructure1 = 0;
	m_nStructure6 = 0;
	m_nStructure7 = 0;
	m_nStructure9 = 0;
	// 更新文本框状态
	UpdateEdit();

	// 更新
	UpdateData(FALSE);
}

BOOL CDXTXBH::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	BOOL	bEnable;

	bEnable = FALSE;



	// 设置文本框不可编辑
	m_Control1.EnableWindow(bEnable);
	m_Control2.EnableWindow(bEnable);
	m_Control3.EnableWindow(bEnable);
	m_Control4.EnableWindow(bEnable);
	m_Control5.EnableWindow(bEnable);
	m_Control6.EnableWindow(bEnable);
	m_Control7.EnableWindow(bEnable);
	m_Control8.EnableWindow(bEnable);
	m_Control9.EnableWindow(bEnable);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}



void CDXTXBH::OnBnClickedRadio8()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nMode = 2;
	if (m_nStructure1 == 1) {
		m_nStructure1 = 0;
	}
	else if (m_nStructure1 == 0) {
		m_nStructure1 = 1;
	}

	// 更新文本框状态
	UpdateEdit();

	// 更新
	UpdateData(FALSE);
}


void CDXTXBH::OnBnClickedRadio9()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nMode = 2;
	if (m_nStructure2 == 1) {
		m_nStructure2 = 0;
	}
	else if (m_nStructure2 == 0) {
		m_nStructure2 = 1;
	}

	// 更新文本框状态
	UpdateEdit();

	// 更新
	UpdateData(FALSE);
}


void CDXTXBH::OnBnClickedRadio10()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nMode = 2;
	if (m_nStructure3 == 1) {
		m_nStructure3 = 0;
	}
	else if (m_nStructure3 == 0) {
		m_nStructure3 = 1;
	}

	// 更新文本框状态
	UpdateEdit();

	// 更新
	UpdateData(FALSE);
}


void CDXTXBH::OnBnClickedRadio11()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nMode = 2;
	if (m_nStructure4 == 1) {
		m_nStructure4 = 0;
	}
	else if (m_nStructure4 == 0) {
		m_nStructure4 = 1;
	}

	// 更新文本框状态
	UpdateEdit();

	// 更新
	UpdateData(FALSE);
}


void CDXTXBH::OnBnClickedRadio12()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nMode = 2;
	if (m_nStructure5 == 1) {
		m_nStructure5 = 0;
	}
	else if (m_nStructure5 == 0) {
		m_nStructure5 = 1;
	}

	// 更新文本框状态
	UpdateEdit();

	// 更新
	UpdateData(FALSE);
}


void CDXTXBH::OnBnClickedRadio13()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nMode = 2;
	if (m_nStructure6 == 1) {
		m_nStructure6 = 0;
	}
	else if (m_nStructure6 == 0) {
		m_nStructure6 = 1;
	}

	// 更新文本框状态
	UpdateEdit();

	// 更新
	UpdateData(FALSE);
}


void CDXTXBH::OnBnClickedRadio14()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nMode = 2;
	if (m_nStructure7 == 1) {
		m_nStructure7 = 0;
	}
	else if (m_nStructure7 == 0) {
		m_nStructure7 = 1;
	}

	// 更新文本框状态
	UpdateEdit();

	// 更新
	UpdateData(FALSE);
}


void CDXTXBH::OnBnClickedRadio15()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nMode = 2;
	if (m_nStructure8 == 1) {
		m_nStructure8 = 0;
	}
	else if (m_nStructure8 == 0) {
		m_nStructure8 = 1;
	}

	// 更新文本框状态
	UpdateEdit();

	// 更新
	UpdateData(FALSE);
}


void CDXTXBH::OnBnClickedRadio16()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nMode = 2;
	if (m_nStructure9 == 1) {
		m_nStructure9 = 0;
	}
	else if (m_nStructure9 == 0) {
		m_nStructure9 = 1;
	}

	// 更新文本框状态
	UpdateEdit();

	// 更新
	UpdateData(FALSE);
}


void CDXTXBH::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	b_nMode = 1;
}





void CDXTXBH::OnBnClickedRadio5()
{
	// TODO: 在此添加控件通知处理程序代码
	b_nMode = 2;
}

