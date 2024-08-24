/**
 * @file MainFrame.h
 * @author Charles B. Owen
 *
 * The top-level (main) frame of the application
 */
#ifndef _MAINFRAME_H_
#define _MAINFRAME_H_


class ViewEdit;
class ViewTimeline;
class Picture;

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    /// View class for our edit window
    ViewEdit *mViewEdit = nullptr;

    /// View class for the timeline
    ViewTimeline *mViewTimeline = nullptr;

    /// The picture object we are viewing/editing
    std::shared_ptr<Picture> mPicture;


public:
    MainFrame();
    void Initialize();

};

#endif //_MAINFRAME_H_
