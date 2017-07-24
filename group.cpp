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
#include "group.h"

long CGroup::m_latestMajorVersion = 2;
long CGroup::m_latestMinorVersion = 0;

float CGroup::GetLatestVersion()
{
	if (m_latestMinorVersion < 100)
	return (float)(m_latestMajorVersion * 100 + m_latestMinorVersion)/(100.0);
	return (m_latestMajorVersion); 
}

CGroup::CGroup()
{
	m_dataFileVersion = 2;
	m_dataFileMinorV  = 0;
	m_name            = "noname";
	m_playerCount     = 0;
	m_gameCount       = 0;
	m_useHarkness     = false;
	m_dataFile        = 0;
	ClearPlayersList();
	ClearGamesList();
}

CGroup::~CGroup()
{
	if (m_dataFile != 0)
	{
		delete m_dataFile;
	}
	m_dataFileVersion = 1;
	m_dataFileMinorV  = 0;
	m_name            = "noname";
	m_playerCount     = 0;
	m_gameCount       = 0;
	m_useHarkness     = false;
	m_dataFile        = 0;
	ClearPlayersList();
	ClearGamesList();
}

float CGroup::get_version()
{
	if (m_dataFileMinorV < 100)
	return (float)(m_dataFileVersion * 100 + m_dataFileMinorV)/(100.0);
}

void CGroup::set_name(CString value)
{
	m_name = value;	
}

POSITION CGroup::GetFirstPlayerHandle()
{
	POSITION retVal = 0;
	if (m_players.GetCount() > 0)
	{
		retVal = m_players.GetHeadPosition();
	}
	return retVal;
}

POSITION CGroup::GetNextPlayerHandle(POSITION pos)
{
	POSITION retVal = pos;
	if (m_players.GetCount() > 0)
	{
		m_players.GetNext(retVal);
	}
	return retVal;
}

POSITION CGroup::GetPlayerHandle(CPlayer& rt)
{
	POSITION retVal = 0;
	if (m_players.GetCount() > 0)
	{
		retVal = m_players.Find(rt,0);
	}
	return retVal;
}

CPlayer& CGroup::GetPlayer(POSITION pos)
{
	if (m_players.GetCount() > 0)
	{
		return m_players.GetAt(pos);
	}
	return (CPlayer());
}

POSITION CGroup::FindPlayer(long id, CPlayer& rt)
{
	//this will take a while... the list must be walked through...
	POSITION retVal = NULL;
	bool found = false;
	POSITION pos = m_players.GetHeadPosition();
	while ((!found) && (pos))
	{
		POSITION current = pos;
		CPlayer player = m_players.GetNext(pos);
		if (player.get_ID() == id)
		{
			found = true;
			rt = player;
			retVal = current;
		}
	}
	return retVal;
}

bool CGroup::UpdatePlayer(POSITION pos, CPlayer& rt)
{
	POSITION head = m_players.GetHeadPosition();
	if (pos == head)
	{
		m_players.RemoveHead();
		m_players.AddHead(rt);
	}
	else
	{
		POSITION prev = pos;
		m_players.GetPrev(prev);
		m_players.RemoveAt(pos);
		m_players.InsertAfter(prev,rt);
	}
	return false;
}

POSITION CGroup::AddPlayer(CPlayer& rt)
{
	POSITION retVal = 0;
	long newId = 0;
	int count = m_players.GetCount();
	if (count > 0)
	{
		CPlayer last = m_players.GetTail();
		newId = last.get_ID();
	}
	newId += 1;
	rt.set_ID(newId);
	m_players.AddTail(rt);
	retVal = m_players.GetTailPosition();
	m_playerCount++;
	return retVal;
}

bool CGroup::DelPlayer(POSITION pos)
{
	bool retVal = false;
	int startCount = m_players.GetCount();
	if ( startCount > 0)
	{
		m_players.RemoveAt(pos);
	}
	int stopCount = m_players.GetCount();
	if (startCount > stopCount)
	{
		m_playerCount--;
		retVal = true;
	}
	return retVal;
}

