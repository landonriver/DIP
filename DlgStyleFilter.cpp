// DlgStyleFilter.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "DlgStyleFilter.h"
#include "stdafx.h"

// DlgStyleFilter 对话框

IMPLEMENT_DYNAMIC(DlgStyleFilter, CDialogEx)

DlgStyleFilter::DlgStyleFilter(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DlgStyleFilter, pParent)
	, m_intType(0)
	, m_nMode(0)
	, m_SThre(128)
	, m_c()
{

}

DlgStyleFilter::~DlgStyleFilter()
{
}

void DlgStyleFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_intType);
	DDX_Radio(pDX, IDC_RADIO10, m_nMode);
	DDX_Text(pDX, Thre_Style, m_SThre);
	DDX_Text(pDX, coefficient, m_c);
	DDX_Text(pDX, IDC_EDIT_S1, m_fpArray[0]);
	DDX_Text(pDX, IDC_EDIT_S2, m_fpArray[1]);
	DDX_Text(pDX, IDC_EDIT_S3, m_fpArray[2]);
	DDX_Text(pDX, IDC_EDIT_S4, m_fpArray[3]);
	DDX_Text(pDX, IDC_EDIT_S5, m_fpArray[4]);
	DDX_Text(pDX, IDC_EDIT_S6, m_fpArray[5]);
	DDX_Text(pDX, IDC_EDIT_S7, m_fpArray[6]);
	DDX_Text(pDX, IDC_EDIT_S8, m_fpArray[7]);
	DDX_Text(pDX, IDC_EDIT_S9, m_fpArray[8]);
}


BEGIN_MESSAGE_MAP(DlgStyleFilter, CDialogEx)

	ON_BN_CLICKED(IDC_RADIO1, &DlgStyleFilter::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &DlgStyleFilter::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &DlgStyleFilter::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &DlgStyleFilter::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &DlgStyleFilter::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &DlgStyleFilter::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO7, &DlgStyleFilter::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO8, &DlgStyleFilter::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_RADIO9, &DlgStyleFilter::OnBnClickedRadio9)
	ON_BN_CLICKED(IDC_RADIO10, &DlgStyleFilter::OnBnClickedRadio10)
	ON_BN_CLICKED(IDC_RADIO11, &DlgStyleFilter::OnBnClickedRadio11)

	ON_BN_CLICKED(IDC_BUTTONSAVE, &DlgStyleFilter::OnBnClickedButtonsave)
	ON_BN_CLICKED(IDC_BUTTONLOAD, &DlgStyleFilter::OnBnClickedButtonload)
	ON_BN_CLICKED(IDC_BUTTONPREVIEW, &DlgStyleFilter::OnBnClickedButtonpreview)
	ON_BN_CLICKED(IDC_BUTTONREcover, &DlgStyleFilter::OnBnClickedButtonrecover)
END_MESSAGE_MAP()


// DlgStyleFilter 消息处理程序


BOOL DlgStyleFilter::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	BOOL	bEnable;

	bEnable = FALSE;
	m_c = 1;

	m_fpArray[0] = 0.0;
	m_fpArray[1] = 0.0;
	m_fpArray[2] = 0.0;
	m_fpArray[3] = 0.0;
	m_fpArray[4] = 0.0;
	m_fpArray[5] = 0.0;
	m_fpArray[6] = 0.0;
	m_fpArray[7] = 0.0;
	m_fpArray[8] = 0.0;
	// 设置模板元素文本框Enable状态

		// 设置文本框不可编辑

	(CEdit*)GetDlgItem(Thre_Style)->EnableWindow(bEnable);
	(CEdit*)GetDlgItem(coefficient)->EnableWindow(bEnable);
	(CEdit*)GetDlgItem(IDC_EDIT_S1)->EnableWindow(bEnable);
	(CEdit*)GetDlgItem(IDC_EDIT_S2)->EnableWindow(bEnable);
	(CEdit*)GetDlgItem(IDC_EDIT_S3)->EnableWindow(bEnable);
	(CEdit*)GetDlgItem(IDC_EDIT_S4)->EnableWindow(bEnable);
	(CEdit*)GetDlgItem(IDC_EDIT_S5)->EnableWindow(bEnable);
	(CEdit*)GetDlgItem(IDC_EDIT_S6)->EnableWindow(bEnable);
	(CEdit*)GetDlgItem(IDC_EDIT_S7)->EnableWindow(bEnable);
	(CEdit*)GetDlgItem(IDC_EDIT_S8)->EnableWindow(bEnable);
	(CEdit*)GetDlgItem(IDC_EDIT_S9)->EnableWindow(bEnable);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE

}




