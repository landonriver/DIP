// MFCApplication1View.cpp: CMFCApplication1View 类的实现
//
#include"CDlgImgInfo.h"
#include"changeImgLight.h"
#include "pch.h"
#include "framework.h"
#include "method.h"
#include "DIgHistorgam.h"
#include "PointInverse.h"
#include "CDVinverse.h"
#include "CVinverse.h"
#include "CDLinverse.h"
#include "CLinverse.h"
#include "CLinerinverse.h"
#include "BPSperate.h"
#include "GammaTrans.h"
#include "CD2ZH.h"
#include "CDXTXPZ.h"
#include "CDXTXFS.h"
#include "CDXTXKQ.h"
#include "CDXTXBH.h"
#include "XTXNBJ.h"
#include "XTXWBJ.h"
#include "DlgThrePara.h"
#include "DlgPointWin.h"
#include "PointStre.h"
#include "DlgStyleFilter.h"
#include "DlgGTrans.h"
#include "MSC.h"
#include "QYCal1.h"
#include "QYCal2.h"
#include "canny.h"
#include "DlgUSM.h"



BYTE BayerPattern[8][8] = { 0,32,8,40,2,34,10,42,
					 48,16,56,24,50,18,58,26,
					 12,44,4,36,14,46,6,38,
					 60,28,52,20,62,30,54,22,
					 3,35,11,43,1,33,9,41,
					 51,19,59,27,49,17,57,25,
					 15,47,7,39,13,45,5,37,
					 63,31,55,23,61,29,53,21 };//m3抖动表

// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DispImgInfo, &CMFCApplication1View::OnDispimginfo)
	ON_COMMAND(ID_changeImgLight, &CMFCApplication1View::Onchangeimglight)
	ON_COMMAND(ID_changeWC, &CMFCApplication1View::Onchangewc)
	ON_COMMAND(ID_24CB24G, &CMFCApplication1View::On24cb24g)
	ON_COMMAND(ID_24CB8C, &CMFCApplication1View::On24cb8c)
	ON_COMMAND(ID_24CB8G, &CMFCApplication1View::On24cb8g)
	ON_COMMAND(ID_8CB8G, &CMFCApplication1View::On8cb8g)
	ON_COMMAND(ID_8GB2Z, &CMFCApplication1View::On8gb2z)
	ON_COMMAND(ID_8YDDXS, &CMFCApplication1View::On8yddxs)
	ON_COMMAND(ID_pointInvert, &CMFCApplication1View::Onpointinvert)
	ON_COMMAND(ID_VIEW_LARGEICON, &CMFCApplication1View::OnViewLargeicon)
	ON_COMMAND(ID_DVtrans, &CMFCApplication1View::OnDvtrans)

	ON_COMMAND(ID_Vtrans, &CMFCApplication1View::OnVtrans)
//	ON_COMMAND(ID_DLtrans, &CMFCApplication1View::OnDltrans)
ON_COMMAND(ID_DLtrans, &CMFCApplication1View::OnDltrans)
ON_COMMAND(ID_Ltrans, &CMFCApplication1View::OnLtrans)
ON_COMMAND(ID_Linetrans, &CMFCApplication1View::OnLinetrans)
ON_COMMAND(ID_BPSperate, &CMFCApplication1View::OnBpsperate)
ON_COMMAND(ID_LOGtrans, &CMFCApplication1View::OnLogtrans)
ON_COMMAND(ID_Gammatrans, &CMFCApplication1View::OnGammatrans)
ON_COMMAND(ID_JZLB, &CMFCApplication1View::OnJzlb)
ON_COMMAND(ID_GSLB, &CMFCApplication1View::OnGslb)
ON_COMMAND(ID_ZZLB, &CMFCApplication1View::OnZzlb)
ON_COMMAND(ID_addnoise, &CMFCApplication1View::Onaddnoise)
ON_COMMAND(ID_Lpls4, &CMFCApplication1View::OnLpls4)
ON_COMMAND(ID_Lpls8, &CMFCApplication1View::OnLpls8)
ON_COMMAND(ID_edgeRobert, &CMFCApplication1View::Onedgerobert)
ON_COMMAND(ID_edgeSobel, &CMFCApplication1View::Onedgesobel)
ON_COMMAND(ID_XTXPZ, &CMFCApplication1View::OnXtxpz)
ON_COMMAND(ID_XTXFS, &CMFCApplication1View::OnXtxfs)
ON_COMMAND(ID_XTXKQ, &CMFCApplication1View::OnXtxkq)
ON_COMMAND(ID_XTXBH, &CMFCApplication1View::OnXtxbh)
ON_COMMAND(ID_XTXNBJ, &CMFCApplication1View::OnXtxnbj)
ON_COMMAND(ID_XTXWBJ, &CMFCApplication1View::OnXtxwbj)
ON_COMMAND(ID_PointThre, &CMFCApplication1View::OnPointthre)
ON_COMMAND(PointWind, &CMFCApplication1View::OnPointwind)
ON_COMMAND(ID_PointStre, &CMFCApplication1View::OnPointstre)
ON_COMMAND(ID_ZFTJHH, &CMFCApplication1View::OnZftjhh)
ON_COMMAND(ID_StyleFilter, &CMFCApplication1View::OnStylefilter)
ON_COMMAND(ID_GTrans, &CMFCApplication1View::OnGtrans)
ON_COMMAND(ID_Transpose, &CMFCApplication1View::OnTranspose)
ON_COMMAND(ID_MirrorX, &CMFCApplication1View::OnMirrorx)
ON_COMMAND(ID_MirrorY, &CMFCApplication1View::OnMirrory)
ON_COMMAND(ID_oilPaint, &CMFCApplication1View::Onoilpaint)
ON_COMMAND(ID_MSC, &CMFCApplication1View::OnMsc)
ON_COMMAND(ID_MGlass, &CMFCApplication1View::OnMglass)
ON_COMMAND(ID_QYCal, &CMFCApplication1View::OnQycal)
ON_COMMAND(ID_CannyDec, &CMFCApplication1View::OnCannydec)
ON_COMMAND(ID_USM, &CMFCApplication1View::OnUsm)
ON_COMMAND(ID_AddSY, &CMFCApplication1View::OnAddsy)
ON_COMMAND(ID_ExtractSY, &CMFCApplication1View::OnExtractsy)
END_MESSAGE_MAP()

// CMFCApplication1View 构造/析构

CMFCApplication1View::CMFCApplication1View() noexcept
{
	// TODO: 在此处添加构造代码

}

CMFCApplication1View::~CMFCApplication1View()
{
}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCApplication1View 绘图

void CMFCApplication1View::OnDraw(CDC* pDC)
{
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	HGLOBAL hDIB = pDoc->GetHObject();

	// 判断DIB是否为空
	if (hDIB != NULL)
	{
		LPSTR lpDibSection = (LPSTR) ::GlobalLock((HGLOBAL)hDIB);

		// 获取DIB宽度
		int cxDIB = (int)pDoc->m_dib.GetWidth(lpDibSection);

		// 获取DIB高度
		int cyDIB = (int)pDoc->m_dib.GetHeight(lpDibSection);
		::GlobalUnlock((HGLOBAL)hDIB);
		CRect rcDIB;
		rcDIB.top = rcDIB.left = 0;
		rcDIB.right = cxDIB;
		rcDIB.bottom = cyDIB;
		CRect rcDest = rcDIB;
		// 输出DIB
		pDoc->m_dib.DrawDib(pDC->m_hDC, &rcDest, pDoc->GetHObject(),
			&rcDIB, pDoc->GetDocPal());
	}
}


// CMFCApplication1View 打印

BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCApplication1View 诊断

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View 消息处理程序


void CMFCApplication1View::OnDispimginfo()
{
	// 显示图像基本信息
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	 */
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////	
	CDlgImgInfo dlgPara;// 创建对话框		
	dlgPara.m_Width = lSrcWidth;
	dlgPara.m_Height = lSrcHeight;
	dlgPara.m_bitCount = lpSrcBitCount;

	if (dlgPara.DoModal() != IDOK)// 显示对话框， 
	{
		return;
	}

}


void CMFCApplication1View::Onchangeimglight()
{
	// 显示图像基本信息
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	 */
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////	
	int i, j;
	int offset;
	unsigned char* lpSrc;
	changeImgLight dlgPara;
	if (dlgPara.DoModal() != IDOK)// 显示对话框， 
	{
		return;
	}
	offset = dlgPara.delt;
	long linebytes;
	int temp, k;
	linebytes = ((lSrcWidth * lpSrcBitCount) + 31) / 32 * 4;

	int page = 1;
	if (lpSrcBitCount == 24)page = 3;
	if (lpSrcBitCount == 8)page = 1;
	for (i = 0; i < lSrcHeight; i++) {
		for (j = 0; j < lSrcWidth; j++) {
			for (k = 0; k < page; k++) {
				lpSrc = (unsigned char*)lpSrcStartBits + linebytes * (lSrcHeight - i - 1) + j * page + k;
				temp = *lpSrc + offset;
				if (temp > 255) {
					*lpSrc = 255;
				}
				else if (temp < 0) {
					*lpSrc = 0;
				}
				else {
					*lpSrc = (unsigned char)(temp + 0.5);
				}
			}
		}
	}
	delete dlgPara;
	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}


