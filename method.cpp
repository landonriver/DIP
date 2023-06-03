#include "pch.h"
#include "method.h"
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif
// 常数π
#define PI 3.1415926535

//角度到弧度转化的宏
#define RADIAN(angle) ((angle)*PI/180.0) 
#include "MFCApplication1Doc.h"
#include <math.h>
#include <direct.h>
#include <propkey.h>
#include "DIBAPI.h"
#include <queue>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
struct point {
	int i;
	int j;
};
//直接排序
int ZjSort(int* src, int* attach, int n)
{
	int cur, cur1;
	int i, j, k = 0;
	for (i = 1; i < n; i++)
	{
		cur = src[i];
		cur1 = attach[i];
		for (j = i - 1; j >= 0; j--)
		{
			if (cur > src[j])
			{
				src[j + 1] = src[j];
				attach[j + 1] = attach[j];
			}
			else
				break;
		}
		src[j + 1] = cur;
		attach[j + 1] = cur1;
	}
	return 0;
}

// 冒泡排序 
int MpSort(int* src, int* attach, int n)
{
	int i, j;
	int temp;
	for (i = 0; i < n - 1; i++)
		for (j = i + 1; j < n; j++)
		{
			if (src[i] < src[j])
			{
				temp = src[j];
				src[j] = src[i];
				src[i] = temp;

				temp = attach[j];
				attach[j] = attach[i];
				attach[i] = temp;
			}
		}
	return 0;
}

//快排
int KsSort(int* src, int* attach, int n)
{
	if (n <= 12)
		return ZjSort(src, attach, n);
	int low = 1, high = n - 1;
	int tmp;
	while (low <= high)
	{
		while (src[low] >= src[0])
		{
			if (++low > n - 1)
				break;
		}
		while (src[high] < src[0])
		{
			if (--high < 1)
				break;
		}
		if (low > high)
			break;
		{
			tmp = src[low];
			src[low] = src[high];
			src[high] = tmp;
			tmp = attach[low];
			attach[low] = attach[high];
			attach[high] = tmp;
		}
		low++;
		high--;
	}

	{
		tmp = src[low - 1];
		src[low - 1] = src[0];
		src[0] = tmp;
		tmp = attach[low - 1];
		attach[low - 1] = attach[0];
		attach[0] = tmp;
	}
	if (low > 1)
		KsSort(src, attach, low - 1);
	if (low < n)
		KsSort(&src[low], &attach[low], n - low);
	return 0;
}

//计算平方差的函数  
int PFC(int color1, int color2)
{
	int x, y, z;
	x = (color1 & 0xf) - (color2 & 0xf);
	y = ((color1 >> 4) & 0xf) - ((color2 >> 4) & 0xf);
	z = ((color1 >> 8) & 0xf) - ((color2 >> 8) & 0xf);
	return (x * x + y * y + z * z);
};


/*************************************************************************
 *
 * 函数名称：
 *   GetMedianNum()
 *
 * 参数:
 *   unsigned char * bpArray	- 指向要获取中值的数组指针
 *   int   iFilterLen			- 数组长度
 *
 * 返回值:
 *   unsigned char      - 返回指定数组的中值。
 *
 * 说明:
 *   该函数用冒泡法对一维数组进行排序，并返回数组元素的中值。
 *
 ************************************************************************/

unsigned char WINAPI GetMedianNum(unsigned char* bArray, int iFilterLen)
{
	// 循环变量
	int		i;
	int		j;

	// 中间变量
	unsigned char bTemp;

	// 用冒泡法对数组进行排序
	for (j = 0; j < iFilterLen - 1; j++)
	{
		for (i = 0; i < iFilterLen - j - 1; i++)
		{
			if (bArray[i] > bArray[i + 1])
			{
				// 互换
				bTemp = bArray[i];
				bArray[i] = bArray[i + 1];
				bArray[i + 1] = bTemp;
			}
		}
	}

	// 计算中值
	if ((iFilterLen & 1) > 0)
	{
		// 数组有奇数个元素，返回中间一个元素
		bTemp = bArray[(iFilterLen + 1) / 2];
	}
	else
	{
		// 数组有偶数个元素，返回中间两个元素平均值
		bTemp = (bArray[iFilterLen / 2] + bArray[iFilterLen / 2 + 1]) / 2;
	}

	// 返回中值
	return bTemp;
}


int BitTran(WORD* color24bit, LONG len, BYTE* Index, RGBQUAD* mainColor) {
	int usedTimes[4096] = { 0 };
	int miniColor[4096] = { 0 };
	LONG i;
	for (i = 0; i < 4096; i++)
		miniColor[i] = i;
	i = 0;
	for (i = 0; i < len; i++)
	{
		assert(color24bit[i] < 4096);  //图像的列宽要为4的倍数！！！
		usedTimes[color24bit[i]]++;
	}
	LONG numberOfColors = 0;
	for (i = 0; i < 4096; i++)
	{
		if (usedTimes[i] > 0)
			numberOfColors++;
	}
	//对usedTimes进行排序，排序过程中minColor数组(保存了颜色值)也作与useTimes  
	//数组相似的交换  
	KsSort(usedTimes, miniColor, 4096);    //ok
	//usedTimes数组中是各颜色使用频率，从高到低排列，显然第numberOfColor个之后的都为0  
	//miniColor数组中是相应的颜色数据  
	//将前256个颜色数据保存到256色位图的调色盘中  
	for (i = 0; i < 256; i++)
	{
		mainColor[i].rgbBlue = (BYTE)((miniColor[i] >> 8) << 4);
		mainColor[i].rgbGreen = (BYTE)(((miniColor[i] >> 4) & 0xf) << 4);
		mainColor[i].rgbRed = (BYTE)((miniColor[i] & 0xf) << 4);
		mainColor[i].rgbReserved = 0;
	}

	int* colorIndex = usedTimes;//用原来的useTimes数组来保存索引值  
	memset(colorIndex, 0, sizeof(int) * 4096);

	if (numberOfColors <= 256)
	{
		for (i = 0; i < numberOfColors; i++)
			colorIndex[miniColor[i]] = i;
	}
	else//为第256之后的颜色在前256种颜色中找一个最接近的  
	{
		for (i = 0; i < 256; i++)
			colorIndex[miniColor[i]] = i;

		int index, tmp, tmp1;
		for (i = 256; i < numberOfColors; i++)
		{
			tmp = PFC(miniColor[0], miniColor[i]);
			index = 0;
			for (int j = 1; j < 256; j++)
			{
				tmp1 = PFC(miniColor[j], miniColor[i]);
				if (tmp > tmp1)
				{
					tmp = tmp1;
					index = j;
				}
			}
			colorIndex[miniColor[i]] = index;
		}
	}
	//记录各点颜色数据的索引值，即256色位图的颜色数据  
	for (i = 0; i < len; i++)
	{
		assert(colorIndex[color24bit[i]] < 256);
		Index[i] = colorIndex[color24bit[i]];
	}

	return 1;
}

//内存分配函数
int BuildNewSize(unsigned char* tem, LPSTR lpSrc, int num)
{
	tem = new BYTE[num];
	memcpy(tem, lpSrc, num);
	return 1;
}

//8位反色函数
BOOL WINAPI LinerTrans(LPSTR lpSrcStartBits, LONG lSrcWidth,LONG lSrcHeight,FLOAT Fa, FLOAT Fb) {
	unsigned char* lpSrc;
	LONG i, j;
	LONG lineBytes = (((lSrcWidth * 8) + 31) / 32 * 4);
	FLOAT ftemp;
	for (i = 0; i < lSrcHeight; i++)
	{
		// 每列
		for (j = 0; j < lSrcWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpSrcStartBits + lineBytes * (lSrcHeight - 1 - i) + j;

			// 线性变换
			ftemp = Fa * (*lpSrc) + Fb;

			// 判断是否超出范围
			if (ftemp > 255)
			{
				// 直接赋值为255
				*lpSrc = 255;
			}
			else if (ftemp < 0)
			{
				// 直接赋值为0
				*lpSrc = 0;
			}
			else
			{
				// 四舍五入
				*lpSrc = (unsigned char)(ftemp + 0.5);
			}
		}
	}
	return 1;
}

BOOL WINAPI LinerTrans24(LPSTR lpSrcStartBits, LONG lSrcWidth, LONG lSrcHeight, FLOAT Fa, FLOAT Fb) {
	unsigned char* lpSrc;
	LONG i, j;
	LONG lineBytes = (((lSrcWidth * 24) + 31) / 32 * 4);
	FLOAT ftemp;
	for (i = 0; i < lSrcHeight; i++) {
		for (j = 0; j < lSrcWidth; j++) {
			lpSrc = (unsigned char*)lpSrcStartBits + lineBytes * i + j*3;
			ftemp = Fa * (*lpSrc) + Fb;
			if (ftemp > 255) {
				*lpSrc = 255;
			}
			else if (ftemp < 0) {
				*lpSrc = 0;
			}
			else {
				*lpSrc = (unsigned char)(ftemp + 0.5);
			}

			lpSrc = (unsigned char*)lpSrcStartBits + lineBytes * i + j * 3+1;
			ftemp = Fa * (*lpSrc) + Fb;
			if (ftemp > 255) {
				*lpSrc = 255;
			}
			else if (ftemp < 0) {
				*lpSrc = 0;
			}
			else {
				*lpSrc = (unsigned char)(ftemp + 0.5);
			}

			lpSrc = (unsigned char*)lpSrcStartBits + lineBytes * i + j * 3+2;
			ftemp = Fa * (*lpSrc) + Fb;
			if (ftemp > 255) {
				*lpSrc = 255;
			}
			else if (ftemp < 0) {
				*lpSrc = 0;
			}
			else {
				*lpSrc = (unsigned char)(ftemp + 0.5);
			}
		}
	}


	return 1;
}

