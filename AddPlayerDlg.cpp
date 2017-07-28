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
// AddPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "eloRater.h"
#include "addPlayerDlg.h"
#include "eloRaterDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddPlayerDlg dialog


CAddPlayerDlg::CAddPlayerDlg()
	: CDialog()
{
	//{{AFX_DATA_INIT(CAddPlayerDlg)
	m_firstName = _T("");
	m_lastName = _T("");
	//}}AFX_DATA_INIT
	m_group  = 0;
	m_rating = 1300;	//default rating for adults
	useAdult = false;
	useChild = false;
	useLevel = false;
	useUSCF  = false;
}


void CAddPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO_CHILD, m_radioChild);
	DDX_Control(pDX, IDC_RADIO_ADULT, m_radioAdult);
	DDX_Control(pDX, IDC_RADIO_LEVEL, m_radioLevel);
	DDX_Control(pDX, IDC_RADIO_RATING, m_radioUSCF);
	DDX_Control(pDX, IDC_PLAYERLIST, m_playerList);
	DDX_Control(pDX, IDC_LEVEL, m_levelCombo);
	DDX_Control(pDX, IDC_AGE, m_ageCombo);
	DDX_Control(pDX, IDC_FIRSTEDIT, m_firstEdit);
	DDX_Text(pDX, IDC_FIRSTEDIT, m_firstName);
	DDX_Text(pDX, IDC_LASTEDIT, m_lastName);
}


BEGIN_MESSAGE_MAP(CAddPlayerDlg, CDialog)
	ON_BN_CLICKED(ID_ADD, OnAdd)
	ON_BN_CLICKED(ID_CLEAR, OnClear)
	ON_CBN_SELCHANGE(IDC_LEVEL, OnLevelSelchangeLevel)
	ON_CBN_SELCHANGE(IDC_AGE, OnCbnSelchangeAge)
	ON_EN_KILLFOCUS(IDC_USCF, OnEnKillfocusUscf)
	ON_BN_CLICKED(IDC_RADIO_LEVEL, OnBnClickedRadioLevel)
	ON_BN_CLICKED(IDC_RADIO_RATING, OnBnClickedRadioRating)
	ON_BN_CLICKED(IDC_RADIO_ADULT, OnBnClickedRadioAdult)
	ON_BN_CLICKED(IDC_RADIO_CHILD, OnBnClickedRadioChild)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddPlayerDlg message handlers

BOOL CAddPlayerDlg::Create(CWnd* pParentWnd) 
{
	BOOL retVal = CDialog::Create(IDD, pParentWnd);
	if (retVal)
	{
		m_radioChild.SetCheck(false);
		m_radioAdult.SetCheck(false);
		m_radioLevel.SetCheck(false);
		m_radioUSCF.SetCheck(false);
		UpdateData(FALSE);
	}
	return retVal;
}




void CAddPlayerDlg::LoadGroup(CGroup* group)
{
	m_group = group;

	//load group data list...
	if (m_group != 0)
	{
		////load player list...
		m_playerList.ResetContent();
		POSITION pos = m_group->GetFirstPlayerHandle();
		while (pos)
		{
			CPlayer player = m_group->GetPlayer(pos);
			CString addThis;
			addThis.Format("%s, %s",
				player.get_lastName(),
				player.get_firstName());
			m_playerList.AddString(addThis);
			pos = m_group->GetNextPlayerHandle(pos);
		}
		this->useAdult = false;
		this->useChild = false;
		this->useLevel = false;
		this->useUSCF = false;
		EnableRatingCtrls();
	}
	else
	{
		m_playerList.ResetContent();
		OnClear();
	}
}

void CAddPlayerDlg::UnloadGroup()
{
	//unload the group data...
	m_playerList.ResetContent();
	OnClear();
	m_group = NULL;
}

void CAddPlayerDlg::SetDefaultTab()
{
	if (m_group)
	{
		m_firstEdit.SetFocus();
	}
	else
	{
		m_playerList.SetFocus();
	}
}

void CAddPlayerDlg::OnAdd() 
{
	CString msg;
	UpdateData(TRUE);
	if (m_group)
	{

		bool playerexists;
		POSITION playerpos = m_group->GetFirstPlayerHandle();
		while (playerpos)
		{
			CPlayer player = m_group->GetPlayer(playerpos);
		
			if (m_firstName == player.get_firstName() &&
				m_lastName == player.get_lastName()
				)
			{
				playerexists = true;
				break;
			}

			playerpos = m_group->GetNextPlayerHandle(playerpos);
		}

		if (!m_lastName.GetLength() && !m_firstName.GetLength())
		{
			//cannot add empty name
			msg.Format("Can not add player to the group.\n"
				"Name is empty.");
			MessageBox(msg,"Error", MB_ICONINFORMATION | MB_OK);		
		}
		else if (playerexists)
		{
			//duplicate entry found... can not add it
			msg.Format("Can not add %s %s to the group.\n"
				"That name already exists in the group.", m_firstName, m_lastName);
			MessageBox(msg,"Error", MB_ICONINFORMATION | MB_OK);		
		}
		else
		{
			msg.Format("Please confirm the addition of %s %s\n"
                       "with an initial  rating of %d\n"
					   "to the group: %s.\n"
						"Press OK to accept or Cancel to abort.",
					   m_firstName, m_lastName, m_rating, m_group->get_name());
			if (IDOK == MessageBox(msg, "Confirm Addition", MB_OKCANCEL))
			{
				//no record found... add it
				CPlayer newPlayer;
				newPlayer.set_firstName(m_firstName);
				newPlayer.set_lastName(m_lastName);
				newPlayer.set_rating(m_rating); 
				newPlayer.set_highest(m_rating);
                newPlayer.set_initial(m_rating);
				newPlayer.set_numGames(0);
				newPlayer.set_rawScore(0);
				m_group->AddPlayer(newPlayer);
				CEloRaterDlg* pParent = (CEloRaterDlg*)GetParent();
				pParent->ReloadGroup();
			}
		}
	}
}

