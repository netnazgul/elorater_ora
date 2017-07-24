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
#ifndef __AF87652i3_GROUP_CLASS_DEFINITION_FILE_3i25678FA__
#define __AF87652i3_GROUP_CLASS_DEFINITION_FILE_3i25678FA__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// group.h : header file
//

#include "stdafx.h"
#include "datafile.h"
#include "player.h"
#include "game.h"

/////////////////////////////////////////////////////////////////////////////
// CGroup
class CGroup
{
public:
	CGroup();
	~CGroup();

	bool get_useHarkness(){return m_useHarkness;}
	void set_useHarkness(bool value){m_useHarkness = value;}
	CString get_name(){return m_name;}
	void set_name(CString value);

	bool loadData();
	bool saveData();

	POSITION GetFirstPlayerHandle();
	POSITION GetNextPlayerHandle(POSITION pos);
	POSITION GetPlayerHandle(CPlayer& rt);
	CPlayer& GetPlayer(POSITION pos);
	POSITION FindPlayer(long id, CPlayer& rt);
	bool     UpdatePlayer(POSITION pos, CPlayer& rt);
	POSITION AddPlayer(CPlayer& rt);
	bool     DelPlayer(POSITION pos);

	POSITION GetFirstGameHandle();
	POSITION GetNextGameHandle(POSITION pos);
	POSITION GetGameHandle(CGame& rt);
	CGame& GetGame(POSITION pos);
	POSITION AddGame(CGame& rt);//can only add game to end
	bool     DelGame();//can only remove last game!

	float get_version();
	static float GetLatestVersion();



private:
	//the name of the Group
	//this name is also used in the file name...
	CString m_name;

	long m_playerCount;
	long m_gameCount;

	//flag indicating whether the simpler Harkness system is used
	//true ideicates Harkness System used
	//false indicates USCF System is used
	bool m_useHarkness;

	//the list of players...
	CList<CPlayer,CPlayer> m_players;

	//the list of games
	CList<CGame, CGame> m_games;

	//the datafile...
	CDataFile *m_dataFile;

	//read write methods...
	bool Read(CGame &rt);
	bool Write(CGame &rt); 
	bool Read(CPlayer& rt);
	bool Write(CPlayer &rt);
	void ClearGamesList();
	void ClearPlayersList();

	long m_dataFileVersion;
	long m_dataFileMinorV;

	static long m_latestMajorVersion;
	static long m_latestMinorVersion;
};

#endif __AF87652i3_GROUP_CLASS_DEFINITION_FILE_3i25678FA__