void DlgStyleFilter::OnBnClickedRadio1()
{
	//底片效果
	m_c = 1;
	m_intType = 0;
	m_SThre = 255;
	// 设置模板元素
	m_fpArray[0] = 0.0;
	m_fpArray[1] = 0.0;
	m_fpArray[2] = 0.0;
	m_fpArray[3] = 0.0;
	m_fpArray[4] = -1.0;
	m_fpArray[5] = 0.0;
	m_fpArray[6] = 0.0;
	m_fpArray[7] = 0.0;
	m_fpArray[8] = 0.0;
	// 更新文本框状态
	UpdateEdit();

	// 更新
	UpdateData(FALSE);
}


void DlgStyleFilter::OnBnClickedRadio2()
{
	//均值模糊
	m_intType = 1;
	m_c = (FLOAT)(1.0 / 9.0);
	m_SThre = 0;
	// 设置模板元素
	m_fpArray[0] = 1.0;
	m_fpArray[1] = 1.0;
	m_fpArray[2] = 1.0;
	m_fpArray[3] = 1.0;
	m_fpArray[4] = 1.0;
	m_fpArray[5] = 1.0;
	m_fpArray[6] = 1.0;
	m_fpArray[7] = 1.0;
	m_fpArray[8] = 1.0;
	// 更新文本框状态
	UpdateEdit();

	// 更新
	UpdateData(FALSE);
}


void DlgStyleFilter::OnBnClickedRadio3()
{
	//高斯模糊
	m_intType = 2;
	m_c = (FLOAT)(1.0 / 16.0);
	m_SThre = 0;
	// 设置模板元素
	m_fpArray[0] = 1.0;
	m_fpArray[1] = 2.0;
	m_fpArray[2] = 1.0;
	m_fpArray[3] = 2.0;
	m_fpArray[4] = 4.0;
	m_fpArray[5] = 2.0;
	m_fpArray[6] = 1.0;
	m_fpArray[7] = 2.0;
	m_fpArray[8] = 1.0;

	// 更新文本框状态
	UpdateEdit();

	// 更新
	UpdateData(FALSE);
}


void DlgStyleFilter::OnBnClickedRadio4()
{
	//拉普拉斯锐化

	m_intType = 3;
	//设置拉普拉斯模板
	m_c = 1.0;
	m_SThre = 0;
	m_fpArray[0] = -1.0;
	m_fpArray[1] = -1.0;
	m_fpArray[2] = -1.0;
	m_fpArray[3] = -1.0;
	m_fpArray[4] = 9.0;
	m_fpArray[5] = -1.0;
	m_fpArray[6] = -1.0;
	m_fpArray[7] = -1.0;
	m_fpArray[8] = -1.0;
	// 更新文本框状态
	UpdateEdit();

	// 更新
	UpdateData(FALSE);
}


void DlgStyleFilter::OnBnClickedRadio5()
{
	//浮雕效果
	m_intType = 4;
	//浮雕模板
	m_c = 1.0;
	m_SThre = 128;
	m_fpArray[0] = 1.0;
	m_fpArray[1] = 0.0;
	m_fpArray[2] = 0.0;
	m_fpArray[3] = 0.0;
	m_fpArray[4] = 0.0;
	m_fpArray[5] = 0.0;
	m_fpArray[6] = 0.0;
	m_fpArray[7] = 0.0;
	m_fpArray[8] = -1.0;
	// 更新文本框状态
	UpdateEdit();

	// 更新
	UpdateData(FALSE);
}


