// MInputBox.cpp : 實作檔
//

#include "stdafx.h"
#include "ImageProcess.h"
#include "MInputBox.h"


// MInputBox 對話方塊

IMPLEMENT_DYNAMIC(MInputBox, CDialog)

MInputBox::MInputBox(CWnd* pParent /*=NULL*/)
	: CDialog(MInputBox::IDD, pParent)
{

}

MInputBox::~MInputBox()
{
}

void MInputBox::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_InputValue, EditInput);
    DDX_Control(pDX, IDC_InputMsg, LabelQuest);
}


BEGIN_MESSAGE_MAP(MInputBox, CDialog)
    ON_BN_CLICKED(IDOK, &MInputBox::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &MInputBox::OnBnClickedCancel)
END_MESSAGE_MAP()


// MInputBox 訊息處理常式

void MInputBox::OnBnClickedOk()
{
    // TODO: 在此加入控制項告知處理常式程式碼
    OnOK();
}

void MInputBox::OnBnClickedCancel()
{
    // TODO: 在此加入控制項告知處理常式程式碼
    OnCancel();
}
