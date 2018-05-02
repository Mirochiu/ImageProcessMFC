#pragma once
#include "afxwin.h"


// MInputBox 對話方塊

class MInputBox : public CDialog
{
	DECLARE_DYNAMIC(MInputBox)

public:
	MInputBox(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~MInputBox();

// 對話方塊資料
	enum { IDD = IDD_INPUTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()

public:
    CEdit EditInput;
    CStatic LabelQuest;

    void SetParms(const CString& msg, 
        const CString& title = _T("My Input Box"), const CString& DefaultVal = _T(""))
    {
        //this->SetWindowText(title);
        //this->LabelQuest.SetWindowText(msg);
        //this->EditInput.SetSel(0,-1);
        //this->EditInput.ReplaceSel(DefaultVal);
    }
    
    CString GetInputValue()
    {
        int len = EditInput.LineLength(0);
        char* input = new char[len];
        EditInput.GetLine(0, input, len);
        CString retstr = input;
        delete[] input;
        return retstr;
    }

    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
};