void CMFCApplication1View::Onchangewc()
{
	// 显示源图像
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////

	int lBitCountNew = lpSrcBitCount;
	long lLineBytesNew = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lBitCountNew);
	int PaletteSize = 0;
	if (lpSrcBitCount == 8) PaletteSize = 1024;
	long total = lSrcHeight * lLineBytesNew+sizeof(BITMAPINFOHEADER) + PaletteSize ;
	memcpy(lpSrcDib, pDoc->OriginBmp, total);
	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::On24cb24g()
{
	// 24位彩色图像变24位灰度图像
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	if (!lpSrcDib) return;
	if (pDoc->m_dib.GetBitCount(lpSrcDib) != 24)// 判断是否是24-bpp位图
	{
		AfxMessageBox(L"对不起，不是24位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////
	unsigned char* lpsrc;
	long i, j;
	long lLineBytes;
	lLineBytes = (((lSrcWidth * 24) + 31) / 32 * 4);
	for (i = 0; i < lSrcHeight;i++) {
		for (j = 0; j < lSrcWidth;j++) {
			int R, G, B;
			int GRAY;
			lpsrc = (unsigned char*)lpSrcStartBits + i * lLineBytes + j * 3;
			B = *lpsrc;
			lpsrc = (unsigned char*)lpSrcStartBits + i * lLineBytes + j * 3 + 1;
			G = *lpsrc;
			lpsrc = (unsigned char*)lpSrcStartBits + i * lLineBytes + j * 3 + 2;
			R = *lpsrc;
			GRAY = R * 0.299 + G * 0.587 + B * 0.114;

			lpsrc = (unsigned char*)lpSrcStartBits + i * lLineBytes + j * 3;
			*lpsrc = GRAY;
			lpsrc = (unsigned char*)lpSrcStartBits + i * lLineBytes + j * 3 + 1;
			*lpsrc = GRAY;
			lpsrc = (unsigned char*)lpSrcStartBits + i * lLineBytes + j * 3 + 2;
			*lpsrc = GRAY;
		}
	}
	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}




void CMFCApplication1View::On24cb8c()
{
	// 24位彩色图像变8位彩色图像
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	if (!lpSrcDib) return;
	if (pDoc->m_dib.GetBitCount(lpSrcDib) != 24)// 判断是否是24-bpp位图
	{
		AfxMessageBox(L"对不起，不是24位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////
		 // 指向源图像的指针
	unsigned char* lpSrc;
	// 循环变量
	LONG	i=0;
	LONG	j=0;
	// 图像每行的字节数
	LONG	lLineBytes;
	// 计算图像每行的字节数
	lLineBytes = (((lSrcWidth * 24) + 31) / 32 * 4);
	BITMAPINFOHEADER* pHead;
	RGBQUAD* pColorTable = NULL;
	int lineByteNew;
	int biBitCount = 8;
	lineByteNew = (lSrcWidth * biBitCount / 8 + 3) / 4 * 4;
	//灰度图像有颜色表，且颜色表表项为
	if (biBitCount == 8) {
		//申请颜色表所需要的空间，给颜色表赋值
		pColorTable = new RGBQUAD[256];
		memset(pColorTable, 0, sizeof(RGBQUAD) * 256);
	}
	BYTE* Index = new BYTE[lineByteNew * lSrcHeight]; //图像数据区的数据(保存在Index中)
	WORD* shortColor = new WORD[lineByteNew * lSrcHeight]; //颜色的高4位
	memset(shortColor, 0, sizeof(WORD) * lineByteNew * lSrcHeight); //清零

	int iRed, iGreen, iBlue;
	for (int i = 0; i < lSrcHeight; i++)
	{//取RGB颜色的高4位  
		for (int j = 0; j < lSrcWidth; j++)
		{
			lpSrc = (unsigned char*)lpSrcStartBits + lLineBytes * (lSrcHeight - 1 - i) + j * 3;
			iBlue = (*lpSrc) >> 4;
			iGreen = (*(++lpSrc)) >> 4;
			iRed = (*(++lpSrc)) >> 4;
			shortColor[lineByteNew * (lSrcHeight - 1 - i) + j] = (iBlue << 8) + (iGreen << 4) + iRed;
		}
	}
	//调用转换函数  24color To->8color
	BitTran(shortColor, lineByteNew * lSrcHeight, Index, pColorTable);

	//申请位图数据所需要的空间，读位图数据进内存
	unsigned char* pBmpBufNew;
	pBmpBufNew = new unsigned char[sizeof(BITMAPINFOHEADER) + 256 * 4];//申请新图像的空间
	memcpy(pBmpBufNew, (unsigned char*)lpSrcDib, sizeof(BITMAPINFOHEADER));//信息头拷贝
	pHead = (BITMAPINFOHEADER*)pBmpBufNew;
	pHead->biBitCount = 8;//改变位数,
	pHead->biHeight = lSrcHeight;
	pHead->biWidth = lSrcWidth;
	pHead->biClrUsed = 256;
	pHead->biClrImportant = 0;
	pHead->biCompression = 0;
	pHead->biPlanes = 1;
	pHead->biSize = 40;
	pHead->biSizeImage = lineByteNew * lSrcHeight;
	pHead->biXPelsPerMeter = 0;
	pHead->biYPelsPerMeter = 0;

	//拷贝
	memcpy(lpSrcDib, pBmpBufNew, sizeof(BITMAPINFOHEADER));
	memcpy(lpSrcDib + sizeof(BITMAPINFOHEADER), pColorTable, sizeof(RGBQUAD) * 256);
	memcpy(lpSrcDib + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256, Index, lineByteNew * lSrcHeight);

	delete[]Index;
	delete[]shortColor;


	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::On24cb8g()
{
	// 24位彩色图像变8位灰色图像
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	if (!lpSrcDib) return;
	if (pDoc->m_dib.GetBitCount(lpSrcDib) != 24)// 判断是否是24-bpp位图
	{
		AfxMessageBox(L"对不起，不是24位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
		 // 指向源图像的指针
	unsigned char* lpSrc;
	// 循环变量
	LONG	i;
	LONG	j;
	// 图像每行的字节数
	LONG	lLineBytes;
	// 计算图像每行的字节数
	lLineBytes = (((lSrcWidth * 24) + 31) / 32 * 4);
	BITMAPINFOHEADER* pHead;
	RGBQUAD* pColorTable;
	int lineByteNew;
	int biBitCount = 8;
	lineByteNew = (lSrcWidth * biBitCount / 8 + 3) / 4 * 4;
	//申请位图数据所需要的空间，读位图数据进内存
	unsigned char* pBmpBufNew;
	pBmpBufNew = new unsigned char[lineByteNew * lSrcHeight + sizeof(BITMAPINFOHEADER) + 256 * 4];//申请新图像的空间
	memcpy(pBmpBufNew, (unsigned char*)lpSrcDib, sizeof(BITMAPINFOHEADER));//信息头拷贝
	pHead = (BITMAPINFOHEADER*)pBmpBufNew;
	pHead->biBitCount = 8;//改变位数,
	pHead->biHeight = lSrcHeight;
	pHead->biWidth = lSrcWidth;
	pHead->biClrUsed = 256;
	pHead->biClrImportant = 0;
	pHead->biCompression = 0;
	pHead->biPlanes = 1;
	pHead->biSize = 40;
	pHead->biSizeImage = lineByteNew * lSrcHeight;
	pHead->biXPelsPerMeter = 0;
	pHead->biYPelsPerMeter = 0;
	pColorTable = (RGBQUAD*)(pBmpBufNew + sizeof(BITMAPINFOHEADER));
	//灰度图像有颜色表，且颜色表表项为
	if (biBitCount == 8) {
		//申请颜色表所需要的空间，给颜色表赋值
		for (int i = 0; i < 256; i++)
		{
			pColorTable[i].rgbBlue = i;
			pColorTable[i].rgbGreen = i;
			pColorTable[i].rgbRed = i;
			pColorTable[i].rgbReserved = 0;
		}
	}

	int Red, Green, Blue, Gray, offset;
	offset = sizeof(BITMAPINFOHEADER) + 256 * 4;
	//逐行扫描
	for (i = 0; i < lSrcHeight; i++)
	{
		//逐列扫描
		for (j = 0; j < lSrcWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpSrcStartBits + lLineBytes * (lSrcHeight - 1 - i) + j * 3;
			Blue = *lpSrc;
			Green = *(++lpSrc);
			Red = *(++lpSrc);
			Gray = (BYTE)(0.299 * Red + 0.587 * Green + 0.114 * Blue + 0.5);
			// 变换
			lpSrc = (unsigned char*)(pBmpBufNew + offset) + lineByteNew * (lSrcHeight - 1 - i) + j;
			*lpSrc = Gray;
		}
	}
	//拷贝
	memcpy(lpSrcDib, pBmpBufNew, lineByteNew * lSrcHeight + sizeof(BITMAPINFOHEADER) + 256 * 4);
	delete	[]pBmpBufNew;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//设置文档修改标志

	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::On8cb8g()
{
	//  8位彩色转8位灰度
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////

		  // 指向源图像的指针
	unsigned char* lpSrc;
	// 循环变量
	LONG	i;
	LONG	j;
	// 图像每行的字节数
	LONG	lLineBytes;

	// 计算图像每行的字节数
	lLineBytes = (((lSrcWidth * 8) + 31) / 32 * 4);

	// 灰度映射表
	BYTE bMap[256] = { 0 };
	RGBQUAD* pTable, * pTable1;//颜色表指针

	pTable = (RGBQUAD*)(lpSrcDib + sizeof(BITMAPINFOHEADER));
	for (i = 0; i < 256; i++)//生成新的调色板,并转换灰度
	{
		// 计算该颜色对应的灰度值g=0.299*r+0.587*g+0.114*b	
		bMap[i] = (BYTE)(0.299 * pTable->rgbRed + 0.587 * pTable->rgbGreen + 0.114 * pTable->rgbBlue + 0.5);
		pTable->rgbRed = (BYTE)i;
		pTable->rgbGreen = (BYTE)i;
		pTable->rgbBlue = (BYTE)i;
		pTable->rgbReserved = (BYTE)0;
		pTable++;
	}
	// 更换每个象素的颜色索引（即按照灰度映射表换成灰度值）
	//逐行扫描
	for (i = 0; i < lSrcHeight; i++)
	{
		//逐列扫描
		for (j = 0; j < lSrcWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpSrcStartBits + lLineBytes * (lSrcHeight - 1 - i) + j;
			// 变换
			*lpSrc = bMap[*lpSrc];
		}
	}

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

}


void CMFCApplication1View::On8gb2z()
{
	//  8位灰度图变二值图
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////
	unsigned char* lpSrc;
	int i, j;
	long linebytes;
	CD2ZH dlgPara;
	if (dlgPara.DoModal() != IDOK)// 显示对话框， 
	{
		return;
	}
	int offset = dlgPara.delt;
	int temp;
	linebytes = ((lSrcWidth * lpSrcBitCount) + 31) / 32 * 4;
	for (i = 0; i < lSrcHeight; i++) {
		for (j = 0; j < lSrcWidth; j++) {
			lpSrc = (unsigned char*)lpSrcStartBits + linebytes * (lSrcHeight - i - 1) + j ;
			temp = *lpSrc;
			if (temp >= offset) {
				*lpSrc = 255;
			}
			else *lpSrc = 0;
		}
	}
	delete dlgPara;
	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定


}


void CMFCApplication1View::On8yddxs()
{
	//  8位灰度图的半影调显示
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图象每行的字节数
		long	lSrcWidth;      //图象的宽度和高度
		long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////
	int palettesize = 0;
	if (lpSrcBitCount == 8) palettesize = 256 * sizeof(RGBQUAD);
	long total = lSrcLineBytes * lSrcHeight + sizeof(BITMAPINFOHEADER) + palettesize;
	long i,j;
	LPSTR lpSrcDibnew;//新图像图像指针
	LPSTR lpSSBN; //新图像像素指针
	unsigned char* bhy;//内存指针
	unsigned char* lpSrcy;
	unsigned char* lpSrcx;
	bhy = new BYTE[total];
	memcpy(bhy, lpSrcDib, total);
	lpSrcDibnew = (LPSTR)bhy;
	lpSSBN = pDoc->m_dib.GetBits(lpSrcDibnew);
	lpSrcDibnew = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	long linebytes = ((lSrcWidth * lpSrcBitCount) + 31) / 32 * 4;

	for (i = 0; i < lSrcHeight; i++) {
			
		for (j = 0; j < lSrcWidth; j++) {
			lpSrcy = (unsigned char*)lpSrcStartBits + linebytes * (lSrcHeight - i - 1) + j ;
			lpSrcx = (unsigned char*)lpSSBN + linebytes * (lSrcHeight - i - 1) + j;
			if ((*lpSrcy >> 2) > BayerPattern[i & 7][j & 7]) {
				*lpSrcx = 255;
			}
			else *lpSrcx = 0;
		}
	}

	memcpy(lpSrcDib, bhy,total);


	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定

}



void CMFCApplication1View::Onpointinvert()
{
	//图像反色
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	//if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	//{
	//	AfxMessageBox(L"对不起，不是256色位图！");// 警告				
	//	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
	//	return;									//返回
	//}
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////
	BeginWaitCursor();
	PointInverse dlgPara;// 创建对话框

	if (dlgPara.DoModal() != IDOK)// 显示对话框 
	{

		return;
	}
	delete dlgPara;
	float Fa = -1.0;
	float Fb = 255;
	if (lpSrcBitCount == 8) {
		LinerTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, Fa, Fb);
	}
	if (lpSrcBitCount == 24) {
		LinerTrans24(lpSrcStartBits, lSrcWidth, lSrcHeight, Fa, Fb);
	}
	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	EndWaitCursor();

}


void CMFCApplication1View::OnViewLargeicon()
{
	// 显示直方图
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档

	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	unsigned char* lpSrc;
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetBitCount(lpSrcDib) != 8)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是8位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数

	CDlgHistogram dlgPara;
	//显示直方图
	// 初始化变量值
	dlgPara.m_lpDIBBits = lpSrcStartBits;
	dlgPara.m_lWidth = lSrcWidth;
	dlgPara.m_lHeight = lSrcHeight;
	dlgPara.m_iLowGray = 0;
	dlgPara.m_iHighGray = 255;
	dlgPara.m_lLineBytes = lSrcLineBytes;

	if (dlgPara.DoModal() != IDOK) // 显示对话框 
	{
		return;
	}
	//////////////////////////
	delete dlgPara;
	EndWaitCursor();
	//设置文档修改标志
	//pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnDvtrans()
{
	// 倒V变换
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档

	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	unsigned char* lpSrc;
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetBitCount(lpSrcDib) != 8)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是8位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	////////////////////////////////////////////////////////////////////////////////
	CDVinverse dlgPara;
	dlgPara.m_threshold = 128;
	if (dlgPara.DoModal() != IDOK)// 显示对话框，设定平移量
	{
		return;
	}
	int type, threshold;
	threshold = dlgPara.m_threshold;
	type = 1;
	int i, j;
	FLOAT fTemp;//中间变量
	for (i = 0; i < lSrcHeight; i++) {
		// 每列
		for (j = 0; j < lSrcWidth; j++) {
			// 指向DIB第i行，第j个像素的指针

			lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
			fTemp = *lpSrc + 0;
			if (fTemp <= threshold) {
				fTemp = (255 / (float)(threshold)) * fTemp;
			}
			else {
				fTemp = (-255 / (float)(255 - threshold)) * (fTemp - threshold) + 255;
			}
			*lpSrc = (unsigned char)(fTemp + 0.5);
		}
	}

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

}


void CMFCApplication1View::OnVtrans()
{
	// V变换
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档

	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	unsigned char* lpSrc;
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetBitCount(lpSrcDib) != 8)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是8位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	////////////////////////////////////////////////////////////////////////////////
	CVinverse dlgPara;
	dlgPara.m_sol= 128;
	if (dlgPara.DoModal() != IDOK)// 显示对话框，设定平移量
	{
		return;
	}
	int type, threshold;
	threshold = dlgPara.m_sol;
	type = 2;
	int i, j;
	FLOAT fTemp;
	for (i = 0; i < lSrcHeight; i++) {
		// 每列
		for (j = 0; j < lSrcWidth; j++) {
			// 指向DIB第i行，第j个像素的指针

			lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
			fTemp = *lpSrc + 0;
			if (fTemp <= threshold) {
				fTemp = (-255 / (float)(threshold)) * fTemp + 255;
			}
			else {
				fTemp = (255 / (float)(255 - threshold)) * (fTemp - threshold);
			}
			*lpSrc = (unsigned char)(fTemp + 0.5);
		}
	}

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}



void CMFCApplication1View::OnDltrans()
{
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档

	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	unsigned char* lpSrc;
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetBitCount(lpSrcDib) != 8)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是8位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	////////////////////////////////////////////////////////////////////////////////
	CDLinverse dlgPara;
	dlgPara.m_sol3 = 128;
	if (dlgPara.DoModal() != IDOK)// 显示对话框，设定平移量
	{
		return;
	}
	int type, threshold;
	threshold = dlgPara.m_sol3;
	type = 3;
	int i, j;
	FLOAT fTemp;


	for (i = 0; i < lSrcHeight; i++) {
		// 每列
		for (j = 0; j < lSrcWidth; j++) {
			// 指向DIB第i行，第j个像素的指针

			lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
			fTemp = *lpSrc + 0;
			if (fTemp <= threshold) {
				fTemp = (255 / (float)(threshold)) * fTemp;
			}
			else {
				fTemp = 255;
			}
			*lpSrc = (unsigned char)(fTemp + 0.5);
		}
	}

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnLtrans()
{
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档

	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	unsigned char* lpSrc;
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetBitCount(lpSrcDib) != 8)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是8位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	////////////////////////////////////////////////////////////////////////////////
	CLinverse dlgPara;
	dlgPara.m_sol4 = 128;
	if (dlgPara.DoModal() != IDOK)// 显示对话框，设定平移量
	{
		return;
	}
	int type, threshold;
	threshold = dlgPara.m_sol4;
	type = 4;
	int i, j;
	FLOAT fTemp;
	for (i = 0; i < lSrcHeight; i++) {
		// 每列
		for (j = 0; j < lSrcWidth; j++) {
			// 指向DIB第i行，第j个像素的指针

			lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
			fTemp = *lpSrc + 0;
			if (fTemp <= threshold) {
				fTemp = (-255 / (float)(threshold)) * fTemp + 255;
			}
			else {
				fTemp = 0;
			}
			*lpSrc = (unsigned char)(fTemp + 0.5);
		}
	}

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnLinetrans()
{
	// 线性变换
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	

	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	CLinerinverse dlgPara;// 创建对话框	


	FLOAT fA, fB;


	if (dlgPara.DoModal() != IDOK)// 显示对话框， 
	{
		return;
	}
	fA = dlgPara.m_Fa;
	fB = dlgPara.m_Fb;

	delete dlgPara;

	// 更改光标形状
	BeginWaitCursor();
	LinerTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, fA, fB);
	pDoc->SetModifiedFlag(TRUE);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	EndWaitCursor();
}


void CMFCApplication1View::OnBpsperate()
{
	// 位平面分解

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	

	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数

	BPSperate dlgPara;

	dlgPara.lSrcLineBytes = lSrcLineBytes;		//图象每行的字节数
	dlgPara.lSrcWidth = lSrcWidth;      //图象的宽度和高度
	dlgPara.lSrcHeight = lSrcHeight;
	dlgPara.lpSrcBitCount = lpSrcBitCount;       //图像的位深
	dlgPara.lpSrcDib = lpSrcDib;		//指向源图象的指针	
	dlgPara.lpSrcStartBits = lpSrcStartBits;	//指向源像素的指针


	//位平面分解
	if (dlgPara.DoModal() != IDOK) // 显示对话框 
	{
		return;
	}

	//////////////////////////
	delete dlgPara;
	EndWaitCursor();
	//设置文档修改标志x	
	//  pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnLogtrans()
{
	// 对数变换
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	

	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数

	BitPlaneSlicing(lpSrcStartBits, lSrcWidth, lSrcLineBytes, lSrcHeight, 6);
	LogTranslation(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes);

	EndWaitCursor();
	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}




void CMFCApplication1View::OnGammatrans()
{
		// 伽马变换
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	

	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数

	GammaTrans dlgPara;
	if (dlgPara.DoModal() != IDOK) // 显示对话框 
	{
		return;
	}
	float gamma = dlgPara.m_fGamma;

	long i;                 //行循环变量
	long j;                 //列循环变量
	unsigned char* lpSrc;
	float val;
	for (i = 0; i < lSrcHeight; i++)// 行
	{
		for (j = 0; j < lSrcWidth; j++)// 列
		{
			lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;// 指向DIB第i行，第j个像素的指针
			val = (*lpSrc);
			val = pow(val, gamma);
			val = 255 * val / pow(255, gamma);

			*lpSrc = (int)val;
		}
	}
	//////////////////////////
	delete dlgPara;
	EndWaitCursor();
	//设置文档修改标志
	//  pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

}


void CMFCApplication1View::OnJzlb()
{
	// 均值滤波
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	int iTempH;
	int iTempW;
	FLOAT fTempC;
	int iTempMX;
	int iTempMY;
	FLOAT aValue[9];
	aValue[0] = 1;
	aValue[1] = 1;
	aValue[2] = 1;
	aValue[3] = 1;
	aValue[4] = 1;
	aValue[5] = 1;
	aValue[6] = 1;
	aValue[7] = 1;
	aValue[8] = 1;
	iTempH = 3;
	iTempW = 3;	
	iTempMX = 1;
	iTempMY = 1;
	fTempC = (FLOAT)(1.0 / 9.0);
	if (Template(lpSrcStartBits, lSrcWidth, lSrcHeight, iTempH, iTempW, iTempMX, iTempMY, aValue, fTempC)) {

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else {
		// 提示用户
		AfxMessageBox(L"分配内存失败！");// 警告
	}
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}




void CMFCApplication1View::OnGslb()
{
	// 高斯滤波
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	

	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	int iTempH;
	int iTempW;
	FLOAT fTempC;
	int iTempMX;
	int iTempMY;
	FLOAT aValue[9];
	aValue[0] = 1;
	aValue[1] = 2;
	aValue[2] = 1;
	aValue[3] = 2;
	aValue[4] = 4;
	aValue[5] = 2;
	aValue[6] = 1;
	aValue[7] = 2;
	aValue[8] = 1;
	iTempH = 3;
	iTempW = 3;
	iTempMX = 1;
	iTempMY = 1;
	fTempC = (FLOAT)(1.0 / 16.0);
	if (Template(lpSrcStartBits, lSrcWidth, lSrcHeight, iTempH, iTempW, iTempMX, iTempMY, aValue, fTempC)) {

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else {
		// 提示用户
		AfxMessageBox(L"分配内存失败！");// 警告
	}
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}


void CMFCApplication1View::OnZzlb()
{
	//中值滤波
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	

	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	int iTempH;
	int iTempW;
	FLOAT fTempC;
	int iTempMX;
	int iTempMY;
	iTempH = 3;
	iTempW = 3;
	iTempMX = 1;
	iTempMY = 1;
	// 调用MedianFilter()函数中值滤波
	Select(lpSrcStartBits, lSrcWidth, lSrcHeight, iTempH, iTempW, iTempMX, iTempMY);
	
		// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

		// 更新视图
	pDoc->UpdateAllViews(NULL);
	
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}


void CMFCApplication1View::Onaddnoise()
{
	//添加椒盐噪声
	// 显示图像基本信息
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	//if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	//{
	//	AfxMessageBox(L"对不起，不是256色位图！");// 警告
	//	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	//	return;									//返回
	//}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	

	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//循环变量
	int i;

	int gap = 1;

	//指向源像素的指针
	unsigned char* lpSrc;
	//信噪比
	float ratio = 0.1;
	//噪点数
	int noisesize = lSrcWidth * lSrcHeight * ratio;

	srand(time(0));

	if (lpSrcBitCount == 8)gap = 1;
	else if (lpSrcBitCount == 24)gap = 3;

	for (i = 0; i < noisesize; i++) {
		int x = rand() % lSrcHeight;
		int y = rand() % lSrcWidth;
		if (rand() % 2 == 0) {
			for (int k = 0; k < gap; k++) {
				lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - x) + y * gap + k;
				*lpSrc = 0;
			}
		}
		else {
			for (int k = 0; k < gap; k++) {
				lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - x) + y * gap + k;
				*lpSrc = 255;
			}
		}

	}
	pDoc->SetModifiedFlag(TRUE);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	EndWaitCursor();
}


void CMFCApplication1View::OnLpls4()
{
	//拉普拉斯锐化4
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	

	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	int iTempH;
	int iTempW;
	FLOAT fTempC;
	int iTempMX;
	int iTempMY;
	FLOAT aValue[9];
	aValue[0] = 0;
	aValue[1] = -1.0;
	aValue[2] = 0;
	aValue[3] = -1.0;
	aValue[4] = 5.0;
	aValue[5] = -1.0;
	aValue[6] = 0;
	aValue[7] = -1.0;
	aValue[8] = 0;
	iTempH = 3;
	iTempW = 3;
	iTempMX = 1;
	iTempMY = 1.0;
	fTempC = 1.0;
	if (Template(lpSrcStartBits, lSrcWidth, lSrcHeight, iTempH, iTempW, iTempMX, iTempMY, aValue, fTempC)) {

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else {
		// 提示用户
		AfxMessageBox(L"分配内存失败！");// 警告
	}
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}


void CMFCApplication1View::OnLpls8()
{
	//拉普拉斯锐化4
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	

	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	int iTempH;
	int iTempW;
	FLOAT fTempC;
	int iTempMX;
	int iTempMY;
	FLOAT aValue[9];
	aValue[0] = -1.0;
	aValue[1] = -1.0;
	aValue[2] = -1.0;
	aValue[3] = -1.0;
	aValue[4] = 9.0;
	aValue[5] = -1.0;
	aValue[6] = -1.0;
	aValue[7] = -1.0;
	aValue[8] = -1.0;
	iTempH = 3;
	iTempW = 3;
	iTempMX = 1;
	iTempMY = 1.0;
	fTempC = 1.0;
	if (Template(lpSrcStartBits, lSrcWidth, lSrcHeight, iTempH, iTempW, iTempMX, iTempMY, aValue, fTempC)) {

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else {
		// 提示用户
		AfxMessageBox(L"分配内存失败！");// 警告
	}
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}


void CMFCApplication1View::Onedgerobert()
{
	//Robert边缘检测运算


	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	

	// 指向DIB的指针
	LPSTR	lpDIB;

	// 指向DIB象素指针
	LPSTR   lpDIBBits;
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	if (pDoc->m_dib.GetColorNum(lpDIB) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

		// 更改光标形状
	BeginWaitCursor();

	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);			// 找到DIB图象像素起始位置	

	lSrcWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpDIB);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数

	// 调用RobertDIB()函数对DIB进行边缘检测
	if (RobertDEC(lpDIBBits, lSrcLineBytes, lSrcHeight))
	{

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		AfxMessageBox(L"分配内存失败！");
	}

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定

	// 恢复光标
	EndWaitCursor();
}


void CMFCApplication1View::Onedgesobel()
{
	//Sobel边缘检测运算

// 获取文档
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	

	// 指向DIB的指针
	LPSTR	lpDIB;

	// 指向DIB象素指针
	LPSTR   lpDIBBits;
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的边缘检测，其它的可以类推）
	if (pDoc->m_dib.GetColorNum(lpDIB) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	// 更改光标形状
	BeginWaitCursor();


	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);			// 找到DIB图象像素起始位置	

	lSrcWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpDIB);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数

	// 调用SobelDIB()函数对DIB进行边缘检测
	if (SobelDEC(lpDIBBits, lSrcLineBytes, lSrcHeight))
	{

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		AfxMessageBox(L"分配内存失败！");
	}

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}


void CMFCApplication1View::OnXtxpz()
{
	//形态学膨胀
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档

	// 指向DIB的指针
	LPSTR	lpDIB;
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	// 指向DIB象素指针
	LPSTR   lpDIBBits;
	int lLineBytes;//


	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB

	// 找到DIB图像象素起始位置
	lpDIBBits = lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	lSrcWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpDIB);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的平滑，其它的可以类推）
	if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
	{
		// 提示用户
		AfxMessageBox(L"目前只支持256色位图的平滑！");

		// 解除锁定

		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}
	int nMode = 0;
	int intType = 0;
	// 创建对话框
	CDXTXPZ dlgPara;
	//初始化变量
	dlgPara.m_nMode = 0;
	// 模板元素数组
	int	aValue[3][3] = { 0 };
	// 初始化对话框变量值


	// 显示对话框，提示用户设定平移量
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}
	if (dlgPara.b_nMode == 1) {
		backcolor1(lpDIBBits, lSrcWidth, lSrcHeight, lSrcLineBytes);
	}
	else if (dlgPara.b_nMode == 2) {
		backcolor2(lpDIBBits, lSrcWidth, lSrcHeight, lSrcLineBytes);
	}
	// 获取用户设定
	nMode = dlgPara.m_nMode;
	if (nMode == 2)
	{

		aValue[0][0] = dlgPara.m_nStructure1;
		aValue[0][1] = dlgPara.m_nStructure2;
		aValue[0][2] = dlgPara.m_nStructure3;
		aValue[1][0] = dlgPara.m_nStructure4;
		aValue[1][1] = dlgPara.m_nStructure5;
		aValue[1][2] = dlgPara.m_nStructure6;
		aValue[2][0] = dlgPara.m_nStructure7;
		aValue[2][1] = dlgPara.m_nStructure8;
		aValue[2][2] = dlgPara.m_nStructure9;

	}
	// 删除对话框
	delete dlgPara;
	long DIBWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	long DIBHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	lLineBytes = pDoc->m_dib.GetReqByteWidth(DIBWidth * lpSrcBitCount);		// 计算图象每行的字节数
	// 更改光标形状
	BeginWaitCursor();
	DilationDIB(lpDIBBits, DIBWidth, DIBHeight, nMode, aValue);
	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}


void CMFCApplication1View::OnXtxfs()
{
	//形态学腐蚀
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档

	// 指向DIB的指针
	LPSTR	lpDIB;
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	// 指向DIB象素指针
	LPSTR   lpDIBBits;
	int lLineBytes;//


	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB

	// 找到DIB图像象素起始位置
	lpDIBBits = lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	lSrcWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpDIB);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的平滑，其它的可以类推）
	if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
	{
		// 提示用户
		AfxMessageBox(L"目前只支持256色位图的平滑！");

		// 解除锁定

		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}
	int nMode = 0;
	int intType = 0;
	// 创建对话框
	CDXTXFS dlgPara;
	//初始化变量
	dlgPara.m_nMode = 0;
	// 模板元素数组
	int	aValue[3][3] = { 0 };
	// 初始化对话框变量值


	// 显示对话框，提示用户设定平移量
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}
	if (dlgPara.b_nMode == 1) {
		backcolor1(lpDIBBits, lSrcWidth, lSrcHeight, lSrcLineBytes);
	}
	else if (dlgPara.b_nMode == 2) {
		backcolor2(lpDIBBits, lSrcWidth, lSrcHeight, lSrcLineBytes);
	}
	// 获取用户设定
	nMode = dlgPara.m_nMode;
	if (nMode == 2)
	{

		aValue[0][0] = dlgPara.m_nStructure1;
		aValue[0][1] = dlgPara.m_nStructure2;
		aValue[0][2] = dlgPara.m_nStructure3;
		aValue[1][0] = dlgPara.m_nStructure4;
		aValue[1][1] = dlgPara.m_nStructure5;
		aValue[1][2] = dlgPara.m_nStructure6;
		aValue[2][0] = dlgPara.m_nStructure7;
		aValue[2][1] = dlgPara.m_nStructure8;
		aValue[2][2] = dlgPara.m_nStructure9;

	}
	// 删除对话框
	delete dlgPara;
	long DIBWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	long DIBHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	lLineBytes = pDoc->m_dib.GetReqByteWidth(DIBWidth * lpSrcBitCount);		// 计算图象每行的字节数
	// 更改光标形状
	BeginWaitCursor();
	ErosionDIB(lpDIBBits, DIBWidth, DIBHeight, nMode, aValue);
	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}


void CMFCApplication1View::OnXtxkq()
{
	//形态学开启
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档

	// 指向DIB的指针
	LPSTR	lpDIB;
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	// 指向DIB象素指针
	LPSTR   lpDIBBits;
	int lLineBytes;//


	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB

	// 找到DIB图像象素起始位置
	lpDIBBits = lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	lSrcWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpDIB);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的平滑，其它的可以类推）
	if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
	{
		// 提示用户
		AfxMessageBox(L"目前只支持256色位图的平滑！");

		// 解除锁定

		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}
	int nMode = 0;
	int intType = 0;
	// 创建对话框
	CDXTXKQ dlgPara;
	//初始化变量
	dlgPara.m_nMode = 0;
	// 模板元素数组
	int	aValue[3][3] = { 0 };
	// 初始化对话框变量值


	// 显示对话框，提示用户设定平移量
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}
	if (dlgPara.b_nMode == 1) {
		backcolor1(lpDIBBits, lSrcWidth, lSrcHeight, lSrcLineBytes);
	}
	else if (dlgPara.b_nMode == 2) {
		backcolor2(lpDIBBits, lSrcWidth, lSrcHeight, lSrcLineBytes);
	}
	// 获取用户设定
	nMode = dlgPara.m_nMode;
	if (nMode == 2)
	{

		aValue[0][0] = dlgPara.m_nStructure1;
		aValue[0][1] = dlgPara.m_nStructure2;
		aValue[0][2] = dlgPara.m_nStructure3;
		aValue[1][0] = dlgPara.m_nStructure4;
		aValue[1][1] = dlgPara.m_nStructure5;
		aValue[1][2] = dlgPara.m_nStructure6;
		aValue[2][0] = dlgPara.m_nStructure7;
		aValue[2][1] = dlgPara.m_nStructure8;
		aValue[2][2] = dlgPara.m_nStructure9;

	}
	// 删除对话框
	delete dlgPara;
	long DIBWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	long DIBHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	lLineBytes = pDoc->m_dib.GetReqByteWidth(DIBWidth * lpSrcBitCount);		// 计算图象每行的字节数
	// 更改光标形状
	BeginWaitCursor();
	OpenDIB(lpDIBBits, DIBWidth, DIBHeight, nMode, aValue);
	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}


