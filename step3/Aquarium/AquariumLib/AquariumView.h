/**
 * @file AquariumView.h
 * @author Sid Amarnath
 *
 *
 */

#ifndef AQUARIUM_AQUARIUMVIEW_H
#define AQUARIUM_AQUARIUMVIEW_H

#include "Aquarium.h"
//#include <wx/frame.h>

class AquariumView : public wxWindow{
private:
    void OnPaint(wxPaintEvent& event);
    /// An object that describes our aquarium
    Aquarium  mAquarium;
    std::shared_ptr<Item> mGrabbedItem;

public:
    void Initialize(wxFrame* parent);
    void OnAddFishBetaFish(wxCommandEvent& event);
    void OnAddFishBubblesFish(wxCommandEvent& event);
    void OnAddFishAnglerFish(wxCommandEvent& event);
    void OnAddFishMosquitoFish(wxCommandEvent& event);
    void OnLeftDown(wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent &event);
    void OnMouseMove(wxMouseEvent &event);


};

#endif //AQUARIUM_AQUARIUMVIEW_H
