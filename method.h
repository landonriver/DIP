#include<iostream>
#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "DlgPointWin.h"
using namespace std;
int MpSort(int* src, int* attach, int n);
int KsSort(int* src, int* attach, int n);
int ZjSort(int* src, int* attach, int n);
int PFC(int color1, int color2);
int BitTran(WORD* color24bit, LONG len, BYTE* Index, RGBQUAD* mainColor);
unsigned char WINAPI GetMedianNum(unsigned char* bArray, int iFilterLen);
int BuildNewSize(unsigned char*tem,LPSTR lpSrc,int num);
BOOL WINAPI LinerTrans(LPSTR lpSrcStartBits, LONG lSrcWidth, LONG lSrcHeight, FLOAT Fa, FLOAT Fb);
BOOL WINAPI LinerTrans24(LPSTR lpSrcStartBits, LONG lSrcWidth, LONG lSrcHeight, FLOAT Fa, FLOAT Fb);
BOOL WINAPI FdLinear_Tran(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int type, int threshold);
BOOL WINAPI LinerTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lSrcLineBytes, FLOAT fA, FLOAT fB);
BOOL BitPlaneSlicing(LPSTR lpDIBBits, LONG lmageWidth, LONG  lLineBytes, LONG lmageHeight, int Bit);
BOOL  LogTranslation(LPSTR lpSrcStartBits, long lWidth, long lHeight, long lLineBytes);
BOOL WINAPI Template(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int iTempH, int iTempW, int iTempMX, int iTempMY, FLOAT* fpArray, FLOAT fCoef);
BOOL WINAPI Select(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int iTempH, int iTempW, int iTempMX, int iTempMY);
BOOL WINAPI RobertDEC(LPSTR lpDIBBits, LONG lWidth, LONG lHeight);
BOOL WINAPI SobelDEC(LPSTR lpDIBBits, LONG lWidth, LONG lHeight);
BOOL WINAPI ErosionDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BOOL bHori, int structure[3][3]);
BOOL WINAPI DilationDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BOOL bHori, int structure[3][3]);
BOOL WINAPI OpenDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BOOL bHori, int structure[3][3]);
BOOL WINAPI CloseDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BOOL bHori, int structure[3][3]);
BOOL WINAPI ThiningDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight);
BOOL WINAPI backcolor1(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lSrcLineBytes);
BOOL WINAPI backcolor2(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lSrcLineBytes);
BOOL WINAPI ThresholdTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bThre);
BOOL WINAPI WindowTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE blow, BYTE bUp);
BOOL WINAPI GrayStretch(LPSTR lpDlBBits, LONG lWidth, LONG lHeight, BYTE bX1, BYTE bY1, BYTE bX2, BYTE bY2);
BOOL WINAPI Templaterelief(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int iTempH, int iTempW, int iTempMX, int iTempMY, FLOAT* fpArray, FLOAT fCoef, int SThre);
BOOL WINAPI TranslationDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG offX1, LONG offY1);
BOOL WINAPI TransposeDIB(LPSTR lpDIB, LPSTR lpDIBBits, LONG lWidth, LONG lHeight);
BOOL WINAPI MirrorDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BOOL bDirection);
int  dealer_eight(LPSTR image, int width, int height, int Bg);
int  dealer_four(LPSTR image, int width, int height, int Bg);
LONG WINAPI getArea_eight(LPSTR start, LONG lWidth, LONG lHeight, int Bg);
LONG WINAPI getArea_four(LPSTR start, LONG lWidth, LONG lHeight, int Bg);
int WINAPI gethearty(LONG lWidth, LONG lHeight, LONG mianji);
int WINAPI heartx(LONG lWidth, LONG lHeight, LONG mianji);