void CMFCApplication1View::OnXtxbh()
{
	//形态学闭合
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档

	// 指向DIB的指针
	LPSTR	lpDIB;
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	// 指向DIB象素指针
	LPSTR   lpDIBBits;
	int lLineBytes;//


	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB

	// 找到DIB图像象素起始位置
	lpDIBBits = lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	lSrcWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpDIB);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的平滑，其它的可以类推）
	if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
	{
		// 提示用户
		AfxMessageBox(L"目前只支持256色位图的平滑！");

		// 解除锁定

		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}
	int nMode = 0;
	int intType = 0;
	// 创建对话框
	CDXTXBH dlgPara;
	//初始化变量
	dlgPara.m_nMode = 0;
	// 模板元素数组
	int	aValue[3][3] = { 0 };
	// 初始化对话框变量值


	// 显示对话框，提示用户设定平移量
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}
	if (dlgPara.b_nMode == 1) {
		backcolor1(lpDIBBits, lSrcWidth, lSrcHeight, lSrcLineBytes);
	}
	else if (dlgPara.b_nMode == 2) {
		backcolor2(lpDIBBits, lSrcWidth, lSrcHeight, lSrcLineBytes);
	}
	// 获取用户设定
	nMode = dlgPara.m_nMode;
	if (nMode == 2)
	{

		aValue[0][0] = dlgPara.m_nStructure1;
		aValue[0][1] = dlgPara.m_nStructure2;
		aValue[0][2] = dlgPara.m_nStructure3;
		aValue[1][0] = dlgPara.m_nStructure4;
		aValue[1][1] = dlgPara.m_nStructure5;
		aValue[1][2] = dlgPara.m_nStructure6;
		aValue[2][0] = dlgPara.m_nStructure7;
		aValue[2][1] = dlgPara.m_nStructure8;
		aValue[2][2] = dlgPara.m_nStructure9;

	}
	// 删除对话框
	delete dlgPara;
	long DIBWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	long DIBHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	lLineBytes = pDoc->m_dib.GetReqByteWidth(DIBWidth * lpSrcBitCount);		// 计算图象每行的字节数
	// 更改光标形状
	BeginWaitCursor();
	CloseDIB(lpDIBBits, DIBWidth, DIBHeight, nMode, aValue);
	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}


