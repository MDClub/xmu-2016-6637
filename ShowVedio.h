
// ShowVedio.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CShowVedioApp: 
// �йش����ʵ�֣������ ShowVedio.cpp
//

class CShowVedioApp : public CWinApp
{
public:
	CShowVedioApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CShowVedioApp theApp;