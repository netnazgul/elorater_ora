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
#include "game.h"

long CGame::m_HighestId = 0;

CGame::CGame()
{
	m_ID         = 0;
	m_whiteID    = 0;
    m_whiteStart = 0;
    m_whiteEnd   = 1300;
	m_blackID    = 0;
    m_blackStart = 1300;
    m_blackEnd   = 1300;
	m_result     = CGame::Draw;
	m_year       = 0;
	m_month      = 0;
	m_day        = 0;
	m_hour       = 0;
	m_min        = 0;
}

CGame::~CGame()
{
	m_ID         = 0;
	m_whiteID    = 0;
    m_whiteStart = 0;
    m_whiteEnd   = 1300;
	m_blackID    = 0;
    m_blackStart = 1300;
    m_blackEnd   = 1300;
	m_result     = CGame::Draw;
	m_year       = 0;
	m_month      = 0;
	m_day        = 0;
	m_hour       = 0;
	m_min        = 0;
}

void CGame::set_ID(long	value) 
{ 
	m_ID         = value; 
	if (value > m_HighestId)
	{
		m_HighestId = value;
	}
}

CGame& CGame::operator=(CGame &rt)
{
	m_ID         = rt.get_ID();        
	m_whiteID    = rt.get_whiteID();
    m_whiteStart = rt.get_whiteStart();
    m_whiteEnd   = rt.get_whiteEnd();  
	m_blackID    = rt.get_blackID();   
    m_blackStart = rt.get_blackStart();
    m_blackEnd   = rt.get_blackEnd();  
	m_result     = rt.get_result();    
	m_year       = rt.get_year();      
	m_month      = rt.get_month();     
	m_day        = rt.get_day();       
	m_hour       = rt.get_hour();      
	m_min        = rt.get_min();  
	return (*this);
}

bool CGame::operator==(const CGame &rt) const
{
	return (this->m_ID == rt.m_ID);
}

