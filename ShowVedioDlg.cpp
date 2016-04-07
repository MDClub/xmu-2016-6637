
// ShowVedioDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ShowVedio.h"
#include "ShowVedioDlg.h"
#include "afxdialogex.h"
#include <opencv2\opencv.hpp>
#include <math.h>
//#include "CvvImage.cpp"


using namespace cv;
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CShowVedioDlg 对话框



CShowVedioDlg::CShowVedioDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShowVedioDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShowVedioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CShowVedioDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OpenVedio, &CShowVedioDlg::OnBnClickedOpenvedio)
	ON_WM_TIMER()
	ON_STN_CLICKED(IDC_PicCtl, &CShowVedioDlg::OnStnClickedPicctl)
	ON_BN_CLICKED(IDOK, &CShowVedioDlg::OnBnClickedOk)
//	ON_BN_CLICKED(IDC_BUTTON1, &CShowVedioDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CloseVideo, &CShowVedioDlg::OnBnClickedClosevideo)
	ON_BN_CLICKED(IDC_Canny, &CShowVedioDlg::OnBnClickedCanny)
	ON_BN_CLICKED(IDC_Sketch, &CShowVedioDlg::OnBnClickedSketch)
	ON_BN_CLICKED(IDC_BUTTON_Wuhua, &CShowVedioDlg::OnBnClickedButtonWuhua)
END_MESSAGE_MAP()


// CShowVedioDlg 消息处理程序

BOOL CShowVedioDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	//创建对象
	m_pVideoInfo = new CVideoInfo();


	m_PicCtlHdc = GetDlgItem(IDC_PicCtl)->GetDC()->GetSafeHdc();
	GetDlgItem(IDC_PicCtl)->GetClientRect(&m_PicCtlRect);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CShowVedioDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CShowVedioDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CShowVedioDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CShowVedioDlg::OnBnClickedOpenvedio()
{
	// TODO:  在此添加控件通知处理程序代码
	char aviName[300] = { 0 };
	//MFC中打开文件夹
	//路径存在一个变量里面.m.lpsstrFile
	CFileDialog inDlg(TRUE, NULL, NULL, NULL, NULL, NULL);

	inDlg.m_ofn.lpstrFile = (LPSTR)&aviName[0];

	//点击OK的话就读取视频
	if (inDlg.DoModal() == IDOK)
	{
		m_pVideoInfo->m_pCapture = cvCreateFileCapture(aviName);

		if (m_pVideoInfo->m_pCapture)
		{
			m_pVideoInfo->m_FrameWidth =(int) cvGetCaptureProperty(m_pVideoInfo->m_pCapture,CV_CAP_PROP_FRAME_WIDTH);
			m_pVideoInfo->m_FrameHeight =(int) cvGetCaptureProperty(m_pVideoInfo->m_pCapture, CV_CAP_PROP_FRAME_HEIGHT);
			//创建图像空间
			//对每一帧存贮起来
			m_pVideoInfo->m_pFrameImage=cvCreateImage(cvSize(m_pVideoInfo->m_FrameWidth, m_pVideoInfo->m_FrameHeight),8,3);
			cvZero(m_pVideoInfo->m_pFrameImage);

			//定时器设置
			SetTimer(1, 10, NULL);
		}
	}


}


