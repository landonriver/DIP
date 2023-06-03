﻿// PointStre.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "PointStre.h"
#include "method.h"

// PointStre 对话框

IMPLEMENT_DYNAMIC(PointStre, CDialogEx)

PointStre::PointStre(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PointStre, pParent)
	, m_bX1(0)
	, m_bY1(0)
	, m_bX2(0)
	, m_bY2(0)
{

}

PointStre::~PointStre()
{
}

void PointStre::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_bX1, m_bX1);
	DDV_MinMaxByte(pDX, m_bX1, 0, 255);
	DDX_Text(pDX, IDC_bX2, m_bX2);
	DDV_MinMaxByte(pDX, m_bY1, 0, 255);
	DDX_Text(pDX, IDC_bY1, m_bY1);
	DDV_MinMaxByte(pDX, m_bX2, 0, 255);
	DDX_Text(pDX, IDC_bY2, m_bY2);
	DDV_MinMaxByte(pDX, m_bY2, 0, 255);
}


BEGIN_MESSAGE_MAP(PointStre, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_EN_KILLFOCUS(IDC_bX1, &PointStre::OnEnKillfocusbx1)
	ON_EN_KILLFOCUS(IDC_bX2, &PointStre::OnEnKillfocusbx2)
	ON_EN_KILLFOCUS(IDC_bY1, &PointStre::OnEnKillfocusby1)
	ON_EN_KILLFOCUS(IDC_bY2, &PointStre::OnEnKillfocusby2)
	ON_BN_CLICKED(IDC_BUTTON1, &PointStre::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &PointStre::OnBnClickedButton2)
END_MESSAGE_MAP()


// PointStre 消息处理程序
BOOL PointStre::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 调用默认OnInitDialog函数
	CDialog::OnInitDialog();

	// 获取绘制直方图的标签
	CWnd* pWnd = GetDlgItem(IDC_COORDP);

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
	m_iIsDraging = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void PointStre::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 当用户单击鼠标左键开始拖动
	if (m_MouseRect.PtInRect(point))
	{
		CRect	rectTemp;

		// 计算点1临近区域
		rectTemp.left = m_MouseRect.left + m_bX1 - 2;
		rectTemp.right = m_MouseRect.left + m_bX1 + 2;
		rectTemp.top = 255 + m_MouseRect.top - m_bY1 - 2;
		rectTemp.bottom = 255 + m_MouseRect.top - m_bY1 + 2;

		// 判断用户是不是想拖动点1
		if (rectTemp.PtInRect(point))
		{

			// 设置拖动状态1，拖动点1
			m_iIsDraging = 1;

			// 更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));
		}
		else
		{
			// 计算点2临近区域
			rectTemp.left = m_MouseRect.left + m_bX2 - 2;
			rectTemp.right = m_MouseRect.left + m_bX2 + 2;
			rectTemp.top = 255 + m_MouseRect.top - m_bY2 - 2;
			rectTemp.bottom = 255 + m_MouseRect.top - m_bY2 + 2;

			// 判断用户是不是想拖动点2
			if (rectTemp.PtInRect(point))
			{

				// 设置拖动状态为2，拖动点2
				m_iIsDraging = 2;

				// 更改光标
				::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));
			}
		}
	}

	// 默认单击鼠标左键处理事件
	CDialog::OnLButtonDown(nFlags, point);
}


void PointStre::OnLButtonUp(UINT nFlags, CPoint point)
{
	// 当用户释放鼠标左键停止拖动
	if (m_iIsDraging != 0)
	{
		// 重置拖动状态
		m_iIsDraging = 0;
	}

	// 默认释放鼠标左键处理事件
	CDialog::OnLButtonUp(nFlags, point);
}


