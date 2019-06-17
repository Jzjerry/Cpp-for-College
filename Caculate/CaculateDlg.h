// CaculateDlg.h : header file
//

#if !defined(AFX_CACULATEDLG_H__15147C55_1233_419F_BA97_4D2A074836E5__INCLUDED_)
#define AFX_CACULATEDLG_H__15147C55_1233_419F_BA97_4D2A074836E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCaculateDlg dialog

class CCaculateDlg : public CDialog
{
// Construction
public:
	CCaculateDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCaculateDlg)
	enum { IDD = IDD_CACULATE_DIALOG };
	CString	m_result;
	double	m_num;
	CString	m_rule;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCaculateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCaculateDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton0();
	afx_msg void OnPoint();
	afx_msg void OnEqual();
	afx_msg void OnAdd();
	afx_msg void OnSub();
	afx_msg void OnMult();
	afx_msg void OnDiv();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnClean();
	afx_msg void OnBackWard();
	afx_msg void OnChangeEdit2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CACULATEDLG_H__15147C55_1233_419F_BA97_4D2A074836E5__INCLUDED_)
