/**
 * @file MainFrame.cpp
 * @authors Derek Hubler, Omay Dogan
 */

#include "pch.h"
#include "ids.h"
#include "MainFrame.h"
#include "GameView.h"

using namespace std;

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Sparty Gnome",
            wxDefaultPosition,  wxSize( 1000,800 ));

    // Create the view class object as a child of MainFrame
    auto gameView = new GameView();
    gameView->Initialize(this);

    auto menuBar = new wxMenuBar();

    auto fileMenu = new wxMenu();
    auto levelMenu = new wxMenu(); //moved to GameView.cpp
    auto helpMenu = new wxMenu();

    menuBar->Append(fileMenu, L"&File" );

    menuBar->Append(helpMenu, L"&Help");

    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

    SetMenuBar( menuBar );

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);

    gameView->AddMenus(this, menuBar, fileMenu, levelMenu);

}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * About menu option handlers
 * @param event
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"About Sparty Gnome",
            L"Sparty Gnome",
            wxOK,
            this);
}
