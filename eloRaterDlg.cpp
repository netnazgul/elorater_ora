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
// eloRaterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "eloRater.h"
#include "eloRaterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEloRaterDlg dialog

CEloRaterDlg::CEloRaterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEloRaterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEloRaterDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_name = "";
	m_path = "";
	m_group = NULL;
}

void CEloRaterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEloRaterDlg)
	DDX_Control(pDX, IDC_JOBTAB, m_jobTabControl);
	//}}AFX_DATA_MAP
}

bool CEloRaterDlg::NewGroup(CString name, bool useHarkness)
{
	//group should not be defined at this moment...
	if (m_group != NULL)
		return false;

    bool retVal = false;
	CGroup *group = new CGroup();
	group->set_name(name);
	group->set_useHarkness(useHarkness);
	m_group = group;
	if (m_addGameDlg != 0)
	{
		m_addGameDlg->LoadGroup(group);
		m_addGameDlg->EnableWindow(true);
		SetTabIcon(0, true);
	}
	if (m_viewRatingsDlg != 0)
	{
		m_viewRatingsDlg->LoadGroup(group);
		m_viewRatingsDlg->EnableWindow(true);
		SetTabIcon(1, true);
	}
	if (m_addPlayerDlg != 0)
	{
		m_addPlayerDlg->LoadGroup(group);
		m_addPlayerDlg->EnableWindow(true);
		SetTabIcon(2, true);
	}
	if (m_addGroupDlg != 0)
	{
		m_addGroupDlg->LoadGroup(group);
		m_addGroupDlg->EnableWindow(true);
		SetTabIcon(3, true);
	}
	//if (m_aboutDlg != 0)
	//{
	//	m_aboutDlg->LoadGroup(group);
	//	m_aboutDlg->EnableWindow(true);
	//	SetTabIcon(4, true);
	//}
	retVal = true;
	return retVal;
}

bool CEloRaterDlg::LoadGroup(CString name)
{
	//group should not be defined at this moment...
	if (m_group != NULL)
		return false;

    bool retVal = false;
	CGroup *group = new CGroup();
	group->set_name(name);
	if (group->loadData())
	{
		m_group = group;
		if (m_addGameDlg != 0)
		{
			m_addGameDlg->LoadGroup(group);
			m_addGameDlg->EnableWindow(true);
			SetTabIcon(0, true);
		}
		if (m_viewRatingsDlg != 0)
		{
			m_viewRatingsDlg->LoadGroup(group);
			m_viewRatingsDlg->EnableWindow(true);
			SetTabIcon(1, true);
		}
		if (m_addPlayerDlg != 0)
		{
			m_addPlayerDlg->LoadGroup(group);
			m_addPlayerDlg->EnableWindow(true);
			SetTabIcon(2, true);
		}
		if (m_addGroupDlg != 0)
		{
			m_addGroupDlg->LoadGroup(group);
			m_addGroupDlg->EnableWindow(true);
			SetTabIcon(3, true);
		}
		//if (m_aboutDlg != 0)
		//{
		//	m_aboutDlg->LoadGroup(group);
		//	m_aboutDlg->EnableWindow(true);
		//}
		retVal = true;
	}
	return retVal;
}

void CEloRaterDlg::ReloadGroup()
{
	if (m_group != NULL)
	{
		m_group->saveData();
		if (m_addGameDlg != 0)
		{
			m_addGameDlg->UnloadGroup();
			m_addGameDlg->LoadGroup(m_group);
		}
		if (m_viewRatingsDlg != 0)
		{
			m_viewRatingsDlg->UnloadGroup();
			m_viewRatingsDlg->LoadGroup(m_group);
		}
		if (m_addPlayerDlg != 0)
		{
			m_addPlayerDlg->UnloadGroup();
			m_addPlayerDlg->LoadGroup(m_group);
		}
		if (m_addGroupDlg != 0)
		{
			m_addGroupDlg->UnloadGroup();
			m_addGroupDlg->LoadGroup(m_group);
		}
		//if (m_aboutDlg != 0)
		//{
		//	m_aboutDlg->UnloadGroup();
		//	m_aboutDlg->LoadGroup(m_group);
		//}
	}
}

