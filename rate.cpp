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
#include "rate.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//compute Provisional Winning expectancy...
double PWe(float R, float Ri)
{	
	if (R - Ri <= -400)
		return 0;
	else if (R - Ri >= 400)
		return 1;
	else
		return ( 0.5 + (R - Ri)/800);
}


//cestimate R based on PWe and Ri (PWe function looses data if |R-Ri| > 400
float inversePWe( float PWe, float Ri)
{
	if (PWe == 0)
		return Ri - 400;
	else if (PWe == 1)
		return Ri + 400;
	else 
	{
		return ( (PWe - 0,5)* 800 + Ri);
	}
}

//the algorithm for the rating was taken from 
//http://math.bu.edu/people/mg/uscf/rs/rs2.html
//
/////////////////////////////////////////////////////////////////////////////
void ComputeNewRatings(CPlayer& white, CPlayer& black, 
					   float whiteScore, float blackScore)
{

	//variables
	int   No_white; //initial number of games played by white
	float Ns_white; //N star for white computed in step 2
	float Np_white; //N prime for white computed in step 2
	float Ro_white; //initial rating of white player
	float Rfinal_white;


	int   No_black; //initial unmber of games played by black
	float Ns_black; //N star for black computed in step 2
	float Np_black; //N prime for black computed in step 2
	float Ro_black; //initial rating of black player
	float Rfinal_black;


/*
Step 1: 
Set initial ratings for unrated players. 
Initial rating estimates are set for all unrated players in an event. 
The purpose of setting initial rating estimates for unrated players is 
(1) to be able to incorporate information about a game result against 
    an unrated player, and 
(2) to choose among equally plausible ratings during a rating calculation 
    for an unrated player (see the details of the ``special'' rating 
	formulas in Section 2.2. 

An initial rating for an unrated player is determined in the following 
order of precedence. 

	----------

	If an unrated player has a FIDE rating, use a converted rating 
	according to the following formula: 

			USCF = FIDE + 50

	If the FIDE rating is over 2150, then this converted rating is treated 
	as based on having played 10 games (N = 10). If the FIDE rating is 2150 or 
	less, then this converted rating is treated as based on having played 
	5 games (N = 5). 

	----------
	
	If an unrated player has a CFC rating over 1500, use a converted rating 
	according to the following formula: 

			USCF = 1.1 * CFC - 240
 
	
	This converted rating is treated as based on having played 5 games (N = 5). 

	If an unrated player has a CFC rating of 1500 or less, use a converted 
	rating according to the following formula: 

			USCF = CFC - 90

 
	This converted rating is treated as based on having played 0 games (N = 0).

	----------

	If the event is a regular event and the player has a QC rating (and does 
	not have a standard rating) based on at least four games, use the QC rating 
	as the imputed standard rating. The rating is assumed to be based on 0 games 
	(N = 0). 
	Conversely, if the event is a QC event and the player only has a standard 
	rating based on at least four games, use the standard rating as the imputed
	rating. The rating is assumed to be based on the lesser of 10 and the number 
	of games upon which the standard rating is based ( N = 10 or N = number of 
	prior QC games, whichever is smaller). 

  	----------
	
	Otherwise, imput an age-based rating according to the following procedure. 
	Define a player's age (in years) to be 

	Age = (Tournament End Date - Birth Date)/365.25

	The formula for an initial rating based on age is given by 

	USCF =   300 + 50 * Age  for 4 < Age < 20
	     =   1300 otherwise
 
	The rating is assumed to be based on 0 games (N = 0). As a practical concern, 
	if ``Age'' is calculated to be less than 4 years old, then it is assumed that 
	a miscoding of the player's birthday occurred, so that such a player is 
	treated as a 20-year old in the Age-based calculation. 

	If no international rating or birth information is supplied, and if the player 
	does not have a non-correspondence USCF rating, imput a rating of 750. This 
	rating is assumed to be based on 0 games (N = 0). 


	//comments.
	For our purposes, we will completely ignore all other rating systems, and
	all players are 20 or older, this means that id no previous games have been played
	the rating is 1300.
	*/
	
	if (white.get_numGames() == 0)
	{
		No_white = 0;
        Ro_white = white.get_initial();
		//Ro_white = 1300.0;
	}
	else
	{
		No_white = white.get_numGames();
        Ro_white = (float)white.get_rating();
	}

	if (black.get_numGames() == 0)
	{
		No_black = 0;
        Ro_black = black.get_initial();
		//Ro_black = 1300.0;
	}
	else
	{
		No_black = black.get_numGames();
		Ro_black = (float)black.get_rating();
	}

/*
Step 2

Calculate the "effective" number of games played by each player

For each player, let N be the number of tournament games the player has competed, 
or, for unrated players, the value assigned from Step 1 of the algorithm. Let Ro be 
the player's pre-event rating, or, for unrated players, the imputed rating assigned 
from Step 1. 

Let 
	Ns = 50/ sqrt(1 + pow((2200-Ro),2)/ 100000 )  if Ro =< 2200
	   = 50                                       if Ro >  2200

Define the "effective" number of games, Np, to be the smaller of N and Ns. As a 
result of the formula,  can be no larger than 50, and it will usually be less, 
especially for players who have not competed in many tournament games. Note that Np 
is a temporary variable in the computation and is not saved after an event is rated. 

Example: Suppose a player's pre-event rating is Ro = 1700 based on N = 30 games. 
		 Then according to the formula above, 
		 
		 Ns = 50/ sqrt(1 + pow((2200-1700),2)/ 100000 ) = 50/sqrt(1.87) = 26.7

Consequently, the value of Np is the smaller of N=30 and Ns = 26.7, which is 
therefore Np = 26.7. So the effective number of games for the player in this 
example is .Np = 26.7

  //comments, no change needed
*/
	if (Ro_white > 2200)
	{
		Ns_white = 50;
	}
	else
	{
		Ns_white = 50/ sqrt(1+pow((2200-Ro_white),2)/100000 );
	}
	Np_white = min(No_white, Ns_white);
	if (No_white == 0)
	  Np_white  = 1;

	if (Ro_black > 2200)
	{
		Ns_black = 50;
	}
	else
	{
		Ns_black = 50/ sqrt(1+pow((2200-Ro_black),2)/100000 );
	}
	Np_black = min(No_black, Ns_black);
	if (No_black == 0)
    	Np_black  = 1;

/*
Step 3: Calculate a first rating estimate for each unrated player using 
        the "special" rating formula
		Let Ro (prior rating) and N(number of games) be values assigned 
		in step 1. however let number of effective games be 1 for each unrated

NOTE: the 5 steps would cause us to compute ratings for unrated individuals twice...
this seems to leads to a heavier weighting of the first game.
We will just use the values computed in steps 1 and 2 in step 4
this makes more sense because we are rating 1 game only...

*/

/*
Step 4: For every (each) player calculate an intermediate rating with 
        appropriate rating formula

If player has played less than 8 games OR
either won all games or lost all games, use the "special" rating formula

otherwise...
use the "normal" formula

*/

{
	double We;
	if (No_white < 8)
	    We = PWe(Ro_white,Ro_black);
	else
	    We = 1 / ( 1 + pow( 10.0, -1.0* (Ro_white - Ro_black) / 400) );
	float K = 800 / (Np_white + 1);
	Rfinal_white = Ro_white + K * ( whiteScore - We );
	
	//make sure rating does not drop if winning
	if ((whiteScore == 1) && (Rfinal_white < Ro_white))
		Rfinal_white = Ro_white;
	//make sure rating does not climb if loosing
	if ((whiteScore == 0) && (Rfinal_white > Ro_white))
		Rfinal_white = Ro_white;
}

{
	double We;
	if (No_black < 8)
	    We = PWe(Ro_black,Ro_white);
	else
	    We = 1 / ( 1.0 + pow( 10.0, -1.0* (Ro_black - Ro_white) / 400) );
	double K      = 800 / (Np_black + 1);
	Rfinal_black = Ro_black + K * ( blackScore - We );

	//make sure rating does not drop if winning
	if ((blackScore == 1) && (Rfinal_black < Ro_black))
		Rfinal_black = Ro_black;
	//make sure rating does not climb if loosing
	if ((blackScore == 0) && (Rfinal_black > Ro_black))
		Rfinal_black = Ro_black;
}



/*
Step 5: Repeat the computation from step 4 for each player, again using a 
        player's pre-event rating (or result of  step 1), but using the 
		results of step 4 for the opponents's ratings.

  we will igonre this because this is to make computations more acureate when
  "event" has multiple games, but, our "events" consist of exactly one game ALWAYS
  therefore this step not needed...
*/

/*
Step 6: Apply minimums (floors)

*/
	int floor = 100;
    if (white.get_numGames() > 25)
	{
		//only apply regular floors to regualr ratings...
        int temp  = ( (int)white.get_highest() - 200) / 100; //truncs!
		floor = temp * 100;
		if (floor > 2100)
			floor = 2100;
		if (floor < 1400)
			floor = 100;			
	}
	int wRating = (int)Rfinal_white;
	if (wRating < floor)
        white.set_rating( floor );
	else
		white.set_rating( wRating );
	white.set_numGames( white.get_numGames() + 1);
	white.set_rawScore( white.get_rawScore() + whiteScore);
    if (  (white.get_numGames() > 25)
        &&(white.get_rating() > white.get_highest() ) )
			white.set_highest( white.get_rating() );

    if (black.get_numGames() > 25)
	{
		//only apply regular floors to regualr ratings...
        int temp  = ( (int)black.get_highest() - 200) / 100; //truncs!
		floor = temp * 100;
		if (floor > 2100)
			floor = 2100;
		if (floor < 1400)
			floor = 100;			
	}
	int bRating = (int)Rfinal_black;
	if (bRating < floor)
        black.set_rating( floor );
	else
		black.set_rating( bRating );
	black.set_numGames( black.get_numGames() + 1);
	black.set_rawScore( black.get_rawScore() + blackScore);
    if (  (black.get_numGames() > 25)
        &&(black.get_rating() > black.get_highest() ) )
			black.set_highest( black.get_rating() );
    
}