void CMFCApplication1View::OnXtxnbj()
{
	//形态学内边界
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档

	// 指向DIB的指针
	LPSTR	lpDIB;
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	// 指向DIB象素指针
	LPSTR   lpDIBBits;
	int lLineBytes;//


	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB

	// 找到DIB图像象素起始位置
	lpDIBBits = lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	lSrcWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpDIB);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的平滑，其它的可以类推）
	if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
	{
		// 提示用户
		AfxMessageBox(L"目前只支持256色位图的平滑！");

		// 解除锁定

		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}
	int nMode = 0;
	int intType = 0;
	// 创建对话框
	XTXNBJ dlgPara;
	//初始化变量
	dlgPara.m_nMode = 0;
	// 模板元素数组
	int	aValue[3][3] = { 0 };
	// 初始化对话框变量值


	// 显示对话框，提示用户设定平移量
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}
	if (dlgPara.b_nMode == 1) {
		backcolor1(lpDIBBits, lSrcWidth, lSrcHeight, lSrcLineBytes);
	}
	else if (dlgPara.b_nMode == 2) {
		backcolor2(lpDIBBits, lSrcWidth, lSrcHeight, lSrcLineBytes);
	}
	// 获取用户设定
	nMode = dlgPara.m_nMode;
	if (nMode == 2)
	{

		aValue[0][0] = dlgPara.m_nStructure1;
		aValue[0][1] = dlgPara.m_nStructure2;
		aValue[0][2] = dlgPara.m_nStructure3;
		aValue[1][0] = dlgPara.m_nStructure4;
		aValue[1][1] = dlgPara.m_nStructure5;
		aValue[1][2] = dlgPara.m_nStructure6;
		aValue[2][0] = dlgPara.m_nStructure7;
		aValue[2][1] = dlgPara.m_nStructure8;
		aValue[2][2] = dlgPara.m_nStructure9;

	}
	// // 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits1;
	HLOCAL	hNewDIBBits1;
	// 指向缓存图像的指针
	LPSTR	lpDst1;
	LPSTR	lpDst;
	long DIBWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	long DIBHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	lLineBytes = pDoc->m_dib.GetReqByteWidth(DIBWidth * lpSrcBitCount);		// 计算图象每行的字节数
	// // 暂时分配内存，以保存新图像
	hNewDIBBits1 = LocalAlloc(LHND, lLineBytes * lSrcWidth);

	if (hNewDIBBits1 == NULL)
	{
		// 分配内存失败
		return;
	}

	// 锁定内存
	lpNewDIBBits1 = (char*)LocalLock(hNewDIBBits1);
	// 拷贝源图像到缓存图像中
	lpDst1 = (char*)lpNewDIBBits1;

	memcpy(lpNewDIBBits1, lpDIBBits, lSrcWidth * lSrcHeight);



	// 删除对话框
	delete dlgPara;

	// 更改光标形状
	BeginWaitCursor();


	if (ErosionDIB(lpNewDIBBits1, DIBWidth, DIBHeight, nMode, aValue))
	{

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		AfxMessageBox(L"分配内存失败！");

	}
	//求两幅缓存图像的最大值
	for (int j = 0; j < DIBHeight; j++)
	{
		for (int i = 0; i < DIBWidth; i++)
		{

			// 指向缓存图像1倒数第j行，第i个象素的指针			
			lpDst1 = (char*)lpNewDIBBits1 + DIBWidth * j + i;
			// 指向源图像倒数第j行，第i个象素的指针			
			lpDst = (char*)lpDIBBits + DIBWidth * j + i;
			if (*lpDst != *lpDst1) {
				*lpDst1 = (unsigned char)0;
			}
			else {
				*lpDst1 = (unsigned char)255;
			}

		}
	}

	// 复制经过模板运算后的图像到源图像
	memcpy(lpDIBBits, lpNewDIBBits1, DIBWidth * DIBHeight);
	// 释放内存
	LocalUnlock(hNewDIBBits1);
	LocalFree(hNewDIBBits1);


	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}