void CEloRaterDlg::UnloadGroup()
{
	if (m_group != NULL)
	{
		if (m_addGameDlg != 0)
		{
			m_addGameDlg->UnloadGroup();
			m_addGameDlg->EnableWindow(false);
			SetTabIcon(0, false);
		}
		if (m_viewRatingsDlg != 0)
		{
			m_viewRatingsDlg->UnloadGroup();
			m_viewRatingsDlg->EnableWindow(false);
			SetTabIcon(1, false);
		}
		if (m_addPlayerDlg != 0)
		{
			m_addPlayerDlg->UnloadGroup();
			m_addPlayerDlg->EnableWindow(false);
			SetTabIcon(2, false);
		}
		if (m_addGroupDlg != 0)
		{
			m_addGroupDlg->UnloadGroup();
			m_addGroupDlg->EnableWindow(true);
			SetTabIcon(3, true);
		}
		//if (m_aboutDlg != 0)
		//{
		//	m_aboutDlg->UnloadGroup();
		//	m_aboutDlg->EnableWindow(false);
		//}
		m_group->saveData();
		delete m_group;
		m_group = NULL;
	}
}


BEGIN_MESSAGE_MAP(CEloRaterDlg, CDialog)
	//{{AFX_MSG_MAP(CEloRaterDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_JOBTAB, OnSelchangeJobtab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CEloRaterDlg::SetTabIcon(int tab, bool enabled)
{
	if ((tab < 0) && (tab > 4))
		return;

	//now set the icon...
	TC_ITEM item;
	m_jobTabControl.GetItem(tab,&item);
	item.mask = TCIF_IMAGE;
	if (enabled)
	{
		item.iImage = tab + 1;
	}
	else
	{
		item.iImage = 0;
	}
	m_jobTabControl.SetItem(tab,&item);
}

/////////////////////////////////////////////////////////////////////////////
// CEloRaterDlg message handlers

