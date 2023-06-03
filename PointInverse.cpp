// PointInverse.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "PointInverse.h"


// PointInverse 对话框

IMPLEMENT_DYNAMIC(PointInverse, CDialogEx)

PointInverse::PointInverse(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PointInverse, pParent)
{

}

PointInverse::~PointInverse()
{
}

void PointInverse::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PointInverse, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// PointInverse 消息处理程序
void PointInverse::OnPaint()
{

	CPaintDC dc(this); // device context for painting

	//获取绘制坐标的文本框
	CWnd* pWnd = GetDlgItem(IDC_inverse);
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
	pPenRed->CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	//创建画笔对象
	CPen* pPenBlue = new CPen;
	//蓝色画笔，红绿蓝
	pPenBlue->CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
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


	//更改成蓝色画笔
	pDC->SelectObject(pPenBlue);
	//画两条变换线，没有计算斜率,没有交互
	pLeft.x = 10;
	pLeft.y = 35;
	//pDC->MoveTo(10,25);
	pDC->MoveTo(pLeft);
	pRight.x = 265;
	pRight.y = 280;
	//pDC->LineTo(265,280);
	pDC->LineTo(pRight);

	// 恢复以前的画笔
	pDC->SelectObject(pOldPen);

	// 删除新的画笔
	delete pPenRed;
	delete pPenBlue;
	delete pPenGreen;
}