void DlgStyleFilter::OnBnClickedRadio6()
{
	//改变亮度
	m_intType = 5;
	m_c = 1;

	m_fpArray[0] = 0.0;
	m_fpArray[1] = 0.0;
	m_fpArray[2] = 0.0;
	m_fpArray[3] = 0.0;
	m_fpArray[4] = 1.0;
	m_fpArray[5] = 0.0;
	m_fpArray[6] = 0.0;
	m_fpArray[7] = 0.0;
	m_fpArray[8] = 0.0;
	// 更新文本框状态
	UpdateEdit();
	(CEdit*)GetDlgItem(Thre_Style)->EnableWindow(true);

	// 更新
	UpdateData(FALSE);
}

void DlgStyleFilter::OnBnClickedRadio7()
{
	//自定义
	m_intType = 6;
	m_fpArray[0] = GetDlgItemInt(IDC_EDIT_S1);//获取指定ID的编辑框内容
	m_fpArray[1] = GetDlgItemInt(IDC_EDIT_S2);
	m_fpArray[2] = GetDlgItemInt(IDC_EDIT_S3);
	m_fpArray[3] = GetDlgItemInt(IDC_EDIT_S4);
	m_fpArray[4] = GetDlgItemInt(IDC_EDIT_S5);

	m_fpArray[5] = GetDlgItemInt(IDC_EDIT_S6);
	m_fpArray[6] = GetDlgItemInt(IDC_EDIT_S7);
	m_fpArray[7] = GetDlgItemInt(IDC_EDIT_S8);
	m_fpArray[8] = GetDlgItemInt(IDC_EDIT_S9);

	m_c = GetDlgItemInt(coefficient);//同上
	m_SThre = GetDlgItemInt(Thre_Style);//同上

	// 更新文本框状态
	UpdateEdit();

	// 更新
	UpdateData(TRUE);
}


void DlgStyleFilter::OnBnClickedRadio8()
{
	//soble垂直算子
	m_intType = 7;
	m_c = 1.0;
	m_SThre = 0;
	if (m_nMode == 0) {
		// 设置模板元素
		m_fpArray[0] = -1.0;
		m_fpArray[1] = 0.0;
		m_fpArray[2] = 1.0;
		m_fpArray[3] = -2.0;
		m_fpArray[4] = 0.0;
		m_fpArray[5] = 2.0;
		m_fpArray[6] = -1.0;
		m_fpArray[7] = 0.0;
		m_fpArray[8] = 1.0;
	}
	//soble水平算子
	if (m_nMode == 1) {
		// 设置模板元素
		m_fpArray[0] = -1.0;
		m_fpArray[1] = -2.0;
		m_fpArray[2] = -1.0;
		m_fpArray[3] = 0.0;
		m_fpArray[4] = 0.0;
		m_fpArray[5] = 0.0;
		m_fpArray[6] = 1.0;
		m_fpArray[7] = 2.0;
		m_fpArray[8] = 1.0;
	}
	// 更新文本框状态
	UpdateEdit();

	// 更新
	UpdateData(FALSE);
}


void DlgStyleFilter::OnBnClickedRadio9()
{
	//prewitt垂直算子
	m_intType = 8;
	m_c = 1.0;
	m_SThre = 0;
	if (m_nMode == 0) {
		// 设置模板元素
		m_fpArray[0] = 1.0;
		m_fpArray[1] = 0.0;
		m_fpArray[2] = -1.0;
		m_fpArray[3] = 1.0;
		m_fpArray[4] = 0.0;
		m_fpArray[5] = -1.0;
		m_fpArray[6] = 1.0;
		m_fpArray[7] = 0.0;
		m_fpArray[8] = -1.0;
	}
	//prewitt水平算子
	if (m_nMode == 1) {
		// 设置模板元素
		m_fpArray[0] = -1.0;
		m_fpArray[1] = -1.0;
		m_fpArray[2] = -1.0;
		m_fpArray[3] = 0.0;
		m_fpArray[4] = 0.0;
		m_fpArray[5] = 0.0;
		m_fpArray[6] = 1.0;
		m_fpArray[7] = 1.0;
		m_fpArray[8] = 1.0;
	}
	// 更新文本框状态
	UpdateEdit();

	// 更新
	UpdateData(FALSE);
}


