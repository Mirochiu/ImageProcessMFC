// ImageProcessDlg.cpp : ��@��
//

#include "stdafx.h"
#include "ImageProcess.h"
#include "ImageProcessDlg.h"

#include "DS.h"
#include <math.h>
#include "MInputBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �� App About �ϥ� CAboutDlg ��ܤ��

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ܤ�����
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

// �{���X��@
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CImageProcessDlg ��ܤ��

CImageProcessDlg::CImageProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageProcessDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageProcessDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_IMAGE1, Image);
}

BEGIN_MESSAGE_MAP(CImageProcessDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_MnExit, &CImageProcessDlg::OnMnexit)
	ON_WM_CLOSE()
	ON_COMMAND(ID_MnOpen, &CImageProcessDlg::OnMnopen)
	ON_COMMAND(ID_MnSave, &CImageProcessDlg::OnMnsave)
	ON_COMMAND(ID_ToGray, &CImageProcessDlg::OnTogray)
    ON_UPDATE_COMMAND_UI(ID_ToGray, &CImageProcessDlg::OnUpdateToGray)
    ON_COMMAND(ID_SobelEdge, &CImageProcessDlg::OnSobelEdge)
END_MESSAGE_MAP()


// CImageProcessDlg �T���B�z�`��

BOOL CImageProcessDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �N [����...] �\���[�J�t�Υ\���C

	// IDM_ABOUTBOX �����b�t�ΩR�O�d�򤧤��C
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �]�w����ܤ�����ϥܡC�����ε{�����D�������O��ܤ���ɡA
	// �ج[�|�۰ʱq�Ʀ��@�~
	SetIcon(m_hIcon, TRUE);			// �]�w�j�ϥ�
	SetIcon(m_hIcon, FALSE);		// �]�w�p�ϥ�

	// TODO: �b���[�J�B�~����l�]�w
    InitShowImageMode();    // �v����ܼҦ�

	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}

void CImageProcessDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �p�G�N�̤p�ƫ��s�[�J�z����ܤ���A�z�ݭn�U�C���{���X�A
// �H�Kø�s�ϥܡC���ϥΤ��/�˵��Ҧ��� MFC ���ε{���A
// �ج[�|�۰ʧ������@�~�C
void CImageProcessDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ø�s���˸m���e

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N�ϥܸm����Τ�ݯx��
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �yø�ϥ�
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ��ϥΪ̩즲�̤p�Ƶ����ɡA
// �t�ΩI�s�o�ӥ\����o�����ܡC
HCURSOR CImageProcessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CImageProcessDlg::OnMnexit()
{
	OnClose();  // use my close function
}

void CImageProcessDlg::OnClose()
{
    // I cannot find 'Exit()', 'Close()' which are use to terminate the program.
    // A function named 'CloseWindow()' I tried, but nothing is happened.
    // Finally, I found 'OnOK()', it is ok like its name!
	OnOK();
}

// Open the image
void CImageProcessDlg::OnMnopen()
{
    // Create an dialog to select the Image for loading
    CString szFilePath;
	CString szFilter = _T("Image files(*.bmp;*.jpg;*.png;*.tif;*.gif)|*.bmp;*.jpg;*.png;*.tif;*.gif|*.*|*.*|");
	CFileDialog cOpnFD(TRUE, _T("bmp"), szFilePath, OFN_HIDEREADONLY, szFilter, this);
	if (cOpnFD.DoModal() != IDOK)
		return;

	szFilePath = cOpnFD.GetPathName();

    // Check the file existence
	CFileFind find;	
	if (find.FindFile(szFilePath) == FALSE)
	{
		MessageBox(_T("Cannot find the file!"), _T("Open file error"), MB_OK|MB_ICONERROR);
		return;
	}

    // Loading image by CImage, it is an esy way!!
    cImgForLoading.Destroy();   // Avoid to trigger the assertion in debug mode
	if (FAILED(cImgForLoading.Load(szFilePath)))
	{
		MessageBox(_T("Cannot load the unknown type of image file!"), _T("Open file error"), MB_OK|MB_ICONERROR);
		return;
	}

	// Set main window title
	CString szCaption;
	AfxGetMainWnd()->GetWindowText(szCaption);
	int iNamePart = szCaption.ReverseFind(_T('-'));
	szCaption.Delete(0, iNamePart); // replace the filename which is the leading text of title.
	AfxGetMainWnd()->SetWindowText(cOpnFD.GetFileName() + szCaption);

    // Show the image loaded by CImage
    Image.SetBitmap(cImgForLoading);
    Image.

	Invalidate(false);
	UpdateWindow(); // Window title is changed.
}

// Save the image
void CImageProcessDlg::OnMnsave()
{
	CImage& rcImg = cImgForLoading;

	// To Make Sure the Image is Loaded for Saving!
	if ( rcImg.IsNull() )
	{
		MessageBox(_T("The image file havent loaded for saving"),
            _T("Save file error"), MB_OK|MB_ICONERROR);
		return;
	}

	CString szFilePath;	// Set default directory for dialog
	CString szFilter = _T("BMP file(*.bmp)|*.bmp|"
        "JPEG file(*.jpg)|*.jpg|"
        "PNG file(*.png)|*.png|"
        "*.*|*.*|");

	CFileDialog cSavFD(FALSE, _T("bmp"), szFilePath, OFN_HIDEREADONLY, szFilter, this);
	if ( cSavFD.DoModal() != IDOK )
		return;

	szFilePath = cSavFD.GetPathName();

    // Check the file overwritten
	CFileFind find;	
	if ( find.FindFile(szFilePath) == TRUE )
	{
		if ( MessageBox(
			_T("The target file for saving exists. Do you want to overwrite it?"), 
			_T("Save file"), MB_YESNO | MB_ICONQUESTION) != IDYES )
			return;
	}

	// Save the Image by CImage
	if ( FAILED(rcImg.Save(szFilePath)) )
	{
		MessageBox(_T("Cannot save image file because System Problem!"), 
            _T("Save file error"), MB_OK|MB_ICONERROR);
		return;
	}
}


void CImageProcessDlg::OnUpdateToGray(CCmdUI *pCmdUI)
{
    // TODO: �b���[�J�z���R�O��s UI �B�z�`���{���X
    
}

// Transform the color image to gray image
void CImageProcessDlg::OnTogray()
{
	CImage& rcImg = cImgForLoading;
	if (rcImg.IsNull() || rcImg.GetBPP()==8) return;

	const int iImgHeight = rcImg.GetHeight();
	const int iImgWidth  = rcImg.GetWidth();

    // Bitmap will be changed, remove it from reference objects
    Image.SetBitmap(NULL);

    ARRAY2D<BYTE> aaTmpImg(iImgHeight, iImgWidth);

    bool bIs32Bits = (rcImg.GetBPP()==32);
    BYTE *dst, *src;

    // Caculate the gray levels
    dst = aaTmpImg.Get1DPtr();
	for (int h=0 ; h<iImgHeight ; ++h)
	{
		src = (BYTE*)rcImg.GetPixelAddress(0,h);
		for (int w=0 ; w<iImgWidth ; ++w)
		{
			BYTE& B  = (*src++);
			BYTE& G  = (*src++);
			BYTE& R  = (*src++);
            *dst++ = (BYTE)(0.114 * B + 0.587 * G + 0.299 * R + 0.5);
            if (bIs32Bits) ++src;
		}
	}


    // Change Bitmap
    rcImg.Destroy();
	if (FALSE == rcImg.CreateEx(iImgWidth, iImgHeight, 8, BI_RGB))
	{
		MessageBox(_T("Cannot create gray CImage!"));
		return;
	}

    // Set color table (If you forgot it, you will get a black image anyway.)
	RGBQUAD GrayPal[256];
    for(int i=0 ; i<256 ; ++i)
    {
        GrayPal[i].rgbBlue     = i;
		GrayPal[i].rgbGreen    = i;
		GrayPal[i].rgbRed      = i;
		GrayPal[i].rgbReserved = 0;
    }
	rcImg.SetColorTable(0, 256, GrayPal);

    // Set gray image data
    src = aaTmpImg.Get1DPtr();
	for (int h=0 ; h<iImgHeight ; ++h)
	{
		dst = (BYTE*)rcImg.GetPixelAddress(0,h);
        memcpy(dst, src, iImgWidth);
        src += iImgWidth;
	}

    Image.SetBitmap(rcImg);

	Invalidate(false);
}


void CImageProcessDlg::OnSobelEdge()
{
	CImage& rcImg = cImgForLoading;
	if (rcImg.IsNull()) return;

    // check the image bits
    if (8 != rcImg.GetBPP())
    {
        MessageBox(_T("Should apply ToGray() first."));
        return;
    }


    int Threshold = 60;

    /*
    CString InputString;
    InputString.Format("%d",Threshold);

    MInputBox inputer;
    //inputer.SetParms("Set Threshold=?", "Parameter Setting", InputString);
    if (IDOK != inputer.DoModal())
        return;

    //inputer.EditInput.SetSel()
    int inputlen = inputer.EditInput.LineLength(-1);
    if (inputlen > 0)
    {
        char* text = new char[inputlen];
        inputer.EditInput.GetLine(-1, text);
        Threshold = atoi(text);
        delete[] text;
    }
    else 
    {
        this->ErrorMessage("Should input somthing");
        return;
    }
    */
    
    int SquaredThreshold = Threshold*Threshold;

	const int iImgHeight = rcImg.GetHeight();
	const int iImgWidth  = rcImg.GetWidth();

    ARRAY2D<BYTE> aaGrayImg(iImgHeight, iImgWidth);
    ARRAY2D<BYTE> aaEdgeImg(iImgHeight, iImgWidth);

    // Copy image data to array
	for (int h=0 ; h<iImgHeight ; ++h)
	{
		BYTE* src = (BYTE*)rcImg.GetPixelAddress(0,h);
		for (int w=0 ; w<iImgWidth ; ++w) {
			aaGrayImg[h][w] = *src++;
		}
	}

    // Do Sobel
    for (int h=1 ; h<iImgHeight-1 ; ++h)
    for (int w=1 ; w<iImgWidth-1  ; ++w)
    {
        int iMag=0, iMagx, iMagy;
        iMagx = (aaGrayImg[h-1][w+1] - (int)aaGrayImg[h-1][w-1]) + 
                2*(aaGrayImg[h][w+1] - (int)aaGrayImg[h][w-1])   +
                (aaGrayImg[h+1][w+1] - (int)aaGrayImg[h+1][w-1]);
        iMagy = (aaGrayImg[h+1][w-1] - (int)aaGrayImg[h-1][w-1]) + 
                2*(aaGrayImg[h+1][w] - (int)aaGrayImg[h-1][w])   +
                (aaGrayImg[h+1][w+1] - (int)aaGrayImg[h-1][w+1]);
        iMag = iMagx*iMagx + iMagy*iMagy;
        if (SquaredThreshold < iMag)
            aaEdgeImg[h][w] = 255;
        else
            aaEdgeImg[h][w] = 0;
    }

   // Copy array to image data
	for (int h=0 ; h<iImgHeight ; ++h)
	{
		BYTE* src = (BYTE*)rcImg.GetPixelAddress(0,h);
		for (int w=0 ; w<iImgWidth ; ++w) {
			*src++ = aaEdgeImg[h][w];
		}
	}

	Invalidate(false);
}