BOOL WINAPI FdLinear_Tran(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int type, int threshold)
{
	// 指向源图像的指针
	unsigned char* lpSrc;

	// 循环变量
	LONG	i;
	LONG	j;

	// 图像每行的字节数
	LONG	lLineBytes;

	// 中间变量
	FLOAT	fTemp=0, fA1 = 1, fB1 = 0, fA2 = 1, fB2 = 0;
	//中间灰度
	int seg_gray = 127;

	// 计算图像每行的字节数
	lLineBytes = (((lWidth * 8) + 31) / 32 * 4);
	//计算线性变换的参数
	if (type == 1)//倒V字型
	{
		fA1 = (float)(255 / threshold);//2.0 if threshold==128;
		fB1 = 0;  //(2f)
		fA2 = -(float)(255 / threshold);//-2.0 if threshold==128;
		fB1 = (float)(255 + (255 * threshold) / (255 - threshold));//(-2f+2*255)  if threshold==128;
	}
	if (type == 2)//V字型
	{
		fA1 = -2.0;
		fB1 = 255;  //(-2f+255)
		fA2 = 2.0;
		fB1 = -255;//(2f-255)
	}
	if (type == 3)//倒L字型
	{
		fA1 = 2.0;
		fB1 = 0;  //(2f)
		fA2 = 0;
		fB1 = 255;//(255)
	}
	if (type == 4)//L字型
	{
		fA1 = -2.0;
		fB1 = 255;  //(-2f+255)
		fA2 = 0.0;
		fB1 = 0;//(0)
	}
	// 每行
	for (i = 0; i < lHeight; i++)
	{
		// 每列
		for (j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 线性变换,分段
			if (*lpSrc >= 0 && *lpSrc <= seg_gray)
				fTemp = fA1 * (*lpSrc) + fB1;
			if (*lpSrc >= seg_gray + 1 && *lpSrc <= 255)
				fTemp = fA2 * (*lpSrc) + fB2;
			// 判断是否超出范围
			if (fTemp > 255)
			{
				// 直接赋值为255
				*lpSrc = 255;
			}
			else if (fTemp < 0)
			{
				// 直接赋值为0
				*lpSrc = 0;
			}
			else
			{
				// 四舍五入
				*lpSrc = (unsigned char)(fTemp + 0.5);
			}
		}
	}

	// 返回
	return TRUE;

}

BOOL WINAPI LinerTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lSrcLineBytes, FLOAT fA, FLOAT fB)
{
	unsigned char* lpSrc;//指向DIB源像素的指针
	FLOAT fTemp;//中间变量
	for (int i = 0; i < lHeight; i++) {
		for (int j = 0; j < lWidth; j++) {
			lpSrc = (unsigned char*)lpDIBBits + lSrcLineBytes * (lHeight - 1 - i) + j;
			fTemp = (float)*lpSrc;
			fTemp = fA * fTemp + fB;
			//线性变换

			//判断是否超出范围
			if (fTemp > 255)
				//直接赋值为255 
				*lpSrc = 255;
			else if (fTemp < 0)
				// 四舍五入
				*lpSrc = 0;
			else {
				*lpSrc = (unsigned char)(fTemp + 0.5);
			}
		}
	}
	return TRUE;
}

/////////////////////////////////////////
//------------------位平面切分函数
/*************************************************************************
* 函数名称：
*   BitPlaneSlicing()
* 参数:
*   LPSTR lpDIBBits    - 指向源DIB图像指针
*   LONG  lWidth       - 源图像宽度（象素数，必须是4的倍数）
*   LONG  lHeight      - 源图像高度（象素数）
*   LONG  lLineBytes   -每行字节数
*   int   Bit    		- 分割 位 （0---7）
* 返回值:
*   BOOL               - 运算成功返回TRUE，否则返回FALSE。
* 说明:
* 该函数用于对图像进行位平面分割。8位
************************************************************************/
BOOL BitPlaneSlicing(LPSTR lpDIBBits, LONG lmageWidth, LONG  lLineBytes, LONG lmageHeight, int Bit)
{
	int i;  //循环变量
	int j;	//循环变量
	// 指向源图像的指针
	unsigned char* lpSrc;
	//像素值
	unsigned char pixeltemp;
	int threshold1, threshold2;
	switch (Bit)
	{
	case 7:
		threshold1 = 128;
		threshold2 = 256;
		break;
	case 6:
		threshold1 = 64;
		threshold2 = 128;
		break;
	case 5:
		threshold1 = 32;
		threshold2 = 64;
		break;
	case 4:
		threshold1 = 16;
		threshold2 = 32;
		break;
	case 3:
		threshold1 = 8;
		threshold2 = 16;
		break;
	case 2:
		threshold1 = 4;
		threshold2 = 8;
		break;
	case 1:
		threshold1 = 2;
		threshold2 = 4;
		break;
	case 0:
		threshold1 = 0;
		threshold2 = 2;
		break;
	default:
		return false;

	}
	for (j = 0; j < lmageHeight; j++)
	{
		for (i = 0; i < lmageWidth; i++)
		{

			// 指向源图像倒数第j行，第i个象素的指针			
			//lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * j + i;
			//取得当前指针处的像素值
			pixeltemp = (unsigned char)*lpSrc;
			//目标图像中灰度值小于门限则设置为黑点
			if (pixeltemp >= threshold1 && pixeltemp < threshold2)
			{
				//*lpSrc = (unsigned char)255;
			}
			else	//否则设置为白点
			{
				*lpSrc = (unsigned char)0;
			}
		}
	}
	return true;
}

/*************************************************************************
 * 函数名称：LogTranslation(LPSTR lpSrcStartBits, long lWidth, long lHeight, long lLineBytes)
 * 函数参数:
	 LPSTR	lpSrcStartBits,指向DIB起始像素的指针
	 long	lWidth，DIB图象的宽度
	 long	lHeight，DIB图象的高度
	 long	lLineBytes，DIB图象的行字节数，为4的倍数
 * 函数类型:BOOL
 * 函数功能:该函数用来对图象进行对数变换
 ************************************************************************/

BOOL  LogTranslation(LPSTR lpSrcStartBits, long lWidth, long lHeight, long lLineBytes)
{
	long i;                 //行循环变量
	long j;                 //列循环变量
	unsigned char* lpSrcUnChr;	//指向像素的指针
	for (i = 0; i < lHeight; i++)// 行
	{
		for (j = 0; j < lWidth; j++)// 列
		{
			lpSrcUnChr = (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight - 1 - i) + j;// 指向DIB第i行，第j个像素的指针
			//*lpSrcUnChr=50*(unsigned char)log((*lpSrcUnChr+1));
			*lpSrcUnChr = 255 * (unsigned char)log((*lpSrcUnChr + 1)) / log(255);
		}
	}
	return TRUE;
}




/*************************************************************************
 *
 * 函数名称：
 *   Template()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   int   iTempH		- 模板的高度
 *   int   iTempW		- 模板的宽度
 *   int   iTempMX		- 模板的中心元素X坐标 ( < iTempW - 1)
 *   int   iTempMY		- 模板的中心元素Y坐标 ( < iTempH - 1)
 *	 FLOAT * fpArray	- 指向模板数组的指针
 *	 FLOAT fCoef		- 模板系数
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用指定的模板（任意大小）来对图像进行操作，参数iTempH指定模板
 * 的高度，参数iTempW指定模板的宽度，参数iTempMX和iTempMY指定模板的中心
 * 元素坐标，参数fpArray指定模板元素，fCoef指定系数。
 *
 ************************************************************************/


