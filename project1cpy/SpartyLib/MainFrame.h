/**
 * @file MainFrame.h
 * @authors Derek Hubler, Omay Dogan
 *
 *
 */

#ifndef PROJECT1_MAINFRAME_H
#define PROJECT1_MAINFRAME_H


class GameView;

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame {
private:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

public:

    void Initialize();
};

#endif //PROJECT1_MAINFRAME_H
