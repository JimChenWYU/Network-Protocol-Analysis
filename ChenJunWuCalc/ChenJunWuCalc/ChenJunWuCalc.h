
// ChenJunWuCalc.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CChenJunWuCalcApp:
// �йش����ʵ�֣������ ChenJunWuCalc.cpp
//

class CChenJunWuCalcApp : public CWinApp
{
public:
	CChenJunWuCalcApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CChenJunWuCalcApp theApp;