BOOL WINAPI Template(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int iTempH, int iTempW, int iTempMX, int iTempMY, FLOAT* fpArray, FLOAT fCoef){
	LPSTR lpNewDIBBits;
	HLOCAL hNewDIBBits;
	unsigned char* lpSrc;
	unsigned char* lpDst;
	LONG i, j, k, l;
	FLOAT fResult;
	LONG lLineBytes;
	lLineBytes = (((lWidth * 8) + 31) / 32 * 4);
	hNewDIBBits = LocalAlloc(LHND, lLineBytes * lHeight);
	if (hNewDIBBits == NULL) {
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

			// 取绝对值
			fResult = (FLOAT)fabs(fResult);

			// 判断是否超过255
			if (fResult > 255)
			{
				// 直接赋值为255
				*lpDst = 255;
			}
			else
			{
				// 赋值
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







BOOL WINAPI Select(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int iTempH, int iTempW, int iTempMX, int iTempMY) {

		
	// 指向源图像的指针
	unsigned char* lpSrc;

	// 指向要复制区域的指针
	unsigned char* lpDst;

	// 指向复制图像的指针
	LPSTR			lpNewDIBBits;
	HLOCAL			hNewDIBBits;

	// 指向滤波器数组的指针
	unsigned char* aValue;
	HLOCAL			hArray;

	// 循环变量
	LONG			i;
	LONG			j;
	LONG			k;
	LONG			l;

	// 图像每行的字节数
	LONG			lLineBytes;

	// 计算图像每行的字节数
	lLineBytes = (lWidth * 8 + 31) / 32 * 4;

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

	// 暂时分配内存，以保存滤波器数组
	hArray = LocalAlloc(LHND, iTempH * iTempW);

	// 判断是否内存分配失败
	if (hArray == NULL)
	{
		// 释放内存
		LocalUnlock(hNewDIBBits);
		LocalFree(hNewDIBBits);

		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	aValue = (unsigned char*)LocalLock(hArray);
	
	// 开始中值滤波
	// 行(除去边缘几行)
	for (i = iTempMY; i < lHeight - iTempH + iTempMY + 1; i++)
	{
		// 列(除去边缘几列)
		for (j = iTempMX; j < lWidth - iTempW + iTempMX + 1; j++)
		{
			// 指向新DIB第i行，第j个象素的指针
			lpDst = (unsigned char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 读取滤波器数组
			for (k = 0; k < iTempH; k++)
			{
				for (l = 0; l < iTempW; l++)
				{
					// 指向DIB第i - iFilterMY + k行，第j - iFilterMX + l个象素的指针
					lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i + iTempMY - k) + j - iTempMX + l;

					// 保存象素值
					aValue[k * iTempW + l] = *lpSrc;
				}
			}

			// 获取中值
			*lpDst = GetMedianNum(aValue, iTempH * iTempW);
		}
	}

	// 复制变换后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
	LocalUnlock(hArray);
	LocalFree(hArray);

	// 返回
	return TRUE;

}

BOOL WINAPI RobertDEC(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{

	// 指向源图像的指针
	LPSTR	lpSrc;

	// 指向缓存图像的指针
	LPSTR	lpDst;

	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//循环变量
	long i;
	long j;

	//像素值
	double result;
	unsigned char pixel[4];

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 初始化新分配的内存，设定初始值为255
	lpDst = (char*)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);


	//使用水平方向的结构元素进行腐蚀
	for (j = lHeight - 1; j > 0; j--)
	{
		for (i = 0; i < lWidth - 1; i++)
		{
			//由于使用2×2的模板，为防止越界，所以不处理最下边和最右边的两列像素

			// 指向源图像第j行，第i个象素的指针			
			lpSrc = (char*)lpDIBBits + lWidth * j + i;

			// 指向目标图像第j行，第i个象素的指针			
			lpDst = (char*)lpNewDIBBits + lWidth * j + i;

			//取得当前指针处2*2区域的像素值，注意要转换为unsigned char型
			pixel[0] = (unsigned char)*lpSrc;
			pixel[1] = (unsigned char)*(lpSrc + 1);
			pixel[2] = (unsigned char)*(lpSrc - lWidth);
			pixel[3] = (unsigned char)*(lpSrc - lWidth + 1);

			//计算目标图像中的当前点
			result = sqrt((pixel[0] - pixel[3]) * (pixel[0] - pixel[3]) + \
				(pixel[1] - pixel[2]) * (pixel[1] - pixel[2]));
			*lpDst = (unsigned char)result;

		}
	}

	// 复制锐化后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// 返回
	return TRUE;
}


BOOL WINAPI SobelDEC(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{

	// 指向缓存图像的指针
	LPSTR	lpDst1;
	LPSTR	lpDst2;

	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits1;
	HLOCAL	hNewDIBBits1;
	LPSTR	lpNewDIBBits2;
	HLOCAL	hNewDIBBits2;

	//循环变量
	long i;
	long j;

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

	//模板数组
	FLOAT aTemplate[9];

	// 暂时分配内存，以保存新图像
	hNewDIBBits1 = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits1 == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits1 = (char*)LocalLock(hNewDIBBits1);

	// 暂时分配内存，以保存新图像
	hNewDIBBits2 = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits2 == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits2 = (char*)LocalLock(hNewDIBBits2);

	// 拷贝源图像到缓存图像中
	lpDst1 = (char*)lpNewDIBBits1;
	memcpy(lpNewDIBBits1, lpDIBBits, lWidth * lHeight);
	lpDst2 = (char*)lpNewDIBBits2;
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);

	// 设置Sobel模板参数
	iTempW = 3;
	iTempH = 3;
	fTempC = 1.0;
	iTempMX = 1;
	iTempMY = 1;
	aTemplate[0] = -1.0;
	aTemplate[1] = -2.0;
	aTemplate[2] = -1.0;
	aTemplate[3] = 0.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 0.0;
	aTemplate[6] = 1.0;
	aTemplate[7] = 2.0;
	aTemplate[8] = 1.0;

	// 调用Template()函数
	if (!Template(lpNewDIBBits1, lWidth, lHeight,
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	// 设置Sobel模板参数
	aTemplate[0] = -1.0;
	aTemplate[1] = 0.0;
	aTemplate[2] = 1.0;
	aTemplate[3] = -2.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 2.0;
	aTemplate[6] = -1.0;
	aTemplate[7] = 0.0;
	aTemplate[8] = 1.0;

	// 调用Template()函数
	if (!Template(lpNewDIBBits2, lWidth, lHeight,
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	//求两幅缓存图像的最大值
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0; i < lWidth - 1; i++)
		{

			// 指向缓存图像1倒数第j行，第i个象素的指针			
			lpDst1 = (char*)lpNewDIBBits1 + lWidth * j + i;

			// 指向缓存图像2倒数第j行，第i个象素的指针			
			lpDst2 = (char*)lpNewDIBBits2 + lWidth * j + i;
			if (*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;

		}
	}

	// 复制经过模板运算后的图像到源图像
	memcpy(lpDIBBits, lpNewDIBBits1, lWidth * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits1);
	LocalFree(hNewDIBBits1);

	LocalUnlock(hNewDIBBits2);
	LocalFree(hNewDIBBits2);
	// 返回
	return TRUE;
}

/*************************************************************************
 *
 * 函数名称：
 *   ErosiontionDIB()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   int   nMode		- 腐蚀方式，0表示水平方向，1表示垂直方向，2表示自定义结构元素。
 *	 int   structure[3][3]
						- 自定义的3×3结构元素。
 *
 * 返回值:
 *   BOOL               - 腐蚀成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 * 该函数用于对图像进行腐蚀运算。结构元素为水平方向或垂直方向的三个点，中间点位于原点；
 * 或者由用户自己定义3×3的结构元素。
 *
 * 要求目标图像为只有0和255两个灰度值的灰度图像。
 ************************************************************************/

BOOL WINAPI ErosionDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int nMode, int structure[3][3])
{

	// 指向源图像的指针
	LPSTR	lpSrc;

	// 指向缓存图像的指针
	LPSTR	lpDst;

	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//循环变量
	long i;
	long j;
	int  n;
	int  m;

	//像素值
	unsigned char pixel;

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 初始化新分配的内存，设定初始值为255
	lpDst = (char*)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);


	if (nMode == 0)
	{
		//使用水平方向的结构元素进行腐蚀
		for (j = 0; j < lHeight; j++)
		{
			for (i = 1; i < lWidth - 1; i++)
			{
				//由于使用1×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//目标图像中的当前点先赋成黑色
				*lpDst = (unsigned char)0;

				//如果源图像中当前点自身或者左右有一个点不是黑色，
				//则将目标图像中的当前点赋成白色
				for (n = 0; n < 3; n++)
				{
					pixel = *(lpSrc + n - 1);
					if (pixel == 255)
					{
						*lpDst = (unsigned char)255;
						break;
					}
				}

			}
		}

	}
	else if (nMode == 1)
	{
		//使用垂直方向的结构元素进行腐蚀
		for (j = 1; j < lHeight - 1; j++)
		{
			for (i = 0; i < lWidth; i++)
			{
				//由于使用1×3的结构元素，为防止越界，所以不处理最上边和最下边的两列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//目标图像中的当前点先赋成黑色
				*lpDst = (unsigned char)0;

				//如果源图像中当前点自身或者上下有一个点不是黑色，
				//则将目标图像中的当前点赋成白色
				for (n = 0; n < 3; n++)
				{
					pixel = *(lpSrc + (n - 1) * lWidth);
					if (pixel == 255)
					{
						*lpDst = (unsigned char)255;
						break;
					}
				}

			}
		}

	}
	else
	{
		//使用自定义的结构元素进行腐蚀
		for (j = 1; j < lHeight - 1; j++)
		{
			for (i = 0; i < lWidth; i++)
			{
				//由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素
				//和最上边和最下边的两列像素
				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//目标图像中的当前点先赋成黑色
				*lpDst = (unsigned char)0;

				//如果原图像中对应结构元素中为黑色的那些点中有一个不是黑色，
				//则将目标图像中的当前点赋成白色
				//注意在DIB图像中内容是上下倒置的
				for (m = 0; m < 3; m++)
				{
					for (n = 0; n < 3; n++)
					{
						if (structure[m][n] == -1)
							continue;
						pixel = *(lpSrc + ((2 - m) - 1) * lWidth + (n - 1));
						if (pixel == 255)
						{
							*lpDst = (unsigned char)255;
							break;
						}
					}
				}

			}
		}

	}
	// 复制腐蚀后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// 返回
	return TRUE;
}


/*************************************************************************
 *
 * 函数名称：
 *   DilationDIB()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   int   nMode		- 膨胀方式，0表示水平方向，1表示垂直方向，2表示自定义结构元素。
 *	 int   structure[3][3]
						- 自定义的3×3结构元素。
 *
 * 返回值:
 *   BOOL               - 膨胀成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 * 该函数用于对图像进行膨胀运算。结构元素为水平方向或垂直方向的三个点，中间点位于原点；
 * 或者由用户自己定义3×3的结构元素。
 *
 * 要求目标图像为只有0和255两个灰度值的灰度图像。
 ************************************************************************/


BOOL WINAPI DilationDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int nMode, int structure[3][3])
{

	// 指向源图像的指针
	LPSTR	lpSrc;

	// 指向缓存图像的指针
	LPSTR	lpDst;

	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//循环变量
	long i;
	long j;
	int  n;
	int  m;

	//像素值
	unsigned char pixel;

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 初始化新分配的内存，设定初始值为255
	lpDst = (char*)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);


	if (nMode == 0)
	{
		//使用水平方向的结构元素进行膨胀
		for (j = 0; j < lHeight; j++)
		{
			for (i = 1; i < lWidth - 1; i++)
			{
				//由于使用1×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && pixel != 0)
					return FALSE;

				//目标图像中的当前点先赋成白色
				*lpDst = (unsigned char)255;

				//源图像中当前点自身或者左右只要有一个点是黑色，
				//则将目标图像中的当前点赋成黑色
				for (n = 0; n < 3; n++)
				{
					pixel = *(lpSrc + n - 1);
					if (pixel == 0)
					{
						*lpDst = (unsigned char)0;
						break;
					}
				}

			}
		}

	}
	else if (nMode == 1)
	{
		//使用垂直方向的结构元素进行膨胀
		for (j = 1; j < lHeight - 1; j++)
		{
			for (i = 0; i < lWidth; i++)
			{
				//由于使用1×3的结构元素，为防止越界，所以不处理最上边和最下边的两列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//目标图像中的当前点先赋成白色
				*lpDst = (unsigned char)255;

				//源图像中当前点自身或者上下只要有一个点是黑色，
				//则将目标图像中的当前点赋成黑色
				for (n = 0; n < 3; n++)
				{
					pixel = *(lpSrc + (n - 1) * lWidth);
					if (pixel == 0)
					{
						*lpDst = (unsigned char)0;
						break;
					}
				}

			}
		}

	}
	else
	{
		//使用自定义的结构元素进行膨胀
		for (j = 1; j < lHeight - 1; j++)
		{
			for (i = 0; i < lWidth; i++)
			{
				//由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素
				//和最上边和最下边的两列像素
				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//目标图像中的当前点先赋成白色
				*lpDst = (unsigned char)255;

				//原图像中对应结构元素中为黑色的那些点中只要有一个是黑色，
				//则将目标图像中的当前点赋成黑色
				//注意在DIB图像中内容是上下倒置的
				for (m = 0; m < 3; m++)
				{
					for (n = 0; n < 3; n++)
					{
						if (structure[m][n] == -1)
							continue;
						pixel = *(lpSrc + ((2 - m) - 1) * lWidth + (n - 1));
						if (pixel == 0)
						{
							*lpDst = (unsigned char)0;
							break;
						}
					}
				}

			}
		}

	}
	// 复制膨胀后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// 返回
	return TRUE;
}


/*************************************************************************
 *
 * 函数名称：
 *   OpenDIB()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   int   nMode		- 开运算方式，0表示水平方向，1表示垂直方向，2表示自定义结构元素。
 *	 int   structure[3][3]
						- 自定义的3×3结构元素。
 *
 * 返回值:
 *   BOOL               - 开运算成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 * 该函数用于对图像进行开运算。结构元素为水平方向或垂直方向的三个点，中间点位于原点；
 * 或者由用户自己定义3×3的结构元素。
 *
 * 要求目标图像为只有0和255两个灰度值的灰度图像。
 ************************************************************************/

BOOL WINAPI OpenDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int nMode, int structure[3][3])
{

	// 指向源图像的指针
	LPSTR	lpSrc;

	// 指向缓存图像的指针
	LPSTR	lpDst;

	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//循环变量
	long i;
	long j;
	int  n;
	int  m;

	//像素值
	unsigned char pixel;

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 初始化新分配的内存，设定初始值为255
	lpDst = (char*)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);


	if (nMode == 0)
	{
		//使用水平方向的结构元素进行腐蚀
		for (j = 0; j < lHeight; j++)
		{
			for (i = 1; i < lWidth - 1; i++)
			{
				//由于使用1×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//目标图像中的当前点先赋成黑色
				*lpDst = (unsigned char)0;

				//如果源图像中当前点自身或者左右有一个点不是黑色，
				//则将目标图像中的当前点赋成白色
				for (n = 0; n < 3; n++)
				{
					pixel = *(lpSrc + n - 1);
					if (pixel == 255)
					{
						*lpDst = (unsigned char)255;
						break;
					}
				}

			}
		}

	}
	else if (nMode == 1)
	{
		//使用垂直方向的结构元素进行腐蚀
		for (j = 1; j < lHeight - 1; j++)
		{
			for (i = 0; i < lWidth; i++)
			{
				//由于使用1×3的结构元素，为防止越界，所以不处理最上边和最下边的两列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//目标图像中的当前点先赋成黑色
				*lpDst = (unsigned char)0;

				//如果源图像中当前点自身或者上下有一个点不是黑色，
				//则将目标图像中的当前点赋成白色
				for (n = 0; n < 3; n++)
				{
					pixel = *(lpSrc + (n - 1) * lWidth);
					if (pixel == 255)
					{
						*lpDst = (unsigned char)255;
						break;
					}
				}

			}
		}

	}
	else
	{
		//使用自定义的结构元素进行腐蚀
		for (j = 1; j < lHeight - 1; j++)
		{
			for (i = 0; i < lWidth; i++)
			{
				//由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素
				//和最上边和最下边的两列像素
				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//目标图像中的当前点先赋成黑色
				*lpDst = (unsigned char)0;

				//如果原图像中对应结构元素中为黑色的那些点中有一个不是黑色，
				//则将目标图像中的当前点赋成白色
				//注意在DIB图像中内容是上下倒置的
				for (m = 0; m < 3; m++)
				{
					for (n = 0; n < 3; n++)
					{
						if (structure[m][n] == -1)
							continue;
						pixel = *(lpSrc + ((2 - m) - 1) * lWidth + (n - 1));
						if (pixel == 255)
						{
							*lpDst = (unsigned char)255;
							break;
						}
					}
				}

			}
		}

	}
	// 复制腐蚀后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// 重新初始化新分配的内存，设定初始值为255
	//lpDst = (char *)lpNewDIBBits;
	//memset(lpDst, (BYTE)255, lWidth * lHeight);


	if (nMode == 0)
	{
		//使用水平方向的结构元素进行膨胀
		for (j = 0; j < lHeight; j++)
		{
			for (i = 1; i < lWidth - 1; i++)
			{
				//由于使用1×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//目标图像中的当前点先赋成白色
				*lpDst = (unsigned char)255;

				//源图像中当前点自身或者左右只要有一个点是黑色，
				//则将目标图像中的当前点赋成黑色
				for (n = 0; n < 3; n++)
				{
					pixel = *(lpSrc + n - 1);
					if (pixel == 0)
					{
						*lpDst = (unsigned char)0;
						break;
					}
				}

			}
		}

	}
	else if (nMode == 1)
	{
		//使用垂直方向的结构元素进行膨胀
		for (j = 1; j < lHeight - 1; j++)
		{
			for (i = 0; i < lWidth; i++)
			{
				//由于使用1×3的结构元素，为防止越界，所以不处理最上边和最下边的两列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//目标图像中的当前点先赋成白色
				*lpDst = (unsigned char)255;

				//源图像中当前点自身或者上下只要有一个点是黑色，
				//则将目标图像中的当前点赋成黑色
				for (n = 0; n < 3; n++)
				{
					pixel = *(lpSrc + (n - 1) * lWidth);
					if (pixel == 0)
					{
						*lpDst = (unsigned char)0;
						break;
					}
				}

			}
		}

	}
	else
	{
		//使用自定义的结构元素进行膨胀
		for (j = 1; j < lHeight - 1; j++)
		{
			for (i = 0; i < lWidth; i++)
			{
				//由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素
				//和最上边和最下边的两列像素
				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//目标图像中的当前点先赋成白色
				*lpDst = (unsigned char)255;

				//原图像中对应结构元素中为黑色的那些点中只要有一个是黑色，
				//则将目标图像中的当前点赋成黑色
				//注意在DIB图像中内容是上下倒置的
				for (m = 0; m < 3; m++)
				{
					for (n = 0; n < 3; n++)
					{
						if (structure[m][n] == -1)
							continue;
						pixel = *(lpSrc + ((2 - m) - 1) * lWidth + (n - 1));
						if (pixel == 0)
						{
							*lpDst = (unsigned char)0;
							break;
						}
					}
				}

			}
		}

	}
	// 复制膨胀后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);


	return TRUE;
}


/*************************************************************************
 *
 * 函数名称：
 *   CloseDIB()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   int   nMode		- 闭运算方式，0表示水平方向，1表示垂直方向，2表示自定义结构元素。
 *	 int   structure[3][3]
						- 自定义的3×3结构元素。
 *
 * 返回值:
 *   BOOL               - 闭运算成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 * 该函数用于对图像进行开运算。结构元素为水平方向或垂直方向的三个点，中间点位于原点；
 * 或者由用户自己定义3×3的结构元素。
 *
 * 要求目标图像为只有0和255两个灰度值的灰度图像。
 ************************************************************************/

 /*************************************************************************
  *
  * 函数名称：
  *   ThinDIB()
  *
  * 参数:
  *   LPSTR lpDIBBits    - 指向源DIB图像指针
  *   LONG  lWidth       - 源图像宽度（象素数，必须是4的倍数）
  *   LONG  lHeight      - 源图像高度（象素数）
  *
  * 返回值:
  *   BOOL               - 闭运算成功返回TRUE，否则返回FALSE。
  *
  * 说明:
  * 该函数用于对图像进行细化运算。
  *
  * 要求目标图像为只有0和255两个灰度值的灰度图像。
  ************************************************************************/

BOOL WINAPI CloseDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int nMode, int structure[3][3])
{
	if (DilationDIB(lpDIBBits, lWidth, lHeight, nMode, structure))
	{

		if (ErosionDIB(lpDIBBits, lWidth, lHeight, nMode, structure))
		{
			// 返回
			return TRUE;

		}
	}
	return FALSE;

	// 返回
	return TRUE;
}

