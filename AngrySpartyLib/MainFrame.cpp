/**
 * @file MainFrame.cpp
 * @author Will Skaggs
 */

#include "pch.h"
#include "MainFrame.h"
#include "ids.h"
#include "GameView.h"

/**
 * MainFrame Initializer
 */
void MainFrame::Initialize()
{

    Create(nullptr, wxID_ANY, L"Angry Sparty",
            wxDefaultPosition, wxSize(1100, 700));

    auto sizer = new wxBoxSizer( wxVERTICAL );

    mGameView = new GameView();
    mGameView->Initialize(this);

    sizer->Add(mGameView,1, wxEXPAND | wxALL );

    SetSizer( sizer );
    Layout();


    // Create a menu bar
    auto menuBar = new wxMenuBar();

    // File menu
    auto fileMenu = new wxMenu();
    menuBar->Append(fileMenu, L"&File");

    // Level menu
    auto levelMenu = new wxMenu();
    menuBar->Append(levelMenu, L"&Level");

    // View menu
    auto viewMenu = new wxMenu();
    menuBar->Append(viewMenu, L"&View");

    // Help menu
    auto helpMenu = new wxMenu();
    menuBar->Append(helpMenu, L"&Help");
    
    //Level load menu options
    levelMenu->Append(IDM_LOADLEVELZERO, L"&Level 0", L"Load level 0");
    levelMenu->Append(IDM_LOADLEVELONE, L"&Level 1", L"Load level 1");
    levelMenu->Append(IDM_LOADLEVELTWO, L"&Level 2", L"Load level 2");
    levelMenu->Append(IDM_LOADLEVELTHREE, L"&Level 3", L"Load level 3");

    //Help Menu options
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

    //File Menu options
    fileMenu->Append(wxID_OPEN, "O&pen\tAlt-O", "Open the xml file to load items");
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");

    //View Menu options
    mGameView->AddMenus(this, menuBar, viewMenu);

    // Set the menu bar to this frame
    SetMenuBar(menuBar);

    // Status bar, Bind OnExit and OnAbout
    CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
}

/**
 * Exit menu option handlers
 * @param event Exit event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * about menu handler
 * @param event About Event
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"Angry Sparty",
            L"About AngrySparty by Royal Terns",
            wxOK,
            this);
}

/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MainFrame::OnClose(wxCloseEvent& event)
{
    mGameView->Stop();
    Destroy();
}