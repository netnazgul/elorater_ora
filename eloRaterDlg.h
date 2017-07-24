/*****************************************************************************\
*                                                                             *
*    EEEEEE  L        OOOO          RRRRR                                     *
*    E    E  L       O    O         R    R            t                       *
*    E       L       O    O         R    R    aaa     t      eeee   r rrr     *
*    EEEE    L       O    O         RRRRR        a  tttttt  e    e  rr   r    *
*    E       L       O    O         R  R     aaa a    t     eeeeee  r         *
*    E    E  L    L  O    O         R   R   a   aa    t     e       r         *
*    EEEEEE  LLLLLL   OOOO          R    R   aaa a    ttt    eeeee  r         *
*                                                                             *
*                                                                             *
*******************************************************************************
*                                                                             *
*        ELO Rater is a Club Rating Utility Program, designed to automate     *
*        implementing a USCF style, or Harkness style Rating system for       *
*        small chess clubs or groups.                                         *
*                                                                             *
*                    Copyright (C)2001 - 2006  James Garner                   *
*                                                                             *
*******************************************************************************
*                                                                             *
*       This program is free software; you can redistribute it and/or         *
*       modify it under the terms of the 2nd version of the GNU General       *
*       Public License as published by the Free Software Foundation.          *
*                                                                             *
*       This program is distributed in the hope that it will be useful,       *
*       but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See copy        *
*       of the GNU General Public License included with the source code       *
*       for more information.                                                 *
*                                                                             *
*       If you have any questions regarding this program or the source,       *
*       contact the author through e-mail at: james_k_garner@yahoo.com,       *
*       listing ELO Rater in the subject text or through regular mail at      *
*       2625 Burkelaun Dr. Montgomery, Alabmam (U.S.A)                        *
*                                                                             *
\*****************************************************************************/


#if !defined(AFX_WLCLRATERDLG_H__6FE750B9_988E_11D5_ADFC_00C04F6DD93E__INCLUDED_)
#define AFX_WLCLRATERDLG_H__6FE750B9_988E_11D5_ADFC_00C04F6DD93E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEloRaterDlg dialog

#include "AboutDlg.h"
#include "AddGameDlg.h"
#include "AddGroupDlg.h"
#include "AddPlayerDlg.h"
#include "ViewRatingsDlg.h"
#include "group.h"

class CEloRaterDlg : public CDialog
{
// Construction
public:
	CEloRaterDlg(CWnd* pParent = NULL);	// standard constructor
	void SetName(CString name){m_name = name;}
	void SetPath(CString path){m_path = path;}
    void SetGroup(CGroup *group);
	bool NewGroup(CString name, bool useHarkness);
	bool LoadGroup(CString name);
	void UnloadGroup();
	void ReloadGroup();
	void ShowChildren();

	// Dialog Data
	//{{AFX_DATA(CEloRaterDlg)
	enum { IDD = IDD_ELORATER_DIALOG };
	CTabCtrl	m_jobTabControl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEloRaterDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEloRaterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeJobtab(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	void SetTabIcon(int tab, bool enabled);
	DECLARE_MESSAGE_MAP();

    CAboutDlg       *m_aboutDlg;
	CAddGameDlg     *m_addGameDlg;
	CAddGroupDlg    *m_addGroupDlg;
	CAddPlayerDlg   *m_addPlayerDlg;
	CViewRatingsDlg *m_viewRatingsDlg;
	CGroup          *m_group;
	CString         m_name;
	CString         m_path;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WLCLRATERDLG_H__6FE750B9_988E_11D5_ADFC_00C04F6DD93E__INCLUDED_)
