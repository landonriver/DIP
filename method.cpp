#include "pch.h"
#include "method.h"
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif
// ������
#define PI 3.1415926535

//�Ƕȵ�����ת���ĺ�
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
//ֱ������
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

// ð������ 
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

//����
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

//����ƽ����ĺ���  
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
 * �������ƣ�
 *   GetMedianNum()
 *
 * ����:
 *   unsigned char * bpArray	- ָ��Ҫ��ȡ��ֵ������ָ��
 *   int   iFilterLen			- ���鳤��
 *
 * ����ֵ:
 *   unsigned char      - ����ָ���������ֵ��
 *
 * ˵��:
 *   �ú�����ð�ݷ���һά����������򣬲���������Ԫ�ص���ֵ��
 *
 ************************************************************************/

unsigned char WINAPI GetMedianNum(unsigned char* bArray, int iFilterLen)
{
	// ѭ������
	int		i;
	int		j;

	// �м����
	unsigned char bTemp;

	// ��ð�ݷ��������������
	for (j = 0; j < iFilterLen - 1; j++)
	{
		for (i = 0; i < iFilterLen - j - 1; i++)
		{
			if (bArray[i] > bArray[i + 1])
			{
				// ����
				bTemp = bArray[i];
				bArray[i] = bArray[i + 1];
				bArray[i + 1] = bTemp;
			}
		}
	}

	// ������ֵ
	if ((iFilterLen & 1) > 0)
	{
		// ������������Ԫ�أ������м�һ��Ԫ��
		bTemp = bArray[(iFilterLen + 1) / 2];
	}
	else
	{
		// ������ż����Ԫ�أ������м�����Ԫ��ƽ��ֵ
		bTemp = (bArray[iFilterLen / 2] + bArray[iFilterLen / 2 + 1]) / 2;
	}

	// ������ֵ
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
		assert(color24bit[i] < 4096);  //ͼ����п�ҪΪ4�ı���������
		usedTimes[color24bit[i]]++;
	}
	LONG numberOfColors = 0;
	for (i = 0; i < 4096; i++)
	{
		if (usedTimes[i] > 0)
			numberOfColors++;
	}
	//��usedTimes�����������������minColor����(��������ɫֵ)Ҳ����useTimes  
	//�������ƵĽ���  
	KsSort(usedTimes, miniColor, 4096);    //ok
	//usedTimes�������Ǹ���ɫʹ��Ƶ�ʣ��Ӹߵ������У���Ȼ��numberOfColor��֮��Ķ�Ϊ0  
	//miniColor����������Ӧ����ɫ����  
	//��ǰ256����ɫ���ݱ��浽256ɫλͼ�ĵ�ɫ����  
	for (i = 0; i < 256; i++)
	{
		mainColor[i].rgbBlue = (BYTE)((miniColor[i] >> 8) << 4);
		mainColor[i].rgbGreen = (BYTE)(((miniColor[i] >> 4) & 0xf) << 4);
		mainColor[i].rgbRed = (BYTE)((miniColor[i] & 0xf) << 4);
		mainColor[i].rgbReserved = 0;
	}

	int* colorIndex = usedTimes;//��ԭ����useTimes��������������ֵ  
	memset(colorIndex, 0, sizeof(int) * 4096);

	if (numberOfColors <= 256)
	{
		for (i = 0; i < numberOfColors; i++)
			colorIndex[miniColor[i]] = i;
	}
	else//Ϊ��256֮�����ɫ��ǰ256����ɫ����һ����ӽ���  
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
	//��¼������ɫ���ݵ�����ֵ����256ɫλͼ����ɫ����  
	for (i = 0; i < len; i++)
	{
		assert(colorIndex[color24bit[i]] < 256);
		Index[i] = colorIndex[color24bit[i]];
	}

	return 1;
}

//�ڴ���亯��
int BuildNewSize(unsigned char* tem, LPSTR lpSrc, int num)
{
	tem = new BYTE[num];
	memcpy(tem, lpSrc, num);
	return 1;
}

//8λ��ɫ����
BOOL WINAPI LinerTrans(LPSTR lpSrcStartBits, LONG lSrcWidth,LONG lSrcHeight,FLOAT Fa, FLOAT Fb) {
	unsigned char* lpSrc;
	LONG i, j;
	LONG lineBytes = (((lSrcWidth * 8) + 31) / 32 * 4);
	FLOAT ftemp;
	for (i = 0; i < lSrcHeight; i++)
	{
		// ÿ��
		for (j = 0; j < lSrcWidth; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpSrcStartBits + lineBytes * (lSrcHeight - 1 - i) + j;

			// ���Ա任
			ftemp = Fa * (*lpSrc) + Fb;

			// �ж��Ƿ񳬳���Χ
			if (ftemp > 255)
			{
				// ֱ�Ӹ�ֵΪ255
				*lpSrc = 255;
			}
			else if (ftemp < 0)
			{
				// ֱ�Ӹ�ֵΪ0
				*lpSrc = 0;
			}
			else
			{
				// ��������
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
	// ָ��Դͼ���ָ��
	unsigned char* lpSrc;

	// ѭ������
	LONG	i;
	LONG	j;

	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;

	// �м����
	FLOAT	fTemp=0, fA1 = 1, fB1 = 0, fA2 = 1, fB2 = 0;
	//�м�Ҷ�
	int seg_gray = 127;

	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = (((lWidth * 8) + 31) / 32 * 4);
	//�������Ա任�Ĳ���
	if (type == 1)//��V����
	{
		fA1 = (float)(255 / threshold);//2.0 if threshold==128;
		fB1 = 0;  //(2f)
		fA2 = -(float)(255 / threshold);//-2.0 if threshold==128;
		fB1 = (float)(255 + (255 * threshold) / (255 - threshold));//(-2f+2*255)  if threshold==128;
	}
	if (type == 2)//V����
	{
		fA1 = -2.0;
		fB1 = 255;  //(-2f+255)
		fA2 = 2.0;
		fB1 = -255;//(2f-255)
	}
	if (type == 3)//��L����
	{
		fA1 = 2.0;
		fB1 = 0;  //(2f)
		fA2 = 0;
		fB1 = 255;//(255)
	}
	if (type == 4)//L����
	{
		fA1 = -2.0;
		fB1 = 255;  //(-2f+255)
		fA2 = 0.0;
		fB1 = 0;//(0)
	}
	// ÿ��
	for (i = 0; i < lHeight; i++)
	{
		// ÿ��
		for (j = 0; j < lWidth; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// ���Ա任,�ֶ�
			if (*lpSrc >= 0 && *lpSrc <= seg_gray)
				fTemp = fA1 * (*lpSrc) + fB1;
			if (*lpSrc >= seg_gray + 1 && *lpSrc <= 255)
				fTemp = fA2 * (*lpSrc) + fB2;
			// �ж��Ƿ񳬳���Χ
			if (fTemp > 255)
			{
				// ֱ�Ӹ�ֵΪ255
				*lpSrc = 255;
			}
			else if (fTemp < 0)
			{
				// ֱ�Ӹ�ֵΪ0
				*lpSrc = 0;
			}
			else
			{
				// ��������
				*lpSrc = (unsigned char)(fTemp + 0.5);
			}
		}
	}

	// ����
	return TRUE;

}

BOOL WINAPI LinerTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lSrcLineBytes, FLOAT fA, FLOAT fB)
{
	unsigned char* lpSrc;//ָ��DIBԴ���ص�ָ��
	FLOAT fTemp;//�м����
	for (int i = 0; i < lHeight; i++) {
		for (int j = 0; j < lWidth; j++) {
			lpSrc = (unsigned char*)lpDIBBits + lSrcLineBytes * (lHeight - 1 - i) + j;
			fTemp = (float)*lpSrc;
			fTemp = fA * fTemp + fB;
			//���Ա任

			//�ж��Ƿ񳬳���Χ
			if (fTemp > 255)
				//ֱ�Ӹ�ֵΪ255 
				*lpSrc = 255;
			else if (fTemp < 0)
				// ��������
				*lpSrc = 0;
			else {
				*lpSrc = (unsigned char)(fTemp + 0.5);
			}
		}
	}
	return TRUE;
}

/////////////////////////////////////////
//------------------λƽ���зֺ���
/*************************************************************************
* �������ƣ�
*   BitPlaneSlicing()
* ����:
*   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
*   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
*   LONG  lHeight      - Դͼ��߶ȣ���������
*   LONG  lLineBytes   -ÿ���ֽ���
*   int   Bit    		- �ָ� λ ��0---7��
* ����ֵ:
*   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
* ˵��:
* �ú������ڶ�ͼ�����λƽ��ָ8λ
************************************************************************/
BOOL BitPlaneSlicing(LPSTR lpDIBBits, LONG lmageWidth, LONG  lLineBytes, LONG lmageHeight, int Bit)
{
	int i;  //ѭ������
	int j;	//ѭ������
	// ָ��Դͼ���ָ��
	unsigned char* lpSrc;
	//����ֵ
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

			// ָ��Դͼ������j�У���i�����ص�ָ��			
			//lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * j + i;
			//ȡ�õ�ǰָ�봦������ֵ
			pixeltemp = (unsigned char)*lpSrc;
			//Ŀ��ͼ���лҶ�ֵС������������Ϊ�ڵ�
			if (pixeltemp >= threshold1 && pixeltemp < threshold2)
			{
				//*lpSrc = (unsigned char)255;
			}
			else	//��������Ϊ�׵�
			{
				*lpSrc = (unsigned char)0;
			}
		}
	}
	return true;
}