BOOL WINAPI ThiningDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{

	// 指向源图像的指针
	LPSTR	lpSrc;

	// 指向缓存图像的指针
	LPSTR	lpDst;

	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//脏标记
	BOOL bModified;

	//循环变量
	long i;
	long j;
	int  n;
	int  m;

	//四个条件
	BOOL bCondition1;
	BOOL bCondition2;
	BOOL bCondition3;
	BOOL bCondition4;

	//计数器
	unsigned char nCount;

	//像素值
	unsigned char pixel;

	//5×5相邻区域像素值
	unsigned char neighbour[5][5];

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 初始化新分配的内存，设定初始值为255
	lpDst = (char*)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);

	bModified = TRUE;

	while (bModified)
	{

		bModified = FALSE;
		// 初始化新分配的内存，设定初始值为255
		lpDst = (char*)lpNewDIBBits;
		memset(lpDst, (BYTE)255, lWidth * lHeight);

		for (j = 2; j < lHeight - 2; j++)
		{
			for (i = 2; i < lWidth - 2; i++)
			{

				bCondition1 = FALSE;
				bCondition2 = FALSE;
				bCondition3 = FALSE;
				bCondition4 = FALSE;

				//由于使用5×5的结构元素，为防止越界，所以不处理外围的几行和几列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && *lpSrc != 0)
					//return FALSE;
					continue;
				//如果源图像中当前点为白色，则跳过
				else if (pixel == 255)
					continue;

				//获得当前点相邻的5×5区域内像素值，白色用0代表，黑色用1代表
				for (m = 0; m < 5; m++)
				{
					for (n = 0; n < 5; n++)
					{
						neighbour[m][n] = (255 - (unsigned char)*(lpSrc + ((4 - m) - 2) * lWidth + n - 2)) / 255;
					}
				}
				//				neighbour[][]
								//逐个判断条件。
								//判断2<=NZ(P1)<=6
				nCount = neighbour[1][1] + neighbour[1][2] + neighbour[1][3] \
					+ neighbour[2][1] + neighbour[2][3] + \
					+ neighbour[3][1] + neighbour[3][2] + neighbour[3][3];
				if (nCount >= 2 && nCount <= 6)
					bCondition1 = TRUE;

				//判断Z0(P1)=1
				nCount = 0;
				if (neighbour[1][2] == 0 && neighbour[1][1] == 1)
					nCount++;
				if (neighbour[1][1] == 0 && neighbour[2][1] == 1)
					nCount++;
				if (neighbour[2][1] == 0 && neighbour[3][1] == 1)
					nCount++;
				if (neighbour[3][1] == 0 && neighbour[3][2] == 1)
					nCount++;
				if (neighbour[3][2] == 0 && neighbour[3][3] == 1)
					nCount++;
				if (neighbour[3][3] == 0 && neighbour[2][3] == 1)
					nCount++;
				if (neighbour[2][3] == 0 && neighbour[1][3] == 1)
					nCount++;
				if (neighbour[1][3] == 0 && neighbour[1][2] == 1)
					nCount++;
				if (nCount == 1)
					bCondition2 = TRUE;

				//判断P2*P4*P8=0 or Z0(p2)!=1
				if (neighbour[1][2] * neighbour[2][1] * neighbour[2][3] == 0)
					bCondition3 = TRUE;
				else
				{
					nCount = 0;
					if (neighbour[0][2] == 0 && neighbour[0][1] == 1)
						nCount++;
					if (neighbour[0][1] == 0 && neighbour[1][1] == 1)
						nCount++;
					if (neighbour[1][1] == 0 && neighbour[2][1] == 1)
						nCount++;
					if (neighbour[2][1] == 0 && neighbour[2][2] == 1)
						nCount++;
					if (neighbour[2][2] == 0 && neighbour[2][3] == 1)
						nCount++;
					if (neighbour[2][3] == 0 && neighbour[1][3] == 1)
						nCount++;
					if (neighbour[1][3] == 0 && neighbour[0][3] == 1)
						nCount++;
					if (neighbour[0][3] == 0 && neighbour[0][2] == 1)
						nCount++;
					if (nCount != 1)
						bCondition3 = TRUE;
				}

				//判断P2*P4*P6=0 or Z0(p4)!=1
				if (neighbour[1][2] * neighbour[2][1] * neighbour[3][2] == 0)
					bCondition4 = TRUE;
				else
				{
					nCount = 0;
					if (neighbour[1][1] == 0 && neighbour[1][0] == 1)
						nCount++;
					if (neighbour[1][0] == 0 && neighbour[2][0] == 1)
						nCount++;
					if (neighbour[2][0] == 0 && neighbour[3][0] == 1)
						nCount++;
					if (neighbour[3][0] == 0 && neighbour[3][1] == 1)
						nCount++;
					if (neighbour[3][1] == 0 && neighbour[3][2] == 1)
						nCount++;
					if (neighbour[3][2] == 0 && neighbour[2][2] == 1)
						nCount++;
					if (neighbour[2][2] == 0 && neighbour[1][2] == 1)
						nCount++;
					if (neighbour[1][2] == 0 && neighbour[1][1] == 1)
						nCount++;
					if (nCount != 1)
						bCondition4 = TRUE;
				}
				if (bCondition1 && bCondition2 && bCondition3 && bCondition4)
				{
					*lpDst = (unsigned char)255;
					bModified = TRUE;
				}
				else
				{
					*lpDst = (unsigned char)0;
				}
			}
		}
		// 复制腐蚀后的图像
		memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);


	}
	// 复制腐蚀后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// 返回
	return TRUE;
}


