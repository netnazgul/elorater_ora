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
// eloRater.cpp : Defines the class behaviors for the application.
//
//allows to compile for use with office 2000
//comment out if compiliong for offiec 97 or 98
#define OFFICE2000 1

#include "stdafx.h"
#include "group.h"
#include "eloRater.h"
#include "eloRaterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEloRaterApp

BEGIN_MESSAGE_MAP(CEloRaterApp, CWinApp)
	//{{AFX_MSG_MAP(CEloRaterApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEloRaterApp construction

CEloRaterApp::CEloRaterApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEloRaterApp object

CEloRaterApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CEloRaterApp initialization

BOOL CEloRaterApp::InitInstance()
{
#ifdef OFFICE2000
//	AfxGetModuleState()->m_dwVersion = 0x0601;
#endif


	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CEloRaterDlg dlg;
	if (m_lpCmdLine[0] != '\0')
    {	 
		CString cmdParam = CString(m_lpCmdLine);

		//strip off quotes if they exists...
		if (cmdParam[0] == '"')
			cmdParam = cmdParam.Mid(1, cmdParam.GetLength()-2);

		int prev = 0;
		int test = 0;
		int length = cmdParam.GetLength();
		while (test > -1)
		{
			test = cmdParam.Find('\\',prev);
			if (test > -1)
				prev =  test +1;
		}
		CString fileName;
		CString path;
		if (prev == 0)
		{
			fileName = cmdParam.Left(length);
			path = "";
		}
		else
		{
			fileName = cmdParam.Mid(prev,length - prev);
			path = cmdParam.Left(prev);
		}

		int dot = fileName.Find('.');
		if (dot > -1)
		{
			int length = fileName.GetLength();
			CString extension = fileName.Right(length - dot);
			if (extension == ".elo")
			{
				CString name = fileName.Left(dot);
				dlg.SetPath(path);
				dlg.SetName(name);
			}
			else
			{
			}
		}
		else
		{
			dlg.SetName(fileName);
		}
	}
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	return FALSE;
}