POSITION CGroup::GetFirstGameHandle()
{
	POSITION retVal = 0;
	if (m_games.GetCount() > 0)
	{
		retVal = m_games.GetHeadPosition();
	}
	return retVal;
}

POSITION CGroup::GetNextGameHandle(POSITION pos)
{
	POSITION retVal = pos;
	if (m_games.GetCount() > 0)
	{
		m_games.GetNext(retVal);
	}
	return retVal;
}

POSITION CGroup::GetGameHandle(CGame& rt)
{
	POSITION retVal = 0;
	if (m_games.GetCount() > 0)
	{
		retVal = m_games.Find(rt,0);
	}
	return retVal;
}

CGame& CGroup::GetGame(POSITION pos)
{
	if (m_games.GetCount() > 0)
	{
		return m_games.GetAt(pos);
	}
	return (CGame());
}

POSITION CGroup::AddGame(CGame& rt)//can only add game to end
{
	POSITION retVal = 0;
	long newId = 0;
	int count = m_games.GetCount();
	if (count > 0)
	{
		CGame last = m_games.GetTail();
		newId = last.get_ID();
	}
	newId += 1;
	rt.set_ID(newId);
	m_games.AddTail(rt);
	retVal = m_games.GetTailPosition();
	m_gameCount++;
	return retVal;
}

bool CGroup::DelGame()//can only remove last game!
{
	bool retVal = false;
	int startCount = m_games.GetCount();
	if ( startCount > 0)
	{
		//TODO: roll back the ratings affected by this game!
		m_games.RemoveTail();
	}
	int stopCount = m_games.GetCount();
	if (startCount > stopCount)
	{
		m_gameCount--;
		retVal = true;
	}
	return retVal;
}


void CGroup::ClearPlayersList()
{
	while (m_players.GetCount() > 0)
	{
		m_players.RemoveTail();
	}
}

void CGroup::ClearGamesList()
{
	while (m_games.GetCount() > 0)
	{
		m_games.RemoveTail();
	}
}

bool CGroup::loadData()
{
	bool retVal = false;
	CString filename = m_name + ".elo";
	m_dataFile = new CDataFile(filename);
	if (m_dataFile->OpenForRead())
	{
		CString headerMessage =
			"XXXX----XXXX----XXXX"
			"      ELO RATER     "
			"XXXX----XXXX----XXXX";
		CString testMessage;
		m_dataFile->loadData(testMessage);
		
		if (headerMessage != testMessage)
		{
			//error... this is not an elo rator data file...
			MessageBox(NULL,"The data file porvided is not\n"
				            "an ELO Rater data file or\n"
						    "the data file is corrupt.\n"
						    "Please load a different file.",
			           "File Error", MB_ICONSTOP);
			delete m_dataFile;
			m_dataFile = 0;
			return false;
		}

		m_dataFile->loadData(m_dataFileVersion);
		m_dataFile->loadData(m_dataFileMinorV);

		if (get_version() > GetLatestVersion())
		{
			//error... 
			//the file version is newer than this program supports...
			char buffer[200];
			sprintf(buffer,"The ELO data file is not supported\n"
				           "by this version of the ELO Rater Utility.\n"
						   "The latest version supported is %f1.3\n"
						   "The ELO data file version is %f1.3\n"
						   "Upgrade your ELO Ratoer to continue.",
						   GetLatestVersion(), get_version());
			MessageBox(NULL, buffer, "Version Error", MB_ICONSTOP);
			delete m_dataFile;
			m_dataFile = 0;
			return false;
		}

		//WE ARE READING WHAT APPEARS TO BE A VALID DATA FILE...
		ClearGamesList();
		ClearPlayersList();

		m_dataFile->loadData(m_playerCount);
		m_dataFile->loadData(m_gameCount);
		m_dataFile->loadData(m_useHarkness);


		if (get_version() >= 2.0)
		{
			//file verion 2.0 and greater has start of list labels
			CString label;
			m_dataFile->loadData(label);
			if (label != "*** BEGIN PLAYER LIST ***")
			{
				//error... this is not an elo rator data file...
				MessageBox(NULL,"The data file is corrupt.\n"
								"Please load a different file.",
						   "File Error", MB_ICONSTOP);
				delete m_dataFile;
				m_dataFile = 0;
				return false;
			}
		}
		int countP = 0;
		while (countP < m_playerCount)
		{
			CPlayer* player = new CPlayer();
			Read(*player);
			m_players.AddTail(*player);
			countP++;
		}


		if (get_version() >= 2.0)
		{
			//file verion 2.0 and greater has start of list labels
			CString label;
			m_dataFile->loadData(label);
			if (label != "*** BEGIN GAME LIST ***")
			{
				//error... this is not an elo rator data file...
				MessageBox(NULL,"The data file is corrupt.\n"
								"Please load a different file.",
						   "File Error", MB_ICONSTOP);
				delete m_dataFile;
				m_dataFile = 0;
				return false;
			}
		}
		int countG = 0;
		while (countG < m_gameCount)
		{
			CGame* game = new CGame();
			Read(*game);
			m_games.AddTail(*game);
			countG++;
		}
		if (  (countP == m_playerCount)
			&&(countG == m_gameCount)  )
		{
			retVal = true;
		}
	}
	return retVal;
}