BOOL WINAPI backcolor1(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lSrcLineBytes) {
	unsigned char* lpSrc;//指向DIB源像素的指针
	FLOAT fTemp;//中间变量
	for (int i = 0; i < lHeight; i++) {
		for (int j = 0; j < lWidth; j++) {
			lpSrc = (unsigned char*)lpDIBBits + lSrcLineBytes * (lHeight - 1 - i) + j;
			fTemp = (float)*lpSrc;
			if (fTemp == 255)
				//直接赋值为255 
				*lpSrc = 255;
			else if (fTemp == 0)
				// 四舍五入
				*lpSrc = 0;
		}
	}
	return TRUE;
}

BOOL WINAPI backcolor2(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lSrcLineBytes) {
	unsigned char* lpSrc;//指向DIB源像素的指针
	FLOAT fTemp;//中间变量
	for (int i = 0; i < lHeight; i++) {
		for (int j = 0; j < lWidth; j++) {
			lpSrc = (unsigned char*)lpDIBBits + lSrcLineBytes * (lHeight - 1 - i) + j;
			fTemp = (float)*lpSrc;
			if (fTemp == 255)
				//直接赋值为255 
				*lpSrc = 0;
			else if (fTemp == 0)
				// 四舍五入
				*lpSrc = 255;
		}
	}
	return TRUE;
}

/**************************************************************************
* 函数名称;
*ThresholdTrans()*
参数:
* LPSTR IpDIBBits  -指向原DIB图像指针
* LONG 1Width      -原图像宽度（像素数)
 LONG lHeight      -原图像高度（像素数>
 BYTEbThre         –阙值
*
*返回值:*B0OL
-成功返回TRUE，否则返回FALSE。
*说明:
*该函数用来对图像进行阈值变换。对于灰度值小于阈值的像素直接设置*灰度值为0;灰度值大于阈值的像素真接设置为255。
***************************************************************************/
BOOL WINAPI ThresholdTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bThre) {
	//指向原图像的指针
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
			if ((*lpSrc) < bThre) {
				//直接赋值为0
				*lpSrc = 0;
			}
			else {
				// 直接赋值为255 
				*lpSrc = 255;
			}
		}
	}
	return true;


}


/***************************************************************************************************
*甬数名称:
*windowTrans ()*
参数:
*LPSTR 1pDIBBits–指向原DIB图像指针
*LONG lWjdth    –原图像宽度〔像素数)
*LoNG lHe ight  –原图像高度（像素数）
*BYTE bLow      –窗口下限
*BYTEblp        –窗口上限
*返回值:*B0OL   –成功返TRLE，否则返回FALSE。
*
*说明:
*该函数用来对图像进行窗I1变换。只有在窗口范围内的灰度保持不变，
*小于下限的像素直接设置灰度值为0;大于上限的像素直接设置灰度值为255。*
***************************************************************************************************/
BOOL WINAPI WindowTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE blow, BYTE bUp)
{
	//指向原图像的指针
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
			if ((*lpSrc) < blow) {
				//直接赋值为0
				*lpSrc = 0;
			}
			else if ((*lpSrc) > bUp) {
				// 直接赋值为255 
				*lpSrc = 255;
			}
		}
	}
	return true;

}


/**************************************************************
*函数名称:GrayStretch()*
参数;
LPSTR lpDIBBits--指向原DIB图像指针
*LONG lWidth--原图像宽度〈像素数)
*LONG lHeight--原图像高度〔像素数)
* BYTE bXl--灰度拉伸第一个点的X坐标
* BYTE bY1--灰度拉仲第一个点的Y坐标
BYTE bX  --灰度拉伸第二个点的x坐标
BYTE bY2 --灰度拉伸第二个点的Y坐标
*
返回值
	BOOL           成功返TRRE，否则返回FALSE.
*
说明:
*该函数用来对图像进行灰度拉伸
***********************************************************************/

BOOL WINAPI GrayStretch(LPSTR lpDlBBits, LONG lWidth, LONG lHeight, BYTE bX1, BYTE bY1, BYTE bX2, BYTE bY2) {
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
	for (i = 0; i <= bX1; i++)
	{ //判断bX1是否大于0（防止分母为0)
		if (bX1 > 0)
		{
			// 线性变换
			bMap[i] = (BYTE)bY1 * i / bX1;
		}
		else
		{ //直接赋值为0
			bMap[i] = 0;
		}

	}
	for (; i <= bX2; i++)
	{
		// 判断bX1是否等于bX2（防止分母为0)
		if (bX2 != bX1) {

			//线性变换
			bMap[i] = bY1 + (BYTE)((bY2 - bY1) * (i - bX1) / (bX2 - bX1));
		}
		else
			// 直接赋值为bY1
			bMap[i] = bY1;
	}
	for (; i < 256; i++) {
		// 判断bX2是否等于255（防止分母为0 ） 
		if (bX2 != 255)
			//线性变换
			bMap[i] = bY2 + (BYTE)((255 - bY2) * (i - bX2) / (255 - bX2));
		else
			//直接赋值为255
			bMap[i] = 255;


	}
	//每行
	for (i = 0; i < lHeight; i++) {
		//每列
		for (j = 0; j < lWidth; j++) {
			// 指向DIB第i行，第j个像素的指针
			lpSrc = (unsigned char*)lpDlBBits + lLineBytes * (lHeight - 1 - i) + j;
			// 计算新的灰度值
			*lpSrc = bMap[*lpSrc];
		}
	}
	// 返回
	return TRUE;

}


/*************************************************************************
 *
 * 函数名称：
 *   Templaterelief()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   int   iTempH		- 模板的高度
 *   int   iTempW		- 模板的宽度
 *   int   iTempMX		- 模板的中心元素X坐标 ( < iTempW - 1)
 *   int   iTempMY		- 模板的中心元素Y坐标 ( < iTempH - 1)
 *	 FLOAT * fpArray	- 指向模板数组的指针
 *	 FLOAT fCoef		- 模板系数
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用指定的模板（任意大小）来对图像进行操作，参数iTempH指定模板
 * 的高度，参数iTempW指定模板的宽度，参数iTempMX和iTempMY指定模板的中心
 * 元素坐标，参数fpArray指定模板元素，fCoef指定系数。
 *
 ************************************************************************/

