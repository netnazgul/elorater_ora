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
#if !defined(AFX_VIEWRATINGSDLG_H__6FE750C4_988E_11D5_ADFC_00C04F6DD93E__INCLUDED_)
#define AFX_VIEWRATINGSDLG_H__6FE750C4_988E_11D5_ADFC_00C04F6DD93E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewRatingsDlg.h : header file
//
#include "resource.h"
#include "group.h"

/////////////////////////////////////////////////////////////////////////////
// CViewRatingsDlg dialog

class CViewRatingsDlg : public CDialog
{
// Construction
public:
	CViewRatingsDlg();
	BOOL Create(CWnd* pParentWnd);
	void SetDefaultTab();
	void LoadData();
	void LoadGroup(CGroup* group);
	void UnloadGroup();

// Dialog Data
	//{{AFX_DATA(CViewRatingsDlg)
	enum { IDD = IDD_RATINGS };
	int		    m_sortBy;
	int         m_ascend;
	CListBox	m_output;
	CButton     m_radioName;
	CButton     m_radioRating;
	CButton     m_radioAsc;
	CButton     m_radioDesc;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewRatingsDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewRatingsDlg)
	afx_msg void OnCompute();
	afx_msg void OnPrint();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeSort();
	afx_msg void OnChangeDir();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CGroup* m_group;
public:
	afx_msg void OnCSV();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWRATINGSDLG_H__6FE750C4_988E_11D5_ADFC_00C04F6DD93E__INCLUDED_)