void CMFCApplication1View::OnXtxwbj()
{
	//形态学外边界
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档

	// 指向DIB的指针
	LPSTR	lpDIB;
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	// 指向DIB象素指针
	LPSTR   lpDIBBits;
	int lLineBytes;//


	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB

	// 找到DIB图像象素起始位置
	lpDIBBits = lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	lSrcWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpDIB);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的平滑，其它的可以类推）
	if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
	{
		// 提示用户
		AfxMessageBox(L"目前只支持256色位图的平滑！");

		// 解除锁定

		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}
	int nMode = 0;
	int intType = 0;
	// 创建对话框
	XTXWBJ dlgPara;
	//初始化变量
	dlgPara.m_nMode = 0;
	// 模板元素数组
	int	aValue[3][3] = { 0 };
	// 初始化对话框变量值


	// 显示对话框，提示用户设定平移量
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}
	if (dlgPara.b_nMode == 1) {
		backcolor1(lpDIBBits, lSrcWidth, lSrcHeight, lSrcLineBytes);
	}
	else if (dlgPara.b_nMode == 2) {
		backcolor2(lpDIBBits, lSrcWidth, lSrcHeight, lSrcLineBytes);
	}
	// 获取用户设定
	nMode = dlgPara.m_nMode;
	if (nMode == 2)
	{

		aValue[0][0] = dlgPara.m_nStructure1;
		aValue[0][1] = dlgPara.m_nStructure2;
		aValue[0][2] = dlgPara.m_nStructure3;
		aValue[1][0] = dlgPara.m_nStructure4;
		aValue[1][1] = dlgPara.m_nStructure5;
		aValue[1][2] = dlgPara.m_nStructure6;
		aValue[2][0] = dlgPara.m_nStructure7;
		aValue[2][1] = dlgPara.m_nStructure8;
		aValue[2][2] = dlgPara.m_nStructure9;

	}
	// // 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits1;
	HLOCAL	hNewDIBBits1;
	// 指向缓存图像的指针
	LPSTR	lpDst1;
	LPSTR	lpDst;
	long DIBWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	long DIBHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	lLineBytes = pDoc->m_dib.GetReqByteWidth(DIBWidth * lpSrcBitCount);		// 计算图象每行的字节数
	// // 暂时分配内存，以保存新图像
	hNewDIBBits1 = LocalAlloc(LHND, lLineBytes * lSrcWidth);

	if (hNewDIBBits1 == NULL)
	{
		// 分配内存失败
		return;
	}

	// 锁定内存
	lpNewDIBBits1 = (char*)LocalLock(hNewDIBBits1);
	// 拷贝源图像到缓存图像中
	lpDst1 = (char*)lpNewDIBBits1;
	memcpy(lpNewDIBBits1, lpDIBBits, lSrcWidth * lSrcHeight);



	// 删除对话框
	delete dlgPara;

	// 更改光标形状
	BeginWaitCursor();


	if (DilationDIB(lpNewDIBBits1, DIBWidth, DIBHeight, nMode, aValue))
	{

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		AfxMessageBox(L"分配内存失败！");

	}
	//求两幅缓存图像的最大值
	for (int j = 0; j < DIBHeight; j++)
	{
		for (int i = 0; i < DIBWidth; i++)
		{

			// 指向缓存图像1倒数第j行，第i个象素的指针			
			lpDst1 = (char*)lpNewDIBBits1 + DIBWidth * j + i;
			// 指向源图像倒数第j行，第i个象素的指针			
			lpDst = (char*)lpDIBBits + DIBWidth * j + i;
			if (*lpDst != *lpDst1) {
				*lpDst1 = (unsigned char)0;
			}
			else {
				*lpDst1 = (unsigned char)255;
			}

		}
	}

	// 复制经过模板运算后的图像到源图像
	memcpy(lpDIBBits, lpNewDIBBits1, DIBWidth * DIBHeight);
	// 释放内存
	LocalUnlock(hNewDIBBits1);
	LocalFree(hNewDIBBits1);

	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}


void CMFCApplication1View::OnPointthre()
{
	// 阈值分割

		// 获取文档
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档

	// 指向DIB的指针
	LPSTR	lpDIB;

	// 指向DIB象素指针
	LPSTR   lpDIBBits;

	// 参数对话框
	DlgThrePara  dlgPara;

	// 阈值
	BYTE	bThre;
	int intType;

	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	// 找到DIB图像象素起始位置
	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);

	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的平滑，其它的可以类推）
	if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
	{
		// 提示用户
		AfxMessageBox(L"目前只支持256色位图的操作！");

		// 解除锁定

		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}
	long DIBWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	long DIBHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	int lpSrcBitCount = pDoc->m_dib.GetBitCount(lpDIB);                    //获取图像位深
	long lLineBytes = pDoc->m_dib.GetReqByteWidth(DIBWidth * lpSrcBitCount);		// 计算图象每行的字节数



	// 初始化图像信息变量值

	dlgPara.m_bThre = 128;
	dlgPara.m_intType = 0;
	dlgPara.pDoc = pDoc;
	dlgPara.lpDIBBits = lpDIBBits;
	dlgPara.lpSrcBitCount = lpSrcBitCount;//////////////////////
	dlgPara.lHeight = DIBHeight;
	dlgPara.lWidth = DIBWidth;
	dlgPara.lSrcLineBytes = lLineBytes;///////////////////
	dlgPara.lpstartBits = new unsigned char[DIBHeight * DIBWidth * sizeof(unsigned char)];
	memcpy(dlgPara.lpstartBits, lpDIBBits, DIBHeight * DIBWidth * sizeof(unsigned char));

	// 显示对话框，提示用户设定阈值
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}

	// 获取用户设定的阈值
	bThre = dlgPara.m_bThre;
	intType = dlgPara.m_intType;

	//指向原图像的指针
		// 删除对话框
	delete dlgPara;

	// 更改光标形状
	BeginWaitCursor();



	// 调用ThresholdTrans()函数进行阈值变换
	if (intType != 3) {
		ThresholdTrans(lpDIBBits, DIBWidth, DIBHeight, bThre);
	}

	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}


void CMFCApplication1View::OnPointwind()
{
	// 窗口变换

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档

	// 指向DIB的指针
	LPSTR lpDIB;

	// 指向DIB象素指针
	LPSTR    lpDIBBits;

	// 创建对话框
	DlgPointWin  dlgPara;

	// 窗口下限
	BYTE	bLow;

	// 窗口上限
	BYTE	bUp;

	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	// 找到DIB图像象素起始位置
	lpDIBBits = lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	long DIBWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	long DIBHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	int lpSrcBitCount = pDoc->m_dib.GetBitCount(lpDIB);                    //获取图像位深
	long lLineBytes = pDoc->m_dib.GetReqByteWidth(DIBWidth * lpSrcBitCount);		// 计算图象每行的字节数

	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的平滑，其它的可以类推）
	if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
	{
		// 提示用户
		AfxMessageBox(L"目前只支持256色位图的操作！");

		// 解除锁定

		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}

	// 初始化变量值
	dlgPara.m_bLow = 55;
	dlgPara.m_bUp = 200;
	dlgPara.pDoc = pDoc;
	dlgPara.lpDIBBits = lpDIBBits;
	dlgPara.lpSrcBitCount = lpSrcBitCount;//////////////////////
	dlgPara.lHeight = DIBHeight;
	dlgPara.lWidth = DIBWidth;
	dlgPara.lSrcLineBytes = lLineBytes;///////////////////
	dlgPara.lpstartBits = new unsigned char[DIBHeight * DIBWidth * sizeof(unsigned char)];
	memcpy(dlgPara.lpstartBits, lpDIBBits, DIBHeight * DIBWidth * sizeof(unsigned char));
	// 显示对话框，提示用户设定窗口上下限
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}

	// 获取用户设定的窗口上下限
	bLow = dlgPara.m_bLow;
	bUp = dlgPara.m_bUp;

	// 删除对话框
	delete dlgPara;

	// 更改光标形状
	BeginWaitCursor();

	// 调用WindowTrans()函数进行窗口变换
	WindowTrans(lpDIBBits, DIBWidth, DIBHeight, bLow, bUp);

	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}


void CMFCApplication1View::OnPointstre()
{

	// 灰度拉伸

// 获取文档
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档

	// 指向DIB的指针
	LPSTR	lpDIB;

	// 指向DIB象素指针
	LPSTR   lpDIBBits;
	long	DIBWidth;      //图象的宽度和高度
	long	DIBHeight;
	// 创建对话框
	PointStre dlgPara;

	// 点1坐标
	BYTE	bX1;
	BYTE	bY1;

	// 点2坐标
	BYTE	bX2;
	BYTE	bY2;

	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB


	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);			// 找到DIB图象像素起始位置	
	DIBWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	DIBHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	

	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的灰度拉伸，其它的可以类推）
	if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
	{
		// 提示用户
		AfxMessageBox(L"对不起，不是256色位图！");// 警告

		// 解除锁定
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}

	int lpSrcBitCount = pDoc->m_dib.GetBitCount(lpDIB);                    //获取图像位深
	long lLineBytes = pDoc->m_dib.GetReqByteWidth(DIBWidth * lpSrcBitCount);		// 计算图象每行的字节数
	dlgPara.pDoc = pDoc;
	dlgPara.lpDIBBits = lpDIBBits;
	dlgPara.lpSrcBitCount = lpSrcBitCount;//////////////////////
	dlgPara.lHeight = DIBHeight;
	dlgPara.lWidth = DIBWidth;
	dlgPara.lSrcLineBytes = lLineBytes;///////////////////
	dlgPara.lpstartBits = new unsigned char[DIBHeight * DIBWidth * sizeof(unsigned char)];
	memcpy(dlgPara.lpstartBits, lpDIBBits, DIBHeight * DIBWidth * sizeof(unsigned char));
	// 初始化变量值
	dlgPara.m_bX1 = 50;
	dlgPara.m_bY1 = 30;
	dlgPara.m_bX2 = 200;
	dlgPara.m_bY2 = 220;

	// 显示对话框，提示用户设定拉伸位置
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}

	// 获取用户的设定
	bX1 = dlgPara.m_bX1;
	bY1 = dlgPara.m_bY1;
	bX2 = dlgPara.m_bX2;
	bY2 = dlgPara.m_bY2;

	// 删除对话框
	delete dlgPara;

	// 更改光标形状
	BeginWaitCursor();

	// 调用GrayStretch()函数进行灰度拉伸
	GrayStretch(lpDIBBits, DIBWidth, DIBHeight, bX1, bY1, bX2, bY2);

	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}


