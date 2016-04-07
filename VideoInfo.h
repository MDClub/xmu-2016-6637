#pragma once
#include <opencv2\opencv.hpp>
class CVideoInfo
{
public:
	CvCapture* m_pCapture;
	IplImage*  m_pFrameImage;
	int m_FrameWidth;
	int m_FrameHeight;
public:
	CVideoInfo();
	~CVideoInfo();
};

