// MInputBox.cpp : ��@��
//

#include "stdafx.h"
#include "ImageProcess.h"
#include "MInputBox.h"


// MInputBox ��ܤ��

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


// MInputBox �T���B�z�`��

void MInputBox::OnBnClickedOk()
{
    // TODO: �b���[�J����i���B�z�`���{���X
    OnOK();
}

void MInputBox::OnBnClickedCancel()
{
    // TODO: �b���[�J����i���B�z�`���{���X
    OnCancel();
}
