// CLinverse.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "CLinverse.h"


// CLinverse 对话框

IMPLEMENT_DYNAMIC(CLinverse, CDialogEx)

CLinverse::CLinverse(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Linverse, pParent)
	, m_sol4(128)
{

}

CLinverse::~CLinverse()
{
}

void CLinverse::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Linverse, m_sol4);
}


BEGIN_MESSAGE_MAP(CLinverse, CDialogEx)
	ON_WM_PAINT()
	ON_EN_KILLFOCUS(IDC_Linverse, &CLinverse::OnEnKillfocusThreshold)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CLinverse 消息处理程序
BOOL CLinverse::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//获取绘制图形的标签
	CWnd* pWnd = GetDlgItem(IDC_COORD4);
	//计算接受鼠标事件的有效区域
	pWnd->GetClientRect(m_MouseRect4);
	pWnd->ClientToScreen(&m_MouseRect4);

	CRect rect;
	GetClientRect(rect);
	ClientToScreen(&rect);

	m_MouseRect4.top -= rect.top;
	m_MouseRect4.left -= rect.left;
	//设置接受鼠标事件的有效区域
	m_MouseRect4.top += 25;
	m_MouseRect4.left += 10;
	m_MouseRect4.bottom = m_MouseRect4.top + 255;
	m_MouseRect4.right = m_MouseRect4.left + 256;
	//初始化拖动状态
	m_bIsDrawing4 = FALSE;


	return true;
}


void CLinverse::OnPaint()
{
	CPaintDC dc(this); // device context for painting


	//获取绘制坐标的文本框
	CWnd* pWnd = GetDlgItem(IDC_COORD4);
	//字符串
	CString str;
	CPoint pLeft, pRight, pCenterTop, pCenterBottom;
	//指针
	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	//x1(left),y1(top),x2(right),y2(bottom)
	pDC->Rectangle(0, 0, 330, 300);
	//创建画笔对象
	CPen* pPenRed = new CPen;
	//红色画笔，红绿蓝
	pPenRed->CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	//创建画笔对象
	CPen* pPenBlue = new CPen;
	//蓝色画笔，红绿蓝
	pPenBlue->CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	//创建画笔对象
	CPen* pPenGreen = new CPen;
	//绿色画笔，红绿蓝
	pPenGreen->CreatePen(PS_DOT, 1, RGB(0, 255, 0));
	//选中当前红色画笔，并保存以前的画笔
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);
	//绘制坐标轴
	pDC->MoveTo(10, 10);
	//垂直轴
	pDC->LineTo(10, 280);
	//水平轴
	pDC->LineTo(320, 280);
	//写坐标
	str.Format(L"0");
	pDC->TextOut(10, 281, str);
	str.Format(L"255");
	pDC->TextOut(265, 281, str);
	pDC->TextOutW(11, 25, str);
	//绘制X箭头
	pDC->LineTo(315, 275);
	pDC->MoveTo(320, 280);
	pDC->LineTo(315, 285);
	//绘制Y箭头
	pDC->MoveTo(10, 10);
	pDC->LineTo(5, 15);
	pDC->MoveTo(10, 10);
	pDC->LineTo(15, 15);
	//更改成绿色画笔,画垂直线

	pDC->SelectObject(pPenGreen);
	pCenterTop.x = 10 + m_sol4;//128;
	pCenterTop.y = 25;

	pCenterBottom.x = 10 + m_sol4;//128;
	pCenterBottom.y = 280;
	pDC->MoveTo(pCenterTop);
	pDC->LineTo(pCenterBottom);

	//更改成蓝色画笔
	pDC->SelectObject(pPenBlue);
	//画两条变换线，没有计算斜率,没有交互
	pLeft.x = 10;
	pLeft.y = 25;
	//pDC->MoveTo(10,280);
	pDC->MoveTo(pLeft);
	pCenterTop.x = 10 + m_sol4;//128;
	pCenterTop.y = 280;
	//pDC->LineTo(138,25);
	pDC->LineTo(pCenterTop);
	pRight.x = 265;
	pRight.y = 280;
	//pDC->LineTo(265,280);
	pDC->LineTo(pRight);

}


void CLinverse::OnEnKillfocusThreshold()
{
	// TODO: 在此添加控件通知处理程序代码
	//保存用户设置
	UpdateData(TRUE);
	//重绘
	InvalidateRect(m_MouseRect4, TRUE);
}


void CLinverse::OnLButtonDown(UINT nFlags, CPoint point)
{
	//  当用户单击鼠标左键开始拖动
	//判断是否在有效区域
	if (m_MouseRect4.PtInRect(point))
	{
		if (point.x == (m_MouseRect4.left + m_sol4))
		{
			//设置拖动状态
			m_bIsDrawing4 = TRUE;
			//更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		}
	}

	//默认
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CLinverse::OnLButtonUp(UINT nFlags, CPoint point)
{
	//  当用户释放鼠标左键停止拖动
	if (m_bIsDrawing4)
	{
		//重新设置拖动状态
		m_bIsDrawing4 = FALSE;
	}
	//默认
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CLinverse::OnMouseMove(UINT nFlags, CPoint point)
{
	//  判断当前光标是否在绘制区域
	if (m_MouseRect4.PtInRect(point))
	{
		//判断是否在拖动
		if (m_bIsDrawing4)
		{
			//更改阈值
			m_sol4 = (BYTE)(point.x - m_MouseRect4.left);
			//更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
			//更新
			UpdateData(FALSE);
			//重绘
			InvalidateRect(m_MouseRect4, TRUE);
		}
		else if (point.x == (m_MouseRect4.left + m_sol4))
		{
			//更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		}
	}
	//默认
	CDialogEx::OnMouseMove(nFlags, point);
}