void DlgStyleFilter::OnBnClickedRadio10()
{

	m_nMode = 0;
	//sobel垂直模板
	if (m_intType == 7) {
		// 设置模板元素
		m_fpArray[0] = -1.0;
		m_fpArray[1] = 0.0;
		m_fpArray[2] = 1.0;
		m_fpArray[3] = -2.0;
		m_fpArray[4] = 0.0;
		m_fpArray[5] = 2.0;
		m_fpArray[6] = -1.0;
		m_fpArray[7] = 0.0;
		m_fpArray[8] = 1.0;
	}
	//prewitt垂直算子
	else if (m_intType == 8) {
		// 设置模板元素
		m_fpArray[0] = 1.0;
		m_fpArray[1] = 0.0;
		m_fpArray[2] = -1.0;
		m_fpArray[3] = 1.0;
		m_fpArray[4] = 0.0;
		m_fpArray[5] = -1.0;
		m_fpArray[6] = 1.0;
		m_fpArray[7] = 0.0;
		m_fpArray[8] = -1.0;
	}
	// 更新文本框状态
	UpdateEdit();

	// 更新
	UpdateData(FALSE);
}


void DlgStyleFilter::OnBnClickedRadio11()
{
	m_nMode = 1;
	//sobel水平模板
	if (m_intType == 7) {
		// 设置模板元素
		m_fpArray[0] = -1.0;
		m_fpArray[1] = -2.0;
		m_fpArray[2] = -1.0;
		m_fpArray[3] = 0.0;
		m_fpArray[4] = 0.0;
		m_fpArray[5] = 0.0;
		m_fpArray[6] = 1.0;
		m_fpArray[7] = 2.0;
		m_fpArray[8] = 1.0;
	}
	//prewitt水平算子
	else if (m_intType == 8) {
		// 设置模板元素
		m_fpArray[0] = -1.0;
		m_fpArray[1] = -1.0;
		m_fpArray[2] = -1.0;
		m_fpArray[3] = 0.0;
		m_fpArray[4] = 0.0;
		m_fpArray[5] = 0.0;
		m_fpArray[6] = 1.0;
		m_fpArray[7] = 1.0;
		m_fpArray[8] = 1.0;
	}

	// 更新文本框状态
	UpdateEdit();

	// 更新
	UpdateData(FALSE);
}

void DlgStyleFilter::UpdateEdit()
{
	BOOL	bEnable;

	// 循环变量
	int		i = 0;
	int		j = 0;

	// 判断是不是自定义模板
	if (m_intType == 6)
	{
		bEnable = TRUE;
	}
	else
	{
		bEnable = FALSE;
	}
	// 设置文本框不可编辑
	(CEdit*)GetDlgItem(Thre_Style)->EnableWindow(bEnable);
	(CEdit*)GetDlgItem(coefficient)->EnableWindow(bEnable);
	(CEdit*)GetDlgItem(IDC_EDIT_S1)->EnableWindow(bEnable);
	(CEdit*)GetDlgItem(IDC_EDIT_S2)->EnableWindow(bEnable);
	(CEdit*)GetDlgItem(IDC_EDIT_S3)->EnableWindow(bEnable);
	(CEdit*)GetDlgItem(IDC_EDIT_S4)->EnableWindow(bEnable);
	(CEdit*)GetDlgItem(IDC_EDIT_S5)->EnableWindow(bEnable);
	(CEdit*)GetDlgItem(IDC_EDIT_S6)->EnableWindow(bEnable);
	(CEdit*)GetDlgItem(IDC_EDIT_S7)->EnableWindow(bEnable);
	(CEdit*)GetDlgItem(IDC_EDIT_S8)->EnableWindow(bEnable);
	(CEdit*)GetDlgItem(IDC_EDIT_S9)->EnableWindow(bEnable);
}


