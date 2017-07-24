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
// AddGroupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "eloRater.h"
#include "eloRaterDLg.h"
#include "AddGroupDlg.h"


// CAddGroupDlg dialog

IMPLEMENT_DYNAMIC(CAddGroupDlg, CDialog)
CAddGroupDlg::CAddGroupDlg()
	: CDialog()
{
	m_group = NULL;
}

CAddGroupDlg::~CAddGroupDlg()
{
	m_group = NULL;
}

void CAddGroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NAMEEDIT, m_editName);
	DDX_Control(pDX, IDC_RADIO_USCF, m_radioUSCF);
	DDX_Control(pDX, IDC_RADIO_HARKNESS, m_radioHarkness);
	DDX_Control(pDX, IDC_CLUBLIST, m_clubList);
	DDX_Control(pDX, ID_ADD, m_btnAdd);
	DDX_Control(pDX, ID_CLEAR, m_btnClear);
	DDX_Control(pDX, ID_LOAD, m_btnLoad);
	DDX_Control(pDX, ID_DELETE, m_btnDelete);
	DDX_Text(pDX, IDC_NAMEEDIT, m_name);
}

BEGIN_MESSAGE_MAP(CAddGroupDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO_USCF, OnBnClickedRadioUscf)
	ON_BN_CLICKED(IDC_RADIO_HARKNESS, OnBnClickedRadioHarkness)
	ON_BN_CLICKED(ID_ADD, OnBnClickedAdd)
	ON_BN_CLICKED(ID_CLEAR, OnBnClickedClear)
	ON_BN_CLICKED(ID_LOAD, OnBnClickedLoad)
	ON_BN_CLICKED(ID_DELETE, OnBnClickedDelete)
	ON_LBN_SELCHANGE(IDC_CLUBLIST, OnLbnSelchangeClublist)
	ON_EN_KILLFOCUS(IDC_NAMEEDIT, OnEnKillfocusNameedit)
	ON_EN_CHANGE(IDC_NAMEEDIT, &CAddGroupDlg::OnEnChangeNameedit)
	ON_BN_CLICKED(ID_CHANGEDIR, &CAddGroupDlg::OnBnClickedChangedir)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAddGroupDlg message handlers

BOOL CAddGroupDlg::Create(CWnd* pParentWnd) 
{
	BOOL retVal = CDialog::Create(IDD, pParentWnd);
	if (retVal)
	{
		this->ClearEditControls();
		this->EnableNameEntryOnly();
		this->LoadGroupList();
	}
	return retVal;
}

void CAddGroupDlg::LoadGroupList()
{
	this->m_clubList.ResetContent();
	CString wildCard = m_path+"*.elo";
	this->m_clubList.Dir(DDL_READWRITE, wildCard);
	int count = this->m_clubList.GetCount();
	int i = 0;
	while (i < count)
	{
		CString fileName;
		m_clubList.GetText(i, fileName);
		m_clubList.DeleteString(i);
		m_clubList.InsertString(i, fileName.Left( fileName.GetLength()-4 ));
		i++;
	}
	UpdateData(FALSE);
}

void CAddGroupDlg::ClearEditControls()
{
	m_radioUSCF.SetCheck(false);
	m_radioHarkness.SetCheck(false);
	m_name = "";
	UpdateData(FALSE);
}

void CAddGroupDlg::EnableViewExisting()
{
	m_editName.EnableWindow(false);
	m_radioUSCF.EnableWindow(false);
	m_radioHarkness.EnableWindow(false);
	m_btnAdd.EnableWindow(false);
	m_btnDelete.EnableWindow(true);
	m_btnClear.EnableWindow(true);
	m_clubList.EnableWindow(true);
	if (m_group)
	{
		m_btnLoad.EnableWindow((m_group->get_name() != m_name));
	}
	else
	{
		if (m_name.GetLength() > 0)
		{
			m_btnLoad.EnableWindow((m_clubList.FindString(0,m_name) > -1));
		}
		else
		{
			m_btnLoad.EnableWindow(false);
		}
	}
}

