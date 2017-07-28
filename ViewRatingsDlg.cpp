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
// ViewRatingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "eloRater.h"
#include "ViewRatingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewRatingsDlg dialog


CViewRatingsDlg::CViewRatingsDlg()
	: CDialog()
{
	//{{AFX_DATA_INIT(CViewRatingsDlg)
	m_sortBy = -1;
	m_ascend = -1;
	//}}AFX_DATA_INIT
	m_group = NULL;
}


void CViewRatingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewRatingsDlg)
	DDX_Radio(pDX, IDC_RADIONAME, m_sortBy);
	DDX_Radio(pDX, IDC_RADIOASC, m_ascend);
	DDX_Control(pDX, IDC_PLAYERS, m_output);
	DDX_Control(pDX, IDC_RADIONAME, m_radioName);
	DDX_Control(pDX, IDC_RADIORATING, m_radioRating);
	DDX_Control(pDX, IDC_RADIOASC, m_radioAsc);
	DDX_Control(pDX, IDC_RADIODESC, m_radioDesc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewRatingsDlg, CDialog)
	//{{AFX_MSG_MAP(CViewRatingsDlg)
	ON_BN_CLICKED(ID_COMPUTE, OnCompute)
	ON_BN_CLICKED(ID_PRINT, OnPrint)
	ON_BN_CLICKED(IDC_RADIONAME, OnChangeSort)
	ON_BN_CLICKED(IDC_RADIORATING, OnChangeSort)
	ON_BN_CLICKED(IDC_RADIOASC, OnChangeDir)
	ON_BN_CLICKED(IDC_RADIODESC, OnChangeDir)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_CSV, &CViewRatingsDlg::OnCSV)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewRatingsDlg message handlers

BOOL CViewRatingsDlg::Create(CWnd* pParentWnd)
{
	return CDialog::Create(IDD, pParentWnd);
}

void CViewRatingsDlg::SetDefaultTab()
{

	this->GetDlgItem(IDC_RADIONAME)->SetFocus();
}


void CViewRatingsDlg::OnCompute() 
{
	MessageBox("Batch ratings computation not implemented yet.","NOTE",
		MB_ICONINFORMATION|MB_OK);
}

void CViewRatingsDlg::OnPrint() 
{
	MessageBox("Print capability not implemented yet.","NOTE",
		MB_ICONINFORMATION|MB_OK);
}

void CViewRatingsDlg::LoadData()
{
	if (m_group)
	{
		m_output.ResetContent();
		POSITION pos = m_group->GetFirstPlayerHandle();
		while (pos)
		{
			CPlayer::SetSort(m_sortBy);
			CPlayer player = m_group->GetPlayer(pos);
			CString addThis;
			if (m_sortBy < 1)
			{
				//sorting by name... list name first
				if (   (player.get_numGames() < 25) 
					&& (m_group->get_useHarkness() == false)   )
					addThis.Format("%s\t%d*",
						player.get_name(),
						player.get_rating());
				else
					addThis.Format("%s\t%d",
						player.get_name(),
						player.get_rating());
			}
			else
			{
				//sorting by rating... list rating first!
				if (   (player.get_numGames() < 25) 
					&& (m_group->get_useHarkness() == false)   )
					addThis.Format("%d*\t%s",
						player.get_rating(),
						player.get_name());
				else
					addThis.Format("%d\t%s",
						player.get_rating(),
						player.get_name());
			}
			int count = m_output.GetCount();
			if (count == 0)
			{
 			    int sel = m_output.AddString(addThis);
				m_output.SetItemDataPtr(sel, pos);
			}
			else
			{
				bool done = false;
				int low = 0;
				int high = count -1;
				int insertHere = 0;
				while (!done)
				{
					if (low > high)
					{
						done = true;
						insertHere = low;
					}
					else
					{
						int mid = (high + low)/2;
						POSITION testPos = (POSITION)m_output.GetItemDataPtr(mid);
						CPlayer testP = m_group->GetPlayer(testPos);
						//players can not be equal...
						if (m_ascend < 1)
						{
							if (testP > player)
							{
								high = mid - 1;
							}
							else
							{
								low = mid + 1;
							}
						}
						else
						{
							if (testP < player)
							{
								high = mid - 1;
							}
							else
							{
								low = mid + 1;
							}
						}
					}
				}
 				int sel = m_output.InsertString(insertHere,addThis);
				m_output.SetItemDataPtr(sel, pos);
			}
			pos = m_group->GetNextPlayerHandle(pos);
		}
	}
}

void CViewRatingsDlg::LoadGroup(CGroup* group)
{
	m_group = group;

	//load group data list...
	if (m_group != 0)
	{
		m_radioName.SetCheck(false);
		m_radioRating.SetCheck(true);
		m_sortBy = 1;
		m_radioAsc.SetCheck(true);
		m_radioDesc.SetCheck(false);
		m_ascend = 1;
		m_radioRating.EnableWindow(true);
		m_radioName.EnableWindow(true);
		m_radioAsc.EnableWindow(true);
		m_radioDesc.EnableWindow(true);
		LoadData();
		UpdateData(FALSE);	
	}
	else
	{
		m_radioRating.EnableWindow(false);
		m_radioName.EnableWindow(false);
		m_sortBy = -1;
		m_radioAsc.EnableWindow(false);
		m_radioDesc.EnableWindow(false);
		m_ascend = -1;
		m_output.ResetContent();
		m_group = NULL;
		UpdateData(FALSE);
	}
}

void CViewRatingsDlg::UnloadGroup()
{
	//unload the group data...
	m_radioRating.EnableWindow(false);
	m_radioName.EnableWindow(false);
	m_sortBy = -1;
	m_radioAsc.EnableWindow(false);
	m_radioDesc.EnableWindow(false);
	m_ascend = -1;
	m_output.ResetContent();
	m_group = NULL;
}

BOOL CViewRatingsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int stops[2];
	stops[0] = 30;
	stops[1] = 150;
	m_output.SetTabStops(2,stops);
    UpdateData(FALSE);
	return TRUE;  
}

void CViewRatingsDlg::OnChangeSort() 
{
	UpdateData(TRUE);
	LoadData();
}

void CViewRatingsDlg::OnChangeDir() 
{
	UpdateData(TRUE);
	LoadData();
}

void CViewRatingsDlg::OnCSV()
{
	if (m_group)
	{
		FILE *fout;
		CString csvname = m_group->get_name();
		csvname.Append(".csv");
		fout = fopen((LPCSTR) csvname,"wt");

		fprintf(fout,"ID;FirstName;LastName;Rating;Games;RatingHighest;Wins;RatingInitial\n");

		POSITION pos = m_group->GetFirstPlayerHandle();
		while (pos)
		{
			CPlayer::SetSort(m_sortBy);
			CPlayer player = m_group->GetPlayer(pos);
			CString addThis;

			addThis.Format("%d,%s,%s,%d,%d,%d,%d,%d",	
				player.get_ID(), 
				player.get_firstName(), 
				player.get_lastName(),
				player.get_rating(),
				player.get_numGames(),
				player.get_highest(),
				player.get_rawScore(),
				player.get_initial());

			fprintf(fout, "%s\n", addThis);

			pos = m_group->GetNextPlayerHandle(pos);
		}

		fclose(fout);
	}
}
