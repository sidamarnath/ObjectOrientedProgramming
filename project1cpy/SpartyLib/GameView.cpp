/**
 * @file GameView.cpp
 *
 * @author Kathryn Nagy
 */

#include "pch.h"
#include "ids.h"
#include "GameView.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <wx/stdpaths.h>
#include "Game.h"

using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;

///XML for level 0
const wstring levelZeroFile = L"../levels/level0.xml";
///XML for level 1
const wstring levelOneFile = L"../levels/level1.xml";
///XML for level 2
const wstring levelTwoFile = L"../levels/level2.xml";
///XML for level 3
const wstring levelThreeFile = L"../levels/level3.xml";

/// integer denoting level 0
const int levelZero = 0;
/// integer denoting level 1
const int levelOne = 1;
/// integer denoting level 2
const int levelTwo = 2;
/// integer denoting level 3
const int levelThree = 3;

/**
 * Initialize the GameView class
 * @param mainFrame mainframe parent of this view
 */
void GameView::Initialize(wxFrame *mainFrame)
{
    Create(mainFrame, wxID_ANY);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &GameView::OnPaint, this);

    // Determine where the images are stored
    //auto standardPaths = wxStandardPaths::Get();
    wxStandardPaths& standardPaths = wxStandardPaths::Get();
    std::wstring resourcesDir = standardPaths.GetResourcesDir().ToStdWstring();
    // mGame.SetImagesDirectory(resourcesDir);
    OnGameOpen();

    Bind(wxEVT_KEY_DOWN, &GameView::OnKeyDown, this);
    Bind(wxEVT_KEY_UP, &GameView::OnKeyUp, this);

    mTimer.Bind(wxEVT_TIMER, &GameView::OnTimer, this);
    mTimer.Start(FrameDuration);

    mScoreTimer.Bind(wxEVT_TIMER, &GameView::OnScoreTimer, this);
    mScoreTimer.Start(1000);
}

/**
 * Add menus specific to the view
 * @param mainFrame The main frame that owns the menu bar
 * @param menuBar The menu bar to add menus to
 * @param fileMenu The file menu, so we can add to it if we wish
 * @param levelMenu The view menu, so we can add to it if we wish
 */
void GameView::AddMenus(wxFrame* mainFrame, wxMenuBar *menuBar, wxMenu* fileMenu, wxMenu* levelMenu)
{

    // Options added to the view menu
    menuBar->Append(levelMenu, L"&Level" );

    levelMenu->Append(IDM_LEVEL_0, "Level 0", L"Load Level 0");
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevel0, this, IDM_LEVEL_0);
    levelMenu->Append(IDM_LEVEL_1, "Level 1", L"Load Level 1");
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevel1, this, IDM_LEVEL_1);
    levelMenu->Append(IDM_LEVEL_2, "Level 2", L"Load Level 2");
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevel2, this, IDM_LEVEL_2);
    levelMenu->Append(IDM_LEVEL_3, "Level 3", L"Load Level 3");
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevel3, this, IDM_LEVEL_3);

}

/**
 * Exit menu option handlers
 * @param event
 */
void GameView::OnLevel0(wxCommandEvent& event)
{
    mGame.UpdateLevel(0);
    Refresh();

}

/**
 * Exit menu option handlers
 * @param event
 */
void GameView::OnLevel1(wxCommandEvent& event)
{
    mGame.UpdateLevel(levelOne);
    mGame.ReturnGnomeToStart();
    Refresh();

}

/**
 * Exit menu option handlers
 * @param event
 */
void GameView::OnLevel2(wxCommandEvent& event)
{
    mGame.UpdateLevel(levelTwo);
    mGame.ReturnGnomeToStart();
    Refresh();

}

/**
 * Exit menu option handlers
 * @param event
 */
void GameView::OnLevel3(wxCommandEvent& event)
{
    mGame.UpdateLevel(levelThree);
    mGame.ReturnGnomeToStart();
    Refresh();

}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent &event)
{
    wxAutoBufferedPaintDC dc(this);
    wxBrush background (*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    auto size = GetClientSize();
    auto mGraphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));
    mGame.OnDraw(mGraphics, size.GetWidth(), size.GetHeight()); // This passes parameters to draw function for mGame

    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    mGame.Update(elapsed);
}

/**
 * File>Open menu handler
 */
void GameView::OnGameOpen()
{
    mGame.Load(levelZeroFile);
    mGame.UpdateLevel(levelOne);
    mGame.Load(levelOneFile);
    mGame.UpdateLevel(levelTwo);
    mGame.Load(levelTwoFile);
    mGame.UpdateLevel(levelThree);
    mGame.Load(levelThreeFile);
    mGame.UpdateLevel(levelOne);
    mGame.ReturnGnomeToStart();
}

/**
 * event handler for the timer
 * @param event timer event
 */
void GameView::OnTimer(wxTimerEvent &event)
{
    Refresh();
    mTimer.Start(FrameDuration);
}

/**
 * event handler for the score timer
 * @param event timer event
 */
void GameView::OnScoreTimer(wxTimerEvent &event)
{
    mGame.TimerRefresh();
}

/**
 * event handler for pressing a key on the keyboard
 * @param event key event
 */
void GameView::OnKeyDown(wxKeyEvent& event)
{
    mGame.OnKeyDown(event);
    Refresh();
}

/**
 * event handler for releasing a key on the keyboard
 * @param event key event
 */
void GameView::OnKeyUp(wxKeyEvent& event)
{
    mGame.OnKeyUp(event);
    Refresh();
}