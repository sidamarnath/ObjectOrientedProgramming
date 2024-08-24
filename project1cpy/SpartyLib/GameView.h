/**
 * @file GameView.h
 *
 * @author Kathryn Nagy
 *
 * Child of MainFrame, window in which the game is displayed.
 */

#ifndef PROJECT1_GAMEVIEW_H
#define PROJECT1_GAMEVIEW_H

#include "Game.h"

/**
 * GameView class
 */
class GameView : public wxWindow {
private:
    Game mGame; ///< Game object
    wxTimer mTimer; ///< timer object
    wxTimer mScoreTimer; ///< score timer
    std::shared_ptr<wxGraphicsContext> mGraphics; ///< graphics context for the window

    void OnPaint(wxPaintEvent &event);

    void OnTimer(wxTimerEvent &event);
    void OnScoreTimer(wxTimerEvent &event);

    void OnLevel0(wxCommandEvent& event);
    void OnLevel1(wxCommandEvent& event);
    void OnLevel2(wxCommandEvent& event);
    void OnLevel3(wxCommandEvent& event);

    void OnKeyDown(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;
    /// The last stopwatch time
    long mTime = 0;
public:
    void Initialize(wxFrame *mainFrame);
    void AddMenus(wxFrame* mainFrame, wxMenuBar *menuBar, wxMenu* fileMenu, wxMenu* viewMenu);


    void OnGameOpen();
};

#endif //PROJECT1_GAMEVIEW_H
