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
#ifndef __AF87652i3_GAME_CLASS_DEFINITION_FILE_3i25678FA__
#define __AF87652i3_GAME_CLASS_DEFINITION_FILE_3i25678FA__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// player.h : header file
//

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// CGame
class CGame
{
public:
	typedef
		enum tagResult {
			WhiteWon = 0,
			Draw = 1,
			BlackWon = 2
		} Result;

    CGame();
    ~CGame();

	void set_ID 	   (long	value);
	void set_blackID   (long	value) { m_blackID    = value; }
	void set_day       (long	value) { m_day        = value; }
	void set_hour 	   (long	value) { m_hour       = value; }
	void set_min 	   (long	value) { m_min        = value; }
	void set_month	   (long	value) { m_month      = value; }
	void set_result    (Result  value) { m_result     = value; }
	void set_whiteID   (long	value) { m_whiteID    = value; }
	void set_year	   (long	value) { m_year       = value; }
	void set_blackStart(long    value) { m_blackStart = value; }
	void set_blackEnd  (long    value) { m_blackEnd   = value; }
	void set_whiteStart(long    value) { m_whiteStart = value; }
	void set_whiteEnd  (long    value) { m_whiteEnd   = value; }

	long	get_blackID(void)          { return m_blackID;     }
	long	get_day(void)              { return m_day;         }
	long	get_hour(void)             { return m_hour;        }
	long	get_ID(void)               { return m_ID;          }
	long	get_min(void)              { return m_min;         }
	long	get_month(void)            { return m_month;       }
	Result	get_result(void)           { return m_result;      }
	long	get_whiteID(void)          { return m_whiteID;     }
	long	get_year(void)             { return m_year;        }
	long    get_blackStart(void)       { return m_blackStart;  }
	long    get_blackEnd(void)         { return m_blackEnd;    }
	long    get_whiteStart(void)       { return m_whiteStart;  }
	long    get_whiteEnd(void)         { return m_whiteEnd;    }

	static   long   HighestID(void)    { return m_HighestId;   }

	CGame& operator=(CGame &rt);
	bool operator==(const CGame &rt) const;

private:
	//Game ID
	long	m_ID;

	//Player ID of the white player
	long	m_whiteID;

	//rating of white player before game
    long     m_whiteStart;

	//rating of white player afer game
    long     m_whiteEnd;

	//Player ID of the black player
	long	m_blackID;

	//rating of black player before game
    long     m_blackStart;

	//rating of black player afer game
    long     m_blackEnd;

	//game result...
	Result	m_result;

	//Day and time game endedm(recorded)
	long		m_year;
	long		m_month;
	long		m_day;
	long		m_hour;
	long		m_min;

    //the highest ID found thus far...
    static long m_HighestId;
};

#endif __AF87652i3_GAME_CLASS_DEFINITION_FILE_3i25678FA__