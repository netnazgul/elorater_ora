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
#ifndef __AF87652i3_PLAYER_CLASS_DEFINITION_FILE_3i25678FA__
#define __AF87652i3_PLAYER_CLASS_DEFINITION_FILE_3i25678FA__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// player.h : header file
//

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// CPlayer
class CPlayer
{
public:
    CPlayer();
    ~CPlayer();

    void     set_ID(long value);
    void     set_firstName(CString& value){ m_firstName = value;      }
    void     set_lastName(CString& value) { m_lastName = value;       }
    void     set_rating(long value)       { m_rating = value;         }
    void     set_numGames(long value)     { m_numGames = value;       }
    void     set_highest(long value)      { m_highest = value;        }
    void     set_rawScore(long value)     { m_rawScore = value;       }
    void     set_initial(long value)      { m_initial = value;        }

    long     get_ID(void)                 { return m_ID;              }
    CString& get_firstName(void)          { return m_firstName;       }
    CString& get_lastName(void)           { return m_lastName;        }
    long     get_rating(void)             { return m_rating;          }
    long     get_numGames(void)           { return m_numGames;        }
    long     get_highest(void)            { return m_highest;         }
    long     get_rawScore(void)           { return m_rawScore;        }
    long     get_initial(void)            { return m_initial;         }

	static   long   HighestID(void)       { return m_HighestId;       }
	static   void   SetSort(int value)    { m_SortBy = value;         }

    CPlayer& operator=(CPlayer &rt);
    bool operator==(const CPlayer &rt) const;
	bool operator<(const CPlayer &rt) const;
	bool operator>(const CPlayer &rt) const;

private:
    //a unique ID
    long	m_ID;

    //player's first name
	CString	m_firstName;

    //player's last name
	CString	m_lastName;

    //player's curent rating
	long	m_rating;

    //number of games player has played
	long	m_numGames;

    //the hightest rating achieved by this player
	long	m_highest;

    //a value used in computation
	long    m_rawScore;

    //the player's initial rating
    long    m_initial;

    //the highest ID found thus far...
    static long m_HighestId;

	static int m_SortBy;
};

#endif //__AF87652i3_PLAYER_CLASS_DEFINITION_FILE_3i25678FA__