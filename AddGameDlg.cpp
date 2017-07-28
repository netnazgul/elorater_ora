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
// AddGameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "eloRater.h"
#include "AddGameDlg.h"
#include "eloRaterDlg.h"
#include "rate.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddGameDlg dialog


CAddGameDlg::CAddGameDlg() : CDialog()
{
	//{{AFX_DATA_INIT(CAddGameDlg)
	m_date = 0;
	m_time = 0;
	//}}AFX_DATA_INIT
	m_refTime = m_refTime.GetCurrentTime();
	m_date    = m_refTime;
	m_time    = m_refTime;
	m_group   = 0;
}

void CAddGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddGameDlg)
	DDX_Control(pDX, IDC_RESULTCOMBO, m_resultCombo);
	DDX_Control(pDX, IDC_WHITECOMBO, m_whiteCombo);
	DDX_Control(pDX, IDC_BLACKCOMBO, m_blackCombo);
	DDX_Control(pDX, IDC_GAMELIST, m_gameList);
	DDX_Control(pDX, IDC_DATEPICKER, m_dateCtrl);
	DDX_Control(pDX, IDC_TIMEPICKER, m_timeCtrl);
	DDX_Control(pDX, ID_ADD, m_btnAdd);
	DDX_Control(pDX, ID_CLEAR, m_btnClear);
	DDX_DateTimeCtrl(pDX, IDC_DATEPICKER, m_date);
	DDX_DateTimeCtrl(pDX, IDC_TIMEPICKER, m_time);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddGameDlg, CDialog)
	//{{AFX_MSG_MAP(CAddGameDlg)
	ON_BN_CLICKED(ID_ADD, OnAdd)
	ON_BN_CLICKED(ID_CLEAR, OnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddGameDlg message handlers

BOOL CAddGameDlg::Create(CWnd* pParentWnd)
{
	BOOL retVal = CDialog::Create(IDD_ADDGAME, pParentWnd);
	int stops[2];
	stops[0] = 100;
	stops[1] = 200;
	m_gameList.SetTabStops(2,stops);
	return retVal;
}

void CAddGameDlg::ClearPlayerLists()
{
	m_whiteCombo.ResetContent();
	m_blackCombo.ResetContent();
	m_whiteCombo.Clear();
	m_blackCombo.Clear();
}

void CAddGameDlg::LoadGroup(CGroup* group)
{
	m_group = group;

	//load group data list...
	if (m_group != 0)
	{
		ClearPlayerLists();	

		POSITION pos = m_group->GetFirstPlayerHandle();
		while (pos)
		{
			CPlayer player = m_group->GetPlayer(pos);
			CString addThis;
			addThis.Format("%s, %s",
				player.get_lastName(),
				player.get_firstName());
			int wIndex = m_whiteCombo.AddString(addThis);
			int bIndex = m_blackCombo.AddString(addThis);
			m_whiteCombo.SetItemDataPtr(wIndex, (void*)pos);
			m_blackCombo.SetItemDataPtr(bIndex, (void*)pos);
			pos = m_group->GetNextPlayerHandle(pos);
		}

		pos = m_group->GetFirstGameHandle();
		while (pos)
		{
			CGame game = m_group->GetGame(pos);
			CPlayer white;
			CPlayer black;
			POSITION wPos = m_group->FindPlayer(game.get_whiteID(), white);
			POSITION bPos = m_group->FindPlayer(game.get_blackID(), black);
			if (wPos != NULL && bPos != NULL)
			{
				CString addThis;
				CGame::Result result = game.get_result();
				CString resStr = "draw";
				switch (result)
				{
				case CGame::WhiteWon: resStr = "White";break;
				case CGame::BlackWon: resStr = "Black";break;
				default:              resStr = "-Draw"; break;
				}
					
				addThis.Format("%d.%02d.%02d   %02d:%02d      %s      %s, %s vs. %s, %s",
					game.get_year(),
					game.get_month(),
					game.get_day(),
					game.get_hour(),
					game.get_min(),
					resStr,
					white.get_lastName(),
					white.get_firstName(),
					black.get_lastName(),
					black.get_firstName());
				int gIndex = m_gameList.InsertString(0,addThis);
				m_gameList.SetItemDataPtr(gIndex, (void*)pos);
			}
			pos = m_group->GetNextPlayerHandle(pos);
		}
		m_dateCtrl.EnableWindow(true);
		m_timeCtrl.EnableWindow(true);
		m_resultCombo.EnableWindow(true);
		m_whiteCombo.EnableWindow(true);
		m_blackCombo.EnableWindow(true);
		m_btnAdd.EnableWindow(true);
		m_btnClear.EnableWindow(true);
	}
	else
	{
		ClearPlayerLists();	
		m_gameList.ResetContent();
		m_resultCombo.SetCurSel(-1);
		m_whiteCombo.SetCurSel(-1);
		m_blackCombo.SetCurSel(-1);
		m_dateCtrl.EnableWindow(false);
		m_timeCtrl.EnableWindow(false);
		m_resultCombo.EnableWindow(false);
		m_whiteCombo.EnableWindow(false);
		m_blackCombo.EnableWindow(false);
		m_btnAdd.EnableWindow(false);
		m_btnClear.EnableWindow(false);
	}
}

void CAddGameDlg::UnloadGroup()
{
	//unload the group data...
	ClearPlayerLists();	
	m_gameList.ResetContent();
	m_resultCombo.SetCurSel(-1);
	m_whiteCombo.SetCurSel(-1);
	m_blackCombo.SetCurSel(-1);
	m_dateCtrl.EnableWindow(false);
	m_timeCtrl.EnableWindow(false);
	m_resultCombo.EnableWindow(false);
	m_whiteCombo.EnableWindow(false);
	m_blackCombo.EnableWindow(false);
	m_btnAdd.EnableWindow(false);
	m_btnClear.EnableWindow(false);
	m_group = NULL;
}

void CAddGameDlg::OnAdd() 
{
	UpdateData(TRUE);
	if (  (m_whiteCombo.GetCurSel() == -1) 
		||(m_blackCombo.GetCurSel() == -1)
		||(m_resultCombo.GetCurSel() == -1) )
	{
		MessageBox("Unable to complete operation:\nNot all fields are defined .",
			"ERROR", MB_ICONINFORMATION |MB_OK);
		return;
	}

	int whiteSel = m_whiteCombo.GetCurSel();
	int blackSel = m_blackCombo.GetCurSel();
	
	if (whiteSel == blackSel)
	{
		//invalid game data
		MessageBox("Unable to complete operation:\nWhite and Black can not be the same.",
			"ERROR", MB_ICONINFORMATION |MB_OK);
		return;
	}

	POSITION wPos = (POSITION)m_whiteCombo.GetItemDataPtr(whiteSel);
	POSITION bPos = (POSITION)m_whiteCombo.GetItemDataPtr(blackSel);
	CPlayer white = m_group->GetPlayer(wPos);
	CPlayer black = m_group->GetPlayer(bPos);

	CString resultStr;
	m_resultCombo.GetLBText(m_resultCombo.GetCurSel(),resultStr);

	CGame::Result result = CGame::Draw;
    int whiteStart = white.get_rating();
    int blackStart = black.get_rating();
	float whiteScore = 0.5;
	float blackScore = 0.5;
	if (resultStr =="White Won")
	{
		result = CGame::WhiteWon;
		whiteScore = 1.0;
		blackScore = 0.0;
	}
	else if (resultStr =="Black Won")
	{
		result = CGame::BlackWon;
		whiteScore = 0.0;
		blackScore = 1.0;
	}

	CString resStr = "draw";
	switch (result)
	{
	case CGame::WhiteWon: resStr = "White";break;
	case CGame::BlackWon: resStr = "Black";break;
	default:              resStr = "-Draw"; break;
	}

	bool gameexists;
	long blackID = black.get_ID(), whiteID = white.get_ID();
	long year = m_date.GetYear(), month = m_date.GetMonth(), day = m_date.GetDay(), hour = m_time.GetHour(), minute = m_time.GetMinute();
	POSITION gamepos = m_group->GetFirstGameHandle();
	while (gamepos)
	{
		CGame game = m_group->GetGame(gamepos);
		
		if ((blackID == game.get_blackID()) &&
			(whiteID == game.get_whiteID()) &&
			 year == game.get_year() && 
			 month == game.get_month() &&
			 day == game.get_day() &&
			 hour == game.get_hour() &&
			 minute == game.get_min() &&
			result == game.get_result()
			)
		{
			gameexists = true;
			break;
		}

		gamepos = m_group->GetNextGameHandle(gamepos);
	}

	CString msg;
	if (!gameexists)
	{
		//no record found... add it
		msg.Format("Please confirm the entry of the game :\n"
					"%s, %s vs. %s, %s\n"
					"Date: %d-%d-%d\n"
					"Time: %02d-%02d.\n"
					"Press OK to accept or Cancel to abort.",
					white.get_lastName(),
					white.get_firstName(),
					black.get_lastName(),
					black.get_firstName(),
					m_date.GetYear(),
					m_date.GetMonth(),
					m_date.GetDay(),
					m_time.GetHour(),
					m_time.GetMinute());
		if (IDOK == MessageBox(msg, "Confirm Addition", MB_OKCANCEL))
		{                
			if (m_group->get_useHarkness())
			{
				ComputeHarknessRatings(white,black,whiteScore, blackScore);
			}
			else
			{
				ComputeNewRatings(white, black,whiteScore, blackScore);				
			}

            //add game to group
			CGame newGame;
			newGame.set_blackID(blackID);
			newGame.set_whiteID(whiteID);
			newGame.set_year(year);
			newGame.set_month(month);
			newGame.set_day(day);
			newGame.set_hour(hour);
			newGame.set_min(minute);
            newGame.set_whiteStart(whiteStart);
            newGame.set_whiteEnd(white.get_rating());
            newGame.set_blackStart(blackStart);
            newGame.set_blackEnd(black.get_rating());
			newGame.set_result(result);
			m_group->AddGame(newGame);

            //update white player record...
			m_group->UpdatePlayer(wPos,white);

			//update black player record...
			m_group->UpdatePlayer(bPos,black);

			CEloRaterDlg* pParent = (CEloRaterDlg*)GetParent();
			pParent->ReloadGroup();
		}
	}
	else
	{
		//record found... can not add it
		msg.Format("Can not add the game :\n"
					"%s, %s vs. %s, %s\n"
					"Date: %d-%d-%d\n"
					"Time: %d-%d\n"
				    "to the database.\n"
					"That game already exists in the database.", 
					black.get_lastName(),
					black.get_firstName(),
					white.get_lastName(),
					white.get_firstName(),
					m_date.GetYear(),
					m_date.GetMonth(),
					m_date.GetDay(),
					m_time.GetHour(),
					m_time.GetMinute());
		MessageBox(msg,"Error", MB_ICONINFORMATION | MB_OK);
	}
}

void CAddGameDlg::SetDefaultTab()
{
	if (m_group)
	{
		m_whiteCombo.SetFocus();
	}
	else
	{
		m_gameList;
	}
}

void CAddGameDlg::OnClear() 
{
	m_resultCombo.SetCurSel(-1);
	m_whiteCombo.SetCurSel(-1);
	m_blackCombo.SetCurSel(-1);
	m_refTime = m_refTime.GetCurrentTime();
	m_date    = m_refTime;
	m_time    = m_refTime;
	UpdateData(FALSE);	
}



BOOL CAddGameDlg::DestroyWindow() 
{
	ClearPlayerLists();	
	return CDialog::DestroyWindow();
}
