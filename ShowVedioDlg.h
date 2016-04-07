
// ShowVedioDlg.h : 头文件
#include "VideoInfo.h" //包含进来
#include "windows.h"
#include "CvvImage.h"

#pragma once


// CShowVedioDlg 对话框
class CShowVedioDlg : public CDialogEx
{
// 构造
public:
	CShowVedioDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SHOWVEDIO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	CVideoInfo*  m_pVideoInfo;

	HDC m_PicCtlHdc;
	CRect m_PicCtlRect;  //申明句柄

	CvvImage m_CvvImage; //复制

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenvedio();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStnClickedPicctl();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedClosevideo();
	afx_msg void OnBnClickedCanny();
	afx_msg void OnBnClickedSketch();
	afx_msg void OnBnClickedButtonWuhua();
};