void CAddPlayerDlg::OnClear() 
{
	m_firstName = "";
	m_lastName = "";
	m_radioChild.SetCheck(false);
	m_radioAdult.SetCheck(false);
	m_radioLevel.SetCheck(false);
	m_radioUSCF.SetCheck(false);
	UpdateData(FALSE);	

	this->useAdult = false;
	this->useChild = false;
	this->useLevel = false;
	this->useUSCF = false;
	EnableRatingCtrls();
}

void CAddPlayerDlg::OnLevelSelchangeLevel()
{
	UpdateData(TRUE);
	int sel = m_levelCombo.GetCurSel();
	switch (sel)
	{
	case 0: m_rating = 500; break; //neophyte
	case 1: m_rating = 900; break; //beginner
	case 2: m_rating = 1300; break; //adv. beginner
	case 3: m_rating = 1500; break; //intermetdiate
	case 4: m_rating = 1800; break; //class A
	case 5: m_rating = 2000; break; //expert
	case 6: m_rating = 2100; break; //cand. master
	case 7: m_rating = 2200; break; //master
	default:  m_rating = 1300; break; //adv. beginner
	}
	char buff[20];
	sprintf(buff,"%d",m_rating);
	GetDlgItem(IDC_USCF)->SetWindowText(buff);
}

void CAddPlayerDlg::EnableRatingCtrls()
{
	this->m_radioAdult.SetCheck(useAdult);
	this->m_radioChild.SetCheck(useChild);
	this->m_radioLevel.SetCheck(useLevel);
	this->m_radioUSCF.SetCheck(useUSCF);
	this->GetDlgItem(IDC_AGE)->EnableWindow(useChild);
	this->GetDlgItem(IDC_LEVEL)->EnableWindow(useLevel);
	this->GetDlgItem(IDC_USCF)->EnableWindow(useUSCF);
	UpdateData(FALSE);
}

void CAddPlayerDlg::OnBnClickedRadioAdult()
{
	UpdateData(TRUE);
	this->useAdult = true;
	this->useChild = false;
	this->useLevel = false;
	this->useUSCF = false;
	EnableRatingCtrls();
	m_rating = 1300;
	char buff[20];
	sprintf(buff,"%d",m_rating);
	GetDlgItem(IDC_USCF)->SetWindowText(buff);
}

void CAddPlayerDlg::OnBnClickedRadioChild()
{
	UpdateData(TRUE);
	this->useAdult = false;
	this->useChild = true;
	this->useLevel = false;
	this->useUSCF = false;
    OnCbnSelchangeAge();
	EnableRatingCtrls();
}

void CAddPlayerDlg::OnBnClickedRadioLevel()
{
	UpdateData(TRUE);
	this->useAdult = false;
	this->useChild = false;
	this->useLevel = true;
	this->useUSCF = false;
    OnLevelSelchangeLevel();
    EnableRatingCtrls();
}

void CAddPlayerDlg::OnBnClickedRadioRating()
{
	UpdateData(TRUE);
	this->useAdult = false;
	this->useChild = false;
	this->useLevel = false;
	this->useUSCF = true;
	EnableRatingCtrls();
}

void CAddPlayerDlg::OnEnKillfocusUscf()
{
	UpdateData(TRUE);
	char buff[20];
	GetDlgItem(IDC_USCF)->GetWindowText(buff,20);
	int temp = 0;
	temp = atoi(buff);
	if ((temp > 100) && (temp < 3000))
	{
		//valid entry...
		m_rating = temp;
	}
	else
	{
		//invalid entry...
		m_rating = 1300;
		sprintf(buff,"%d",m_rating);
		GetDlgItem(IDC_USCF)->SetWindowText(buff);
	}
}


void CAddPlayerDlg::OnCbnSelchangeAge()
{
	UpdateData(TRUE);
	int sel = m_ageCombo.GetCurSel();
	int age = 0;
	switch (sel)
	{
	case 0: age = 4; break;
	case 1: age = 5; break;
	case 2: age = 6; break;
	case 3: age = 7; break;
	case 4: age = 8; break;
	case 5: age = 9; break;
	case 6: age = 10; break;
	case 7: age = 11; break;
	case 8: age = 12; break;
	case 9: age = 13; break;
	case 10: age = 14; break;
	case 11: age = 15; break;
	case 12: age = 16; break;
	case 13: age = 17; break;
	case 14: age = 18; break;
	case 15: age = 19; break;
	case 16: age = 20; break;
	default:  m_rating = 1300; break;
	}
	if (age > 0)
	{
		m_rating = 300 +(50*age);
	}

	char buff[20];
	sprintf(buff,"%d",m_rating);
	GetDlgItem(IDC_USCF)->SetWindowText(buff);
}