void PointStre::OnMouseMove(UINT nFlags, CPoint point)
{
	// 判断当前光标是否在绘制区域
	if (m_MouseRect.PtInRect(point))
	{
		// 判断是否正在拖动
		if (m_iIsDraging != 0)
		{
			// 判断正在拖动点1还是点2
			if (m_iIsDraging == 1)
			{
				// 判断是否下限<上限
				if (point.x - m_MouseRect.left < m_bX2)
				{
					// 更改下限
					m_bX1 = (BYTE)(point.x - m_MouseRect.left);
				}
				else
				{
					// 下限拖过上限，设置为上限-1
					m_bX1 = m_bX2 - 1;

					// 重设鼠标位置
					point.x = m_MouseRect.left + m_bX2 - 1;
				}

				// 更改Y坐标
				m_bY1 = (BYTE)(255 + m_MouseRect.top - point.y);
			}
			else
			{
				// 正在拖动点2

				// 判断是否上限>下限
				if (point.x - m_MouseRect.left > m_bX1)
				{
					// 更改下限
					m_bX2 = (BYTE)(point.x - m_MouseRect.left);
				}
				else
				{
					// 下限拖过上限，设置为下限＋1
					m_bX2 = m_bX1 + 1;

					// 重设鼠标位置
					point.x = m_MouseRect.left + m_bX1 + 1;
				}

				// 更改Y坐标
				m_bY2 = (BYTE)(255 + m_MouseRect.top - point.y);
			}

			// 更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));

			// 更新
			UpdateData(FALSE);

			// 重绘
			InvalidateRect(m_MouseRect, TRUE);
		}
		else
		{
			CRect	rectTemp1;
			CRect	rectTemp2;

			// 计算点1临近区域
			rectTemp1.left = m_MouseRect.left + m_bX1 - 2;
			rectTemp1.right = m_MouseRect.left + m_bX1 + 2;
			rectTemp1.top = 255 + m_MouseRect.top - m_bY1 - 2;
			rectTemp1.bottom = 255 + m_MouseRect.top - m_bY1 + 2;

			// 计算点2临近区域
			rectTemp2.left = m_MouseRect.left + m_bX2 - 2;
			rectTemp2.right = m_MouseRect.left + m_bX2 + 2;
			rectTemp2.top = 255 + m_MouseRect.top - m_bY2 - 2;
			rectTemp2.bottom = 255 + m_MouseRect.top - m_bY2 + 2;

			// 判断用户在点1或点2旁边
			if ((rectTemp1.PtInRect(point)) || (rectTemp2.PtInRect(point)))
			{
				// 更改光标
				::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));
			}
		}
	}

	// 默认鼠标移动处理事件
	CDialog::OnMouseMove(nFlags, point);
}


void PointStre::OnPaint()
{
	// 字符串
	CString str;

	// 设备上下文
	CPaintDC dc(this);

	// 获取绘制坐标的文本框
	CWnd* pWnd = GetDlgItem(IDC_COORDP);

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
	pPenBlue->CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

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

	// 更改成蓝色画笔
	pDC->SelectObject(pPenBlue);

	// 绘制坐标值
	str.Format(L"(%d, %d)", m_bX1, m_bY1);
	pDC->TextOut(m_bX1 + 10, 281 - m_bY1, str);
	str.Format(L"(%d, %d)", m_bX2, m_bY2);
	pDC->TextOut(m_bX2 + 10, 281 - m_bY2, str);

	// 绘制用户指定的变换直线
	pDC->MoveTo(10, 280);
	pDC->LineTo(m_bX1 + 10, 280 - m_bY1);
	pDC->LineTo(m_bX2 + 10, 280 - m_bY2);
	pDC->LineTo(265, 25);

	// 绘制点边缘的小矩形
	CBrush  brush;
	brush.CreateSolidBrush(RGB(0, 255, 0));

	// 选中刷子
	CGdiObject* pOldBrush = pDC->SelectObject(&brush);

	// 绘制小矩形
	pDC->Rectangle(m_bX1 + 10 - 2, 280 - m_bY1 - 2, m_bX1 + 12, 280 - m_bY1 + 2);
	pDC->Rectangle(m_bX2 + 10 - 2, 280 - m_bY2 - 2, m_bX2 + 12, 280 - m_bY2 + 2);

	// 恢复以前的画笔
	pDC->SelectObject(pOldPen);

	// 绘制边缘
	pDC->MoveTo(10, 25);
	pDC->LineTo(265, 25);
	pDC->LineTo(265, 280);

	// 删除新的画笔
	delete pPenRed;
	delete pPenBlue;
}