void CAddGroupDlg::EnableNameEntryOnly()
{
	m_editName.EnableWindow(true);
	m_radioUSCF.EnableWindow(false);
	m_radioHarkness.EnableWindow(false);
	m_btnAdd.EnableWindow(false);
	m_btnDelete.EnableWindow(false);
	m_btnClear.EnableWindow(true);
	m_clubList.EnableWindow(true);
	m_btnLoad.EnableWindow(false);
}

void CAddGroupDlg::EnableForEdit()
{
	m_editName.EnableWindow(true);
	m_radioUSCF.EnableWindow(true);
	m_radioHarkness.EnableWindow(true);
	m_btnAdd.EnableWindow(true);
	m_btnDelete.EnableWindow(false);
	m_btnClear.EnableWindow(true);
	m_clubList.EnableWindow(true);
	m_btnLoad.EnableWindow(false);
}


void CAddGroupDlg::LoadGroup(CGroup* group)
{
	m_group = group;

	//load group data list...
	if (m_group != 0)
	{
		m_radioHarkness.SetCheck(m_group->get_useHarkness());
		m_radioUSCF.SetCheck(!(m_group->get_useHarkness()));
		CString longName = m_group->get_name();
		if (longName.Find(m_path,0) > -1)
		{
			m_name = longName.Right(longName.GetLength() - m_path.GetLength());
		}
		else
		{
			m_name = longName;
		}
		this->EnableViewExisting();
		UpdateData(FALSE);
	}
	else
	{
		this->ClearEditControls();
		this->EnableNameEntryOnly();
	}
}

void CAddGroupDlg::UnloadGroup()
{
	//unload the group data...
	this->ClearEditControls();
	this->EnableNameEntryOnly();
	m_group = NULL;
}

void CAddGroupDlg::SetDefaultTab()
{
	if (m_group)
	{
		m_clubList.SetFocus();
	}
	else
	{
		m_editName.SetFocus();
	}
}


void CAddGroupDlg::OnBnClickedRadioUscf()
{
	UpdateData(TRUE);
	this->m_radioHarkness.SetCheck(false);
	this->m_radioUSCF.SetCheck(true);
	UpdateData(FALSE);
}

void CAddGroupDlg::OnBnClickedRadioHarkness()
{
	UpdateData(TRUE);
	this->m_radioHarkness.SetCheck(true);
	this->m_radioUSCF.SetCheck(false);
	UpdateData(FALSE);
}

void CAddGroupDlg::OnBnClickedAdd()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_name.GetLength() > 0)
	{
		if (m_clubList.FindString(0,m_name) < 0)
		{
			CString name = m_name;
			bool useHarkness = this->m_radioHarkness.GetCheck();
			CEloRaterDlg* pParent = (CEloRaterDlg*)GetParent();
			this->ClearEditControls();
			if (m_group)
			{
				//disconecnt the current group object...
				pParent->UnloadGroup();
			}

			//load the new grup object...
			if (pParent->NewGroup(name, useHarkness))
			{
				this->m_clubList.AddString(m_name);
				this->EnableViewExisting();
			}
			else
			{
				//failed to load new group object...
				this->EnableNameEntryOnly();
			}
		}
		else
		{
			MessageBox("Another group with the name requested\n"
				       "already exists.  Please enter a new name\n"
					   "and press Add again.",
					   "Duplicate Group", MB_ICONINFORMATION);
		}
	}
	else
	{
		this->ClearEditControls();
		this->EnableNameEntryOnly();
	}
}