/*************************************************************************
 * �������ƣ�LogTranslation(LPSTR lpSrcStartBits, long lWidth, long lHeight, long lLineBytes)
 * ��������:
	 LPSTR	lpSrcStartBits,ָ��DIB��ʼ���ص�ָ��
	 long	lWidth��DIBͼ��Ŀ��
	 long	lHeight��DIBͼ��ĸ߶�
	 long	lLineBytes��DIBͼ������ֽ�����Ϊ4�ı���
 * ��������:BOOL
 * ��������:�ú���������ͼ����ж����任
 ************************************************************************/

BOOL  LogTranslation(LPSTR lpSrcStartBits, long lWidth, long lHeight, long lLineBytes)
{
	long i;                 //��ѭ������
	long j;                 //��ѭ������
	unsigned char* lpSrcUnChr;	//ָ�����ص�ָ��
	for (i = 0; i < lHeight; i++)// ��
	{
		for (j = 0; j < lWidth; j++)// ��
		{
			lpSrcUnChr = (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight - 1 - i) + j;// ָ��DIB��i�У���j�����ص�ָ��
			//*lpSrcUnChr=50*(unsigned char)log((*lpSrcUnChr+1));
			*lpSrcUnChr = 255 * (unsigned char)log((*lpSrcUnChr + 1)) / log(255);
		}
	}
	return TRUE;
}




/*************************************************************************
 *
 * �������ƣ�
 *   Template()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   int   iTempH		- ģ��ĸ߶�
 *   int   iTempW		- ģ��Ŀ��
 *   int   iTempMX		- ģ�������Ԫ��X���� ( < iTempW - 1)
 *   int   iTempMY		- ģ�������Ԫ��Y���� ( < iTempH - 1)
 *	 FLOAT * fpArray	- ָ��ģ�������ָ��
 *	 FLOAT fCoef		- ģ��ϵ��
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú�����ָ����ģ�壨�����С������ͼ����в���������iTempHָ��ģ��
 * �ĸ߶ȣ�����iTempWָ��ģ��Ŀ�ȣ�����iTempMX��iTempMYָ��ģ�������
 * Ԫ�����꣬����fpArrayָ��ģ��Ԫ�أ�fCoefָ��ϵ����
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
	// �����ڴ�
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// ��ʼ��ͼ��Ϊԭʼͼ��
	memcpy(lpNewDIBBits, lpDIBBits, lLineBytes * lHeight);

	// ��(��ȥ��Ե����)
	for (i = iTempMY; i < lHeight - iTempH + iTempMY + 1; i++)
	{
		// ��(��ȥ��Ե����)
		for (j = iTempMX; j < lWidth - iTempW + iTempMX + 1; j++)
		{
			// ָ����DIB��i�У���j�����ص�ָ��
			lpDst = (unsigned char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			fResult = 0;

			// ����
			for (k = 0; k < iTempH; k++)
			{
				for (l = 0; l < iTempW; l++)
				{
					// ָ��DIB��i - iTempMY + k�У���j - iTempMX + l�����ص�ָ��
					lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i + iTempMY - k)
						+ j - iTempMX + l;

					// ��������ֵ
					fResult += (*lpSrc) * fpArray[k * iTempW + l];
				}
			}

			// ����ϵ��
			fResult *= fCoef;

			// ȡ����ֵ
			fResult = (FLOAT)fabs(fResult);

			// �ж��Ƿ񳬹�255
			if (fResult > 255)
			{
				// ֱ�Ӹ�ֵΪ255
				*lpDst = 255;
			}
			else
			{
				// ��ֵ
				*lpDst = (unsigned char)(fResult + 0.5);
			}

		}
	}

	// ���Ʊ任���ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// ����
	return TRUE;

}







BOOL WINAPI Select(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int iTempH, int iTempW, int iTempMX, int iTempMY) {

		
	// ָ��Դͼ���ָ��
	unsigned char* lpSrc;

	// ָ��Ҫ���������ָ��
	unsigned char* lpDst;

	// ָ����ͼ���ָ��
	LPSTR			lpNewDIBBits;
	HLOCAL			hNewDIBBits;

	// ָ���˲��������ָ��
	unsigned char* aValue;
	HLOCAL			hArray;

	// ѭ������
	LONG			i;
	LONG			j;
	LONG			k;
	LONG			l;

	// ͼ��ÿ�е��ֽ���
	LONG			lLineBytes;

	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = (lWidth * 8 + 31) / 32 * 4;

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits = LocalAlloc(LHND, lLineBytes * lHeight);

	// �ж��Ƿ��ڴ����ʧ��
	if (hNewDIBBits == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}

	// �����ڴ�
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// ��ʼ��ͼ��Ϊԭʼͼ��
	memcpy(lpNewDIBBits, lpDIBBits, lLineBytes * lHeight);

	// ��ʱ�����ڴ棬�Ա����˲�������
	hArray = LocalAlloc(LHND, iTempH * iTempW);

	// �ж��Ƿ��ڴ����ʧ��
	if (hArray == NULL)
	{
		// �ͷ��ڴ�
		LocalUnlock(hNewDIBBits);
		LocalFree(hNewDIBBits);

		// �����ڴ�ʧ��
		return FALSE;
	}

	// �����ڴ�
	aValue = (unsigned char*)LocalLock(hArray);
	
	// ��ʼ��ֵ�˲�
	// ��(��ȥ��Ե����)
	for (i = iTempMY; i < lHeight - iTempH + iTempMY + 1; i++)
	{
		// ��(��ȥ��Ե����)
		for (j = iTempMX; j < lWidth - iTempW + iTempMX + 1; j++)
		{
			// ָ����DIB��i�У���j�����ص�ָ��
			lpDst = (unsigned char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// ��ȡ�˲�������
			for (k = 0; k < iTempH; k++)
			{
				for (l = 0; l < iTempW; l++)
				{
					// ָ��DIB��i - iFilterMY + k�У���j - iFilterMX + l�����ص�ָ��
					lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i + iTempMY - k) + j - iTempMX + l;

					// ��������ֵ
					aValue[k * iTempW + l] = *lpSrc;
				}
			}

			// ��ȡ��ֵ
			*lpDst = GetMedianNum(aValue, iTempH * iTempW);
		}
	}

	// ���Ʊ任���ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
	LocalUnlock(hArray);
	LocalFree(hArray);

	// ����
	return TRUE;

}

BOOL WINAPI RobertDEC(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{

	// ָ��Դͼ���ָ��
	LPSTR	lpSrc;

	// ָ�򻺴�ͼ���ָ��
	LPSTR	lpDst;

	// ָ�򻺴�DIBͼ���ָ��
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//ѭ������
	long i;
	long j;

	//����ֵ
	double result;
	unsigned char pixel[4];

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}

	// �����ڴ�
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst = (char*)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);


	//ʹ��ˮƽ����ĽṹԪ�ؽ��и�ʴ
	for (j = lHeight - 1; j > 0; j--)
	{
		for (i = 0; i < lWidth - 1; i++)
		{
			//����ʹ��2��2��ģ�壬Ϊ��ֹԽ�磬���Բ��������±ߺ����ұߵ���������

			// ָ��Դͼ���j�У���i�����ص�ָ��			
			lpSrc = (char*)lpDIBBits + lWidth * j + i;

			// ָ��Ŀ��ͼ���j�У���i�����ص�ָ��			
			lpDst = (char*)lpNewDIBBits + lWidth * j + i;

			//ȡ�õ�ǰָ�봦2*2���������ֵ��ע��Ҫת��Ϊunsigned char��
			pixel[0] = (unsigned char)*lpSrc;
			pixel[1] = (unsigned char)*(lpSrc + 1);
			pixel[2] = (unsigned char)*(lpSrc - lWidth);
			pixel[3] = (unsigned char)*(lpSrc - lWidth + 1);

			//����Ŀ��ͼ���еĵ�ǰ��
			result = sqrt((pixel[0] - pixel[3]) * (pixel[0] - pixel[3]) + \
				(pixel[1] - pixel[2]) * (pixel[1] - pixel[2]));
			*lpDst = (unsigned char)result;

		}
	}

	// �����񻯺��ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// ����
	return TRUE;
}


BOOL WINAPI SobelDEC(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{

	// ָ�򻺴�ͼ���ָ��
	LPSTR	lpDst1;
	LPSTR	lpDst2;

	// ָ�򻺴�DIBͼ���ָ��
	LPSTR	lpNewDIBBits1;
	HLOCAL	hNewDIBBits1;
	LPSTR	lpNewDIBBits2;
	HLOCAL	hNewDIBBits2;

	//ѭ������
	long i;
	long j;

	// ģ��߶�
	int		iTempH;

	// ģ����
	int		iTempW;

	// ģ��ϵ��
	FLOAT	fTempC;

	// ģ������Ԫ��X����
	int		iTempMX;

	// ģ������Ԫ��Y����
	int		iTempMY;

	//ģ������
	FLOAT aTemplate[9];

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits1 = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits1 == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}

	// �����ڴ�
	lpNewDIBBits1 = (char*)LocalLock(hNewDIBBits1);

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits2 = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits2 == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}

	// �����ڴ�
	lpNewDIBBits2 = (char*)LocalLock(hNewDIBBits2);

	// ����Դͼ�񵽻���ͼ����
	lpDst1 = (char*)lpNewDIBBits1;
	memcpy(lpNewDIBBits1, lpDIBBits, lWidth * lHeight);
	lpDst2 = (char*)lpNewDIBBits2;
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);

	// ����Sobelģ�����
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

	// ����Template()����
	if (!Template(lpNewDIBBits1, lWidth, lHeight,
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	// ����Sobelģ�����
	aTemplate[0] = -1.0;
	aTemplate[1] = 0.0;
	aTemplate[2] = 1.0;
	aTemplate[3] = -2.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 2.0;
	aTemplate[6] = -1.0;
	aTemplate[7] = 0.0;
	aTemplate[8] = 1.0;

	// ����Template()����
	if (!Template(lpNewDIBBits2, lWidth, lHeight,
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	//����������ͼ������ֵ
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0; i < lWidth - 1; i++)
		{

			// ָ�򻺴�ͼ��1������j�У���i�����ص�ָ��			
			lpDst1 = (char*)lpNewDIBBits1 + lWidth * j + i;

			// ָ�򻺴�ͼ��2������j�У���i�����ص�ָ��			
			lpDst2 = (char*)lpNewDIBBits2 + lWidth * j + i;
			if (*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;

		}
	}

	// ���ƾ���ģ��������ͼ��Դͼ��
	memcpy(lpDIBBits, lpNewDIBBits1, lWidth * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits1);
	LocalFree(hNewDIBBits1);

	LocalUnlock(hNewDIBBits2);
	LocalFree(hNewDIBBits2);
	// ����
	return TRUE;
}

/*************************************************************************
 *
 * �������ƣ�
 *   ErosiontionDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   int   nMode		- ��ʴ��ʽ��0��ʾˮƽ����1��ʾ��ֱ����2��ʾ�Զ���ṹԪ�ء�
 *	 int   structure[3][3]
						- �Զ����3��3�ṹԪ�ء�
 *
 * ����ֵ:
 *   BOOL               - ��ʴ�ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú������ڶ�ͼ����и�ʴ���㡣�ṹԪ��Ϊˮƽ�����ֱ����������㣬�м��λ��ԭ�㣻
 * �������û��Լ�����3��3�ĽṹԪ�ء�
 *
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ��
 ************************************************************************/

