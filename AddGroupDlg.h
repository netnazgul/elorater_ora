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
#ifndef AFX_ADDGROUPDLG_H__6FE750B9_988E_11D5_ADFC_00C04F6DD93E__INCLUDED_
#define AFX_ADDGROUPDLG_H__6FE750B9_988E_11D5_ADFC_00C04F6DD93E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma once

#include "resource.h"
#include "group.h"

// CAddGroupDlg dialog

class CAddGroupDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddGroupDlg)

public:
	CAddGroupDlg();
	BOOL Create(CWnd* pParentWnd);
	void SetPath(CString path){m_path = path;}
	virtual ~CAddGroupDlg();
	void SetDefaultTab();
	void LoadGroup(CGroup* group);
	void UnloadGroup();

// Dialog Data
	enum { IDD = IDD_ADDCLUB };
	CString m_name;
	CEdit m_editName;
	CButton m_radioHarkness;
	CButton m_radioUSCF;
	CButton m_btnAdd;
	CButton m_btnClear;
	CButton m_btnDelete;
	CButton m_btnLoad;
	CListBox m_clubList;
	CGroup *m_group;
	CString m_path;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void ClearEditControls();
	void EnableViewExisting();
	void EnableNameEntryOnly();
	void EnableForEdit();
	void LoadGroupList();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadioUscf();
	afx_msg void OnBnClickedRadioHarkness();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedLoad();
	afx_msg void OnLbnSelchangeClublist();
	afx_msg void OnEnKillfocusNameedit();
public:
	afx_msg void OnEnChangeNameedit();
public:
	afx_msg void OnBnClickedChangedir();
};
#endif //AFX_ADDGROUPDLG_H__6FE750B9_988E_11D5_ADFC_00C04F6DD93E__INCLUDED_