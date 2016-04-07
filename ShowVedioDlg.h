
// ShowVedioDlg.h : ͷ�ļ�
#include "VideoInfo.h" //��������
#include "windows.h"
#include "CvvImage.h"

#pragma once


// CShowVedioDlg �Ի���
class CShowVedioDlg : public CDialogEx
{
// ����
public:
	CShowVedioDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SHOWVEDIO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	CVideoInfo*  m_pVideoInfo;

	HDC m_PicCtlHdc;
	CRect m_PicCtlRect;  //�������

	CvvImage m_CvvImage; //����

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