bool CGroup::saveData()
{
	bool retVal = false;
	CString filename = m_name + ".elo";
	m_dataFile = new CDataFile(filename);
	if (m_dataFile->OpenForWrite())
	{
		CString headerMessage =
			"XXXX----XXXX----XXXX"
			"      ELO RATER     "
			"XXXX----XXXX----XXXX";
		m_dataFile->saveData(headerMessage);
		m_dataFile->saveData(m_dataFileVersion);
		m_dataFile->saveData(m_dataFileMinorV);
		m_dataFile->saveData(m_playerCount);
		m_dataFile->saveData(m_gameCount);
		m_dataFile->saveData(m_useHarkness);

		if (get_version() >= 2.0)
		{
			//file verion 2.0 and greater has start of list labels
			CString label = "*** BEGIN PLAYER LIST ***";
			m_dataFile->saveData(label);
		}
		POSITION pos = m_players.GetHeadPosition();
		while (pos)
		{
			CPlayer player = m_players.GetNext(pos);
			Write(player);
		}

		if (get_version() >= 2.0)
		{
			//file verion 2.0 and greater has start of list labels
			CString label = "*** BEGIN GAME LIST ***";
			m_dataFile->saveData(label);
		}
		pos = m_games.GetHeadPosition();
		while (pos)
		{
			CGame game = m_games.GetNext(pos);
			Write(game);
		}
		retVal = true;
	}
	return retVal;
}