void CMFCApplication1View::OnZftjhh()
{
	// 直方图法均衡化

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档

	// 指向DIB的指针
	LPSTR lpDIB;

	// 指向DIB象素指针
	LPSTR    lpDIBBits;
	unsigned char* lpSrc;




	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	// 找到DIB图像象素起始位置
	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	long DIBWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	long DIBHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	int lpSrcBitCount = pDoc->m_dib.GetBitCount(lpDIB);                    //获取图像位深
	long lLineBytes = pDoc->m_dib.GetReqByteWidth(DIBWidth * lpSrcBitCount);		// 计算图象每行的字节数

	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的平滑，其它的可以类推）
	if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
	{
		// 提示用户
		AfxMessageBox(L"目前只支持256色位图的操作！");

		// 解除锁定

		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}


	// 更改光标形状
	BeginWaitCursor();

	//循环变量
	int i;
	int j;
	//统计数组
	int hist[256];
	// 设置脏标记//计算直方图
	// 重置计数为0
	for (i = 0; i < 256; i++)
	{
		// 清零
		hist[i] = 0;
	}

	for (i = 0; i < DIBHeight; i++)
	{
		for (j = 0; j < DIBWidth; j++)
		{
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (DIBHeight - 1 - i) + j;
			// 计数加1
			hist[*(lpSrc)]++;
		}
	}

	double sumratio = 0.0;
	double sum[256] = { 0.0 };

	//计算累计频率
	for (i = 0; i < 256; i++)
	{
		sumratio += hist[i] * 1.0 / (DIBHeight * DIBWidth);
		sum[i] = sumratio;

	}
	//灰度映射
	for (i = 0; i < DIBHeight; i++)
	{
		for (j = 0; j < DIBWidth; j++)
		{
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (DIBHeight - 1 - i) + j;
			// 计数加1
			*lpSrc = (unsigned char)255 * sum[(*lpSrc)];
		}
	}


	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}




void CMFCApplication1View::OnStylefilter()
{
	// 滤镜（模板操作）

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档

	// 指向DIB的指针
	LPSTR	lpDIB;

	// 指向DIB象素指针
	LPSTR   lpDIBBits;

	// 模板高度
	int		iTempH;

	// 模板宽度
	int		iTempW;

	// 模板系数
	FLOAT	fTempC;

	//常数或阈值
	int SThre = 0;

	//算子类型
	int intType = 0;
	int nMode = 0;

	// 模板中心元素X坐标
	int		iTempMX;

	// 模板中心元素Y坐标
	int		iTempMY;

	// 模板元素数组
	FLOAT	aValue[9];

	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB

	// 找到DIB图像象素起始位置
	lpDIBBits = lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	long DIBWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	long DIBHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	int lpSrcBitCount = pDoc->m_dib.GetBitCount(lpDIB);                    //获取图像位深
	long lLineBytes = pDoc->m_dib.GetReqByteWidth(DIBWidth * lpSrcBitCount);		// 计算图象每行的字节数	
	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的平滑，其它的可以类推）
	if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
	{
		// 提示用户
		AfxMessageBox(L"目前只支持256色位图的平滑！");

		// 解除锁定

		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}

	// 创建对话框
	DlgStyleFilter dlgPara;

	// 给模板数组赋初值（为平均模板）
	aValue[0] = 0.0;
	aValue[1] = 0.0;
	aValue[2] = 0.0;
	aValue[3] = 0.0;
	aValue[4] = 0.0;
	aValue[5] = 0.0;
	aValue[6] = 0.0;
	aValue[7] = 0.0;
	aValue[8] = 0.0;


	// 初始化对话框变量值
	dlgPara.m_intType = 0;
	dlgPara.m_SThre = 0;
	dlgPara.m_c = 1.0;
	dlgPara.m_fpArray = aValue;
	//给对话框的图片信息变量传值
	dlgPara.pDoc = pDoc;
	dlgPara.lpSrcBitCount = lpSrcBitCount;//////////////////////
	dlgPara.lpSrcStartBits = lpDIBBits;/////////////////
	dlgPara.lSrcHeight = DIBHeight;///////////////////////////
	dlgPara.lSrcWidth = DIBWidth;///////////////////////////
	dlgPara.lSrcLineBytes = lLineBytes;///////////////////
	dlgPara.lpstartBits = new unsigned char[DIBHeight * DIBWidth * sizeof(unsigned char)];
	memcpy(dlgPara.lpstartBits, lpDIBBits, DIBHeight * DIBWidth * sizeof(unsigned char));
	// 显示对话框，提示用户设定平移量
	if (dlgPara.DoModal() != IDOK)
	{

		// 返回
		return;
	}

	// 获取用户设定的平移量
	iTempH = 3;
	iTempW = 3;
	iTempMX = 1;
	iTempMY = 1;
	fTempC = dlgPara.m_c;
	intType = dlgPara.m_intType;
	nMode = dlgPara.m_nMode;
	SThre = dlgPara.m_SThre;

	// 删除对话框
	delete dlgPara;
	//CString   temp;//调试输出
	//temp.Format(L"%d ", intType);
	//AfxMessageBox(temp);


	if (::Templaterelief(lpDIBBits, DIBWidth, DIBHeight,
		iTempH, iTempW, iTempMX, iTempMY, aValue, fTempC, SThre))
	{

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		AfxMessageBox(L"分配内存失败！");
		AfxMessageBox(L"系统提示");
	}

	// 更改光标形状
	BeginWaitCursor();

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}




void CMFCApplication1View::OnGtrans()
{
	// 图像平移

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档

	// 指向DIB的指针
	LPSTR lpDIB;

	// 指向DIB象素指针
	LPSTR    lpDIBBits;

	// 创建对话框
	DlgGTrans  dlgPara;

	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	// 找到DIB图像象素起始位置
	lpDIBBits = lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	long DIBWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	long DIBHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	int lpSrcBitCount = pDoc->m_dib.GetBitCount(lpDIB);                    //获取图像位深
	long lLineBytes = pDoc->m_dib.GetReqByteWidth(DIBWidth * lpSrcBitCount);		// 计算图象每行的字节数

	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的平滑，其它的可以类推）
	if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
	{
		// 提示用户
		AfxMessageBox(L"目前只支持256色位图的操作！");

		// 解除锁定

		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}

	LONG offX1;
	LONG offY1;

	// 初始化变量值
	dlgPara.m_offX= 100;
	dlgPara.m_offY = 100;

	// 显示对话框，提示用户设定窗口上下限
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}

	// 获取用户设定的平移量
	offX1 = dlgPara.m_offX;
	offY1 = dlgPara.m_offY;

	// 删除对话框
	delete dlgPara;

	// 更改光标形状
	BeginWaitCursor();

	// 调用TranslationDIB()函数平移DIB
	if (TranslationDIB(lpDIBBits, DIBWidth, DIBHeight, offY1, offX1))
	{

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		AfxMessageBox(L"分配内存失败！");
	}


	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}




void CMFCApplication1View::OnTranspose()
{
	// 图像转置
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档

	// 指向DIB的指针
	LPSTR lpDIB;

	// 指向DIB象素指针
	LPSTR    lpDIBBits;



	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	// 找到DIB图像象素起始位置
	lpDIBBits = lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	long DIBWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	long DIBHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	int lpSrcBitCount = pDoc->m_dib.GetBitCount(lpDIB);                    //获取图像位深
	long lLineBytes = pDoc->m_dib.GetReqByteWidth(DIBWidth * lpSrcBitCount);		// 计算图象每行的字节数

	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的平滑，其它的可以类推）
	if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
	{
		// 提示用户
		AfxMessageBox(L"目前只支持256色位图的操作！");

		// 解除锁定

		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}

	// 更改光标形状
	BeginWaitCursor();

	// 调用TransposeDIB()函数转置DIB
	if (TransposeDIB(lpDIB, lpDIBBits, DIBWidth, DIBHeight))
	{
		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);
		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		AfxMessageBox(L"分配内存失败！");
	}

	//TransposeDIB(lpDIB, lpDIBBits, DIBWidth, DIBHeight);
	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}


void CMFCApplication1View::OnMirrorx()
{
	// 水平镜像
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档

	// 指向DIB的指针
	LPSTR lpDIB;

	// 指向DIB象素指针
	LPSTR    lpDIBBits;



	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	// 找到DIB图像象素起始位置
	lpDIBBits = lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	long DIBWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	long DIBHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	int lpSrcBitCount = pDoc->m_dib.GetBitCount(lpDIB);                    //获取图像位深
	long lLineBytes = pDoc->m_dib.GetReqByteWidth(DIBWidth * lpSrcBitCount);		// 计算图象每行的字节数

	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的平滑，其它的可以类推）
	if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
	{
		// 提示用户
		AfxMessageBox(L"目前只支持256色位图的操作！");

		// 解除锁定

		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}

	// 更改光标形状
	BeginWaitCursor();

	// 调用MirrorDIB()函数垂直镜像DIB
	if (MirrorDIB(lpDIBBits, DIBWidth, DIBHeight, TRUE))
	{

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		AfxMessageBox(L"分配内存失败！");
	}


	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}


void CMFCApplication1View::OnMirrory()
{
	// 垂直镜像
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档

	// 指向DIB的指针
	LPSTR lpDIB;

	// 指向DIB象素指针
	LPSTR    lpDIBBits;



	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	// 找到DIB图像象素起始位置
	lpDIBBits = lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	long DIBWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	long DIBHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	int lpSrcBitCount = pDoc->m_dib.GetBitCount(lpDIB);                    //获取图像位深
	long lLineBytes = pDoc->m_dib.GetReqByteWidth(DIBWidth * lpSrcBitCount);		// 计算图象每行的字节数

	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的平滑，其它的可以类推）
	if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
	{
		// 提示用户
		AfxMessageBox(L"目前只支持256色位图的操作！");

		// 解除锁定

		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}

	// 更改光标形状
	BeginWaitCursor();

	// 调用MirrorDIB()函数垂直镜像DIB
	if (MirrorDIB(lpDIBBits, DIBWidth, DIBHeight, FALSE))
	{

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		AfxMessageBox(L"分配内存失败！");
	}


	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}



