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

#ifndef __AF87652i3_DATAFILE_CLASS_DEFINITION_FILE_3i25678FA__
#define __AF87652i3_DATAFILE_CLASS_DEFINITION_FILE_3i25678FA__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// datafile.h : header file
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
using namespace std;

class CDataFile
{
public:
    CDataFile(CString fileName);
    virtual ~CDataFile();
    
    bool OpenForRead();
    bool OpenForWrite(bool append = false);
    void Close();

    //**********************************************************************************
	//  Description
	//    writes (saves) the data parameter to the stream 
	//
	// Parameters: 
    //    data      the value to save... this method has several overloads...
    //    each implementing the save for a different data type
    //
    //    ofstream *os   a pointer to the file stream to which to write the data
	//
	// Return Value: 
    //    none.
	//
    void saveData(char data);
    void saveData(unsigned char data);
    void saveData(short data);
    void saveData(unsigned short data);
    void saveData(long data);
    void saveData(unsigned long data);
    void saveData(float data);
    void saveData(double data);
    void saveData(CString &data);
    void saveData(bool &data);

	//**********************************************************************************
	//  Description
	//    reads (loads) the data parameter from the stream 
	//
	// Parameters: 
    //    data the address of the value to read)... this method has several overloads...
    //    each implementing the load for a different data type
    //
    //    ifstream *is   a pointer to the file stream to which to write the data
	//
	// Return Value: 
    //    none.
	//
    void loadData(char &data);
    void loadData(unsigned char &data);
    void loadData(short &data);
    void loadData(unsigned short &data);
    void loadData(long &data);
    void loadData(unsigned long &data);
    void loadData(float &data);
    void loadData(double &data);
    void loadData(CString &data);
    void loadData(bool &data);

	bool canRead() {return ( (m_isOpen == true) && (m_is != 0) );}
	bool canWrite(){return ( (m_isOpen == true) && (m_os != 0) );}

private:
    CString   m_fileName;
    bool      m_isOpen;
    ofstream* m_os;
    ifstream* m_is;
};
#endif //__AF87652i3_DATAFILE_CLASS_DEFINITION_FILE_3i25678FA__