bool CGroup::Read(CGame &rt)
{
	bool retValue = false;
	if (m_dataFile->canRead())
	{
		long	t_ID;
		long	t_whiteID;
		long	t_whiteStart;
		long	t_whiteEnd;
		long	t_blackID;
		long	t_blackStart;
		long	t_blackEnd;
		long	t_result;
		long	t_year;
		long	t_month;
		long	t_day;
		long	t_hour;
		long	t_min;

		m_dataFile->loadData(t_ID);
		m_dataFile->loadData(t_whiteID);
		m_dataFile->loadData(t_whiteStart);
		m_dataFile->loadData(t_whiteEnd);
		m_dataFile->loadData(t_blackID);
		m_dataFile->loadData(t_blackStart);
		m_dataFile->loadData(t_blackEnd);
		m_dataFile->loadData(t_result);
		m_dataFile->loadData(t_year);
		m_dataFile->loadData(t_month);
		m_dataFile->loadData(t_day);
		m_dataFile->loadData(t_hour);
		m_dataFile->loadData(t_min);

		rt.set_ID(t_ID);
		rt.set_whiteID(t_whiteID);
		rt.set_whiteStart(t_whiteStart);
		rt.set_whiteEnd(t_whiteEnd);
		rt.set_blackID(t_blackID);
		rt.set_blackStart(t_blackStart);
		rt.set_blackEnd(t_blackEnd);
		switch (t_result)
		{
		case 0:
			rt.set_result(CGame::WhiteWon);
			break;
		case 2:
			rt.set_result(CGame::BlackWon);
			break;
		case 1:
		default:
			rt.set_result(CGame::Draw);
			break;
		}
		rt.set_year(t_year);
		rt.set_month(t_month);
		rt.set_day(t_day);
		rt.set_hour(t_hour);
		rt.set_min(t_min);

		retValue = true;
	}
	return retValue;
}

bool CGroup::Write(CGame &rt)
{
	bool retValue = false;
	if (m_dataFile->canWrite())
	{
		long t_result = 1;
		switch (rt.get_result())
		{
		case CGame::WhiteWon:
			t_result = 0;
			break;
		case CGame::BlackWon:
			t_result = 2;
			break;
		case CGame::Draw:
		default:
			t_result = 0;
			break;
		}
		m_dataFile->saveData(rt.get_ID());
		m_dataFile->saveData(rt.get_whiteID());
		m_dataFile->saveData(rt.get_whiteStart());
		m_dataFile->saveData(rt.get_whiteEnd());
		m_dataFile->saveData(rt.get_blackID());
		m_dataFile->saveData(rt.get_blackStart());
		m_dataFile->saveData(rt.get_blackEnd());
		m_dataFile->saveData(t_result);
		m_dataFile->saveData(rt.get_year());
		m_dataFile->saveData(rt.get_month());
		m_dataFile->saveData(rt.get_day());
		m_dataFile->saveData(rt.get_hour());
		m_dataFile->saveData(rt.get_min());
			
		retValue = false;
	}
	return retValue;
}



bool CGroup::Read(CPlayer &rt)
{
	bool retValue = false;
	if (m_dataFile->canRead())
	{
		long    t_ID;
        CString t_firstName;
        CString t_lastName;
		long    t_rating;
		long    t_numGames;
		long    t_highest;
		long    t_rawScore;
		long    t_initial;

		m_dataFile->loadData(t_ID);
		m_dataFile->loadData(t_firstName);
		m_dataFile->loadData(t_lastName);
		m_dataFile->loadData(t_rating);
		m_dataFile->loadData(t_numGames);
		m_dataFile->loadData(t_highest);
		m_dataFile->loadData(t_rawScore);
		m_dataFile->loadData(t_initial);

		rt.set_ID(t_ID);        
		rt.set_firstName(t_firstName); 
		rt.set_lastName(t_lastName);  
		rt.set_rating(t_rating);    
		rt.set_numGames(t_numGames);  
		rt.set_highest(t_highest);   
		rt.set_rawScore(t_rawScore);  
		rt.set_initial(t_initial);
		retValue = true;
	}
	return retValue;
}

bool CGroup::Write(CPlayer &rt)
{
	bool retValue = false;
	if (m_dataFile->canWrite())
	{
		m_dataFile->saveData(rt.get_ID());        
		m_dataFile->saveData(rt.get_firstName()); 
		m_dataFile->saveData(rt.get_lastName());  
		m_dataFile->saveData(rt.get_rating());    
		m_dataFile->saveData(rt.get_numGames());  
		m_dataFile->saveData(rt.get_highest());   
		m_dataFile->saveData(rt.get_rawScore());  
		m_dataFile->saveData(rt.get_initial());
		retValue = false;
	}
	return retValue;
}


