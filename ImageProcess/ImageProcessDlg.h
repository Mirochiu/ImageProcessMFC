// ImageProcessDlg.h : 標頭檔
//

#pragma once
#include "afxwin.h"

#include "atlimage.h"


// CImageProcessDlg 對話方塊
class CImageProcessDlg : public CDialog
{
// 建構
public:
	CImageProcessDlg(CWnd* pParent = NULL);	// 標準建構函式

// 對話方塊資料
	enum { IDD = IDD_IMAGEPROCESS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援

// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
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

    // 介面上用來顯示影像的元件
    CStatic Image;

// 自訂私有屬性
private:
    // 顯示影像的模式
	enum MY_IMGSHOWMODE{
		MY_SHOW_NORMAL, MY_SHOW_ASPECT, MY_SHOW_STRETCH
	} m_eImgShowMode;

	// 用來讀取與寫入檔案用的
	CImage cImgForLoading;

// 自訂公開屬性
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

    // ConCan的回傳值
    enum{YES,NO,CANCEL,NONE};
        // 使用 if (YES == ConCanBox("Msg")) 來判斷所需的回應
        // 若是在其他檔案, 或是自定義的函數中使用, 請將程式改成
        //     if (MainForm::YES == MainForm->ConCanBox("Msg"))

	//---------------------------------------------------------------------------
	// 基礎建設, 各種不同的對話框
	//---------------------------------------------------------------------------
	void ShowMessage(const CString& msg, const CString& cap = _T("訊息"))
	{
		MessageBox(msg, cap, MB_OK|MB_ICONINFORMATION);
	}
	//---------------------------------------------------------------------------
	void ErrorMessage(const CString& msg, const CString& cap = _T("錯誤"))
	{
		MessageBox(msg, cap, MB_OK|MB_ICONERROR);
	}
	//---------------------------------------------------------------------------
	void WarnMessage(const CString& msg, const CString& cap = _T("警告"))
	{
		MessageBox(msg, cap, MB_OK|MB_ICONWARNING);
	}
	//---------------------------------------------------------------------------
	bool ConfirmBox(const CString& msg, const CString& cap = _T("確認"))
	{
		return (IDYES==MessageBox(msg, cap, MB_YESNO|MB_ICONQUESTION));
	}
	//---------------------------------------------------------------------------
	int ConCanBox(const CString& msg, const CString& cap = _T("確認"))
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
