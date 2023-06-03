// CDXTXKQ.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "CDXTXKQ.h"


// CDXTXKQ 对话框

IMPLEMENT_DYNAMIC(CDXTXKQ, CDialogEx)

CDXTXKQ::CDXTXKQ(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_XTXKQ, pParent)
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

CDXTXKQ::~CDXTXKQ()
{
}

void CDXTXKQ::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(CDXTXKQ, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &CDXTXKQ::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDXTXKQ::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CDXTXKQ::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO8, &CDXTXKQ::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_RADIO9, &CDXTXKQ::OnBnClickedRadio9)
	ON_BN_CLICKED(IDC_RADIO10, &CDXTXKQ::OnBnClickedRadio10)
	ON_BN_CLICKED(IDC_RADIO11, &CDXTXKQ::OnBnClickedRadio11)
	ON_BN_CLICKED(IDC_RADIO12, &CDXTXKQ::OnBnClickedRadio12)
	ON_BN_CLICKED(IDC_RADIO13, &CDXTXKQ::OnBnClickedRadio13)
	ON_BN_CLICKED(IDC_RADIO14, &CDXTXKQ::OnBnClickedRadio14)
	ON_BN_CLICKED(IDC_RADIO15, &CDXTXKQ::OnBnClickedRadio15)
	ON_BN_CLICKED(IDC_RADIO16, &CDXTXKQ::OnBnClickedRadio16)
	ON_BN_CLICKED(IDC_RADIO4, &CDXTXKQ::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CDXTXKQ::OnBnClickedRadio5)
END_MESSAGE_MAP()



// CDXTXKQ 消息处理程序

// CDXTXKQ 消息处理程序
void CDXTXKQ::UpdateEdit()
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


void CDXTXKQ::OnBnClickedRadio1()
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


void CDXTXKQ::OnBnClickedRadio2()
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


void CDXTXKQ::OnBnClickedRadio3()
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

BOOL CDXTXKQ::OnInitDialog()
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



void CDXTXKQ::OnBnClickedRadio8()
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


void CDXTXKQ::OnBnClickedRadio9()
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


void CDXTXKQ::OnBnClickedRadio10()
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


void CDXTXKQ::OnBnClickedRadio11()
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


void CDXTXKQ::OnBnClickedRadio12()
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


void CDXTXKQ::OnBnClickedRadio13()
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


void CDXTXKQ::OnBnClickedRadio14()
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


void CDXTXKQ::OnBnClickedRadio15()
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


void CDXTXKQ::OnBnClickedRadio16()
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


void CDXTXKQ::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	b_nMode = 1;
}





void CDXTXKQ::OnBnClickedRadio5()
{
	// TODO: 在此添加控件通知处理程序代码
	b_nMode = 2;
}