void CMFCApplication1View::Onoilpaint()
{
	// 油画风格

	LONG i, j;

	unsigned char* lpSrc;
	unsigned char* lpDst;

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////	
		// 更改光标形状
	BeginWaitCursor();
	int rectangleLenth = 8;//方格大小
	int level[8] = { 0 };//灰度等级分类
	struct Sum {
		FLOAT r;
		FLOAT g;
		FLOAT b;
	}sum[8]; //每个灰度等级的灰度值和
	FLOAT fTemp;//中间变量


	int gap = 1;
	if (lpSrcBitCount == 8)gap = 1;
	else if (lpSrcBitCount == 24) {
		gap = 3;

	}
	for (i = 0; i < lSrcHeight - rectangleLenth + 1; i++) {
		// 每列
		for (j = 0; j < lSrcWidth - rectangleLenth + 1; j++) {
			// 指向DIB第i行，第j个像素的指针，小方块的第一个像素
			for (int p = 0; p < 8; p++) {
				level[p] = 0;//灰度等级分类
				sum[p].r = 0;
				sum[p].g = 0;
				sum[p].b = 0;
			}
			for (int k = 0; k < rectangleLenth; k++) {
				for (int m = 0; m < rectangleLenth; m++)
				{
					//统计每个小方块里灰度等级
					lpDst = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i - k) + (j + m) * gap;
					// 计算该颜色对应的灰度值g = 0.299 * r + 0.587 * g + 0.114 * b
					FLOAT fTemp1 = *(lpDst + 0);
					FLOAT fTemp2 = 0.0;
					FLOAT fTemp3 = 0.0;
					fTemp2 = *(lpDst + 1);
					fTemp3 = *(lpDst + 2);

					fTemp = fTemp1 * 0.299 + fTemp2 * 0.587 + fTemp3 * 0.114;
					int a = (int)(fTemp) / 32;

					level[a]++;
					sum[a].r += fTemp1;
					sum[a].g += fTemp2;
					sum[a].b += fTemp3;

				}
			}
			//比较出像素最多的灰度等级
			int max = 0;
			for (int l = 1; l < 8; l++) {
				if (level[l] > level[max]) {
					max = l;
				}
			}
			//求平均值

			FLOAT averager = sum[max].r / level[max];
			FLOAT averageg = sum[max].g / level[max];
			FLOAT averageb = sum[max].b / level[max];

			//替换当前像素的rgb
			lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + (j)*gap;
			*(lpSrc + 0) = (unsigned char)averager;
			if (gap == 3) {
				*(lpSrc + 1) = (unsigned char)averageg;
				*(lpSrc + 2) = (unsigned char)averageb;
			}
		}
	}

	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}


void CMFCApplication1View::OnMsc()
{
	// 马赛克处理

	LONG i, j;

	unsigned char* lpSrc;
	unsigned char* lpDst;

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	 */
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////	
	int rectangleLenth = 9;//方格大小
	int Mx = 0, My = 0;//方格中心
	// 创建对话框
	MSC  dlgPara;
	// 初始化变量值
	dlgPara.m_ret = 5;


	// 显示对话框，提示用户设定窗口上下限
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}

	// 获取用户设定的旋转量
	rectangleLenth = dlgPara.m_ret;

	// 删除对话框
	delete dlgPara;



	// 更改光标形状
	BeginWaitCursor();

	Mx = My = rectangleLenth / 2;
	LONG fTemp;
	//每行
	int gap = 1;
	if (lpSrcBitCount == 8)gap = 1;
	else if (lpSrcBitCount == 24)gap = 3;
	for (i = Mx; i < lSrcHeight - rectangleLenth + Mx + 1; i += rectangleLenth) {
		// 每列
		for (j = My; j < lSrcWidth - rectangleLenth + My + 1; j += rectangleLenth) {
			// 指向DIB第i行，第j个像素的指针
			lpDst = (unsigned char*)lpSrcStartBits + lSrcLineBytes *
				(lSrcHeight - 1 - i) + j * gap;

			for (int k = 0; k < rectangleLenth; k++) {
				for (int m = 0; m < rectangleLenth; m++) {
					lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes *
						(lSrcHeight - 1 - i - My + k) + (j - Mx + m) * gap;
					for (int g = 0; g < gap; g++) {
						//在这里进行颜色的修改
						fTemp = *(lpDst + g);
						*(lpSrc + g) = (unsigned)fTemp;
					}
				}
			}
		}
	}
	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);

	// 解除锁定	
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}


void CMFCApplication1View::OnMglass()
{
	// 毛玻璃风格
	LONG i, j;

	unsigned char* lpSrc;
	unsigned char* lpDst;

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	 */
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////	
		// 更改光标形状
	BeginWaitCursor();
	int rectangleLenth = 8;//方格大小

	srand(time(0));//生成随机数种子
	FLOAT fTemp;
	//每行
	int gap = 1;
	if (lpSrcBitCount == 8)gap = 1;
	else if (lpSrcBitCount == 24)gap = 3;
	for (i = 0; i < lSrcHeight; i++) {
		// 每列
		for (j = 0; j < lSrcWidth; j++) {
			// 指向DIB第i行，第j个像素的指针
			lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j * gap;
			int index = rand() % rectangleLenth + 1;
			if (i + index >= lSrcHeight || j + index >= lSrcWidth) {
				continue;
			}
			lpDst = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i - index) + (j + index) * gap;
			for (int g = 0; g < gap; g++) {
				//在这里进行颜色的修改
				fTemp = *(lpDst + g);
				*(lpSrc + g) = (unsigned)fTemp;

			}
		}
	}
	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}



void CMFCApplication1View::OnQycal()
{
	// 区域计数
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	
	long    lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	//if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	//{		
	//AfxMessageBox(L"对不起，不是256色位图！");// 警告				
	// ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定		
	//return;									//返回
	//}										//判断是否是8-bpp位图,不是则返回	
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * 8);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////	
	QYCal1  dlg;// 创建对话框

	int my_choice;
	int my_link;

	int my_number = 0;
	double my_area = 0;
	double my_meter;
	double my_circle;
	double my_square;
	if (dlg.DoModal() != IDOK)// 显示对话框，设定平移量
	{
		return;
	}
	my_choice = dlg.m_foreground;
	my_link = dlg.m_link;

	if (my_link == 0)//4联通
	{
		if (dlg.m_foreground == 0)//黑
		{
			my_number = dealer_four(lpSrcStartBits, lSrcWidth, lSrcHeight, 0);
			my_area = getArea_four(lpSrcStartBits, lSrcWidth, lSrcHeight, 0);
			my_meter = sqrt(my_area / 3.14) * 2 * 3.14;
			my_circle = 0.6868 * my_meter * my_meter / my_area;
			my_square = 0.5483 * my_circle;


		}
		if (dlg.m_foreground == 1)//白
		{
			my_number = dealer_four(lpSrcStartBits, lSrcWidth, lSrcHeight, 255);
			my_area = getArea_four(lpSrcStartBits, lSrcWidth, lSrcHeight, 255);
			my_meter = sqrt(my_area / 3.14) * 2 * 3.14;
			my_circle = 0.6868 * my_meter * my_meter / my_area;
			my_square = 0.5483 * my_circle;

		}
		if (dlg.m_foreground == 2)//自动
		{

			unsigned char* img;
			int black = 0, white = 0;
			for (int i = 0; i < lSrcHeight; i++) {
				for (int j = 0; j < lSrcWidth; j++) {
					img = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;//i行j列
					if (*img == 0)
						black++;
					else
						white++;

				}
			}
			if (black >= white)//白
			{
				my_number = dealer_four(lpSrcStartBits, lSrcWidth, lSrcHeight, 255);
				my_area = getArea_four(lpSrcStartBits, lSrcWidth, lSrcHeight, 255);
				my_meter = sqrt(my_area / 3.14) * 2 * 3.14;
				my_circle = 0.6868 * my_meter * my_meter / my_area;
				my_square = 0.5483 * my_circle;

			}
			else//黑
			{
				my_number = dealer_four(lpSrcStartBits, lSrcWidth, lSrcHeight, 0);
				my_area = getArea_four(lpSrcStartBits, lSrcWidth, lSrcHeight, 0);
				my_meter = sqrt(my_area / 3.14) * 2 * 3.14;
				my_circle = 0.6868 * my_meter * my_meter / my_area;
				my_square = 0.5483 * my_circle;

			}
		}

	}

	if (my_link == 1)//8联通
	{
		if (dlg.m_foreground == 0)//黑
		{
			my_number = dealer_eight(lpSrcStartBits, lSrcWidth, lSrcHeight, 0);
			my_area = getArea_eight(lpSrcStartBits, lSrcWidth, lSrcHeight, 0);
			my_meter = sqrt(my_area / 3.14) * 2 * 3.14;
			my_circle = 0.7854 * my_meter * my_meter / my_area;
			my_square = 0.5483 * my_circle;

		}
		if (dlg.m_foreground == 1)//白
		{
			my_number = dealer_eight(lpSrcStartBits, lSrcWidth, lSrcHeight, 255);
			my_area = getArea_eight(lpSrcStartBits, lSrcWidth, lSrcHeight, 255);
			my_meter = sqrt(my_area / 3.14) * 2 * 3.14;
			my_circle = 0.5932 * my_meter * my_meter / my_area;
			my_square = 0.5483 * my_circle;

		}
		if (dlg.m_foreground == 2)//自动
		{

			unsigned char* img;
			int black = 0, white = 0;
			for (int i = 0; i < lSrcHeight; i++) {
				for (int j = 0; j < lSrcWidth; j++) {
					img = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;//i行j列
					if (*img == 0)
						black++;
					else
						white++;

				}
			}
			if (black >= white)//白
			{
				my_number = dealer_eight(lpSrcStartBits, lSrcWidth, lSrcHeight, 255);
				my_area = getArea_eight(lpSrcStartBits, lSrcWidth, lSrcHeight, 255);
				my_meter = sqrt(my_area / 3.14) * 2 * 3.14;
				my_circle = 0.7168 * my_meter * my_meter / my_area;
				my_square = 0.5483 * my_circle;

			}
			else//黑
			{
				my_number = dealer_eight(lpSrcStartBits, lSrcWidth, lSrcHeight, 0);
				my_area = getArea_eight(lpSrcStartBits, lSrcWidth, lSrcHeight, 0);
				my_meter = sqrt(my_area / 3.14) * 2 * 3.14;
				my_circle = 0.5968 * my_meter * my_meter / my_area;
				my_square = 0.5483 * my_circle;

			}
		}

	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定

	QYCal2  Dlg;// 创建对话框

	Dlg.m_Num = my_number;
	Dlg.m_mSquare = my_area;
	Dlg.m_mCmeter = my_meter;
	Dlg.m_circle = my_circle;
	Dlg.m_square = my_square;
	Dlg.m_x = heartx(lSrcWidth, lSrcHeight, my_area);
	Dlg.m_y = gethearty(lSrcWidth, lSrcHeight, my_area);

	if (Dlg.DoModal() != IDOK)// 显示对话框，设定平移量
	{
		return;
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定

}


void CMFCApplication1View::OnCannydec()
{
	//Canny边缘算子
	CMFCApplication1Doc* pDoc = GetDocument();
	long lSrcLineBytes;		//图象每行的字节数
	long lSrcWidth;      //图象的宽度和高度
	long lSrcHeight;
	int lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	//判断是否是8-bpp位图,不是则返回	
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * 8);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////
	// 更改光标形状
	BeginWaitCursor();

	// 循环控制变量
	int y;
	int x;

	// 开辟内存，存储图像数据
	unsigned char* pUnchImage = new unsigned char[lSrcWidth * lSrcHeight];

	for (y = 0; y < lSrcHeight; y++)
	{
		for (x = 0; x < lSrcWidth; x++)
		{
			pUnchImage[y * lSrcWidth + x] = lpSrcStartBits[y * lSrcLineBytes + x];
		}
	}

	// canny 算子计算后的结果
	unsigned char* pUnchEdge = new unsigned char[lSrcWidth * lSrcHeight];

	// 调用 canny 函数进行边界提取
	Canny(pUnchImage, lSrcWidth, lSrcHeight, 0.4, 0.4, 0.79, pUnchEdge);

	for (y = 0; y < lSrcHeight; y++)
	{
		for (x = 0; x < lSrcWidth; x++)
		{
			lpSrcStartBits[y * lSrcWidth + x] = (unsigned char)(255 - pUnchEdge[y * lSrcWidth + x]);
		}
	}

	// 释放内存
	delete[]pUnchImage;
	pUnchImage = NULL;
	delete[]pUnchEdge;
	pUnchEdge = NULL;
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标形状
	EndWaitCursor();

	// 刷新屏幕
	Invalidate();
}


