/**
 * @file TimelineDlg.h
 * @author Sid Amarnath
 *
 * Timeline dialog box
 */

#ifndef CANADIANEXPERIENCE_TIMELINEDLG_H
#define CANADIANEXPERIENCE_TIMELINEDLG_H

#include "Timeline.h"

/**
 * Timeline dialog box
 */
class TimelineDlg final : public wxDialog {
private:
    /// Timeline we are working with
    Timeline *mTimeline;
    /// Number of frames in the animation
    int mNumberOfFrames;
    /// Frame rate in the animation
    int mFrameRate;

public:
    TimelineDlg(wxWindow *parent, Timeline *timeline);
    void OnOK(wxCommandEvent& event);

};

#endif //CANADIANEXPERIENCE_TIMELINEDLG_H