//HARKNESS SYSTEM*
//
//Opponent 	    If High Wins		If Low Wins 		If a Draw 
//Rating 	    Add to Winner and	Add to Winner and	Add to Low and 
//Difference	Deduct from Loser 	Deduct from Loser 	Deduct fromHigh 
//  
//
//  0 to  24 	16                  16                  0 
// 25 to  49 	15                  17                  1 
// 50 to  74	14	                18	                2 
// 75 to  99	13	                19	                3 
//100 to 124	12	                20	                4 
//125 to 149	11	                21	                5 
//150 to 174	10	                22	                6 
//175 to 199	9	                23	                7 
//200 to 224	8	                24	                8 
//225 to 249	7	                25	                9 
//250 to 274	6	                26	                10 
//275 to 299	5	                27	                11 
//300 or more	4	                28	                12 
//
//*Official USCF Rulebook 4th Ed. , p. 156


int HarknessDelta(int rWhite, int rBlack, float whiteScore, float blackScore)
{
	int delta = 0;
    if (rWhite >= rBlack)
    {
        if (whiteScore > blackScore)
		{
			//expected result
			delta = max( 16 - (rWhite - rBlack)/25 , 4 );
		}
		else if (blackScore > whiteScore)
		{
			//upset
			delta = -1 * min( (rWhite - rBlack)/25 + 16, 28 );
		}
		else
		{
			//draw
			delta = -1 * min( (rWhite - rBlack)/25, 12 );
		}
    }
    else
    {
        if (blackScore > whiteScore)
		{
			//expected result
			delta = max( 16 - (rBlack - rWhite)/25 , 4 );
		}
		else if (whiteScore > blackScore)
		{
			//upset
			delta = -1 * min( (rBlack - rWhite)/25 + 16, 28 );
		}
		else
		{
			//draw
			delta = -1 * min( (rBlack - rWhite)/25, 12 );
		}
        delta *= -1;
    }
	return delta;
}

void ComputeHarknessRatings(CPlayer& white, CPlayer& black, float whiteScore, float blackScore)
{
    long rWhite = white.get_rating();
    long rBlack = black.get_rating();
	int delta = HarknessDelta(rWhite, rBlack, whiteScore, blackScore);
	white.set_rating( rWhite + delta);
    black.set_rating( rBlack - delta);
}

