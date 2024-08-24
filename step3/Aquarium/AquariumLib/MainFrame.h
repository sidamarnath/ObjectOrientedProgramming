/**
 * @file MainFrame.h
 * @author Sid Amarnath
 *
 * The top-level (main) frame of the application
 */

#ifndef AQUARIUM_MAINFRAME_H
#define AQUARIUM_MAINFRAME_H

//#include <wx/frame.h>

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame {
private:

public:
    void Initialize();
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);


};

#endif //AQUARIUM_MAINFRAME_H