BOOL WINAPI Templaterelief(LPSTR lpDIBBits, LONG lWidth, LONG lHeight,
	int iTempH, int iTempW,
	int iTempMX, int iTempMY,
	FLOAT* fpArray, FLOAT fCoef, int SThre)
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
	lLineBytes = (lWidth * 8 + 31) / 32 * 4;

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

			// 结果加上阈值
			fResult = fResult + SThre;

			// 判断是否超过255或0
			if (fResult > 255)
			{
				// 直接赋值为255
				*lpDst = 255;
			}
			else if (fResult < 0) {
				*lpDst = 0;
			}
			else {
				// 赋值
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

/*************************************************************************
 *
 * 函数名称：
 *   TranslationDIB()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   LONG  lXOffset     - X轴平移量（象素数）
 *   LONG  lYOffset     - Y轴平移量（象素数）
 *
 * 返回值:
 *   BOOL               - 平移成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来水平移动DIB图像。函数不会改变图像的大小，移出的部分图像
 * 将截去，空白部分用白色填充。
 *
 ************************************************************************/

BOOL WINAPI TranslationDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lXOffset, LONG lYOffset)
{
	// 平移后剩余图像在源图像中的位置（矩形区域）
	CRect	rectSrc;

	// 平移后剩余图像在新图像中的位置（矩形区域）
	CRect	rectDst;

	// 指向源图像的指针
	LPSTR	lpSrc;

	// 指向要复制区域的指针
	LPSTR	lpDst;

	// 指向复制图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	// 指明图像是否全部移去可视区间
	BOOL	bVisible;

	// 循环变量
	LONG	i;

	// 图像每行的字节数
	LONG lLineBytes;

	// 计算图像每行的字节数
	lLineBytes = (lWidth * 8 + 31) / 32 * 4;

	// 赋初值
	bVisible = TRUE;

	// 计算rectSrc和rectDst的X坐标
	if (lXOffset <= -lWidth)
	{
		// X轴方向全部移出可视区域
		bVisible = FALSE;
	}
	else if (lXOffset <= 0)
	{
		// 移动后，有图区域左上角X坐标为0
		rectDst.left = 0;

		// 移动后，有图区域右下角X坐标为lWidth - |lXOffset| = lWidth + lXOffset
		rectDst.right = lWidth + lXOffset;
	}
	else if (lXOffset < lWidth)
	{
		// 移动后，有图区域左上角X坐标为lXOffset
		rectDst.left = lXOffset;

		// 移动后，有图区域右下角X坐标为lWidth
		rectDst.right = lWidth;
	}
	else
	{
		// X轴方向全部移出可视区域
		bVisible = FALSE;
	}

	// 平移后剩余图像在源图像中的X坐标
	rectSrc.left = rectDst.left - lXOffset;
	rectSrc.right = rectDst.right - lXOffset;

	//  计算rectSrc和rectDst的Y坐标
	if (lYOffset <= -lHeight)
	{
		// Y轴方向全部移出可视区域
		bVisible = FALSE;
	}
	else if (lYOffset <= 0)
	{
		// 移动后，有图区域左上角Y坐标为0
		rectDst.top = 0;

		// 移动后，有图区域右下角Y坐标为lHeight - |lYOffset| = lHeight + lYOffset
		rectDst.bottom = lHeight + lYOffset;
	}
	else if (lYOffset < lHeight)
	{
		// 移动后，有图区域左上角Y坐标为lYOffset
		rectDst.top = lYOffset;

		// 移动后，有图区域右下角Y坐标为lHeight
		rectDst.bottom = lHeight;
	}
	else
	{
		// X轴方向全部移出可视区域
		bVisible = FALSE;
	}

	// 平移后剩余图像在源图像中的Y坐标
	rectSrc.top = rectDst.top - lYOffset;
	rectSrc.bottom = rectDst.bottom - lYOffset;

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lLineBytes * lHeight);
	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 初始化新分配的内存，设定初始值为255
	lpDst = (char*)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lLineBytes * lHeight);

	// 如果有部分图像可见
	if (bVisible)
	{

		// 平移图像
		for (i = 0; i < (rectSrc.bottom - rectSrc.top); i++)
		{
			// 要复制区域的起点，注意由于DIB图像内容是上下倒置的，第一行内容是保存在最后
			// 一行，因此复制区域的起点不是lpDIBBits + lLineBytes * (i + rectSrc.top) + 
			// rectSrc.left，而是 lpDIBBits + lLineBytes * (lHeight - i - rectSrc.top - 1) + 
			// rectSrc.left。

			lpSrc = (char*)lpDIBBits + lLineBytes * (lHeight - i - rectSrc.top - 1) + rectSrc.left;

			// 要目标区域的起点
			// 同样注意上下倒置的问题。
			lpDst = (char*)lpNewDIBBits + lLineBytes * (lHeight - i - rectDst.top - 1) +
				rectDst.left;

			// 拷贝每一行，宽度为rectSrc.right - rectSrc.left
			memcpy(lpDst, lpSrc, rectSrc.right - rectSrc.left);

		}
	}

	// 复制平移后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// 返回
	return TRUE;
}


/*************************************************************************
 *
 * 函数名称：
 *   RotateDIB()
 *
 * 参数:
 *   LPSTR lpDIB		- 指向源DIB的指针
 *   int iRotateAngle	- 旋转的角度（0-360度）
 *
 * 返回值:
 *   HGLOBAL            - 旋转成功返回新DIB句柄，否则返回NULL。
 *
 * 说明:
 *   该函数用来以图像中心为中心旋转DIB图像，返回新生成DIB的句柄。
 * 调用该函数会自动扩大图像以显示所有的象素。函数中采用最邻近插
 * 值算法进行插值。
 *
 ************************************************************************/

HGLOBAL WINAPI RotateDIB(CMFCApplication1Doc* pDoc, LPSTR lpDIB, int iRotateAngle)
{

	// 源图像的宽度和高度
	LONG	lWidth;
	LONG	lHeight;

	// 旋转后图像的宽度和高度
	LONG	lNewWidth;
	LONG	lNewHeight;

	// 图像每行的字节数
	LONG	lLineBytes;

	// 旋转后图像的宽度（lNewWidth'，必须是4的倍数）
	LONG	lNewLineBytes;

	// 指向源图像的指针
	LPSTR	lpDIBBits;

	// 指向源象素的指针
	LPSTR	lpSrc;

	//保存新的DIB句柄
	HDIB hDIB;
	
	// 指向旋转图像对应象素的指针
	LPSTR	lpDst;

	// 指向旋转图像的指针
	LPSTR	lpNewDIB;
	LPSTR	lpNewDIBBits;

	// 指向BITMAPINFO结构的指针（Win3.0）
	LPBITMAPINFOHEADER lpbmi;

	// 指向BITMAPCOREINFO结构的指针
	LPBITMAPCOREHEADER lpbmc;

	// 循环变量（象素在新DIB中的坐标）
	LONG	i;
	LONG	j;

	// 象素在源DIB中的坐标
	LONG	i0;
	LONG	j0;

	// 旋转角度（弧度）
	float	fRotateAngle;

	// 旋转角度的正弦和余弦
	float	fSina, fCosa;

	// 源图四个角的坐标（以图像中心为坐标系原点）
	float	fSrcX1, fSrcY1, fSrcX2, fSrcY2, fSrcX3, fSrcY3, fSrcX4, fSrcY4;

	// 旋转后四个角的坐标（以图像中心为坐标系原点）
	float	fDstX1, fDstY1, fDstX2, fDstY2, fDstX3, fDstY3, fDstX4, fDstY4;

	// 两个中间常量
	float	f1, f2;
	// 找到DIB图像象素起始位置
	lpDIBBits =  pDoc->m_dib.GetBits(lpDIB);
	lWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	lHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	int lpSrcBitCount = pDoc->m_dib.GetBitCount(lpDIB);                    //获取图像位深
	lLineBytes = pDoc->m_dib.GetReqByteWidth(lWidth * lpSrcBitCount);		// 计算图象每行的字节数	


	// 将旋转角度从度转换到弧度
	fRotateAngle = (float)RADIAN(iRotateAngle);

	// 计算旋转角度的正弦
	fSina = (float)sin((double)fRotateAngle);

	// 计算旋转角度的余弦
	fCosa = (float)cos((double)fRotateAngle);

	// 计算原图的四个角的坐标（以图像中心为坐标系原点）
	fSrcX1 = (float)(-(lWidth - 1) / 2);
	fSrcY1 = (float)((lHeight - 1) / 2);
	fSrcX2 = (float)((lWidth - 1) / 2);
	fSrcY2 = (float)((lHeight - 1) / 2);
	fSrcX3 = (float)(-(lWidth - 1) / 2);
	fSrcY3 = (float)(-(lHeight - 1) / 2);
	fSrcX4 = (float)((lWidth - 1) / 2);
	fSrcY4 = (float)(-(lHeight - 1) / 2);

	// 计算新图四个角的坐标（以图像中心为坐标系原点）
	fDstX1 = fCosa * fSrcX1 + fSina * fSrcY1;
	fDstY1 = -fSina * fSrcX1 + fCosa * fSrcY1;
	fDstX2 = fCosa * fSrcX2 + fSina * fSrcY2;
	fDstY2 = -fSina * fSrcX2 + fCosa * fSrcY2;
	fDstX3 = fCosa * fSrcX3 + fSina * fSrcY3;
	fDstY3 = -fSina * fSrcX3 + fCosa * fSrcY3;
	fDstX4 = fCosa * fSrcX4 + fSina * fSrcY4;
	fDstY4 = -fSina * fSrcX4 + fCosa * fSrcY4;

	// 计算旋转后的图像实际宽度
	lNewWidth = (LONG)(max(fabs(fDstX4 - fDstX1), fabs(fDstX3 - fDstX2)) + 0.5);

	// 计算新图像每行的字节数
	lNewLineBytes = (lNewWidth * 8+31)*32/4;

	// 计算旋转后的图像高度
	lNewHeight = (LONG)(max(fabs(fDstY4 - fDstY1), fabs(fDstY3 - fDstY2)) + 0.5);

	// 两个常数，这样不用以后每次都计算了
	f1 = (float)(-0.5 * (lNewWidth - 1) * fCosa - 0.5 * (lNewHeight - 1) * fSina
		+ 0.5 * (lWidth - 1));
	f2 = (float)(0.5 * (lNewWidth - 1) * fSina - 0.5 * (lNewHeight - 1) * fCosa
		+ 0.5 * (lHeight - 1));

	// 分配内存，以保存新DIB
	hDIB = (HDIB) ::GlobalAlloc(GHND, lNewLineBytes * lNewHeight + *(LPDWORD)lpDIB + pDoc->m_dib.GetPalSize(lpDIB));

	// 判断是否内存分配失败
	if (hDIB == NULL)
	{
		// 分配内存失败
		return NULL;
	}

	// 锁定内存
	lpNewDIB = (char*)::GlobalLock((HGLOBAL)hDIB);

	// 复制DIB信息头和调色板
	memcpy(lpNewDIB, lpDIB, *(LPDWORD)lpDIB + pDoc->m_dib.GetPalSize(lpDIB));

	// 找到新DIB象素起始位置
	lpNewDIBBits = lpNewDIB + *(LPDWORD)lpNewDIB + pDoc->m_dib.GetPalSize(lpDIB);

	// 获取指针
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;


		// 对于Windows 3.0 DIB
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	

	// 针对图像每行进行操作
	for (i = 0; i < lNewHeight; i++)
	{
		// 针对图像每列进行操作
		for (j = 0; j < lNewWidth; j++)
		{
			// 指向新DIB第i行，第j个象素的指针
			// 注意此处宽度和高度是新DIB的宽度和高度
			lpDst = (char*)lpNewDIBBits + lNewLineBytes * (lNewHeight - 1 - i) + j;

			// 计算该象素在源DIB中的坐标
			i0 = (LONG)(-((float)j) * fSina + ((float)i) * fCosa + f2 + 0.5);
			j0 = (LONG)(((float)j) * fCosa + ((float)i) * fSina + f1 + 0.5);

			// 判断是否在源图范围内
			if ((j0 >= 0) && (j0 < lWidth) && (i0 >= 0) && (i0 < lHeight))
			{
				// 指向源DIB第i0行，第j0个象素的指针
				lpSrc = (char*)lpDIBBits + lLineBytes * (lHeight - 1 - i0) + j0;

				// 复制象素
				*lpDst = *lpSrc;
			}
			else
			{
				// 对于源图中没有的象素，直接赋值为255
				*((unsigned char*)lpDst) = 255;
			}

		}

	}
	
	// 返回
	return hDIB;
}