void CShowVedioDlg::OnTimer(UINT_PTR nIDEvent)
//nIDEvent时钟ID号
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case 1:
	{
		if (m_pVideoInfo->m_pCapture)
		{
			IplImage* frame;
			//IplImage* frame_canny;
			frame = cvQueryFrame(m_pVideoInfo->m_pCapture);
			//frame_canny = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
			if (frame)
			{
				cvCopy(frame, m_pVideoInfo->m_pFrameImage);
				//cvFlip(m_pVideoInfo->m_pFrameImage);
				//cvCanny(m_pVideoInfo->m_pFrameImage, frame_canny, 10, 100, 3);

				m_CvvImage.CopyOf(m_pVideoInfo->m_pFrameImage);
				//m_CvvImage.CopyOf(frame_canny);
				m_CvvImage.DrawToHDC(m_PicCtlHdc, m_PicCtlRect);

			}
		}

	}
		break;

	case 2:
	{
		if (m_pVideoInfo->m_pCapture)
		{
			IplImage* frame;
			IplImage* frame_canny;
		
					frame = cvQueryFrame(m_pVideoInfo->m_pCapture);
					frame_canny = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 0);
					cvCopy(frame, m_pVideoInfo->m_pFrameImage);

					cvCanny(m_pVideoInfo->m_pFrameImage, frame_canny, 10, 100, 3);
					//m_CvvImage.CopyOf(m_pVideoInfo->m_pFrameImage);
					m_CvvImage.CopyOf(frame_canny);
					m_CvvImage.DrawToHDC(m_PicCtlHdc, m_PicCtlRect);
			
		}
	}
	break;

	case 3:
	{
		if (m_pVideoInfo->m_pCapture)
		{
			IplImage* frame = cvQueryFrame(m_pVideoInfo->m_pCapture);
			
		
			cvCopy(frame, m_pVideoInfo->m_pFrameImage);
			Mat src = cv::cvarrToMat(m_pVideoInfo->m_pFrameImage);
			int width = src.cols;
			int heigh = src.rows;
			Mat gray0, gray1;
		
			//去色
			cvtColor(src, gray0, CV_BGR2GRAY);
			//反色
			addWeighted(gray0, -1, NULL, 0, 255, gray1);
			//高斯模糊,高斯核的Size与最后的效果有关
			GaussianBlur(gray1, gray1, Size(11, 11), 0);

			//融合：颜色减淡
			Mat img(gray1.size(), CV_8UC1);
			for (int y = 0; y<heigh; y++)
			{

				uchar* P0 = gray0.ptr<uchar>(y);
				uchar* P1 = gray1.ptr<uchar>(y);
				uchar* P = img.ptr<uchar>(y);
				for (int x = 0; x<width; x++)
				{
					int tmp0 = P0[x];
					int tmp1 = P1[x];
					P[x] = (uchar)min((tmp0 + (tmp0*tmp1) / (256 - tmp1)), 255);
				}

			}
		
			IplImage* dst = &IplImage(img);
				
			m_CvvImage.CopyOf(dst);
			m_CvvImage.DrawToHDC(m_PicCtlHdc, m_PicCtlRect);
		
		}
		

	}
	break;

	case 4:
	{
		if (m_pVideoInfo->m_pFrameImage)
		{
			IplImage* frame;

			
			frame = cvQueryFrame(m_pVideoInfo->m_pCapture);
			float mSize = 0.5;
			Mat src = cv::cvarrToMat(m_pVideoInfo->m_pFrameImage);
			int width = src.cols;
			int heigh = src.rows;
			int centerX = width >> 1;
			int centerY = heigh >> 1;
			int maxV = centerX*centerX + centerY*centerY;
			int minV = (int)(maxV*(1 - mSize));
			int diff = maxV - minV;
			float ratio = width >heigh ? (float)heigh / (float)width : (float)width / (float)heigh;
			Mat img;
			src.copyTo(img);

			Scalar avg = mean(src);
			Mat dst(img.size(), CV_8UC3);
			Mat mask1u[3];
			float tmp, r;
			for (int y = 0; y<heigh; y++)
			{
				uchar* imgP = img.ptr<uchar>(y);
				uchar* dstP = dst.ptr<uchar>(y);
				for (int x = 0; x<width; x++)
				{
					int b = imgP[3 * x];
					int g = imgP[3 * x + 1];
					int r = imgP[3 * x + 2];

					float dx = centerX - x;
					float dy = centerY - y;

					if (width > heigh)
						dx = (dx*ratio);
					else
						dy = (dy*ratio);

					int dstSq = dx*dx + dy*dy;

					float v = ((float)dstSq / diff) * 255;

					r = (int)(r + v);
					g = (int)(g + v);
					b = (int)(b + v);
					r = (r>255 ? 255 : (r<0 ? 0 : r));
					g = (g>255 ? 255 : (g<0 ? 0 : g));
					b = (b>255 ? 255 : (b<0 ? 0 : b));

							dstP[3 * x] = (uchar)b;
							dstP[3 * x + 1] = (uchar)g;
							dstP[3 * x + 2] = (uchar)r;
				}
			}

			IplImage* dst1 = &IplImage(dst);

			m_CvvImage.CopyOf(dst1);
			m_CvvImage.DrawToHDC(m_PicCtlHdc, m_PicCtlRect);
		}


	}
	break;


	}



	CDialogEx::OnTimer(nIDEvent);
}


