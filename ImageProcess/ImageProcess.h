// ImageProcess.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CImageProcessApp:
// �аѾ\��@�����O�� ImageProcess.cpp
//

class CImageProcessApp : public CWinApp
{
public:
	CImageProcessApp();

// �мg
	public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CImageProcessApp theApp;