BOOL CEloRaterDlg::OnInitDialog()
{
	BOOL retVal = FALSE;
	if (CDialog::OnInitDialog() == TRUE)
	{
		// Set the icon for this dialog.  The framework does this automatically
		//  when the application's main window is not a dialog
		SetIcon(m_hIcon, TRUE);			// Set big icon
		SetIcon(m_hIcon, FALSE);		// Set small icon
		
		CImageList* pawns = new CImageList();
		pawns->Create(16,16,TRUE,6,1);
		HICON grayp    = AfxGetApp()->LoadIcon(IDI_GRAYPAWN);
		HICON redp     = AfxGetApp()->LoadIcon(IDI_REDPAWN);
		HICON greenp   = AfxGetApp()->LoadIcon(IDI_GREENPAWN);
		HICON bluep    = AfxGetApp()->LoadIcon(IDI_BLUEPAWN);
		HICON yellowp  = AfxGetApp()->LoadIcon(IDI_YELLOWPAWN);
		HICON cyanp    = AfxGetApp()->LoadIcon(IDI_CYANPAWN);
		pawns->Add(grayp    );   
		pawns->Add(bluep    );    
		pawns->Add(cyanp    );   
		pawns->Add(greenp   );  
		pawns->Add(yellowp  );
		pawns->Add(redp     );    
		m_jobTabControl.SetImageList(pawns);

		CRect placeHere;
		CRect itemRect;
		m_jobTabControl.GetClientRect(placeHere);

		//ADD GAME TAB...
		m_addGameDlg     = new CAddGameDlg();
		if (m_addGameDlg->Create(this))
		{
			m_jobTabControl.InsertItem(0, "Games");
			m_jobTabControl.GetClientRect(placeHere);
			m_jobTabControl.GetItemRect(0,itemRect);
			placeHere.top  = itemRect.bottom + 5;
			placeHere.left   += 5;
			placeHere.right  -= 5;
			placeHere.bottom -= 5;
			m_jobTabControl.ClientToScreen(placeHere);
			this->ScreenToClient(placeHere);

			m_addGameDlg->MoveWindow(placeHere,TRUE);
			m_addGameDlg->ShowWindow(SW_SHOW);
			m_addGameDlg->EnableWindow(false);
			SetTabIcon(0, false);
		}
		else
		{
			delete m_addGameDlg;
			m_addGameDlg = 0;
		}

		//VIEW RATINGS TAB...
		m_viewRatingsDlg = new CViewRatingsDlg();
		if (m_viewRatingsDlg->Create(this))
		{
			m_jobTabControl.InsertItem(1, "Ratings");
			m_jobTabControl.GetClientRect(placeHere);
			m_jobTabControl.GetItemRect(0,itemRect);
			placeHere.top  = itemRect.bottom + 5;
			placeHere.left   += 5;
			placeHere.right  -= 5;
			placeHere.bottom -= 5;
			m_jobTabControl.ClientToScreen(placeHere);
			this->ScreenToClient(placeHere);

			m_viewRatingsDlg->MoveWindow(placeHere,TRUE);
			m_viewRatingsDlg->ShowWindow(SW_HIDE);
			m_viewRatingsDlg->EnableWindow(false);
			SetTabIcon(1, false);
		}
		else
		{
			delete m_addPlayerDlg;
			m_viewRatingsDlg = 0;
		}

		//ADD PLAYER TAB...
		m_addPlayerDlg   = new CAddPlayerDlg(); 
		if (m_addPlayerDlg->Create(this))
		{
			m_jobTabControl.InsertItem(2, "Players");
			m_jobTabControl.GetClientRect(placeHere);
			m_jobTabControl.GetItemRect(0,itemRect);
			placeHere.top  = itemRect.bottom + 5;
			placeHere.left   += 5;
			placeHere.right  -= 5;
			placeHere.bottom -= 5;
			m_jobTabControl.ClientToScreen(placeHere);
			this->ScreenToClient(placeHere);

			m_addPlayerDlg->MoveWindow(placeHere,TRUE);
			m_addPlayerDlg->ShowWindow(SW_HIDE);
			m_addPlayerDlg->EnableWindow(false);
			SetTabIcon(2, false);
		}
		else
		{
			delete m_addPlayerDlg;
			m_addPlayerDlg = 0;
		}

		//ADD GROUP TAB...
		m_addGroupDlg   = new CAddGroupDlg();
		m_addGroupDlg->SetPath(m_path);
		if (m_addGroupDlg->Create(this))
		{
			m_jobTabControl.InsertItem(3, "Groups");
			m_jobTabControl.GetClientRect(placeHere);
			m_jobTabControl.GetItemRect(0,itemRect);
			placeHere.top  = itemRect.bottom + 5;
			placeHere.left   += 5;
			placeHere.right  -= 5;
			placeHere.bottom -= 5;
			m_jobTabControl.ClientToScreen(placeHere);
			this->ScreenToClient(placeHere);

			m_addGroupDlg->MoveWindow(placeHere,TRUE);
			m_addGroupDlg->ShowWindow(SW_HIDE);
			m_addGroupDlg->EnableWindow(false);
			SetTabIcon(3, false);
		}
		else
		{
			delete m_aboutDlg;
			m_aboutDlg = 0;
		}

		//ABOUT TAB...
		m_aboutDlg   = new CAboutDlg(); 
		if (m_aboutDlg->Create(this))
		{
			m_jobTabControl.InsertItem(4, "About");
			m_jobTabControl.GetClientRect(placeHere);
			m_jobTabControl.GetItemRect(0,itemRect);
			placeHere.top  = itemRect.bottom + 5;
			placeHere.left   += 5;
			placeHere.right  -= 5;
			placeHere.bottom -= 5;
			m_jobTabControl.ClientToScreen(placeHere);
			this->ScreenToClient(placeHere);

			m_aboutDlg->MoveWindow(placeHere,TRUE);
			m_aboutDlg->ShowWindow(SW_HIDE);
			m_aboutDlg->EnableWindow(true);
			SetTabIcon(4, true);
		}
		else
		{
			delete m_aboutDlg;
			m_aboutDlg = 0;
		}

		if (m_name.GetLength() > 0)
		{
			CString fileName = m_path+m_name;
			if (false == this->LoadGroup(fileName))
			{
				MessageBox("Failed to load the group from the command line.\n"
						   "The filename specified does not exist or it is\n"
						   "not a valid ELO data file.  Please check the \n"
						   "command line parameter in your pif (shortcut).\n"
						   "Or select the desired group from the group list\n"
						   "on the 'Groups' tab.",
						   "Load Error", MB_ICONSTOP);
			}
		}
		else
		{
			MessageBox("There is no Rating Group Defined,\n"
					   "or currently selected to display.\n"
					   "Please select a group below, or\n"
					   "Add an new group by typing its name\n"
					   "and pressing ADD below.",
					   "No Group Data", MB_ICONINFORMATION);		
		}

		if (m_group != NULL)
		{
			m_jobTabControl.SetCurSel(0);
		}
		else
		{
			m_jobTabControl.SetCurSel(3);
			m_addGroupDlg->EnableWindow(true);
			SetTabIcon(3, true);
		}
		ShowChildren();
		
		//attempt to set the focus
		if (m_addGameDlg)
		{
			m_addGameDlg->SetDefaultTab();
			return FALSE;
		}
		if (m_addGroupDlg)
		{
			m_addGroupDlg->SetDefaultTab();
			return FALSE;
		}
		else if (m_addPlayerDlg)
		{
			m_addPlayerDlg->SetDefaultTab();
			return FALSE;
		}
		else  if (m_viewRatingsDlg)
		{
			m_viewRatingsDlg->SetDefaultTab();
			return FALSE;
		}
		else
			return FALSE;
	}
	return retVal;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEloRaterDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEloRaterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEloRaterDlg::OnSelchangeJobtab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	ShowChildren();
	*pResult = 0;
}

