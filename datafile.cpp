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
#include "datafile.h"

CDataFile::CDataFile(CString fileName)
{
    m_fileName = fileName;
    m_isOpen   = false;
    m_os       = 0;
    m_is       = 0;
}

CDataFile::~CDataFile()
{
    m_fileName = "";
    m_isOpen   = false;
    m_os       = 0;
    m_is       = 0;
}

bool CDataFile::OpenForRead()
{
    bool retVal = false;
    if ((m_fileName != "") && (m_isOpen == false))
    {
        m_is = new ifstream(m_fileName.GetBuffer());
		m_isOpen = (m_is != NULL);
		retVal = m_isOpen;
    }
    return retVal;
}

bool CDataFile::OpenForWrite(bool append)
{
    bool retVal = false;
    if ((m_fileName != "") && (m_isOpen == false))
    {
        m_os = (append)?new ofstream(m_fileName.GetBuffer(), ios::app):
                        new ofstream(m_fileName.GetBuffer(), ios::out);  
		m_isOpen = (m_os != NULL);
		retVal = m_isOpen;
    }
    return retVal;
}

void CDataFile::Close()
{
    if ((m_fileName != "") && (m_isOpen == true))
    {
        if (m_is)
        {
            m_is->close();
            delete m_is;
            m_is = 0;
        }
        if (m_os)
        {
            m_os->flush();
            m_os->close();
            delete m_os;
            m_os = 0;
        }
		m_isOpen = false;
    }
}



//**************************************************************************************
// Implementation of saveData
void CDataFile::saveData(char data)
{
    if (m_os)
    {
        m_os->write(&data, sizeof(char));
        *m_os << endl;
    }
}

//**************************************************************************************
// Implementation of saveData
void CDataFile::saveData(unsigned char data)
{
    if (m_os)
    {
        char buff[200];
        sprintf(buff,"%u",data);
        m_os->write(buff,sizeof(char)*strlen(buff));
        *m_os << endl;
    }
}

//**************************************************************************************
// Implementation of saveData
void CDataFile::saveData(short data)
{
    if (m_os)
    {
        char buff[200];
        sprintf(buff,"%d",data);
        m_os->write(buff,sizeof(char)*strlen(buff));
        *m_os << endl;
    }
}

//**************************************************************************************
// Implementation of saveData
void CDataFile::saveData(unsigned short data)
{
    if (m_os)
    {
        char buff[200];
        sprintf(buff,"%u",data);
        m_os->write(buff,sizeof(char)*strlen(buff));
        *m_os << endl;
    }
}

//**************************************************************************************
// Implementation of saveData
void CDataFile::saveData(long data)
{
    if (m_os)
    {
        char buff[200];
        sprintf(buff,"%d",data);
        m_os->write(buff,sizeof(char)*strlen(buff));
        *m_os << endl;
    }
}

//**************************************************************************************
// Implementation of saveData
void CDataFile::saveData(unsigned long data)
{
    if (m_os)
    {
        char buff[200];
        sprintf(buff,"%u",data);
        m_os->write(buff,sizeof(char)*strlen(buff));
        *m_os << endl;
    }
}

//**************************************************************************************
// Implementation of saveData
void CDataFile::saveData(float data)
{
    if (m_os)
    {
        char buff[200];
        sprintf(buff,"%f",data);
        m_os->write(buff,sizeof(char)*strlen(buff));
        *m_os << endl;
    }
}

//**************************************************************************************
// Implementation of saveData
void CDataFile::saveData(double data)
{
    if (m_os)
    {
        char buff[200];
        sprintf(buff,"%f",data);
        m_os->write(buff,sizeof(char)*strlen(buff));
        *m_os << endl;
    }
}

//**************************************************************************************
// Implementation of saveData
void CDataFile::saveData(CString &data)
{
    if (m_os)
    {
        m_os->write(data.GetBuffer(),sizeof(char)*data.GetLength());
        *m_os << endl;
    }
}

//**************************************************************************************
// Implementation of saveData
void CDataFile::saveData(bool &data)
{
    if (m_os)
    {
        if (data)
            m_os->write("TRUE", sizeof(char)*5);
        else
            m_os->write("FALSE", sizeof(char)*5);
        *m_os << endl;
    }
}

//**************************************************************************************
// Implementation of loadData
void CDataFile::loadData(char &data)
{
    if (m_is)
    {
        char buff[200];
        m_is->getline(buff,200);
        strcpy(&data,buff);
    }
}

//**************************************************************************************
// Implementation of loadData
void CDataFile::loadData(unsigned char &data)
{
    if (m_is)
    {
        char buff[200];
        m_is->getline(buff,200);
        strcpy((char*)&data,buff);
    }
}

//**************************************************************************************
// Implementation of loadData
void CDataFile::loadData(short &data)
{
    if (m_is)
    {
        char buff[200];
        m_is->getline(buff,200);
        int temp = atoi(buff);
        short temp2 = (short)temp;
        data = temp;
    }
}

//**************************************************************************************
// Implementation of loadData
void CDataFile::loadData(unsigned short &data)
{
    if (m_is)
    {
        char buff[200];
        m_is->getline(buff,200);
        int temp = atoi(buff);
        unsigned short temp2 = (unsigned short)temp;
        data = temp;
    }
}

//**************************************************************************************
// Implementation of loadData
void CDataFile::loadData(long &data)
{
    if (m_is)
    {
        char buff[200];
        m_is->getline(buff,200);
        data = atol(buff);
    }
}

//**************************************************************************************
// Implementation of loadData
void CDataFile::loadData(unsigned long &data)
{
    if (m_is)
    {
        char buff[200];
        m_is->getline(buff,200);
        data = (unsigned long)atoi(buff);
    }
}

//**************************************************************************************
// Implementation of loadData
void CDataFile::loadData(float &data)
{
    if (m_is)
    {
        char buff[200];
        m_is->getline(buff,200);
        data = (float)atof(buff);
    }
}

//**************************************************************************************
// Implementation of loadData
void CDataFile::loadData(double &data)
{
    if (m_is)
    {
        char buff[200];
        m_is->getline(buff,200);
        double temp = atoi(buff);
    }
}

//**************************************************************************************
// Implementation of loadData
void CDataFile::loadData(CString &data)
{
    if (m_is)
    {
        char buff[256];
        m_is->getline(buff,256);
        data = buff;
    }
}

//**************************************************************************************
// Implementation of loadData
void CDataFile::loadData(bool &data)
{    
    if (m_is)
    {
        char buff[200];
        m_is->getline(buff,200);
        if (strcmp(buff,"TRUE") == 0)
            data = true;
        else
            data = false;
    }
}


