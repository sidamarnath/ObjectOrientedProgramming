/**
 * @file AquariumView.h
 * @author Sid Amarnath
 *
 * Adds event handlers and ability to add fish and decor to the aquarium
 */

#ifndef AQUARIUM_AQUARIUMVIEW_H
#define AQUARIUM_AQUARIUMVIEW_H

#include "Aquarium.h"
//#include <wx/frame.h>
#include <wx/timer.h>

class AquariumView : public wxWindow{
private:
    void OnPaint(wxPaintEvent& event);
    /// An object that describes our aquarium
    Aquarium  mAquarium;
    std::shared_ptr<Item> mGrabbedItem;
    wxTimer mTimer;
    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;

public:
    void Initialize(wxFrame* parent);
    void OnAddFishBetaFish(wxCommandEvent& event);
    void OnAddFishBubblesFish(wxCommandEvent& event);
    void OnAddFishAnglerFish(wxCommandEvent& event);
    void OnAddDecorCastleDecor(wxCommandEvent& event);
    void OnFileSaveAs(wxCommandEvent& event);
    void OnFileOpen(wxCommandEvent& event);
    void OnLeftDown(wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent &event);
    void OnMouseMove(wxMouseEvent &event);
    void OnTimer(wxTimerEvent &event);


};

#endif //AQUARIUM_AQUARIUMVIEW_H
