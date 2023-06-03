
// MFCApplication1View.h: CMFCApplication1View 类的接口
//

#pragma once


class CMFCApplication1View : public CView
{
protected: // 仅从序列化创建
	CMFCApplication1View() noexcept;
	DECLARE_DYNCREATE(CMFCApplication1View)

// 特性
public:
	CMFCApplication1Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCApplication1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDispimginfo();
	afx_msg void Onchangeimglight();
	afx_msg void Onchangewc();
	afx_msg void On24cb24g();
	afx_msg void On24cb8c();
	afx_msg void On24cb8g();
	afx_msg void On8cb8g();
	afx_msg void On8gb2z();
	afx_msg void On8yddxs();
	afx_msg void Onpointinvert();
	afx_msg void OnViewLargeicon();
	afx_msg void OnDvtrans();
	afx_msg void OnVtrans();
//	afx_msg void OnDltrans();
	afx_msg void OnDltrans();
	afx_msg void OnLtrans();
	afx_msg void OnLinetrans();
	afx_msg void OnBpsperate();
	afx_msg void OnLogtrans();
	afx_msg void OnGammatrans();
	afx_msg void OnJzlb();
	afx_msg void OnGslb();
	afx_msg void OnZzlb();
	afx_msg void Onaddnoise();
	afx_msg void OnLpls4();
	afx_msg void OnLpls8();
	afx_msg void Onedgerobert();
	afx_msg void Onedgesobel();
	afx_msg void OnXtxpz();
	afx_msg void OnXtxfs();
	afx_msg void OnXtxkq();
	afx_msg void OnXtxbh();
	afx_msg void OnXtxnbj();
	afx_msg void OnXtxwbj();
	afx_msg void OnPointthre();
	afx_msg void OnPointwind();
	afx_msg void OnPointstre();
	afx_msg void OnZftjhh();
	afx_msg void OnStylefilter();
	afx_msg void OnGtrans();
	afx_msg void OnGeorotate();
	afx_msg void OnTranspose();
	afx_msg void OnMirrorx();
	afx_msg void OnMirrory();
	afx_msg void OnZoomdib();
	afx_msg void Onoilpaint();
	afx_msg void OnMsc();
	afx_msg void OnMglass();
	afx_msg void OnQycal();
	afx_msg void OnCannydec();
	afx_msg void OnUsm();
	afx_msg void OnAddsy();
	afx_msg void OnExtractsy();
};

#ifndef _DEBUG  // MFCApplication1View.cpp 中的调试版本
inline CMFCApplication1Doc* CMFCApplication1View::GetDocument() const
   { return reinterpret_cast<CMFCApplication1Doc*>(m_pDocument); }
#endif

