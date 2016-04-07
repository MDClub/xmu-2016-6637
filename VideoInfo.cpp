#include "stdafx.h"
#include "VideoInfo.h"

//构造函数里面赋空值
CVideoInfo::CVideoInfo()
{
	m_pCapture = NULL;
   m_pFrameImage = NULL;
}


CVideoInfo::~CVideoInfo()
{
}