void CShowVedioDlg::OnStnClickedPicctl()
{
	// TODO:  在此添加控件通知处理程序代码

}


void CShowVedioDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_pVideoInfo->m_pCapture)
	{
		cvReleaseCapture(&m_pVideoInfo->m_pCapture);
		m_pVideoInfo->m_pCapture = NULL;

	}
	if (m_pVideoInfo->m_pFrameImage)
	{
		cvReleaseImage(&m_pVideoInfo->m_pFrameImage);
		m_pVideoInfo->m_pFrameImage = NULL;
	}
	KillTimer(1);
	CDialogEx::OnOK();
}


void CShowVedioDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CShowVedioDlg::OnBnClickedClosevideo()
{
	// TODO:  在此添加控件通知处理程序代码
	//用计数器来表示暂停还是开始
	static int count = 0;

	if (count % 2 ==0)
	{
		SetDlgItemTextA(IDC_CloseVideo, "开始");
		KillTimer(1);
		count = 1;

	} 
	else
	{
		SetTimer(1, 10, NULL);
		SetDlgItemTextA(IDC_CloseVideo, "暂停");
		count = 0;
	}
}

////////////////////////////////////////////////////////////////////

void CShowVedioDlg::OnBnClickedCanny()
{
	// TODO:  在此添加控件通知处理程序代码

	static int count2 = 0;

	if (count2 % 2 == 0)
	{
		SetDlgItemTextA(IDC_Canny, "恢复图像");
		KillTimer(1);
		SetTimer(2, 1, NULL);
		count2 = 1;

	}
	else
	{
		KillTimer(2);
		SetTimer(1, 1, NULL);
		SetDlgItemTextA(IDC_Canny, "边缘检测");
		count2 = 0;
	}
						
}




void CShowVedioDlg::OnBnClickedSketch()
{
	// TODO:  在此添加控件通知处理程序代码

	static int count3 = 0;

	if (count3 % 2 == 0)
	{
		SetDlgItemTextA(IDC_Sketch, "恢复图像");
		KillTimer(1);
		KillTimer(2);
		SetTimer(3, 1, NULL);
		count3 = 1;

	}
	else
	{
		KillTimer(3);
		SetTimer(1, 1, NULL);
		SetDlgItemTextA(IDC_Sketch, "素描");
		count3 = 0;
	}
}


void CShowVedioDlg::OnBnClickedButtonWuhua()
{
	// TODO:  在此添加控件通知处理程序代码

	static int count4 = 0;

	if (count4 % 2 == 0)
	{
		SetDlgItemTextA(IDC_BUTTON_Wuhua, "恢复图像");
		KillTimer(1);
		//KillTimer(2);
		//KillTimer(3);
		SetTimer(4, 1, NULL);
		count4 = 1;

	}
	else
	{
		KillTimer(4);
		SetTimer(1, 1, NULL);
		SetDlgItemTextA(IDC_BUTTON_Wuhua, "雾化");
		count4 = 0;
	}

}


