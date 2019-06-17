// CaculateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Caculate.h"
#include "CaculateDlg.h"
#include "stdlib.h"
#include "math.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
double num1=0.0;
double num2=0.0;
bool if_num1=false;
bool if_point=false;
int order=0;
void caculation(int od)
{
	if(od==1)
	{
		num1=num1+num2;
	}
	else if(od==2)
	{
		num1=num1-num2;
	}
	else if(od==3)
	{
		num1=num1*num2;
	}
	else if(od==4)
	{
		num1=num1/num2;
	}
	od=0;
}
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaculateDlg dialog

CCaculateDlg::CCaculateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCaculateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCaculateDlg)
	m_result = _T("");
	m_num = 0.0;
	m_rule = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCaculateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCaculateDlg)
	DDX_Text(pDX, IDC_EDIT1, m_result);
	DDV_MaxChars(pDX, m_result, 32);
	DDX_Text(pDX, IDC_EDIT2, m_num);
	DDX_Text(pDX, IDC_EDIT3, m_rule);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCaculateDlg, CDialog)
	//{{AFX_MSG_MAP(CCaculateDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON10, OnButton0)
	ON_BN_CLICKED(IDC_BUTTON11, OnPoint)
	ON_BN_CLICKED(IDC_BUTTON12, OnEqual)
	ON_BN_CLICKED(IDC_BUTTON13, OnAdd)
	ON_BN_CLICKED(IDC_BUTTON14, OnSub)
	ON_BN_CLICKED(IDC_BUTTON15, OnMult)
	ON_BN_CLICKED(IDC_BUTTON16, OnDiv)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON17, OnClean)
	ON_BN_CLICKED(IDC_BUTTON18, OnBackWard)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaculateDlg message handlers

BOOL CCaculateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCaculateDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCaculateDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCaculateDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCaculateDlg::OnPoint() 
{
	// TODO: Add your control notification handler code here
	if(!if_point)
	{
		UpdateData(TRUE);
		m_result+='.';
		UpdateData(FALSE);
		if_point=true;
	}
}

void CCaculateDlg::OnEqual() 
{
	// TODO: Add your control notification handler code here
	if(if_num1)
	{
		UpdateData(TRUE);
		num2=atof(m_result);
		caculation(order);
		m_result.Format(_T("%lf"),num1);
		UpdateData(FALSE);
		order=0;
		m_rule="";
	}
}
void CCaculateDlg::OnAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if_num1=true;
	if(m_result!="")num1=atof(m_result);
	m_num=num1;
	m_result="";
	m_rule="+";
	UpdateData(FALSE);
	order=1;
	if_point=false;
}

void CCaculateDlg::OnSub() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if_num1=true;
	if(m_result!="")num1=atof(m_result);
	m_num=num1;
	m_result="";
	m_rule="-";
	UpdateData(FALSE);
	order=2;
	if_point=false;
}

void CCaculateDlg::OnMult() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if_num1=true;
	if(m_result!="")num1=atof(m_result);
	m_num=num1;
	m_result="";
	m_rule="¡Á";
	UpdateData(FALSE);
	order=3;
	if_point=false;
}

void CCaculateDlg::OnDiv() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if_num1=true;
	if(m_result!="")num1=atof(m_result);
	m_num=num1;
	m_result="";
	m_rule="¡Â";
	UpdateData(FALSE);
	order=4;
	if_point=false;
}

void CCaculateDlg::OnButton0() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_result+='0';
	UpdateData(FALSE);
}

void CCaculateDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_result+='1';
	UpdateData(FALSE);
}

void CCaculateDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_result+='2';
	UpdateData(FALSE);
}

void CCaculateDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_result+='3';
	UpdateData(FALSE);
}

void CCaculateDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_result+='4';
	UpdateData(FALSE);
}

void CCaculateDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_result+='5';
	UpdateData(FALSE);	
}

void CCaculateDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_result+='6';
	UpdateData(FALSE);	
}

void CCaculateDlg::OnButton7() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_result+='7';
	UpdateData(FALSE);
}

void CCaculateDlg::OnButton8() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_result+='8';
	UpdateData(FALSE);
}

void CCaculateDlg::OnButton9() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_result+='9';
	UpdateData(FALSE);
}

void CCaculateDlg::OnClean() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_result="";
	num1=0.0;
	num2=0.0;
	m_num=0;
	if_num1=false;
	if_point=true;
	UpdateData(FALSE);
}

void CCaculateDlg::OnBackWard() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_result.Delete(m_result.GetLength()-1);
	UpdateData(FALSE);
}

void CCaculateDlg::OnChangeEdit2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
