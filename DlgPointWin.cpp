// DlgPointWin.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "DlgPointWin.h"


// DlgPointWin 对话框

IMPLEMENT_DYNAMIC(DlgPointWin, CDialogEx)

DlgPointWin::DlgPointWin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DlgPointWin, pParent)
	, m_bUp(0)
	, m_bLow(0)
{

}

DlgPointWin::~DlgPointWin()
{
}

void DlgPointWin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Up, m_bUp);
	DDX_Text(pDX, IDC_EDIT_Low, m_bLow);
	DDV_MinMaxByte(pDX, m_bUp, 0, 255);
	DDV_MinMaxByte(pDX, m_bLow, 0, 255);
}


BEGIN_MESSAGE_MAP(DlgPointWin, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_EN_KILLFOCUS(IDC_EDIT_Low, &DlgPointWin::OnEnKillfocusEditLow)
	ON_EN_KILLFOCUS(IDC_EDIT_Up, &DlgPointWin::OnEnKillfocusEditUp)
	ON_BN_CLICKED(IDC_BUTTON1, &DlgPointWin::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &DlgPointWin::OnBnClickedButton2)
END_MESSAGE_MAP()


// DlgPointWin 消息处理程序
void DlgPointWin::OnOK()
{
	// 判断是否下限超过上限
	if (m_bLow > m_bUp)
	{
		// 互换
		BYTE bTemp = m_bLow;
		m_bLow = m_bUp;
		m_bUp = bTemp;
	}

	// 默认处理事件
	CDialog::OnOK();
}


void DlgPointWin::OnPaint()
{
	// 字符串
	CString str;

	// 设备上下文
	CPaintDC dc(this);

	// 获取绘制坐标的文本框
	CWnd* pWnd = GetDlgItem(IDC_COORDWin);

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

	// 绘制窗口上下限
	pDC->MoveTo(m_bLow + 10, 25);
	pDC->LineTo(m_bLow + 10, 280);

	pDC->MoveTo(m_bUp + 10, 25);
	pDC->LineTo(m_bUp + 10, 280);

	// 更改成蓝色画笔
	pDC->SelectObject(pPenBlue);

	// 绘制坐标值
	str.Format(L"(%d, %d)", m_bLow, m_bLow);
	pDC->TextOut(m_bLow + 10, 281 - m_bLow, str);
	str.Format(L"(%d, %d)", m_bUp, m_bUp);
	pDC->TextOut(m_bUp + 10, 281 - m_bUp, str);

	// 绘制用户指定的窗口（注意转换坐标系）
	pDC->MoveTo(10, 280);
	pDC->LineTo(m_bLow + 10, 280);
	pDC->LineTo(m_bLow + 10, 280 - m_bLow);
	pDC->LineTo(m_bUp + 10, 280 - m_bUp);
	pDC->LineTo(m_bUp + 10, 25);
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


BOOL DlgPointWin::OnInitDialog()
{
	// 调用默认OnInitDialog函数
	CDialog::OnInitDialog();

	// 获取绘制直方图的标签
	CWnd* pWnd = GetDlgItem(IDC_COORDWin);

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

	// 返回TRUE
	return TRUE;
}


void DlgPointWin::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 当用户单击鼠标左键开始拖动
	if (m_MouseRect.PtInRect(point))
	{
		if (point.x == (m_MouseRect.left + m_bLow))
		{

			// 设置拖动状态1，拖动下限
			m_iIsDraging = 1;

			// 更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		}
		else if (point.x == (m_MouseRect.left + m_bUp))
		{

			// 设置拖动状态为2，拖动上限
			m_iIsDraging = 2;

			// 更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		}
	}

	// 默认单击鼠标左键处理事件
	CDialog::OnLButtonDown(nFlags, point);
}


void DlgPointWin::OnLButtonUp(UINT nFlags, CPoint point)
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


void DlgPointWin::OnMouseMove(UINT nFlags, CPoint point)
{
	// 判断当前光标是否在绘制区域
	if (m_MouseRect.PtInRect(point))
	{
		// 判断是否正在拖动
		if (m_iIsDraging != 0)
		{
			// 判断正在拖动上限还是下限
			if (m_iIsDraging == 1)
			{
				// 判断是否下限<上限
				if (point.x - m_MouseRect.left < m_bUp)
				{
					// 更改下限
					m_bLow = (BYTE)(point.x - m_MouseRect.left);
				}
				else
				{
					// 下限拖过上限，设置为上限-1
					m_bLow = m_bUp - 1;

					// 重设鼠标位置
					point.x = m_MouseRect.left + m_bUp - 1;
				}
			}
			else
			{
				// 正在拖动上限

				// 判断是否上限>下限
				if (point.x - m_MouseRect.left > m_bLow)
				{
					// 更改下限
					m_bUp = (BYTE)(point.x - m_MouseRect.left);
				}
				else
				{
					// 下限拖过上限，设置为下限＋1
					m_bUp = m_bLow + 1;

					// 重设鼠标位置
					point.x = m_MouseRect.left + m_bLow + 1;
				}
			}

			// 更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));

			// 更新
			UpdateData(FALSE);

			// 重绘
			InvalidateRect(m_MouseRect, TRUE);
		}
		else if (point.x == (m_MouseRect.left + m_bLow) || point.x == (m_MouseRect.left + m_bUp))
		{
			// 更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		}
	}

	// 默认鼠标移动处理事件
	CDialog::OnMouseMove(nFlags, point);
}


void DlgPointWin::OnEnKillfocusEditLow()
{
	// 更新
	UpdateData(TRUE);

	// 判断是否下限超过上限
	if (m_bLow > m_bUp)
	{
		// 互换
		BYTE bTemp = m_bLow;
		m_bLow = m_bUp;
		m_bUp = bTemp;

		// 更新
		UpdateData(FALSE);
	}

	// 重绘
	InvalidateRect(m_MouseRect, TRUE);
}


void DlgPointWin::OnEnKillfocusEditUp()
{
	// 更新
	UpdateData(TRUE);

	// 判断是否下限超过上限
	if (m_bLow > m_bUp)
	{
		// 互换
		BYTE bTemp = m_bLow;
		m_bLow = m_bUp;
		m_bUp = bTemp;

		// 更新
		UpdateData(FALSE);
	}

	// 重绘
	InvalidateRect(m_MouseRect, TRUE);
}


void DlgPointWin::OnBnClickedButton1()
{
	// 指向DIB象素指针
	unsigned char* lpSrc;

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
			if ((*lpSrc) < m_bLow) {
				//直接赋值为0
				*lpSrc = 0;
			}
			else if ((*lpSrc) > m_bUp) {
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


void DlgPointWin::OnBnClickedButton2()
{
	for (int i = 0; i < lHeight ; i++)
		for (int j = 0; j < lWidth ; j++)
		{
			lpDIBBits[i * lWidth + j] = lpstartBits[i * lWidth + j];

		}

	// 设置脏标记
	pDoc->SetModifiedFlag(false);///////////////////////////////////////////

	// 更新视图
	pDoc->UpdateAllViews(NULL);
	UpdateData(false);
}