void PointStre::OnEnKillfocusbx1()
{
	// 更新
	UpdateData(TRUE);

	// 判断是否下限超过上限
	if (m_bX1 > m_bX2)
	{
		// 互换
		BYTE bTemp = m_bX1;
		m_bX1 = m_bX2;
		m_bX2 = bTemp;
		bTemp = m_bY1;
		m_bY1 = m_bY2;
		m_bY2 = bTemp;

		// 更新
		UpdateData(FALSE);
	}

	// 重绘
	InvalidateRect(m_MouseRect, TRUE);
}


void PointStre::OnEnKillfocusbx2()
{
	// 更新
	UpdateData(TRUE);

	// 判断是否下限超过上限
	if (m_bX1 > m_bX2)
	{
		// 互换
		BYTE bTemp = m_bX1;
		m_bX1 = m_bX2;
		m_bX2 = bTemp;
		bTemp = m_bY1;
		m_bY1 = m_bY2;
		m_bY2 = bTemp;

		// 更新
		UpdateData(FALSE);
	}

	// 重绘
	InvalidateRect(m_MouseRect, TRUE);
}


void PointStre::OnEnKillfocusby1()
{
	// 更新
	UpdateData(TRUE);

	// 重绘
	InvalidateRect(m_MouseRect, TRUE);
}


void PointStre::OnEnKillfocusby2()
{
	// 更新
	UpdateData(TRUE);

	// 重绘
	InvalidateRect(m_MouseRect, TRUE);
}


void PointStre::OnOK()
{
	// 判断是否下限超过上限
	if (m_bX1 > m_bX2)
	{
		// 互换
		BYTE bTemp = m_bX1;
		m_bX1 = m_bX2;
		m_bX2 = bTemp;
		bTemp = m_bY1;
		m_bY1 = m_bY2;
		m_bY2 = bTemp;

		// 更新
		UpdateData(FALSE);
	}

	// 默认处理事件
	CDialog::OnOK();
}



void PointStre::OnBnClickedButton1()
{
	//指向原图像的指针
	unsigned char* lpSrc;
	// 循环变量
	LONG i;
	LONG j;
	//灰度映射表
	BYTE bMap[256];
	//图像每行的字节数
	LONG lLineBytes;
	// 计算.图像每行的字节数
	lLineBytes = (lWidth * 8 + 31) / 32 * 4;
	//计算灰度映射表
	for (i = 0; i <= m_bX1; i++)
	{ //判断bX1是否大于0（防止分母为0)
		if (m_bX1 > 0)
		{
			// 线性变换
			bMap[i] = (BYTE)m_bY1 * i / m_bX1;
		}
		else
		{ //直接赋值为0
			bMap[i] = 0;
		}

	}
	for (; i <= m_bX2; i++)
	{
		// 判断bX1是否等于bX2（防止分母为0)
		if (m_bX2 != m_bX1) {

			//线性变换
			bMap[i] = m_bY1 + (BYTE)((m_bY2 - m_bY1) * (i - m_bX1) / (m_bX2 - m_bX1));
		}
		else
			// 直接赋值为bY1
			bMap[i] = m_bY1;
	}
	for (; i < 256; i++) {
		// 判断bX2是否等于255（防止分母为0 ） 
		if (m_bX2 != 255)
			//线性变换
			bMap[i] = m_bY2 + (BYTE)((255 - m_bY2) * (i - m_bX2) / (255 - m_bX2));
		else
			//直接赋值为255
			bMap[i] = 255;
	}

	//每行
	for (i = 0; i < lHeight; i++) {
		//每列
		for (j = 0; j < lWidth; j++) {
			// 指向DIB第i行，第j个像素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			// 计算新的灰度值
			*lpSrc = bMap[*lpSrc];
		}
	}

	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);
	UpdateData(false);

}


void PointStre::OnBnClickedButton2()
{
	for (int i = 0; i < lHeight; i++)
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