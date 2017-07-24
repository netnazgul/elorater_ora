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
#if !defined(AFX_ADDGAMEDLG_H__6FE750C2_988E_11D5_ADFC_00C04F6DD93E__INCLUDED_)
#define AFX_ADDGAMEDLG_H__6FE750C2_988E_11D5_ADFC_00C04F6DD93E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddGameDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddGameDlg dialog
#include "resource.h"
#include "group.h"

class CAddGameDlg : public CDialog
{
// Construction
public:
	CAddGameDlg();   // standard constructor
	BOOL Create(CWnd* pParentWnd);
	void SetDefaultTab();
	void LoadData();
	void LoadGroup(CGroup* group);
	void UnloadGroup();
	void ClearPlayerLists();

// Dialog Data
	//{{AFX_DATA(CAddGameDlg)
	CButton     m_btnAdd;
	CButton     m_btnClear;
	CComboBox	m_resultCombo;
	CComboBox	m_whiteCombo;
	CComboBox	m_blackCombo;
	CListBox    m_gameList;
	CWnd        m_dateCtrl;
	CWnd        m_timeCtrl;
	CTime	    m_date;
	CTime	    m_time;
	//}}AFX_DATA
	CTime   m_refTime;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddGameDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddGameDlg)
	afx_msg void OnAdd();
	afx_msg void OnClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CGroup* m_group;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDGAMEDLG_H__6FE750C2_988E_11D5_ADFC_00C04F6DD93E__INCLUDED_)