void DlgStyleFilter::OnBnClickedButtonsave()
{
	//保存算子
	CFileDialog dlg(FALSE, _T("txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"(所有文件)*.txt");
	dlg.m_ofn.lpstrTitle = L"Save File";
	/*dlg.m_ofn.lpstrInitialDir = L"C:\\Users\\fenline\\Desktop";//默认路径*/
	if (dlg.DoModal() == IDOK) {

		/*CFileDialog dlg(FALSE, _T("txt"), _T("addr.txt"));*/
		CString strEDITS1, strEDITS2, strEDITS3, strEDITS4, strEDITS5, strEDITS6, strEDITS7, strEDITS8, strEDITS9,
			strPort, strThre;
		CString strFile = dlg.GetPathName();//获取完整路径


		GetDlgItemText(IDC_EDIT_S1, strEDITS1);//获取指定ID的编辑框内容
		GetDlgItemText(IDC_EDIT_S2, strEDITS2);
		GetDlgItemText(IDC_EDIT_S3, strEDITS3);
		GetDlgItemText(IDC_EDIT_S4, strEDITS4);
		GetDlgItemText(IDC_EDIT_S5, strEDITS5);
		GetDlgItemText(IDC_EDIT_S6, strEDITS6);
		GetDlgItemText(IDC_EDIT_S7, strEDITS7);
		GetDlgItemText(IDC_EDIT_S8, strEDITS8);
		GetDlgItemText(IDC_EDIT_S9, strEDITS9);

		GetDlgItemText(coefficient, strPort);//同上
		GetDlgItemText(Thre_Style, strThre);//同上

		CStdioFile file;

		if (file.Open(strFile, CStdioFile::modeCreate | CStdioFile::modeNoTruncate | CStdioFile::modeWrite))//创建/打开文件
		{

			file.WriteString(strEDITS1);//写入内容
			file.WriteString(_T("\n"));//换行
			file.WriteString(strEDITS2);//写入内容
			file.WriteString(_T("\n"));//换行
			file.WriteString(strEDITS3);//写入内容
			file.WriteString(_T("\n"));//换行
			file.WriteString(strEDITS4);//写入内容
			file.WriteString(_T("\n"));//换行
			file.WriteString(strEDITS5);//写入内容
			file.WriteString(_T("\n"));//换行
			file.WriteString(strEDITS6);//写入内容
			file.WriteString(_T("\n"));//换行
			file.WriteString(strEDITS7);//写入内容
			file.WriteString(_T("\n"));//换行
			file.WriteString(strEDITS8);//写入内容
			file.WriteString(_T("\n"));//换行
			file.WriteString(strEDITS9);//写入内容
			file.WriteString(_T("\n"));//换行
			file.WriteString(strPort);//写入内容
			file.WriteString(_T("\n"));//换行
			file.WriteString(strThre);//写入内容
			file.Close();//关闭输出文件
		}
	}
}


void DlgStyleFilter::OnBnClickedButtonload()
{
	//装载算子
	CFileDialog fdlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"All files(*.*)|*.txt|*.JPG|*.PNG|*.BMP||");
	fdlg.m_ofn.lpstrTitle = L"Open File";

	if (fdlg.DoModal() == IDOK)
	{
		CStdioFile file;
		CString strEDITS1, strEDITS2, strEDITS3, strEDITS4, strEDITS5, strEDITS6, strEDITS7, strEDITS8, strEDITS9, strPort, strThre;
		CString strFile = fdlg.GetPathName();//获取完整路径
		if (file.Open(strFile, CFile::modeRead))
		{

			if (file.ReadString(strEDITS1))
				GetDlgItem(IDC_EDIT_S1)->SetWindowText(strEDITS1);
			if (file.ReadString(strEDITS2))
				GetDlgItem(IDC_EDIT_S2)->SetWindowText(strEDITS2);
			if (file.ReadString(strEDITS3))
				GetDlgItem(IDC_EDIT_S3)->SetWindowText(strEDITS3);

			if (file.ReadString(strEDITS4))
				GetDlgItem(IDC_EDIT_S4)->SetWindowText(strEDITS4);
			if (file.ReadString(strEDITS5))
				GetDlgItem(IDC_EDIT_S5)->SetWindowText(strEDITS5);
			if (file.ReadString(strEDITS6))
				GetDlgItem(IDC_EDIT_S6)->SetWindowText(strEDITS6);
			if (file.ReadString(strEDITS7))
				GetDlgItem(IDC_EDIT_S7)->SetWindowText(strEDITS7);
			if (file.ReadString(strEDITS8))
				GetDlgItem(IDC_EDIT_S8)->SetWindowText(strEDITS8);
			if (file.ReadString(strEDITS9))
				GetDlgItem(IDC_EDIT_S9)->SetWindowText(strEDITS9);
			if (file.ReadString(strPort))
				GetDlgItem(coefficient)->SetWindowText(strPort);
			if (file.ReadString(strThre))
				GetDlgItem(Thre_Style)->SetWindowText(strThre);
			file.Close();
		}

	}


	// 更新
	UpdateData(TRUE);

}

BOOL WINAPI Template(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int iTempH, int iTempW,
	int iTempMX, int iTempMY, FLOAT* fpArray, FLOAT fCoef, float threshold)
{
	// 指向复制图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;
	// 指向源图像的指针
	unsigned char* lpSrc;

	// 指向要复制区域的指针
	unsigned char* lpDst;

	// 循环变量
	LONG	i;
	LONG	j;
	LONG	k;
	LONG	l;

	// 计算结果
	FLOAT	fResult;
	// 图像每行的字节数
	LONG lLineBytes;
	// 计算图像每行的字节数
	lLineBytes = (lWidth + 3) / 4 * 4;
	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lLineBytes * lHeight);
	// 判断是否内存分配失败
	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}
	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);
	// 初始化图像为原始图像
	memcpy(lpNewDIBBits, lpDIBBits, lLineBytes * lHeight);
	// 行(除去边缘几行)
	for (i = iTempMY; i < lHeight - iTempH + iTempMY + 1; i++)
	{
		// 列(除去边缘几列)
		for (j = iTempMX; j < lWidth - iTempW + iTempMX + 1; j++)
		{
			// 指向新DIB第i行，第j个象素的指针
			lpDst = (unsigned char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			fResult = 0;

			// 计算
			for (k = 0; k < iTempH; k++)
			{
				for (l = 0; l < iTempW; l++)
				{
					// 指向DIB第i - iTempMY + k行，第j - iTempMX + l个象素的指针
					lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i + iTempMY - k)
						+ j - iTempMX + l;
					// 保存象素值
					fResult += (*lpSrc) * fpArray[k * iTempW + l];
				}
			}
			// 乘上系数
			fResult *= fCoef;
			//加上常数
			fResult += threshold;
			//取绝对值
			fResult = (FLOAT)fabs(fResult);

			if (fResult > 255)
			{
				*lpDst = 255;
			}
			else if (fResult < 0)
			{
				*lpDst = 0;

			}
			else {
				*lpDst = (unsigned char)(fResult + 0.5);
			}
		}
	}
	// 复制变换后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// 返回
	return TRUE;

}
void DlgStyleFilter::OnBnClickedButtonpreview()
{

	// 指向DIB象素指针
	unsigned char* lpSrc;

	//模板高度
	int iTempH;
	//模板宽度
	int iTempW;

	//模板中心元素X坐标
	int iTempMX;
	//模板中心元素Y坐标
	int iTempMY;

	// 设定平移量（3*3）
	iTempH = 3;
	iTempW = 3;
	iTempMX = 1;
	iTempMY = 1;

	//反色单独处理
	if (m_intType == 0) {
		int gap = 1;
		LONG  fTemp;
		if (lpSrcBitCount == 8)gap = 1;
		else if (lpSrcBitCount == 24)gap = 3;
		for (int i = 0; i < lSrcHeight; i++) {
			// 每列
			for (int j = 0; j < lSrcWidth; j++) {
				// 指向DIB第i行，第j个像素的指针
				for (int k = 0; k < gap; k++) {
					lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j * gap + k;

					fTemp = *lpSrc;
					fTemp = 255 - fTemp;
					*lpSrc = (unsigned char)fTemp;

				}
			}
		}
	}
	else {
		Template(lpSrcStartBits, lSrcWidth, lSrcHeight,
			iTempH, iTempW, iTempMX, iTempMY, m_fpArray, m_c, m_SThre);
	}
	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);
	//UpdateData(false);

}


void DlgStyleFilter::OnBnClickedButtonrecover()
{
	for (int i = 0; i < lSrcHeight ; i++)
		for (int j = 0; j < lSrcWidth ; j++)
		{
			lpSrcStartBits[i * lSrcWidth + j] = lpstartBits[i * lSrcWidth + j];

		}

	// 设置脏标记
	pDoc->SetModifiedFlag(false);///////////////////////////////////////////

	// 更新视图
	pDoc->UpdateAllViews(NULL);
	//UpdateData(false);
}
