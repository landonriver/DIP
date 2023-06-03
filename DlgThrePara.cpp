// DlgThrePara.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "DlgThrePara.h"


// DlgThrePara 对话框

IMPLEMENT_DYNAMIC(DlgThrePara, CDialogEx)

DlgThrePara::DlgThrePara(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDlgThrePara, pParent)
	, m_bThre(0)
	, m_intType(0)
{

}

DlgThrePara::~DlgThrePara()
{
}

void DlgThrePara::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, Thre, m_bThre);
	DDV_MinMaxByte(pDX, m_bThre, 0, 255);
	DDX_Radio(pDX, IDC_RADIO1, m_intType);
}



BEGIN_MESSAGE_MAP(DlgThrePara, CDialogEx)
	ON_EN_KILLFOCUS(Thre, &DlgThrePara::OnEnKillfocusThre)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_RADIO1, &DlgThrePara::OnBnClickedRadio1)

	ON_BN_CLICKED(IDC_RADIO3, &DlgThrePara::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO2, &DlgThrePara::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO4, &DlgThrePara::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_calculate, &DlgThrePara::OnBnClickedcalculate)
	ON_BN_CLICKED(IDC_BUTTONPRE, &DlgThrePara::OnBnClickedButtonpre)
	ON_BN_CLICKED(IDC_BUTTON2REC, &DlgThrePara::OnBnClickedButton2rec)
END_MESSAGE_MAP()


// DlgThrePara 消息处理程序
BOOL DlgThrePara::OnInitDialog()
{
	// 调用默认OnInitDialog函数
	CDialog::OnInitDialog();

	// 获取绘制直方图的标签
	CWnd* pWnd = GetDlgItem(IDC_COORDT);

	// 计算接受鼠标事件的有效区域
	pWnd->GetClientRect(m_MouseRect);
	pWnd->ClientToScreen(&m_MouseRect);

	CRect rect;
	GetClientRect(rect);
	ClientToScreen(&rect);

	m_MouseRect.top -= rect.top;
	m_MouseRect.left -= rect.left;

	// 设置接受鼠标事件的有效区域
	m_MouseRect.top += 25;
	m_MouseRect.left += 10;
	m_MouseRect.bottom = m_MouseRect.top + 255;
	m_MouseRect.right = m_MouseRect.left + 256;

	// 初始化拖动状态
	m_bIsDraging = FALSE;

	// 返回TRUE
	return TRUE;
}


void DlgThrePara::OnEnKillfocusThre()
{
	// 更新
	UpdateData(TRUE);

	// 重绘
	InvalidateRect(m_MouseRect, TRUE);
}


void DlgThrePara::OnPaint()
{
	// 字符串
	CString str;

	// 设备上下文
	CPaintDC dc(this);

	// 获取绘制坐标的文本框
	CWnd* pWnd = GetDlgItem(IDC_COORDT);

	// 指针
	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();

	pDC->Rectangle(0, 0, 330, 300);

	// 创建画笔对象
	CPen* pPenRed = new CPen;

	// 红色画笔
	pPenRed->CreatePen(PS_SOLID, 2, RGB(255, 0, 0));

	// 创建画笔对象
	CPen* pPenBlue = new CPen;

	// 蓝色画笔
	pPenBlue->CreatePen(PS_SOLID, 2, RGB(0, 0, 255));

	// 创建画笔对象
	CPen* pPenGreen = new CPen;

	// 绿色画笔
	pPenGreen->CreatePen(PS_DOT, 1, RGB(0, 255, 0));

	// 选中当前红色画笔，并保存以前的画笔
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);

	// 绘制坐标轴
	pDC->MoveTo(10, 10);

	// 垂直轴
	pDC->LineTo(10, 280);

	// 水平轴
	pDC->LineTo(320, 280);

	// 写坐标
	str.Format(L"0");
	pDC->TextOut(10, 281, str);

	str.Format(L"255");
	pDC->TextOut(265, 281, str);
	pDC->TextOut(11, 25, str);

	// 绘制X轴箭头
	pDC->LineTo(315, 275);
	pDC->MoveTo(320, 280);
	pDC->LineTo(315, 285);

	// 绘制X轴箭头
	pDC->MoveTo(10, 10);
	pDC->LineTo(5, 15);
	pDC->MoveTo(10, 10);
	pDC->LineTo(15, 15);

	// 更改成绿色画笔
	pDC->SelectObject(pPenGreen);

	// 绘制窗口阈值线
	pDC->MoveTo(m_bThre + 10, 25);
	pDC->LineTo(m_bThre + 10, 280);

	// 更改成蓝色画笔
	pDC->SelectObject(pPenBlue);

	// 绘制坐标值
	str.Format(L"%d", m_bThre);
	pDC->TextOut(m_bThre + 10, 281, str);

	// 绘制用户指定的窗口（注意转换坐标系）
	pDC->MoveTo(10, 280);
	pDC->LineTo(m_bThre + 10, 280);
	pDC->LineTo(m_bThre + 10, 25);
	pDC->LineTo(265, 25);

	// 恢复以前的画笔
	pDC->SelectObject(pOldPen);

	// 绘制边缘
	pDC->MoveTo(10, 25);
	pDC->LineTo(265, 25);
	pDC->LineTo(265, 280);

	// 删除新的画笔
	delete pPenRed;
	delete pPenBlue;
	delete pPenGreen;
}