void CAddGroupDlg::OnBnClickedDelete()
{
	//delete the group data file...
	MessageBox("Automatic delete is not implemeted at this time.\n"
			    "To delete a club's rating, and remove the data,\n"
				"first, exit this program comletely.\n"
				"second, find ELORater.exe in your files system and\n"
				"third, locate the .elo file whose name matches\n"
				"the club you wish to delete (club-name.elo).  \n"
				"finally, delete the elo file (club-name.elo)\n"
				"You may then restart the ELO Rater program.",
				"Delete Group", MB_ICONINFORMATION);
	//TODO: implement the automatic deletion logic...
}

void CAddGroupDlg::OnBnClickedClear()
{
	this->ClearEditControls();
	if (m_group)
	{
		//disconect the current group object...
		CEloRaterDlg* pParent = (CEloRaterDlg*)GetParent();
		pParent->UnloadGroup();
	}
	this->EnableNameEntryOnly();
}

void CAddGroupDlg::OnLbnSelchangeClublist()
{
	UpdateData(TRUE);
	int sel = m_clubList.GetCurSel();
	if (sel > -1)
	{
		this->ClearEditControls();
		m_clubList.GetText(sel,m_name);
		this->EnableViewExisting();
		this->m_radioHarkness.SetCheck(false);
		this->m_radioUSCF.SetCheck(false);
		UpdateData(FALSE);
	}
}

void CAddGroupDlg::OnBnClickedLoad()
{
	if (m_name.GetLength() > 0)
	{
		CString name = m_name;
		CEloRaterDlg* pParent = (CEloRaterDlg*)GetParent();
		this->ClearEditControls();
		if (m_group)
		{
			//disconect the current group object...
			pParent->UnloadGroup();
		}

		//load the new grup object...
		CString fileName = m_path+name;
		if (pParent->LoadGroup(fileName))
		{
			this->EnableViewExisting();
		}
		else
		{
			//failed to load new group object...
			this->ClearEditControls();
			this->EnableNameEntryOnly();
		}
	}
	else
	{
		this->ClearEditControls();
		this->EnableNameEntryOnly();
	}
}

void CAddGroupDlg::OnEnKillfocusNameedit()
{
	UpdateData(true);
	if (m_name.GetLength() > 0)
	{
		//something types into name field...
		if (m_clubList.FindString(0, m_name) > -1)
		{
			//club already exists... do not enable controls
			MessageBox("A club exists with the specified name.\n"
				       "Enter a new name to add a new club, or\n"
					   "Select on the club from the list to the\n"
					   "right to view its informations.", 
					   "Duplicate Club");
			this->ClearEditControls();
			this->EnableNameEntryOnly();
		}
		else
		{
			//possible new club name...
			this->EnableForEdit();
			m_radioUSCF.SetCheck(true);
			UpdateData(FALSE);
		}
	}
}

void CAddGroupDlg::OnEnChangeNameedit()
{
	UpdateData(true);
	if (m_name.GetLength() > 0)
	{
		//something types into name field...
		if (m_clubList.FindString(0, m_name) < 0)
		{
			//possible new club name...
			this->EnableForEdit();
			m_radioUSCF.SetCheck(true);
			UpdateData(FALSE);
		}
	}
}

void CAddGroupDlg::OnBnClickedChangedir()
{
	char dispName[1024];
	char path[1024];
	BROWSEINFO info;
	info.hwndOwner = this->m_hWnd;
	info.ulFlags = BIF_RETURNONLYFSDIRS;
	info.pszDisplayName = dispName;
	info.lpszTitle = "Select Data Directory...";
	info.iImage = 0;
	info.lParam = 0;
	info.lpfn = 0;
	info.pidlRoot = 0;
	LPITEMIDLIST item = ::SHBrowseForFolder(&info);
	if (item != NULL)
	{
		::SHGetPathFromIDList(item,path);
		CString pathName(path);
		m_path = pathName + "\\";
		CEloRaterDlg* pParent = (CEloRaterDlg*)GetParent();
		pParent->SetPath(m_path);
		LoadGroupList();
	}
}