void CMFCApplication1View::OnUsm()
{
	// USM锐化

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档

	// 指向DIB的指针
	LPSTR	lpDIB;

	// 指向DIB象素指针
	LPSTR   lpDIBBits;

	// 指向缓存图像的指针
	LPSTR	lpDst;
	LPSTR  lpSrc;
	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//循环变量
	long i;
	long j;
	//中间变量
	FLOAT fTemp;
	FLOAT fTemp2;
	FLOAT result;

	// 模板高度
	int		iTempH;

	// 模板宽度
	int		iTempW;

	// 模板系数
	FLOAT	fTempC;

	// 模板中心元素X坐标
	int		iTempMX;

	// 模板中心元素Y坐标
	int		iTempMY;

	// 模板元素数组
	FLOAT	aValue[9];

	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB

	// 找到DIB图像象素起始位置
	lpDIBBits = lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	long DIBWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	long DIBHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	int lpSrcBitCount = pDoc->m_dib.GetBitCount(lpDIB);                    //获取图像位深
	long lLineBytes = pDoc->m_dib.GetReqByteWidth(DIBWidth * lpSrcBitCount);		// 计算图象每行的字节数
	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的平滑，其它的可以类推）
	if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
	{
		// 提示用户
		AfxMessageBox(L"目前只支持256色位图！");

		// 解除锁定

		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}

	// 创建对话框
	DlgUSM dlgPara;

	// 给模板赋初值（高斯模板）
	aValue[0] = 1.0;
	aValue[1] = 2.0;
	aValue[2] = 1.0;
	aValue[3] = 2.0;
	aValue[4] = 4.0;
	aValue[5] = 2.0;
	aValue[6] = 1.0;
	aValue[7] = 2.0;
	aValue[8] = 1.0;
	/*aValue[0] = 0.0;
	aValue[1] = -1.0;
	aValue[2] = 0.0;
	aValue[3] = -1.0;
	aValue[4] = 4.0;
	aValue[5] = -1.0;
	aValue[6] = 0.0;
	aValue[7] = -1.0;
	aValue[8] = 0.0;*/

	iTempH = 3;
	iTempW = 3;
	iTempMX = 1;
	iTempMY = 1;
	fTempC = FLOAT(1.0 / 16.0);

	// 初始化对话框变量值
	dlgPara.m_weight = 0.5;


	// 显示对话框，提示用户设定平移量
	if (dlgPara.DoModal() != IDOK)
	{

		// 返回
		return;
	}

	// 获取用户设定权重
	FLOAT weight = dlgPara.m_weight;

	// 删除对话框
	delete dlgPara;

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, DIBWidth * DIBHeight);

	if (hNewDIBBits == NULL)
	{
		// 提示用户
		AfxMessageBox(L"分配内存失败！");
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 初始化新分配的内存，为源图像
	lpDst = (char*)lpNewDIBBits;
	memcpy(lpNewDIBBits, lpDIBBits, DIBWidth * DIBHeight);

	// 更改光标形状
	BeginWaitCursor();



	// 调用Template()函数高斯滤波DIB
	if (::Template(lpNewDIBBits, DIBWidth, DIBHeight,
		iTempH, iTempW, iTempMX, iTempMY, aValue, fTempC))
	{
		//对每个像素进行计算
		//24位8位分别处理
		int gap = 1;
		if (lpSrcBitCount == 8)gap = 1;
		else if (lpSrcBitCount == 24)gap = 3;
		for (i = 0; i < DIBHeight; i++) {
			// 每列
			for (j = 0; j < DIBWidth; j++) {
				// 指向源图像第i行，第j个像素的指针
				lpSrc = (char*)lpDIBBits + lLineBytes * (DIBHeight - 1 - i) + j * gap;
				// 指向高斯模糊图像第i行，第j个像素的指针
				lpDst = (char*)lpNewDIBBits + lLineBytes * (DIBHeight - 1 - i) + j * gap;

				for (int k = 0; k < gap; k++) {
					fTemp = *(lpSrc + k);
					fTemp2 = *(lpDst + k);
					result = fTemp - fTemp2;

					if (abs(result) > 0) {//此处设置阈值，通过调节该值，来决定达到何种程度对比度的像素才需要增强
						result = ((fTemp - weight * fTemp2) / (1 - weight));
						//result = ((fTemp + weight * result));
						if (result > 255) {//防止溢出
							*(lpSrc + k) = *(lpSrc + k);
						}
						else {
							*(lpSrc + k) = (unsigned char)result;
						}
					}
				}
			}
		}





		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		AfxMessageBox(L"分配内存失败！");
		AfxMessageBox(L"系统提示");
	}

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}


void CMFCApplication1View::OnAddsy()
{
	//添加隐藏式数字水印，采取最低有效位法，水印只能使用二值图片
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 更改光标形状
	BeginWaitCursor();
	LONG i, j;//循环变量
	FLOAT fTemp1, fTemp2;//中间变量
	unsigned char* lpSrc;//指向缓存原图像像素的指针
	unsigned char* lpDst;//指向缓存水印像素的指针

	//最低有效位法，对源图像r值偶数化处理
		// 24位8位分别处理
	int gap = 1;
	if (lpSrcBitCount == 8)gap = 1;
	else if (lpSrcBitCount == 24)gap = 3;
	for (i = 0; i < lSrcHeight; i++) {
		// 每列
		for (j = 0; j < lSrcWidth; j++) {
			// 指向源DIB第i行，第j个像素的指针

			lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j * gap;
			fTemp1 = *lpSrc;
			int Temp = (int)fTemp1;
			if (Temp % 2 != 0) {
				fTemp1 += 1;
				if (fTemp1 > 255) {
					fTemp1 = 254;
				}
			}
			*lpSrc = (unsigned)fTemp1;

		}
	}



	CFileDialog fdlg(TRUE, _T("BMP"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"All files(*.*)|*.BMP|*.PNG|*.JPG||");
	fdlg.m_ofn.lpstrTitle = L"添加水印图片";
	// 数字水印

	long	lSrcLineBytesDst;		//水印图像每行的字节数
	long	lSrcWidthDst;      //水印图像的宽度和高度
	long	lSrcHeightDst;
	int     lpSrcBitCountDst;       //水印图像的位深

	if (fdlg.DoModal() == IDOK)
	{
		CStdioFile file;
		CString strFile = fdlg.GetPathName();//获取完整路径
		if (!file.Open(strFile, CFile::modeRead))
		{
			AfxMessageBox(L"打开文件失败");// 警告//读取失败，文件不符合要求
			return;
		}
		DWORD m_nFileLen = file.GetLength();//获取文件的长度
		char* m_pBMPBuffer = new char[m_nFileLen + 1];//开辟符数组
		if (!m_pBMPBuffer) {
			AfxMessageBox(L"水印图片过大，空间不足");// 警告//如果控件不够大
			return;
		}

		if (!file.Read(m_pBMPBuffer, m_nFileLen))//读取文件保存在字符数组中
		{
			AfxMessageBox(L"保存文件失败");// 警告
			return;
		}
		LPSTR hDIB, lpBuffer = m_pBMPBuffer;
		LPVOID lpSrcStartBitsDst;//保存水印图像像素的指针
		BITMAPFILEHEADER bmfHeader; //保存bmp文件头的信息
		DWORD bmfHeaderLen;//保存文件头的长度

		bmfHeaderLen = sizeof(bmfHeader); //读取文件头的长度
		strncpy_s((LPSTR)&bmfHeader, bmfHeaderLen, (LPSTR)lpBuffer, bmfHeaderLen);//文件的赋值
		if (bmfHeader.bfType != (*(WORD*)"BMP")) {//如果文件类型不对
			AfxMessageBox(L"文件类型不正确");// 警告
			return;
		}
		hDIB = lpBuffer + bmfHeaderLen; //将指针移动到文件头的后面
		BITMAPINFOHEADER& bmiHeader = *(LPBITMAPINFOHEADER)hDIB;//读取bmp文件的数据
		BITMAPINFO& bmInfo = *(LPBITMAPINFO)hDIB;
		lpSrcStartBitsDst = (lpBuffer)+((BITMAPFILEHEADER*)lpBuffer)->bfOffBits;//像素位
		//bfOffBits是从位图文件头到位图数据的偏移量
		//bfOffBits= sizeof (BITMAPFILEHEADER) + NumberOfRGBQUAD * sizeof (RGBQUAD)  + sizeof (BITMAPINFOHEADER);

		lSrcWidthDst = bmiHeader.biWidth;
		lSrcHeightDst = bmiHeader.biHeight;
		lpSrcBitCountDst = bmiHeader.biBitCount;
		lSrcLineBytesDst = (lSrcWidthDst * lpSrcBitCountDst + 31) / 32 * 4;
		if (lpSrcBitCountDst == 8) {
			for (i = 0; i < lSrcHeightDst; i++) {
				// 每列
				for (j = 0; j < lSrcWidthDst; j++) {

					// 指向水印DIB第i行，第j个像素的指针
					lpDst = (unsigned char*)lpSrcStartBitsDst + lSrcLineBytesDst * (lSrcHeightDst - 1 - i) + j;
					//二值判断
					fTemp2 = *lpDst;
					if (fTemp2 != 255 && fTemp2 != 0 && fTemp2 != 205) {
						CString   temp;//调试输出
						temp.Format(L"%f ", fTemp2);
						AfxMessageBox(temp);
						AfxMessageBox(L"添加的水印图片不是二值图！");// 警告
						return;

					}

				}

			}
		}
		else {
			AfxMessageBox(L"添加的水印图片不是二值图！");// 警告
			return;
		}
		if (lSrcHeightDst > lSrcHeight || lSrcWidthDst > lSrcWidth) {
			AfxMessageBox(L"水印图片较大，可能造成信息丢失");// 警告
		}

		//添加水印,最低有效位法
		// 24位8位分别处理
		int gap = 1;
		if (lpSrcBitCount == 8)gap = 1;
		else if (lpSrcBitCount == 24)gap = 3;
		for (i = 0; i < lSrcHeight; i++) {
			// 每列
			for (j = 0; j < lSrcWidth; j++) {
				// 指向源DIB第i行，第j个像素的指针
				lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j * gap;
				// 指向水印DIB第i行，第j个像素的指针
				//防止水印图像指针溢出
				if (i >= lSrcHeightDst || j >= lSrcWidthDst) {
					continue;
				}
				lpDst = (unsigned char*)lpSrcStartBitsDst + lSrcLineBytesDst * (lSrcHeightDst - 1 - i) + j;

				//文字部分像素r值为奇数，灰度图则灰度值为奇数
				fTemp1 = *lpSrc;
				fTemp2 = *lpDst;
				if (fTemp2 == 255) {
					fTemp1 -= 1;
					if (fTemp1 < 0)//防止下溢影响奇偶性
					{
						fTemp1 = 1;
					}
				}
				*lpSrc = fTemp1;
			}

		}
		file.Close();

	}

	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);

	AfxMessageBox(L"已成功添加目标水印！");// 提示
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}


void CMFCApplication1View::OnExtractsy()
{
	//提取水印信息
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 更改光标形状
	BeginWaitCursor();
	LONG i, j;//循环变量
	FLOAT fTemp;//中间变量
	unsigned char* lpSrc;//指向缓存原图像像素的指针


	//根据奇偶性二值化源图像
		// 24位8位分别处理
	int gap = 1;
	if (lpSrcBitCount == 8)gap = 1;
	else if (lpSrcBitCount == 24)gap = 3;
	for (i = 0; i < lSrcHeight; i++) {
		// 每列
		for (j = 0; j < lSrcWidth; j++) {
			// 指向源DIB第i行，第j个像素的指针

			lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j * gap;
			fTemp = *lpSrc;
			int Temp = (int)fTemp;
			if (Temp % 2 != 0) {
				fTemp = 255;
			}
			else {
				fTemp = 0;
			}
			*lpSrc = (unsigned)fTemp;
			if (lpSrcBitCount == 24) {
				*(lpSrc + 1) = (unsigned)fTemp;
				*(lpSrc + 2) = (unsigned)fTemp;
			}
		}
	}
	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);
	AfxMessageBox(L"成功提取水印信息");// 提示

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}
