// CLLK.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCLLKApp:
// �йش����ʵ�֣������ CLLK.cpp
//

class CCLLKApp : public CWinApp
{
public:
	CCLLKApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCLLKApp theApp;
extern int FRONTHEIGHT;
extern int FRONTWIDTH;