/*************************************************************************
 *
 * 函数名称：
 *   TransposeDIB()
 *
 * 参数:
 *   LPSTR lpDIB		- 指向源DIB的指针
 *
 * 返回值:
 *   BOOL               - 转置成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来转置DIB图像，即图像x、y坐标互换。函数将不会改变图像的大小，
 * 但是图像的高宽将互换。
 *
 ************************************************************************/

BOOL WINAPI TransposeDIB(LPSTR lpDIB,LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{

	
	// 指向源象素的指针
	LPSTR	lpSrc;
	
	// 指向转置图像对应象素的指针
	LPSTR	lpDst;

	// 指向转置图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;
	
	// 指向BITMAPINFO结构的指针（Win3.0）
	LPBITMAPINFOHEADER lpbmi;
	
	// 指向BITMAPCOREINFO结构的指针
	LPBITMAPCOREHEADER lpbmc;

	// 循环变量
	LONG	i;
	LONG	j;
	
	// 图像每行的字节数
	LONG lLineBytes;
	
	// 新图像每行的字节数
	LONG lNewLineBytes;

	// 获取指针
	lpbmi = (LPBITMAPINFOHEADER)lpDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpDIB;

	
	// 计算图像每行的字节数
	lLineBytes = (lWidth * 8+31)/32*4;
	
	// 计算新图像每行的字节数
	lNewLineBytes = (lHeight * 8 + 31) / 32 * 4;
	
	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lNewLineBytes);

	// 判断是否内存分配失败
	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}
	
	// 锁定内存
	lpNewDIBBits = (char * )LocalLock(hNewDIBBits);
	
	// 针对图像每行进行操作
	for(i = 0; i < lHeight; i++)
	{
		// 针对每行图像每列进行操作
		for(j = 0; j < lWidth; j++)
		{
			
			// 指向源DIB第i行，第j个象素的指针
			lpSrc = (char *)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// 指向转置DIB第j行，第i个象素的指针
			// 注意此处lWidth和lHeight是源DIB的宽度和高度，应该互换
			lpDst = (char *)lpNewDIBBits + lNewLineBytes * (lWidth - 1 - j) + i;
			
			// 复制象素
			*lpDst = *lpSrc;
			
		}
		
	}
	
	// 复制转置后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lNewLineBytes);
	
	// 互换DIB中图像的高宽

		// 对于Windows 3.0 DIB
		lpbmi->biWidth = lHeight;
		
		lpbmi->biHeight = lWidth;
	
	
	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
	return TRUE;
}





/*************************************************************************
 *
 * 函数名称：
 *   MirrorDIB()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   BOOL  bDirection   - 镜像的方向，TRUE表示水平镜像，FALSE表示垂直镜像
 *
 * 返回值:
 *   BOOL               - 镜像成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来镜像DIB图像。可以指定镜像的方式是水平还是垂直。
 *
 ************************************************************************/

BOOL WINAPI MirrorDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BOOL bDirection)
{

	// 指向源图像的指针
	LPSTR	lpSrc;

	// 指向要复制区域的指针
	LPSTR	lpDst;

	// 指向复制图像的指针
	LPSTR	lpBits;
	HLOCAL	hBits;

	// 循环变量
	LONG	i;
	LONG	j;

	// 图像每行的字节数
	LONG lLineBytes;

	// 计算图像每行的字节数
	lLineBytes = (lWidth * 8 + 31) / 32 * 4;

	// 暂时分配内存，以保存一行图像
	hBits = LocalAlloc(LHND, lLineBytes);
	if (hBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpBits = (char*)LocalLock(hBits);

	// 判断镜像方式
	if (bDirection)
	{
		// 水平镜像

		// 针对图像每行进行操作
		for (i = 0; i < lHeight; i++)
		{
			// 针对每行图像左半部分进行操作
			for (j = 0; j < lWidth / 2; j++)
			{

				// 指向倒数第i行，第j个象素的指针
				lpSrc = (char*)lpDIBBits + lLineBytes * i + j;

				// 指向倒数第i行，倒数第j个象素的指针
				lpDst = (char*)lpDIBBits + lLineBytes * (i + 1) - j;

				// 备份一个象素
				*lpBits = *lpDst;

				// 将倒数第i行，第j个象素复制到倒数第i行，倒数第j个象素
				*lpDst = *lpSrc;

				// 将倒数第i行，倒数第j个象素复制到倒数第i行，第j个象素
				*lpSrc = *lpBits;
			}

		}
	}
	else
	{
		// 垂直镜像

		// 针对上半图像进行操作
		for (i = 0; i < lHeight / 2; i++)
		{

			// 指向倒数第i行象素起点的指针
			lpSrc = (char*)lpDIBBits + lLineBytes * i;

			// 指向第i行象素起点的指针
			lpDst = (char*)lpDIBBits + lLineBytes * (lHeight - i - 1);

			// 备份一行，宽度为lWidth
			memcpy(lpBits, lpDst, lLineBytes);

			// 将倒数第i行象素复制到第i行
			memcpy(lpDst, lpSrc, lLineBytes);

			// 将第i行象素复制到倒数第i行
			memcpy(lpSrc, lpBits, lLineBytes);

		}
	}

	// 释放内存
	LocalUnlock(hBits);
	LocalFree(hBits);

	// 返回
	return TRUE;
}

//4连通计数
/*************************************************************************
*
* 函数名称：
*   dealer()
*
* 参数:
*   LPSTR lpDIBBits    - 指向源DIB图像指针
*   LONG  lWidth       - 源图像宽度（象素数）
*   LONG  lHeight      - 源图像高度（象素数）
*
* 返回值:
*   int               - 米粒
*
* 说明:
*   该函数用来计算图中物体个数。
*
************************************************************************/

int  dealer_four(LPSTR image, int width, int height, int Bg)
{
	int** flag_max;
	flag_max = new int* [height];
	for (int i = 0; i < height; i++) {
		flag_max[i] = new int[width];
	}                                         //动态分配二维数组
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			flag_max[i][j] = 0;
		}
	}


	int count_flag = 0;
	queue<point> buffer;
	int count = 1;    //区域标记
	int color;
	unsigned char* ptemp = (unsigned char*)image;

	/*point temp1;
	temp1.i=180;
	temp1.j=180;
	buffer.push(temp1);*/

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((*(ptemp + i * width + j) == Bg) && (flag_max[i][j] == 0))
			{
				point temp;
				temp.i = i;
				temp.j = j;
				buffer.push(temp);
				while (buffer.size() > 0)
				{
					count_flag = 1;//表明进入循环
					temp = buffer.front();
					buffer.pop();
					if (temp.i >= 0 && temp.i <= height && temp.j >= 0 && temp.j <= width && *(ptemp + temp.i * width + temp.j) == Bg && flag_max[temp.i][temp.j] == 0)
					{
						//标记
						flag_max[temp.i][temp.j] = count;
						if (temp.i - 1 >= 0 && temp.i - 1 < height && temp.j >= 0 && temp.j < width && *(ptemp + (temp.i - 1) * width + temp.j) == Bg && flag_max[temp.i - 1][temp.j] == 0) {
							point linyu;
							linyu.i = temp.i - 1;
							linyu.j = temp.j;
							buffer.push(linyu);
						}
						if (temp.i >= 0 && temp.i < height && temp.j - 1 >= 0 && temp.j - 1 < width && *(ptemp + temp.i * width + temp.j - 1) == Bg && flag_max[temp.i][temp.j - 1] == 0) {
							point linyu;
							linyu.i = temp.i;
							linyu.j = temp.j - 1;
							buffer.push(linyu);
						}
						if (temp.i >= 0 && temp.i < height && temp.j + 1 >= 0 && temp.j + 1 < width && *(ptemp + temp.i * width + temp.j + 1) == Bg && flag_max[temp.i][temp.j + 1] == 0) {
							point linyu;
							linyu.i = temp.i;
							linyu.j = temp.j + 1;
							buffer.push(linyu);
						}
						if (temp.i + 1 >= 0 && temp.i + 1 < height && temp.j >= 0 && temp.j < width && *(ptemp + (temp.i + 1) * width + temp.j) == Bg && flag_max[temp.i + 1][temp.j] == 0) {
							point linyu;
							linyu.i = temp.i + 1;
							linyu.j = temp.j;
							buffer.push(linyu);
						}
					}
				}//while
			}//if

			 //j++;
			if (count_flag == 1)
			{
				count++;
				count_flag = 0;
			}
		}
	}
	return count - 1;
}

//8连通计数
/*************************************************************************
*
* 函数名称：
*   dealer()
*
* 参数:
*   LPSTR lpDIBBits    - 指向源DIB图像指针
*   LONG  lWidth       - 源图像宽度（象素数）
*   LONG  lHeight      - 源图像高度（象素数）
*
* 返回值:
*   int               - 米粒
*
* 说明:
*   该函数用来计算图中物体个数。
*
************************************************************************/

