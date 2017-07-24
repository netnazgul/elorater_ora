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
#include "player.h"

long CPlayer::m_HighestId = 0;
int  CPlayer::m_SortBy = 0;

CPlayer::CPlayer()
{
    m_ID        = 0;
    m_firstName = "";
    m_lastName  = "";
    m_rating    = 1300;
    m_numGames  = 0;
    m_highest   = 1300;
    m_rawScore  = 0;
    m_initial   = 1300;
}

CPlayer::~CPlayer()
{
    m_ID        = 0;
    m_firstName = "";
    m_lastName  = "";
    m_rating    = 1300;
    m_numGames  = 0;
    m_highest   = 1300;
    m_rawScore  = 0;
    m_initial   = 1300;
}

void CPlayer::set_ID(long value)
{ 
	m_ID = value;
	if (value > m_HighestId)
	{
		m_HighestId = value;
	}
}

CPlayer& CPlayer::operator=(CPlayer &rt)
{
    m_ID        = rt.m_ID;
    m_firstName = rt.m_firstName;
    m_lastName  = rt.m_lastName; 
    m_rating    = rt.m_rating; 
    m_numGames  = rt.m_numGames; 
    m_highest   = rt.m_highest; 
    m_rawScore  = rt.m_rawScore; 
    m_initial   = rt.m_initial; 
    return (*this);
}

bool CPlayer::operator==(const CPlayer &rt) const
{
	return (this->m_ID == rt.m_ID);
}

bool CPlayer::operator<(const CPlayer &rt) const
{
	switch (m_SortBy)
	{
	case 1: //rating first then by name
		if (this->m_rating != rt.m_rating)
			return (m_rating < rt.m_rating);
		else
			if (this->m_lastName != rt.m_lastName)
				return (m_lastName < rt.m_lastName);
			else
				return (m_firstName < rt.m_firstName);
	default: //name 
		if (this->m_lastName != rt.m_lastName)
			return (m_lastName < rt.m_lastName);
		else
			return (m_firstName < rt.m_firstName);
	}
}

bool CPlayer::operator>(const CPlayer &rt) const
{
	switch (m_SortBy)
	{
	case 1: //rating first then by name
		if (this->m_rating != rt.m_rating)
			return (m_rating > rt.m_rating);
		else
			if (this->m_lastName != rt.m_lastName)
				return (m_lastName > rt.m_lastName);
			else
				return (m_firstName > rt.m_firstName);
	default: //name 
		if (this->m_lastName != rt.m_lastName)
			return (m_lastName > rt.m_lastName);
		else
			return (m_firstName > rt.m_firstName);
	}
}