void CEloRaterDlg::ShowChildren()
{
	// TODO: Add your control notification handler code here
	switch (m_jobTabControl.GetCurSel())
	{
	case 4:
		if (m_addGameDlg) 
			m_addGameDlg->ShowWindow(SW_HIDE);
		if (m_addPlayerDlg) 
            m_addPlayerDlg->ShowWindow(SW_HIDE);
		if (m_viewRatingsDlg) 
			m_viewRatingsDlg->ShowWindow(SW_HIDE);
		if (m_addGroupDlg) 
            m_addGroupDlg->ShowWindow(SW_HIDE);
        if (m_aboutDlg)
			m_aboutDlg->ShowWindow(SW_SHOW);
		break;
	case 3:
		if (m_addGameDlg) 
			m_addGameDlg->ShowWindow(SW_HIDE);
		if (m_addPlayerDlg) 
            m_addPlayerDlg->ShowWindow(SW_HIDE);
		if (m_viewRatingsDlg) 
			m_viewRatingsDlg->ShowWindow(SW_HIDE);
		if (m_addGroupDlg) 
		{
			m_addGroupDlg->ShowWindow(SW_SHOW);
			m_addGroupDlg->SetDefaultTab();
		}
        if (m_aboutDlg)
			m_aboutDlg->ShowWindow(SW_HIDE);
		break;
	case 2:
		if (m_addGameDlg) 
			m_addGameDlg->ShowWindow(SW_HIDE);
		if (m_viewRatingsDlg) 
			m_viewRatingsDlg->ShowWindow(SW_HIDE);
		if (m_addPlayerDlg) 
		{
			m_addPlayerDlg->ShowWindow(SW_SHOW);
			m_addPlayerDlg->SetDefaultTab();
		}
		if (m_addGroupDlg) 
            m_addGroupDlg->ShowWindow(SW_HIDE);
        if (m_aboutDlg)
            m_aboutDlg->ShowWindow(SW_HIDE);
		break;
	case 1:
		if (m_addGameDlg) 
			m_addGameDlg->ShowWindow(SW_HIDE);
		if (m_viewRatingsDlg) 
		{
			m_viewRatingsDlg->ShowWindow(SW_SHOW);
			m_viewRatingsDlg->SetDefaultTab();
		}
		if (m_addPlayerDlg) 
			m_addPlayerDlg->ShowWindow(SW_HIDE);
		if (m_addGroupDlg) 
            m_addGroupDlg->ShowWindow(SW_HIDE);
        if (m_aboutDlg)
            m_aboutDlg->ShowWindow(SW_HIDE);
		break;
	case 0:
		if (m_addGameDlg) 
		{
			m_addGameDlg->ShowWindow(SW_SHOW);
			m_addGameDlg->SetDefaultTab();
		}
		if (m_addPlayerDlg) 
		m_addPlayerDlg->ShowWindow(SW_HIDE);
		if (m_viewRatingsDlg) 
		m_viewRatingsDlg->ShowWindow(SW_HIDE);
		if (m_addGroupDlg) 
            m_addGroupDlg->ShowWindow(SW_HIDE);
        if (m_aboutDlg)
            m_aboutDlg->ShowWindow(SW_HIDE);
		break;
	}	
}

BOOL CEloRaterDlg::DestroyWindow() 
{
	if (m_group != NULL)
	{
		this->UnloadGroup();
	}

	if (m_addGameDlg != 0) 
	{
		m_addGameDlg->DestroyWindow();
		delete m_addGameDlg;
	}
	if (m_addPlayerDlg != 0) 
	{
		m_addPlayerDlg->DestroyWindow();
		delete m_addPlayerDlg;
	}
	if (m_viewRatingsDlg != 0) 
	{
		m_viewRatingsDlg->DestroyWindow();
		delete m_viewRatingsDlg;
	}
	if (m_aboutDlg != 0) 
	{
		m_aboutDlg->DestroyWindow();
		delete m_aboutDlg;
	}
	if (m_addGroupDlg != 0) 
	{
		m_addGroupDlg->DestroyWindow();
		delete m_addGroupDlg;
	}

	return CDialog::DestroyWindow();
}