int  dealer_eight(LPSTR image, int width, int height, int Bg)
{
	int** flag_max;
	flag_max = new int* [height];
	for (int i = 0; i < height; i++) {
		flag_max[i] = new int[width];
	}                                         //动态分配二维数组
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			flag_max[i][j] = 0;
		}
	}


	int count_flag = 0;
	queue<point> buffer;
	int count = 1;    //区域标记
	int color;
	unsigned char* ptemp = (unsigned char*)image;

	/*point temp1;
	temp1.i=180;
	temp1.j=180;
	buffer.push(temp1);*/

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((*(ptemp + i * width + j) == Bg) && (flag_max[i][j] == 0))
			{
				point temp;
				temp.i = i;
				temp.j = j;
				buffer.push(temp);
				while (buffer.size() > 0)
				{
					count_flag = 1;//表明进入循环
					temp = buffer.front();
					buffer.pop();
					if (temp.i >= 0 && temp.i <= height && temp.j >= 0 && temp.j <= width && *(ptemp + temp.i * width + temp.j) == Bg && flag_max[temp.i][temp.j] == 0)
					{
						//标记
						flag_max[temp.i][temp.j] = count;
						if (temp.i - 1 >= 0 && temp.i - 1 < height && temp.j - 1 >= 0 && temp.j - 1 < width && *(ptemp + (temp.i - 1) * width + temp.j - 1) == Bg && flag_max[temp.i - 1][temp.j - 1] == 0) {
							point linyu;
							linyu.i = temp.i - 1;
							linyu.j = temp.j - 1;
							buffer.push(linyu);
						}
						if (temp.i - 1 >= 0 && temp.i - 1 < height && temp.j >= 0 && temp.j < width && *(ptemp + (temp.i - 1) * width + temp.j) == Bg && flag_max[temp.i - 1][temp.j] == 0) {
							point linyu;
							linyu.i = temp.i - 1;
							linyu.j = temp.j;
							buffer.push(linyu);
						}
						if (temp.i - 1 >= 0 && temp.i - 1 < height && temp.j + 1 >= 0 && temp.j + 1 < width && *(ptemp + (temp.i - 1) * width + temp.j + 1) == Bg && flag_max[temp.i - 1][temp.j + 1] == 0) {
							point linyu;
							linyu.i = temp.i - 1;
							linyu.j = temp.j + 1;
							buffer.push(linyu);
						}
						if (temp.i >= 0 && temp.i < height && temp.j - 1 >= 0 && temp.j - 1 < width && *(ptemp + temp.i * width + temp.j - 1) == Bg && flag_max[temp.i][temp.j - 1] == 0) {
							point linyu;
							linyu.i = temp.i;
							linyu.j = temp.j - 1;
							buffer.push(linyu);
						}
						if (temp.i >= 0 && temp.i < height && temp.j + 1 >= 0 && temp.j + 1 < width && *(ptemp + temp.i * width + temp.j + 1) == Bg && flag_max[temp.i][temp.j + 1] == 0) {
							point linyu;
							linyu.i = temp.i;
							linyu.j = temp.j + 1;
							buffer.push(linyu);
						}
						if (temp.i + 1 >= 0 && temp.i + 1 < height && temp.j - 1 >= 0 && temp.j - 1 < width && *(ptemp + (temp.i + 1) * width + temp.j - 1) == Bg && flag_max[temp.i + 1][temp.j - 1] == 0) {
							point linyu;
							linyu.i = temp.i + 1;
							linyu.j = temp.j - 1;
							buffer.push(linyu);
						}
						if (temp.i + 1 >= 0 && temp.i + 1 < height && temp.j >= 0 && temp.j < width && *(ptemp + (temp.i + 1) * width + temp.j) == Bg && flag_max[temp.i + 1][temp.j] == 0) {
							point linyu;
							linyu.i = temp.i + 1;
							linyu.j = temp.j;
							buffer.push(linyu);
						}
						if (temp.i + 1 >= 0 && temp.i + 1 < height && temp.j + 1 >= 0 && temp.j + 1 < width && *(ptemp + (temp.i + 1) * width + temp.j + 1) == Bg && flag_max[temp.i + 1][temp.j + 1] == 0) {
							point linyu;
							linyu.i = temp.i + 1;
							linyu.j = temp.j + 1;
							buffer.push(linyu);
						}
					}
				}//while
			}//if

			 //j++;
			if (count_flag == 1)
			{
				count++;
				count_flag = 0;
			}
		}
	}
	return count - 1;
}

#define MAX 10000
typedef struct Xiangsu
{
	int xiangsu;
	int value;
}Xiangsu;

LONG WINAPI getArea_four(LPSTR start, LONG lWidth, LONG lHeight, int Bg)
{
	LONG max_area = 0;
	LONG temp = 0;
	int a = 0;
	Xiangsu(*x)[MAX] = new Xiangsu[lHeight][MAX];
	//初始化
	for (long i = 0; i < lHeight; i++)
		for (long j = 0; j < lWidth; j++)
		{
			x[i][j].value = 0;
			x[i][j].xiangsu = 0;
		}
	//赋值
	for (long i = 0; i < lHeight; i++)
		for (long j = 0; j < lWidth; j++)
			x[i][j].xiangsu = unsigned char(start[i * lWidth + j]);
	int i, j;

	for (i = 1; i < lHeight - 1;) {
		int temp_x = i;
		for (j = 1; j < lWidth - 1;)
		{
			int temp_y = j;
			if (x[i][j].xiangsu == Bg && x[i][j].value == 0)
			{
				a = 0;
				int x1, x2, x3;
				int y1, y2, y3;
				x1 = i - 1; x2 = i; x3 = i + 1; y1 = j - 1; y2 = j; y3 = j + 1;
				x[i][j].value = 1; temp++;
				//判断四邻域

				if (x2 >= 1 && y1 >= 1 && x[x2][y1].xiangsu == Bg && x[x2][y1].value == 0)
				{
					i = x2; j = y1; a = 1; continue;
				}

				else if (x1 >= 1 && x[x1][y2].xiangsu == Bg && x[x1][y2].value == 0)
				{
					i = x1; j = y2; a = 1; continue;
				}

				else if (x3 <= lHeight - 1 && x[x3][y2].xiangsu == Bg && x[x3][y2].value == 0)
				{
					i = x3; j = y2; a = 1; continue;
				}


				else if (y3 <= lWidth - 1 && x[x2][y3].xiangsu == Bg && x[x2][y3].value == 0)
				{
					i = x2; j = y3; a = 1; continue;
				}

				j = temp_y++;
				if (temp > max_area)
					max_area = temp;
				temp = 0;
			}
			else
				j++;
		}
		i = temp_x + 1;
	}
	delete[]x;
	return max_area;
}


LONG WINAPI getArea_eight(LPSTR start, LONG lWidth, LONG lHeight, int Bg)
{
	LONG max_area = 0;
	LONG temp = 0;
	int a = 0;
	Xiangsu(*x)[MAX] = new Xiangsu[lHeight][MAX];
	//初始化
	for (long i = 0; i < lHeight; i++)
		for (long j = 0; j < lWidth; j++)
		{
			x[i][j].value = 0;
			x[i][j].xiangsu = 0;
		}
	//赋值
	for (long i = 0; i < lHeight; i++)
		for (long j = 0; j < lWidth; j++)
			x[i][j].xiangsu = unsigned char(start[i * lWidth + j]);
	int i, j;

	for (i = 1; i < lHeight - 1;) {
		int temp_x = i;
		for (j = 1; j < lWidth - 1;)
		{
			int temp_y = j;
			if (x[i][j].xiangsu == Bg && x[i][j].value == 0)
			{
				a = 0;
				int x1, x2, x3;
				int y1, y2, y3;
				x1 = i - 1; x2 = i; x3 = i + 1; y1 = j - 1; y2 = j; y3 = j + 1;
				x[i][j].value = 1; temp++;
				//判断八邻域
				if (x1 >= 1 && y1 >= 1 && x[x1][y1].xiangsu == Bg && x[x1][y1].value == 0)
				{
					i = x1; j = y1; a = 1; continue;
				}

				else if (y1 >= 1 && y1 >= 1 && x[x2][y1].xiangsu == Bg && x[x2][y1].value == 0)
				{
					i = x2; j = y1; a = 1; continue;
				}

				else if (x3 <= lHeight - 1 && y1 >= 1 && x[x3][y1].xiangsu == Bg && x[x3][y1].value == 0)
				{
					i = x3; j = y1; a = 1; continue;
				}

				else if (x1 >= 1 && x[x1][y2].xiangsu == Bg && x[x1][y2].value == 0)
				{
					i = x1; j = y2; a = 1; continue;
				}

				else if (x3 <= lHeight - 1 && x[x3][y2].xiangsu == Bg && x[x3][y2].value == 0)
				{
					i = x3; j = y2; a = 1; continue;
				}

				else if (x1 >= 1 && y3 <= lWidth - 1 && x[x1][y3].xiangsu == Bg && x[x1][y3].value == 0)
				{
					i = x1; j = y3; a = 1; continue;
				}

				else if (y3 <= lWidth - 1 && x[x2][y3].xiangsu == Bg && x[x2][y3].value == 0)
				{
					i = x2; j = y3; a = 1; continue;
				}

				else if (y3 <= lWidth - 1 && x3 <= lHeight - 1 && x[x3][y3].xiangsu == Bg && x[x3][y3].value == 0)
				{
					i = x3; j = y3; a = 1; continue;
				}

				j = temp_y++;
				if (temp > max_area)
					max_area = temp;
				temp = 0;
			}
			else
				j++;
		}
		i = temp_x + 1;
	}
	delete[]x;
	return max_area;
}


int  I[500][500];

int ab = 0;
int WINAPI heartx(LONG lWidth, LONG lHeight, LONG mianji)
{
	int x;
	x = 0;
	for (int i = 0; i < lWidth; i++)
	{
		for (int j = 0; j < lHeight; j++)
		{
			if (I[i][j] == ab)
			{
				x = x + i;
				//y=y+j;
			}
		}
	}
	double ans = x / mianji;
	return ans;

}

int WINAPI gethearty(LONG lWidth, LONG lHeight, LONG mianji)
{
	int y;
	y = 0;
	for (int i = 0; i < lWidth; i++)
	{
		for (int j = 0; j < lHeight; j++)
		{
			if (I[i][j] == ab)
			{

				y = y + j;
			}
		}
	}
	double ans = y / mianji;
	return ans;
}