void DlgThrePara::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 当用户单击鼠标左键开始拖动

	// 判断是否在有效区域中
	if (m_MouseRect.PtInRect(point))
	{
		if (point.x == (m_MouseRect.left + m_bThre))
		{

			// 设置拖动状态
			m_bIsDraging = TRUE;

			// 更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		}
	}

	// 默认单击鼠标左键处理事件
	CDialog::OnLButtonDown(nFlags, point);
}


void DlgThrePara::OnLButtonUp(UINT nFlags, CPoint point)
{
	// 当用户释放鼠标左键停止拖动
	if (m_bIsDraging)
	{
		// 重置拖动状态
		m_bIsDraging = FALSE;
	}

	// 默认释放鼠标左键处理事件
	CDialog::OnLButtonUp(nFlags, point);
}


void DlgThrePara::OnMouseMove(UINT nFlags, CPoint point)
{
	// 判断当前光标是否在绘制区域
	if (m_MouseRect.PtInRect(point))
	{
		// 判断是否正在拖动
		if (m_bIsDraging)
		{
			// 更改阈值
			m_bThre = (BYTE)(point.x - m_MouseRect.left);

			// 更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));

			// 更新
			UpdateData(FALSE);

			// 重绘
			InvalidateRect(m_MouseRect, TRUE);
		}
		else if (point.x == (m_MouseRect.left + m_bThre))
		{
			// 更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		}
	}

	// 默认鼠标移动处理事件
	CDialog::OnMouseMove(nFlags, point);
}


void DlgThrePara::OnBnClickedRadio1()
{
	//迭代法

	m_intType = 0;
	/*CString   temp;//调试输出
	temp.Format(L"%d ", m_intType);
	AfxMessageBox(temp);*/
	//指向原图像的指针
	unsigned char* lpSrc;
	//循环变量
	LONG i; LONG j;
	// 图像每行的字节数
	LONG lLineBytes;
	//讦算图像每行的字节数
	lLineBytes = (lWidth * 8 + 31) / 32 * 4;;
	//平均值
	int averageS = 0;
	int averageL = 0;
	//两部分个数
	int countS = 0;
	int countL = 0;
	//计算阈值
	int T1 = 128;
	int T2 = 128;
	//预设参数T0
	int T0 = 3;

	while (T0 > abs(T1 - T2)) {
		T1 = T2;
		// 每行
		for (i = 0; i < lHeight; i++) {
			// 每列
			for (j = 0; j < lWidth; j++) {
				// 指向DIB第i行，第j个像素的指针
				lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
				//判断是否小于阙值
				if ((*lpSrc) < T1) {
					averageS += (*lpSrc);
					countS++;
				}
				else {
					// 直接赋值为255 
					averageL += (*lpSrc);
					countL++;
				}
			}
		}
		averageL /= countL;
		averageS /= countS;
		T2 = (averageL + averageS) / 2;

	}
	m_bThre = T2;


}


void DlgThrePara::OnBnClickedRadio3()
{
	//直方图法

	m_intType = 2;
	int i = 0;
	int j = 0;

	unsigned char* lpSrc;//指向原图像的指针
	//讦算图像每行的字节数
	long lLineBytes = (lWidth * 8 + 31) / 32 * 4;;
	int thresHold = 0;//最佳二值化阈值
	unsigned int hist[256];//用来统计各个灰度值的像素个数
	int sumHist = lWidth * lHeight;//总的像素个数
	//统计各个灰度值的像素个数
	for (i = 0; i < lHeight; i++)
	{
		for (j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个像素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			hist[(*lpSrc)]++;
		}

	}
	//灰度值总数最大得两个
	int max1 = 0;
	int max2 = 0;
	int min = 0;
	//最多的两个灰度值
	int T1 = 0;
	int T2 = 0;
	//阈值
	int T = 0;
	for (j = 0; j < 256; j++)
	{
		if (hist[j] > max1) {
			max1 = hist[j];
			T1 = j;
		}
	}

	for (j = 0; j < 256; j++)
	{
		if (hist[j] > max2 && j != T1) {
			max2 = hist[j];
			T2 = j;
		}
	}
	min = max1;
	if (T2 > T1) {
		for (j = T1; j < T2; j++)
		{
			if (hist[j] < min) {
				min = hist[j];
				T = j;
			}
		}
	}
	else {
		for (j = T2; j < T1; j++)
		{
			if (hist[j] < min) {
				min = hist[j];
				T = j;
			}
		}
	}
	m_bThre = T;
}


void DlgThrePara::OnBnClickedRadio2()
{
	//大津法

	m_intType = 1;
	int i = 0;
	int j = 0;

	unsigned char* lpSrc;//指向原图像的指针
	int thresHold = 0;//最佳二值化阈值
	unsigned int hist[256];//用来统计各个灰度值的像素个数
	int sumHist = lWidth * lHeight;//总的像素个数
	float g = 0.0;
	float maxg = 0.0;
	float u0 = 0.0;
	float u1 = 0.0;
	float w0 = 0.0;
	float w1 = 0.0;

	unsigned int N0 = 0;
	unsigned int N1 = 0;

	for (i = 0; i < 256; i++)

	{
		hist[i] = 0;
	}

	//统计各个灰度值的像素个数
	for (i = 0; i < lHeight; i++)
	{
		for (j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个像素的指针
			lpSrc = (unsigned char*)lpDIBBits + lSrcLineBytes * (lHeight - 1 - i) + j;
			int x = *lpSrc;
			hist[x]++;
		}

	}

	for (i = 0; i < 256; i++)
	{
		N0 = 0;
		//计算N0、u0、w0

		for (j = 0; j < i; j++)
		{
			N0 += hist[j];
		}
		w0 = N0 * 1.0 / sumHist;

		for (j = 0; j < i; j++)
		{
			if (N0 == 0)
			{
				u0 = 0;
			}
			else
			{
				u0 += hist[j] * j * 1.0 / N0;
			}
		}

		//计算N1、u1、w1
		N1 = sumHist - N0;
		w1 = 1 - w0;

		for (j = i; j < 256; j++)
		{
			if (N1 == 0)
			{
				u1 = 0;
			}
			else
			{
				u1 += hist[j] * j * 1.0 / N1;
			}
		}
		g = w0 * w1 * (u0 - u1) * (u0 - u1);

		if (g > maxg)
		{
			maxg = g;
			thresHold = i;
		}
	}
	m_bThre = thresHold;


}


void DlgThrePara::OnBnClickedRadio4()
{
	//自适应阈值变换
	m_intType = 3;
	m_bThre = 0;

	//指向原图像的指针
	unsigned char* lpSrc;
	//循环变量
	LONG i; LONG j;
	// 图像每行的字节数
	LONG lLineBytes;
	//讦算图像每行的字节数
	lLineBytes = (lWidth * 8 + 31) / 32 * 4;;

	int sumHist = (lWidth * lHeight) / 4;//  1/4的像素个数
	//计算阈值
	int T = 0;
	//**************************第一部分**************************
			// 每行
	for (i = 0; i < lHeight / 2; i++) {
		// 每列
		for (j = 0; j < lWidth / 2; j++) {
			// 指向DIB第i行，第j个像素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			T += *lpSrc;
		}
	}
	T = T / sumHist ;
	for (i = 0; i < lHeight / 2; i++) {
		// 每列
		for (j = 0; j < lWidth / 2; j++) {
			// 指向DIB第i行，第j个像素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			//判断是否小于阙值
			if ((*lpSrc) < T) {
				//直接赋值为0
				*lpSrc = 0;
			}
			else {
				// 直接赋值为255 
				*lpSrc = 255;
			}
		}
	}
	T = 0;
	//**************************第2部分**************************
	// 		   // 每行
	for (i = 0; i < lHeight / 2; i++) {
		// 每列
		for (j = lWidth / 2; j < lWidth; j++) {
			// 指向DIB第i行，第j个像素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			T += *lpSrc;
		}
	}
	T = T / sumHist ;
	for (i = 0; i < lHeight / 2; i++) {
		// 每列
		for (j = lWidth / 2; j < lWidth; j++) {
			// 指向DIB第i行，第j个像素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			//判断是否小于阙值
			if ((*lpSrc) < T) {
				//直接赋值为0
				*lpSrc = 0;
			}
			else {
				// 直接赋值为255 
				*lpSrc = 255;
			}
		}
	}
	T = 0;
	//**************************第3部分**************************
	// 		   // 每行
	for (i = lHeight / 2; i < lHeight; i++) {
		// 每列
		for (j = 0; j < lWidth / 2; j++) {
			// 指向DIB第i行，第j个像素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			T += *lpSrc;
		}
	}
	T = T / sumHist ;
	for (i = lHeight / 2; i < lHeight; i++) {
		// 每列
		for (j = 0; j < lWidth / 2; j++) {
			// 指向DIB第i行，第j个像素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			//判断是否小于阙值
			if ((*lpSrc) < T) {
				//直接赋值为0
				*lpSrc = 0;
			}
			else {
				// 直接赋值为255 
				*lpSrc = 255;
			}
		}
	}
	T = 0;
	//**************************第4部分**************************	
	// 		      // 每行
	for (i = lHeight / 2; i < lHeight; i++) {
		// 每列
		for (j = lWidth / 2; j < lWidth; j++) {
			// 指向DIB第i行，第j个像素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			T += *lpSrc;
		}
	}
	T = T / sumHist;
	for (i = lHeight / 2; i < lHeight; i++) {
		// 每列
		for (j = lWidth / 2; j < lWidth; j++) {
			// 指向DIB第i行，第j个像素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			//判断是否小于阙值
			if ((*lpSrc) < T) {
				//直接赋值为0
				*lpSrc = 0;
			}
			else {
				// 直接赋值为255 
				*lpSrc = 255;
			}
		}
	}

}


void DlgThrePara::OnBnClickedcalculate()
{
	if (m_intType == 3) {
		// 设置文本框不可编辑
		(CEdit*)GetDlgItem(Thre)->EnableWindow(FALSE);

	}
	else {
		(CEdit*)GetDlgItem(Thre)->EnableWindow(TRUE);
	}
	// 更新
	UpdateData(FALSE);
	//重绘
	InvalidateRect(m_MouseRect, TRUE);
	Sleep(300);//停顿300ms
}




void DlgThrePara::OnBnClickedButtonpre()
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


	//循环变量
	LONG i; LONG j;
	// 图像每行的字节数
	LONG lLineBytes;
	//讦算图像每行的字节数
	lLineBytes = (lWidth * 8 + 31) / 32 * 4;;
	// 每行
	for (i = 0; i < lHeight; i++) {
		// 每列
		for (j = 0; j < lWidth; j++) {
			// 指向DIB第i行，第j个像素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			//判断是否小于阙值
			if ((*lpSrc) < m_bThre) {
				//直接赋值为0
				*lpSrc = 0;
			}
			else {
				// 直接赋值为255 
				*lpSrc = 255;
			}
		}
	}


	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);
	UpdateData(false);
}


void DlgThrePara::OnBnClickedButton2rec()
{
	for (int i = 0; i < lHeight ; i++)
		for (int j = 0; j < lWidth; j++)
		{
			lpDIBBits[i * lWidth + j] = lpstartBits[i * lWidth + j];

		}

	// 设置脏标记
	pDoc->SetModifiedFlag(false);///////////////////////////////////////////

	// 更新视图
	pDoc->UpdateAllViews(NULL);
	UpdateData(false);
}
