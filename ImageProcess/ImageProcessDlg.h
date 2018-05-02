// ImageProcessDlg.h : ���Y��
//

#pragma once
#include "afxwin.h"

#include "atlimage.h"


// CImageProcessDlg ��ܤ��
class CImageProcessDlg : public CDialog
{
// �غc
public:
	CImageProcessDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
	enum { IDD = IDD_IMAGEPROCESS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩

// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMnexit();
	afx_msg void OnClose();
	afx_msg void OnMnopen();
	afx_msg void OnMnsave();
	afx_msg void OnTogray();

    // �����W�Ψ���ܼv��������
    CStatic Image;

// �ۭq�p���ݩ�
private:
    // ��ܼv�����Ҧ�
	enum MY_IMGSHOWMODE{
		MY_SHOW_NORMAL, MY_SHOW_ASPECT, MY_SHOW_STRETCH
	} m_eImgShowMode;

	// �Ψ�Ū���P�g�J�ɮץΪ�
	CImage cImgForLoading;

// �ۭq���}�ݩ�
public:
	void InitShowImageMode() {
		m_eImgShowMode = MY_SHOW_NORMAL;
	}

	int GetShowImageMode() {
		return m_eImgShowMode;
	}

	void SetShowImageMode(int mode)
	{
		switch(mode)
		{
			case 0: m_eImgShowMode = MY_SHOW_NORMAL; break;
			case 1: m_eImgShowMode = MY_SHOW_ASPECT; break;
			case 2: m_eImgShowMode = MY_SHOW_STRETCH; break;
			default: ASSERT(!"The programmer's fault!"); break;
		}
	}

    // ConCan���^�ǭ�
    enum{YES,NO,CANCEL,NONE};
        // �ϥ� if (YES == ConCanBox("Msg")) �ӧP�_�һݪ��^��
        // �Y�O�b��L�ɮ�, �άO�۩w�q����Ƥ��ϥ�, �бN�{���令
        //     if (MainForm::YES == MainForm->ConCanBox("Msg"))

	//---------------------------------------------------------------------------
	// ��¦�س], �U�ؤ��P����ܮ�
	//---------------------------------------------------------------------------
	void ShowMessage(const CString& msg, const CString& cap = _T("�T��"))
	{
		MessageBox(msg, cap, MB_OK|MB_ICONINFORMATION);
	}
	//---------------------------------------------------------------------------
	void ErrorMessage(const CString& msg, const CString& cap = _T("���~"))
	{
		MessageBox(msg, cap, MB_OK|MB_ICONERROR);
	}
	//---------------------------------------------------------------------------
	void WarnMessage(const CString& msg, const CString& cap = _T("ĵ�i"))
	{
		MessageBox(msg, cap, MB_OK|MB_ICONWARNING);
	}
	//---------------------------------------------------------------------------
	bool ConfirmBox(const CString& msg, const CString& cap = _T("�T�{"))
	{
		return (IDYES==MessageBox(msg, cap, MB_YESNO|MB_ICONQUESTION));
	}
	//---------------------------------------------------------------------------
	int ConCanBox(const CString& msg, const CString& cap = _T("�T�{"))
	{
		switch (MessageBox(msg, cap, MB_YESNOCANCEL|MB_ICONQUESTION))
		{
			case IDYES:		return YES;
			case IDCANCEL:	return CANCEL;
			case IDNO:		return NO;
			default:		return NONE;
		}
	}
    afx_msg void OnUpdateToGray(CCmdUI *pCmdUI);
    afx_msg void OnSobelEdge();
};