BOOL WINAPI ErosionDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int nMode, int structure[3][3])
{

	// ָ��Դͼ���ָ��
	LPSTR	lpSrc;

	// ָ�򻺴�ͼ���ָ��
	LPSTR	lpDst;

	// ָ�򻺴�DIBͼ���ָ��
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//ѭ������
	long i;
	long j;
	int  n;
	int  m;

	//����ֵ
	unsigned char pixel;

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}

	// �����ڴ�
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst = (char*)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);


	if (nMode == 0)
	{
		//ʹ��ˮƽ����ĽṹԪ�ؽ��и�ʴ
		for (j = 0; j < lHeight; j++)
		{
			for (i = 1; i < lWidth - 1; i++)
			{
				//����ʹ��1��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұߵ���������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɺ�ɫ
				*lpDst = (unsigned char)0;

				//���Դͼ���е�ǰ���������������һ���㲻�Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɰ�ɫ
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
		//ʹ�ô�ֱ����ĽṹԪ�ؽ��и�ʴ
		for (j = 1; j < lHeight - 1; j++)
		{
			for (i = 0; i < lWidth; i++)
			{
				//����ʹ��1��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ��������ϱߺ����±ߵ���������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɺ�ɫ
				*lpDst = (unsigned char)0;

				//���Դͼ���е�ǰ���������������һ���㲻�Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɰ�ɫ
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
		//ʹ���Զ���ĽṹԪ�ؽ��и�ʴ
		for (j = 1; j < lHeight - 1; j++)
		{
			for (i = 0; i < lWidth; i++)
			{
				//����ʹ��3��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұߵ���������
				//�����ϱߺ����±ߵ���������
				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɺ�ɫ
				*lpDst = (unsigned char)0;

				//���ԭͼ���ж�Ӧ�ṹԪ����Ϊ��ɫ����Щ������һ�����Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɰ�ɫ
				//ע����DIBͼ�������������µ��õ�
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
	// ���Ƹ�ʴ���ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// ����
	return TRUE;
}


/*************************************************************************
 *
 * �������ƣ�
 *   DilationDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   int   nMode		- ���ͷ�ʽ��0��ʾˮƽ����1��ʾ��ֱ����2��ʾ�Զ���ṹԪ�ء�
 *	 int   structure[3][3]
						- �Զ����3��3�ṹԪ�ء�
 *
 * ����ֵ:
 *   BOOL               - ���ͳɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú������ڶ�ͼ������������㡣�ṹԪ��Ϊˮƽ�����ֱ����������㣬�м��λ��ԭ�㣻
 * �������û��Լ�����3��3�ĽṹԪ�ء�
 *
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ��
 ************************************************************************/


BOOL WINAPI DilationDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int nMode, int structure[3][3])
{

	// ָ��Դͼ���ָ��
	LPSTR	lpSrc;

	// ָ�򻺴�ͼ���ָ��
	LPSTR	lpDst;

	// ָ�򻺴�DIBͼ���ָ��
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//ѭ������
	long i;
	long j;
	int  n;
	int  m;

	//����ֵ
	unsigned char pixel;

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}

	// �����ڴ�
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst = (char*)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);


	if (nMode == 0)
	{
		//ʹ��ˮƽ����ĽṹԪ�ؽ�������
		for (j = 0; j < lHeight; j++)
		{
			for (i = 1; i < lWidth - 1; i++)
			{
				//����ʹ��1��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұߵ���������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if (pixel != 255 && pixel != 0)
					return FALSE;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɰ�ɫ
				*lpDst = (unsigned char)255;

				//Դͼ���е�ǰ�������������ֻҪ��һ�����Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɺ�ɫ
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
		//ʹ�ô�ֱ����ĽṹԪ�ؽ�������
		for (j = 1; j < lHeight - 1; j++)
		{
			for (i = 0; i < lWidth; i++)
			{
				//����ʹ��1��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ��������ϱߺ����±ߵ���������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɰ�ɫ
				*lpDst = (unsigned char)255;

				//Դͼ���е�ǰ�������������ֻҪ��һ�����Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɺ�ɫ
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
		//ʹ���Զ���ĽṹԪ�ؽ�������
		for (j = 1; j < lHeight - 1; j++)
		{
			for (i = 0; i < lWidth; i++)
			{
				//����ʹ��3��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұߵ���������
				//�����ϱߺ����±ߵ���������
				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɰ�ɫ
				*lpDst = (unsigned char)255;

				//ԭͼ���ж�Ӧ�ṹԪ����Ϊ��ɫ����Щ����ֻҪ��һ���Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɺ�ɫ
				//ע����DIBͼ�������������µ��õ�
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
	// �������ͺ��ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// ����
	return TRUE;
}


/*************************************************************************
 *
 * �������ƣ�
 *   OpenDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   int   nMode		- �����㷽ʽ��0��ʾˮƽ����1��ʾ��ֱ����2��ʾ�Զ���ṹԪ�ء�
 *	 int   structure[3][3]
						- �Զ����3��3�ṹԪ�ء�
 *
 * ����ֵ:
 *   BOOL               - ������ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú������ڶ�ͼ����п����㡣�ṹԪ��Ϊˮƽ�����ֱ����������㣬�м��λ��ԭ�㣻
 * �������û��Լ�����3��3�ĽṹԪ�ء�
 *
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ��
 ************************************************************************/

BOOL WINAPI OpenDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int nMode, int structure[3][3])
{

	// ָ��Դͼ���ָ��
	LPSTR	lpSrc;

	// ָ�򻺴�ͼ���ָ��
	LPSTR	lpDst;

	// ָ�򻺴�DIBͼ���ָ��
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//ѭ������
	long i;
	long j;
	int  n;
	int  m;

	//����ֵ
	unsigned char pixel;

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}

	// �����ڴ�
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst = (char*)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);


	if (nMode == 0)
	{
		//ʹ��ˮƽ����ĽṹԪ�ؽ��и�ʴ
		for (j = 0; j < lHeight; j++)
		{
			for (i = 1; i < lWidth - 1; i++)
			{
				//����ʹ��1��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұߵ���������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɺ�ɫ
				*lpDst = (unsigned char)0;

				//���Դͼ���е�ǰ���������������һ���㲻�Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɰ�ɫ
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
		//ʹ�ô�ֱ����ĽṹԪ�ؽ��и�ʴ
		for (j = 1; j < lHeight - 1; j++)
		{
			for (i = 0; i < lWidth; i++)
			{
				//����ʹ��1��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ��������ϱߺ����±ߵ���������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɺ�ɫ
				*lpDst = (unsigned char)0;

				//���Դͼ���е�ǰ���������������һ���㲻�Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɰ�ɫ
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
		//ʹ���Զ���ĽṹԪ�ؽ��и�ʴ
		for (j = 1; j < lHeight - 1; j++)
		{
			for (i = 0; i < lWidth; i++)
			{
				//����ʹ��3��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұߵ���������
				//�����ϱߺ����±ߵ���������
				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɺ�ɫ
				*lpDst = (unsigned char)0;

				//���ԭͼ���ж�Ӧ�ṹԪ����Ϊ��ɫ����Щ������һ�����Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɰ�ɫ
				//ע����DIBͼ�������������µ��õ�
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
	// ���Ƹ�ʴ���ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// ���³�ʼ���·�����ڴ棬�趨��ʼֵΪ255
	//lpDst = (char *)lpNewDIBBits;
	//memset(lpDst, (BYTE)255, lWidth * lHeight);


	if (nMode == 0)
	{
		//ʹ��ˮƽ����ĽṹԪ�ؽ�������
		for (j = 0; j < lHeight; j++)
		{
			for (i = 1; i < lWidth - 1; i++)
			{
				//����ʹ��1��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұߵ���������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɰ�ɫ
				*lpDst = (unsigned char)255;

				//Դͼ���е�ǰ�������������ֻҪ��һ�����Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɺ�ɫ
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
		//ʹ�ô�ֱ����ĽṹԪ�ؽ�������
		for (j = 1; j < lHeight - 1; j++)
		{
			for (i = 0; i < lWidth; i++)
			{
				//����ʹ��1��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ��������ϱߺ����±ߵ���������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɰ�ɫ
				*lpDst = (unsigned char)255;

				//Դͼ���е�ǰ�������������ֻҪ��һ�����Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɺ�ɫ
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
		//ʹ���Զ���ĽṹԪ�ؽ�������
		for (j = 1; j < lHeight - 1; j++)
		{
			for (i = 0; i < lWidth; i++)
			{
				//����ʹ��3��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұߵ���������
				//�����ϱߺ����±ߵ���������
				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɰ�ɫ
				*lpDst = (unsigned char)255;

				//ԭͼ���ж�Ӧ�ṹԪ����Ϊ��ɫ����Щ����ֻҪ��һ���Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɺ�ɫ
				//ע����DIBͼ�������������µ��õ�
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
	// �������ͺ��ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);


	return TRUE;
}


/*************************************************************************
 *
 * �������ƣ�
 *   CloseDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   int   nMode		- �����㷽ʽ��0��ʾˮƽ����1��ʾ��ֱ����2��ʾ�Զ���ṹԪ�ء�
 *	 int   structure[3][3]
						- �Զ����3��3�ṹԪ�ء�
 *
 * ����ֵ:
 *   BOOL               - ������ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú������ڶ�ͼ����п����㡣�ṹԪ��Ϊˮƽ�����ֱ����������㣬�м��λ��ԭ�㣻
 * �������û��Լ�����3��3�ĽṹԪ�ء�
 *
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ��
 ************************************************************************/

 /*************************************************************************
  *
  * �������ƣ�
  *   ThinDIB()
  *
  * ����:
  *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
  *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
  *   LONG  lHeight      - Դͼ��߶ȣ���������
  *
  * ����ֵ:
  *   BOOL               - ������ɹ�����TRUE�����򷵻�FALSE��
  *
  * ˵��:
  * �ú������ڶ�ͼ�����ϸ�����㡣
  *
  * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ��
  ************************************************************************/

BOOL WINAPI CloseDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int nMode, int structure[3][3])
{
	if (DilationDIB(lpDIBBits, lWidth, lHeight, nMode, structure))
	{

		if (ErosionDIB(lpDIBBits, lWidth, lHeight, nMode, structure))
		{
			// ����
			return TRUE;

		}
	}
	return FALSE;

	// ����
	return TRUE;
}

BOOL WINAPI ThiningDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{

	// ָ��Դͼ���ָ��
	LPSTR	lpSrc;

	// ָ�򻺴�ͼ���ָ��
	LPSTR	lpDst;

	// ָ�򻺴�DIBͼ���ָ��
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//����
	BOOL bModified;

	//ѭ������
	long i;
	long j;
	int  n;
	int  m;

	//�ĸ�����
	BOOL bCondition1;
	BOOL bCondition2;
	BOOL bCondition3;
	BOOL bCondition4;

	//������
	unsigned char nCount;

	//����ֵ
	unsigned char pixel;

	//5��5������������ֵ
	unsigned char neighbour[5][5];

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}

	// �����ڴ�
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst = (char*)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);

	bModified = TRUE;

	while (bModified)
	{

		bModified = FALSE;
		// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
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

				//����ʹ��5��5�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ�������Χ�ļ��кͼ�������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if (pixel != 255 && *lpSrc != 0)
					//return FALSE;
					continue;
				//���Դͼ���е�ǰ��Ϊ��ɫ��������
				else if (pixel == 255)
					continue;

				//��õ�ǰ�����ڵ�5��5����������ֵ����ɫ��0������ɫ��1����
				for (m = 0; m < 5; m++)
				{
					for (n = 0; n < 5; n++)
					{
						neighbour[m][n] = (255 - (unsigned char)*(lpSrc + ((4 - m) - 2) * lWidth + n - 2)) / 255;
					}
				}
				//				neighbour[][]
								//����ж�������
								//�ж�2<=NZ(P1)<=6
				nCount = neighbour[1][1] + neighbour[1][2] + neighbour[1][3] \
					+ neighbour[2][1] + neighbour[2][3] + \
					+ neighbour[3][1] + neighbour[3][2] + neighbour[3][3];
				if (nCount >= 2 && nCount <= 6)
					bCondition1 = TRUE;

				//�ж�Z0(P1)=1
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

				//�ж�P2*P4*P8=0 or Z0(p2)!=1
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

				//�ж�P2*P4*P6=0 or Z0(p4)!=1
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
		// ���Ƹ�ʴ���ͼ��
		memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);


	}
	// ���Ƹ�ʴ���ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// ����
	return TRUE;
}


BOOL WINAPI backcolor1(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lSrcLineBytes) {
	unsigned char* lpSrc;//ָ��DIBԴ���ص�ָ��
	FLOAT fTemp;//�м����
	for (int i = 0; i < lHeight; i++) {
		for (int j = 0; j < lWidth; j++) {
			lpSrc = (unsigned char*)lpDIBBits + lSrcLineBytes * (lHeight - 1 - i) + j;
			fTemp = (float)*lpSrc;
			if (fTemp == 255)
				//ֱ�Ӹ�ֵΪ255 
				*lpSrc = 255;
			else if (fTemp == 0)
				// ��������
				*lpSrc = 0;
		}
	}
	return TRUE;
}

BOOL WINAPI backcolor2(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lSrcLineBytes) {
	unsigned char* lpSrc;//ָ��DIBԴ���ص�ָ��
	FLOAT fTemp;//�м����
	for (int i = 0; i < lHeight; i++) {
		for (int j = 0; j < lWidth; j++) {
			lpSrc = (unsigned char*)lpDIBBits + lSrcLineBytes * (lHeight - 1 - i) + j;
			fTemp = (float)*lpSrc;
			if (fTemp == 255)
				//ֱ�Ӹ�ֵΪ255 
				*lpSrc = 0;
			else if (fTemp == 0)
				// ��������
				*lpSrc = 255;
		}
	}
	return TRUE;
}

/**************************************************************************
* ��������;
*ThresholdTrans()*
����:
* LPSTR IpDIBBits  -ָ��ԭDIBͼ��ָ��
* LONG 1Width      -ԭͼ���ȣ�������)
 LONG lHeight      -ԭͼ��߶ȣ�������>
 BYTEbThre         �C��ֵ
*
*����ֵ:*B0OL
-�ɹ�����TRUE�����򷵻�FALSE��
*˵��:
*�ú���������ͼ�������ֵ�任�����ڻҶ�ֵС����ֵ������ֱ������*�Ҷ�ֵΪ0;�Ҷ�ֵ������ֵ�������������Ϊ255��
***************************************************************************/
BOOL WINAPI ThresholdTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bThre) {
	//ָ��ԭͼ���ָ��
	unsigned char* lpSrc;
	//ѭ������
	LONG i; LONG j;
	// ͼ��ÿ�е��ֽ���
	LONG lLineBytes;
	//ڦ��ͼ��ÿ�е��ֽ���
	lLineBytes = (lWidth * 8 + 31) / 32 * 4;;
	// ÿ��
	for (i = 0; i < lHeight; i++) {
		// ÿ��
		for (j = 0; j < lWidth; j++) {
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			//�ж��Ƿ�С����ֵ
			if ((*lpSrc) < bThre) {
				//ֱ�Ӹ�ֵΪ0
				*lpSrc = 0;
			}
			else {
				// ֱ�Ӹ�ֵΪ255 
				*lpSrc = 255;
			}
		}
	}
	return true;


}


/***************************************************************************************************
*�������:
*windowTrans ()*
����:
*LPSTR 1pDIBBits�Cָ��ԭDIBͼ��ָ��
*LONG lWjdth    �Cԭͼ���ȡ�������)
*LoNG lHe ight  �Cԭͼ��߶ȣ���������
*BYTE bLow      �C��������
*BYTEblp        �C��������
*����ֵ:*B0OL   �C�ɹ���TRLE�����򷵻�FALSE��
*
*˵��:
*�ú���������ͼ����д�I1�任��ֻ���ڴ��ڷ�Χ�ڵĻҶȱ��ֲ��䣬
*С�����޵�����ֱ�����ûҶ�ֵΪ0;�������޵�����ֱ�����ûҶ�ֵΪ255��*
***************************************************************************************************/
BOOL WINAPI WindowTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE blow, BYTE bUp)
{
	//ָ��ԭͼ���ָ��
	unsigned char* lpSrc;
	//ѭ������
	LONG i; LONG j;
	// ͼ��ÿ�е��ֽ���
	LONG lLineBytes;
	//ڦ��ͼ��ÿ�е��ֽ���
	lLineBytes = (lWidth * 8 + 31) / 32 * 4;;
	// ÿ��
	for (i = 0; i < lHeight; i++) {
		// ÿ��
		for (j = 0; j < lWidth; j++) {
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			//�ж��Ƿ�С����ֵ
			if ((*lpSrc) < blow) {
				//ֱ�Ӹ�ֵΪ0
				*lpSrc = 0;
			}
			else if ((*lpSrc) > bUp) {
				// ֱ�Ӹ�ֵΪ255 
				*lpSrc = 255;
			}
		}
	}
	return true;

}


/**************************************************************
*��������:GrayStretch()*
����;
LPSTR lpDIBBits--ָ��ԭDIBͼ��ָ��
*LONG lWidth--ԭͼ���ȡ�������)
*LONG lHeight--ԭͼ��߶ȡ�������)
* BYTE bXl--�Ҷ������һ�����X����
* BYTE bY1--�Ҷ����ٵ�һ�����Y����
BYTE bX  --�Ҷ�����ڶ������x����
BYTE bY2 --�Ҷ�����ڶ������Y����
*
����ֵ
	BOOL           �ɹ���TRRE�����򷵻�FALSE.
*
˵��:
*�ú���������ͼ����лҶ�����
***********************************************************************/

BOOL WINAPI GrayStretch(LPSTR lpDlBBits, LONG lWidth, LONG lHeight, BYTE bX1, BYTE bY1, BYTE bX2, BYTE bY2) {
	//ָ��ԭͼ���ָ��
	unsigned char* lpSrc;
	// ѭ������
	LONG i;
	LONG j;
	//�Ҷ�ӳ���
	BYTE bMap[256];
	//ͼ��ÿ�е��ֽ���
	LONG lLineBytes;
	// ����.ͼ��ÿ�е��ֽ���
	lLineBytes = (lWidth * 8 + 31) / 32 * 4;
	//����Ҷ�ӳ���
	for (i = 0; i <= bX1; i++)
	{ //�ж�bX1�Ƿ����0����ֹ��ĸΪ0)
		if (bX1 > 0)
		{
			// ���Ա任
			bMap[i] = (BYTE)bY1 * i / bX1;
		}
		else
		{ //ֱ�Ӹ�ֵΪ0
			bMap[i] = 0;
		}

	}
	for (; i <= bX2; i++)
	{
		// �ж�bX1�Ƿ����bX2����ֹ��ĸΪ0)
		if (bX2 != bX1) {

			//���Ա任
			bMap[i] = bY1 + (BYTE)((bY2 - bY1) * (i - bX1) / (bX2 - bX1));
		}
		else
			// ֱ�Ӹ�ֵΪbY1
			bMap[i] = bY1;
	}
	for (; i < 256; i++) {
		// �ж�bX2�Ƿ����255����ֹ��ĸΪ0 �� 
		if (bX2 != 255)
			//���Ա任
			bMap[i] = bY2 + (BYTE)((255 - bY2) * (i - bX2) / (255 - bX2));
		else
			//ֱ�Ӹ�ֵΪ255
			bMap[i] = 255;


	}
	//ÿ��
	for (i = 0; i < lHeight; i++) {
		//ÿ��
		for (j = 0; j < lWidth; j++) {
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDlBBits + lLineBytes * (lHeight - 1 - i) + j;
			// �����µĻҶ�ֵ
			*lpSrc = bMap[*lpSrc];
		}
	}
	// ����
	return TRUE;

}


/*************************************************************************
 *
 * �������ƣ�
 *   Templaterelief()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   int   iTempH		- ģ��ĸ߶�
 *   int   iTempW		- ģ��Ŀ��
 *   int   iTempMX		- ģ�������Ԫ��X���� ( < iTempW - 1)
 *   int   iTempMY		- ģ�������Ԫ��Y���� ( < iTempH - 1)
 *	 FLOAT * fpArray	- ָ��ģ�������ָ��
 *	 FLOAT fCoef		- ģ��ϵ��
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú�����ָ����ģ�壨�����С������ͼ����в���������iTempHָ��ģ��
 * �ĸ߶ȣ�����iTempWָ��ģ��Ŀ�ȣ�����iTempMX��iTempMYָ��ģ�������
 * Ԫ�����꣬����fpArrayָ��ģ��Ԫ�أ�fCoefָ��ϵ����
 *
 ************************************************************************/

BOOL WINAPI Templaterelief(LPSTR lpDIBBits, LONG lWidth, LONG lHeight,
	int iTempH, int iTempW,
	int iTempMX, int iTempMY,
	FLOAT* fpArray, FLOAT fCoef, int SThre)
{
	// ָ����ͼ���ָ��
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	// ָ��Դͼ���ָ��
	unsigned char* lpSrc;

	// ָ��Ҫ���������ָ��
	unsigned char* lpDst;

	// ѭ������
	LONG	i;
	LONG	j;
	LONG	k;
	LONG	l;

	// ������
	FLOAT	fResult;

	// ͼ��ÿ�е��ֽ���
	LONG lLineBytes;

	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = (lWidth * 8 + 31) / 32 * 4;

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits = LocalAlloc(LHND, lLineBytes * lHeight);

	// �ж��Ƿ��ڴ����ʧ��
	if (hNewDIBBits == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}

	// �����ڴ�
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// ��ʼ��ͼ��Ϊԭʼͼ��
	memcpy(lpNewDIBBits, lpDIBBits, lLineBytes * lHeight);

	// ��(��ȥ��Ե����)
	for (i = iTempMY; i < lHeight - iTempH + iTempMY + 1; i++)
	{
		// ��(��ȥ��Ե����)
		for (j = iTempMX; j < lWidth - iTempW + iTempMX + 1; j++)
		{
			// ָ����DIB��i�У���j�����ص�ָ��
			lpDst = (unsigned char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			fResult = 0;

			// ����
			for (k = 0; k < iTempH; k++)
			{
				for (l = 0; l < iTempW; l++)
				{
					// ָ��DIB��i - iTempMY + k�У���j - iTempMX + l�����ص�ָ��
					lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i + iTempMY - k)
						+ j - iTempMX + l;

					// ��������ֵ
					fResult += (*lpSrc) * fpArray[k * iTempW + l];
				}
			}

			// ����ϵ��
			fResult *= fCoef;

			// ���������ֵ
			fResult = fResult + SThre;

			// �ж��Ƿ񳬹�255��0
			if (fResult > 255)
			{
				// ֱ�Ӹ�ֵΪ255
				*lpDst = 255;
			}
			else if (fResult < 0) {
				*lpDst = 0;
			}
			else {
				// ��ֵ
				*lpDst = (unsigned char)(fResult + 0.5);
			}

		}
	}

	// ���Ʊ任���ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// ����
	return TRUE;

}

/*************************************************************************
 *
 * �������ƣ�
 *   TranslationDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   LONG  lXOffset     - X��ƽ��������������
 *   LONG  lYOffset     - Y��ƽ��������������
 *
 * ����ֵ:
 *   BOOL               - ƽ�Ƴɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú�������ˮƽ�ƶ�DIBͼ�񡣺�������ı�ͼ��Ĵ�С���Ƴ��Ĳ���ͼ��
 * ����ȥ���հײ����ð�ɫ��䡣
 *
 ************************************************************************/

BOOL WINAPI TranslationDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lXOffset, LONG lYOffset)
{
	// ƽ�ƺ�ʣ��ͼ����Դͼ���е�λ�ã���������
	CRect	rectSrc;

	// ƽ�ƺ�ʣ��ͼ������ͼ���е�λ�ã���������
	CRect	rectDst;

	// ָ��Դͼ���ָ��
	LPSTR	lpSrc;

	// ָ��Ҫ���������ָ��
	LPSTR	lpDst;

	// ָ����ͼ���ָ��
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	// ָ��ͼ���Ƿ�ȫ����ȥ��������
	BOOL	bVisible;

	// ѭ������
	LONG	i;

	// ͼ��ÿ�е��ֽ���
	LONG lLineBytes;

	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = (lWidth * 8 + 31) / 32 * 4;

	// ����ֵ
	bVisible = TRUE;

	// ����rectSrc��rectDst��X����
	if (lXOffset <= -lWidth)
	{
		// X�᷽��ȫ���Ƴ���������
		bVisible = FALSE;
	}
	else if (lXOffset <= 0)
	{
		// �ƶ�����ͼ�������Ͻ�X����Ϊ0
		rectDst.left = 0;

		// �ƶ�����ͼ�������½�X����ΪlWidth - |lXOffset| = lWidth + lXOffset
		rectDst.right = lWidth + lXOffset;
	}
	else if (lXOffset < lWidth)
	{
		// �ƶ�����ͼ�������Ͻ�X����ΪlXOffset
		rectDst.left = lXOffset;

		// �ƶ�����ͼ�������½�X����ΪlWidth
		rectDst.right = lWidth;
	}
	else
	{
		// X�᷽��ȫ���Ƴ���������
		bVisible = FALSE;
	}

	// ƽ�ƺ�ʣ��ͼ����Դͼ���е�X����
	rectSrc.left = rectDst.left - lXOffset;
	rectSrc.right = rectDst.right - lXOffset;

	//  ����rectSrc��rectDst��Y����
	if (lYOffset <= -lHeight)
	{
		// Y�᷽��ȫ���Ƴ���������
		bVisible = FALSE;
	}
	else if (lYOffset <= 0)
	{
		// �ƶ�����ͼ�������Ͻ�Y����Ϊ0
		rectDst.top = 0;

		// �ƶ�����ͼ�������½�Y����ΪlHeight - |lYOffset| = lHeight + lYOffset
		rectDst.bottom = lHeight + lYOffset;
	}
	else if (lYOffset < lHeight)
	{
		// �ƶ�����ͼ�������Ͻ�Y����ΪlYOffset
		rectDst.top = lYOffset;

		// �ƶ�����ͼ�������½�Y����ΪlHeight
		rectDst.bottom = lHeight;
	}
	else
	{
		// X�᷽��ȫ���Ƴ���������
		bVisible = FALSE;
	}

	// ƽ�ƺ�ʣ��ͼ����Դͼ���е�Y����
	rectSrc.top = rectDst.top - lYOffset;
	rectSrc.bottom = rectDst.bottom - lYOffset;

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits = LocalAlloc(LHND, lLineBytes * lHeight);
	if (hNewDIBBits == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}

	// �����ڴ�
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst = (char*)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lLineBytes * lHeight);

	// ����в���ͼ��ɼ�
	if (bVisible)
	{

		// ƽ��ͼ��
		for (i = 0; i < (rectSrc.bottom - rectSrc.top); i++)
		{
			// Ҫ�����������㣬ע������DIBͼ�����������µ��õģ���һ�������Ǳ��������
			// һ�У���˸����������㲻��lpDIBBits + lLineBytes * (i + rectSrc.top) + 
			// rectSrc.left������ lpDIBBits + lLineBytes * (lHeight - i - rectSrc.top - 1) + 
			// rectSrc.left��

			lpSrc = (char*)lpDIBBits + lLineBytes * (lHeight - i - rectSrc.top - 1) + rectSrc.left;

			// ҪĿ����������
			// ͬ��ע�����µ��õ����⡣
			lpDst = (char*)lpNewDIBBits + lLineBytes * (lHeight - i - rectDst.top - 1) +
				rectDst.left;

			// ����ÿһ�У����ΪrectSrc.right - rectSrc.left
			memcpy(lpDst, lpSrc, rectSrc.right - rectSrc.left);

		}
	}

	// ����ƽ�ƺ��ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// ����
	return TRUE;
}


/*************************************************************************
 *
 * �������ƣ�
 *   RotateDIB()
 *
 * ����:
 *   LPSTR lpDIB		- ָ��ԴDIB��ָ��
 *   int iRotateAngle	- ��ת�ĽǶȣ�0-360�ȣ�
 *
 * ����ֵ:
 *   HGLOBAL            - ��ת�ɹ�������DIB��������򷵻�NULL��
 *
 * ˵��:
 *   �ú���������ͼ������Ϊ������תDIBͼ�񣬷���������DIB�ľ����
 * ���øú������Զ�����ͼ������ʾ���е����ء������в������ڽ���
 * ֵ�㷨���в�ֵ��
 *
 ************************************************************************/

HGLOBAL WINAPI RotateDIB(CMFCApplication1Doc* pDoc, LPSTR lpDIB, int iRotateAngle)
{

	// Դͼ��Ŀ�Ⱥ͸߶�
	LONG	lWidth;
	LONG	lHeight;

	// ��ת��ͼ��Ŀ�Ⱥ͸߶�
	LONG	lNewWidth;
	LONG	lNewHeight;

	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;

	// ��ת��ͼ��Ŀ�ȣ�lNewWidth'��������4�ı�����
	LONG	lNewLineBytes;

	// ָ��Դͼ���ָ��
	LPSTR	lpDIBBits;

	// ָ��Դ���ص�ָ��
	LPSTR	lpSrc;

	//�����µ�DIB���
	HDIB hDIB;
	
	// ָ����תͼ���Ӧ���ص�ָ��
	LPSTR	lpDst;

	// ָ����תͼ���ָ��
	LPSTR	lpNewDIB;
	LPSTR	lpNewDIBBits;

	// ָ��BITMAPINFO�ṹ��ָ�루Win3.0��
	LPBITMAPINFOHEADER lpbmi;

	// ָ��BITMAPCOREINFO�ṹ��ָ��
	LPBITMAPCOREHEADER lpbmc;

	// ѭ����������������DIB�е����꣩
	LONG	i;
	LONG	j;

	// ������ԴDIB�е�����
	LONG	i0;
	LONG	j0;

	// ��ת�Ƕȣ����ȣ�
	float	fRotateAngle;

	// ��ת�Ƕȵ����Һ�����
	float	fSina, fCosa;

	// Դͼ�ĸ��ǵ����꣨��ͼ������Ϊ����ϵԭ�㣩
	float	fSrcX1, fSrcY1, fSrcX2, fSrcY2, fSrcX3, fSrcY3, fSrcX4, fSrcY4;

	// ��ת���ĸ��ǵ����꣨��ͼ������Ϊ����ϵԭ�㣩
	float	fDstX1, fDstY1, fDstX2, fDstY2, fDstX3, fDstY3, fDstX4, fDstY4;

	// �����м䳣��
	float	f1, f2;
	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits =  pDoc->m_dib.GetBits(lpDIB);
	lWidth = pDoc->m_dib.GetWidth(lpDIB);					// ��ȡͼ��Ŀ��		
	lHeight = pDoc->m_dib.GetHeight(lpDIB);					// ��ȡͼ��ĸ߶�	
	int lpSrcBitCount = pDoc->m_dib.GetBitCount(lpDIB);                    //��ȡͼ��λ��
	lLineBytes = pDoc->m_dib.GetReqByteWidth(lWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���	


	// ����ת�ǶȴӶ�ת��������
	fRotateAngle = (float)RADIAN(iRotateAngle);

	// ������ת�Ƕȵ�����
	fSina = (float)sin((double)fRotateAngle);

	// ������ת�Ƕȵ�����
	fCosa = (float)cos((double)fRotateAngle);

	// ����ԭͼ���ĸ��ǵ����꣨��ͼ������Ϊ����ϵԭ�㣩
	fSrcX1 = (float)(-(lWidth - 1) / 2);
	fSrcY1 = (float)((lHeight - 1) / 2);
	fSrcX2 = (float)((lWidth - 1) / 2);
	fSrcY2 = (float)((lHeight - 1) / 2);
	fSrcX3 = (float)(-(lWidth - 1) / 2);
	fSrcY3 = (float)(-(lHeight - 1) / 2);
	fSrcX4 = (float)((lWidth - 1) / 2);
	fSrcY4 = (float)(-(lHeight - 1) / 2);

	// ������ͼ�ĸ��ǵ����꣨��ͼ������Ϊ����ϵԭ�㣩
	fDstX1 = fCosa * fSrcX1 + fSina * fSrcY1;
	fDstY1 = -fSina * fSrcX1 + fCosa * fSrcY1;
	fDstX2 = fCosa * fSrcX2 + fSina * fSrcY2;
	fDstY2 = -fSina * fSrcX2 + fCosa * fSrcY2;
	fDstX3 = fCosa * fSrcX3 + fSina * fSrcY3;
	fDstY3 = -fSina * fSrcX3 + fCosa * fSrcY3;
	fDstX4 = fCosa * fSrcX4 + fSina * fSrcY4;
	fDstY4 = -fSina * fSrcX4 + fCosa * fSrcY4;

	// ������ת���ͼ��ʵ�ʿ��
	lNewWidth = (LONG)(max(fabs(fDstX4 - fDstX1), fabs(fDstX3 - fDstX2)) + 0.5);

	// ������ͼ��ÿ�е��ֽ���
	lNewLineBytes = (lNewWidth * 8+31)*32/4;

	// ������ת���ͼ��߶�
	lNewHeight = (LONG)(max(fabs(fDstY4 - fDstY1), fabs(fDstY3 - fDstY2)) + 0.5);

	// �������������������Ժ�ÿ�ζ�������
	f1 = (float)(-0.5 * (lNewWidth - 1) * fCosa - 0.5 * (lNewHeight - 1) * fSina
		+ 0.5 * (lWidth - 1));
	f2 = (float)(0.5 * (lNewWidth - 1) * fSina - 0.5 * (lNewHeight - 1) * fCosa
		+ 0.5 * (lHeight - 1));

	// �����ڴ棬�Ա�����DIB
	hDIB = (HDIB) ::GlobalAlloc(GHND, lNewLineBytes * lNewHeight + *(LPDWORD)lpDIB + pDoc->m_dib.GetPalSize(lpDIB));

	// �ж��Ƿ��ڴ����ʧ��
	if (hDIB == NULL)
	{
		// �����ڴ�ʧ��
		return NULL;
	}

	// �����ڴ�
	lpNewDIB = (char*)::GlobalLock((HGLOBAL)hDIB);

	// ����DIB��Ϣͷ�͵�ɫ��
	memcpy(lpNewDIB, lpDIB, *(LPDWORD)lpDIB + pDoc->m_dib.GetPalSize(lpDIB));

	// �ҵ���DIB������ʼλ��
	lpNewDIBBits = lpNewDIB + *(LPDWORD)lpNewDIB + pDoc->m_dib.GetPalSize(lpDIB);

	// ��ȡָ��
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;


		// ����Windows 3.0 DIB
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	

	// ���ͼ��ÿ�н��в���
	for (i = 0; i < lNewHeight; i++)
	{
		// ���ͼ��ÿ�н��в���
		for (j = 0; j < lNewWidth; j++)
		{
			// ָ����DIB��i�У���j�����ص�ָ��
			// ע��˴���Ⱥ͸߶�����DIB�Ŀ�Ⱥ͸߶�
			lpDst = (char*)lpNewDIBBits + lNewLineBytes * (lNewHeight - 1 - i) + j;

			// �����������ԴDIB�е�����
			i0 = (LONG)(-((float)j) * fSina + ((float)i) * fCosa + f2 + 0.5);
			j0 = (LONG)(((float)j) * fCosa + ((float)i) * fSina + f1 + 0.5);

			// �ж��Ƿ���Դͼ��Χ��
			if ((j0 >= 0) && (j0 < lWidth) && (i0 >= 0) && (i0 < lHeight))
			{
				// ָ��ԴDIB��i0�У���j0�����ص�ָ��
				lpSrc = (char*)lpDIBBits + lLineBytes * (lHeight - 1 - i0) + j0;

				// ��������
				*lpDst = *lpSrc;
			}
			else
			{
				// ����Դͼ��û�е����أ�ֱ�Ӹ�ֵΪ255
				*((unsigned char*)lpDst) = 255;
			}

		}

	}
	
	// ����
	return hDIB;
}




/*************************************************************************
 *
 * �������ƣ�
 *   TransposeDIB()
 *
 * ����:
 *   LPSTR lpDIB		- ָ��ԴDIB��ָ��
 *
 * ����ֵ:
 *   BOOL               - ת�óɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú�������ת��DIBͼ�񣬼�ͼ��x��y���껥��������������ı�ͼ��Ĵ�С��
 * ����ͼ��ĸ߿�������
 *
 ************************************************************************/

BOOL WINAPI TransposeDIB(LPSTR lpDIB,LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{

	
	// ָ��Դ���ص�ָ��
	LPSTR	lpSrc;
	
	// ָ��ת��ͼ���Ӧ���ص�ָ��
	LPSTR	lpDst;

	// ָ��ת��ͼ���ָ��
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;
	
	// ָ��BITMAPINFO�ṹ��ָ�루Win3.0��
	LPBITMAPINFOHEADER lpbmi;
	
	// ָ��BITMAPCOREINFO�ṹ��ָ��
	LPBITMAPCOREHEADER lpbmc;

	// ѭ������
	LONG	i;
	LONG	j;
	
	// ͼ��ÿ�е��ֽ���
	LONG lLineBytes;
	
	// ��ͼ��ÿ�е��ֽ���
	LONG lNewLineBytes;

	// ��ȡָ��
	lpbmi = (LPBITMAPINFOHEADER)lpDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpDIB;

	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = (lWidth * 8+31)/32*4;
	
	// ������ͼ��ÿ�е��ֽ���
	lNewLineBytes = (lHeight * 8 + 31) / 32 * 4;
	
	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits = LocalAlloc(LHND, lWidth * lNewLineBytes);

	// �ж��Ƿ��ڴ����ʧ��
	if (hNewDIBBits == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// �����ڴ�
	lpNewDIBBits = (char * )LocalLock(hNewDIBBits);
	
	// ���ͼ��ÿ�н��в���
	for(i = 0; i < lHeight; i++)
	{
		// ���ÿ��ͼ��ÿ�н��в���
		for(j = 0; j < lWidth; j++)
		{
			
			// ָ��ԴDIB��i�У���j�����ص�ָ��
			lpSrc = (char *)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// ָ��ת��DIB��j�У���i�����ص�ָ��
			// ע��˴�lWidth��lHeight��ԴDIB�Ŀ�Ⱥ͸߶ȣ�Ӧ�û���
			lpDst = (char *)lpNewDIBBits + lNewLineBytes * (lWidth - 1 - j) + i;
			
			// ��������
			*lpDst = *lpSrc;
			
		}
		
	}
	
	// ����ת�ú��ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lNewLineBytes);
	
	// ����DIB��ͼ��ĸ߿�

		// ����Windows 3.0 DIB
		lpbmi->biWidth = lHeight;
		
		lpbmi->biHeight = lWidth;
	
	
	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
	return TRUE;
}





/*************************************************************************
 *
 * �������ƣ�
 *   MirrorDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   BOOL  bDirection   - ����ķ���TRUE��ʾˮƽ����FALSE��ʾ��ֱ����
 *
 * ����ֵ:
 *   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú�����������DIBͼ�񡣿���ָ������ķ�ʽ��ˮƽ���Ǵ�ֱ��
 *
 ************************************************************************/

BOOL WINAPI MirrorDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BOOL bDirection)
{

	// ָ��Դͼ���ָ��
	LPSTR	lpSrc;

	// ָ��Ҫ���������ָ��
	LPSTR	lpDst;

	// ָ����ͼ���ָ��
	LPSTR	lpBits;
	HLOCAL	hBits;

	// ѭ������
	LONG	i;
	LONG	j;

	// ͼ��ÿ�е��ֽ���
	LONG lLineBytes;

	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = (lWidth * 8 + 31) / 32 * 4;

	// ��ʱ�����ڴ棬�Ա���һ��ͼ��
	hBits = LocalAlloc(LHND, lLineBytes);
	if (hBits == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}

	// �����ڴ�
	lpBits = (char*)LocalLock(hBits);

	// �жϾ���ʽ
	if (bDirection)
	{
		// ˮƽ����

		// ���ͼ��ÿ�н��в���
		for (i = 0; i < lHeight; i++)
		{
			// ���ÿ��ͼ����벿�ֽ��в���
			for (j = 0; j < lWidth / 2; j++)
			{

				// ָ������i�У���j�����ص�ָ��
				lpSrc = (char*)lpDIBBits + lLineBytes * i + j;

				// ָ������i�У�������j�����ص�ָ��
				lpDst = (char*)lpDIBBits + lLineBytes * (i + 1) - j;

				// ����һ������
				*lpBits = *lpDst;

				// ��������i�У���j�����ظ��Ƶ�������i�У�������j������
				*lpDst = *lpSrc;

				// ��������i�У�������j�����ظ��Ƶ�������i�У���j������
				*lpSrc = *lpBits;
			}

		}
	}
	else
	{
		// ��ֱ����

		// ����ϰ�ͼ����в���
		for (i = 0; i < lHeight / 2; i++)
		{

			// ָ������i����������ָ��
			lpSrc = (char*)lpDIBBits + lLineBytes * i;

			// ָ���i����������ָ��
			lpDst = (char*)lpDIBBits + lLineBytes * (lHeight - i - 1);

			// ����һ�У����ΪlWidth
			memcpy(lpBits, lpDst, lLineBytes);

			// ��������i�����ظ��Ƶ���i��
			memcpy(lpDst, lpSrc, lLineBytes);

			// ����i�����ظ��Ƶ�������i��
			memcpy(lpSrc, lpBits, lLineBytes);

		}
	}

	// �ͷ��ڴ�
	LocalUnlock(hBits);
	LocalFree(hBits);

	// ����
	return TRUE;
}

//4��ͨ����
/*************************************************************************
*
* �������ƣ�
*   dealer()
*
* ����:
*   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
*   LONG  lWidth       - Դͼ���ȣ���������
*   LONG  lHeight      - Դͼ��߶ȣ���������
*
* ����ֵ:
*   int               - ����
*
* ˵��:
*   �ú�����������ͼ�����������
*
************************************************************************/

int  dealer_four(LPSTR image, int width, int height, int Bg)
{
	int** flag_max;
	flag_max = new int* [height];
	for (int i = 0; i < height; i++) {
		flag_max[i] = new int[width];
	}                                         //��̬�����ά����
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			flag_max[i][j] = 0;
		}
	}


	int count_flag = 0;
	queue<point> buffer;
	int count = 1;    //������
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
					count_flag = 1;//��������ѭ��
					temp = buffer.front();
					buffer.pop();
					if (temp.i >= 0 && temp.i <= height && temp.j >= 0 && temp.j <= width && *(ptemp + temp.i * width + temp.j) == Bg && flag_max[temp.i][temp.j] == 0)
					{
						//���
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

//8��ͨ����
/*************************************************************************
*
* �������ƣ�
*   dealer()
*
* ����:
*   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
*   LONG  lWidth       - Դͼ���ȣ���������
*   LONG  lHeight      - Դͼ��߶ȣ���������
*
* ����ֵ:
*   int               - ����
*
* ˵��:
*   �ú�����������ͼ�����������
*
************************************************************************/

int  dealer_eight(LPSTR image, int width, int height, int Bg)
{
	int** flag_max;
	flag_max = new int* [height];
	for (int i = 0; i < height; i++) {
		flag_max[i] = new int[width];
	}                                         //��̬�����ά����
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			flag_max[i][j] = 0;
		}
	}


	int count_flag = 0;
	queue<point> buffer;
	int count = 1;    //������
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
					count_flag = 1;//��������ѭ��
					temp = buffer.front();
					buffer.pop();
					if (temp.i >= 0 && temp.i <= height && temp.j >= 0 && temp.j <= width && *(ptemp + temp.i * width + temp.j) == Bg && flag_max[temp.i][temp.j] == 0)
					{
						//���
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
	//��ʼ��
	for (long i = 0; i < lHeight; i++)
		for (long j = 0; j < lWidth; j++)
		{
			x[i][j].value = 0;
			x[i][j].xiangsu = 0;
		}
	//��ֵ
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
				//�ж�������

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
	//��ʼ��
	for (long i = 0; i < lHeight; i++)
		for (long j = 0; j < lWidth; j++)
		{
			x[i][j].value = 0;
			x[i][j].xiangsu = 0;
		}
	//��ֵ
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
				//�жϰ�����
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

