/**
 * @file ViewTimeline.h
 * @author Charles B. Owen
 *
 * View class for the timeline area of the screen.
 */

#ifndef CANADIANEXPERIENCE_VIEWTIMELINE_H
#define CANADIANEXPERIENCE_VIEWTIMELINE_H

#include "PictureObserver.h"
#include "MainFrame.h"
//#include "Timeline.h"

class Timeline;
//class Picture;


/**
 * View class for the timeline area of the screen.
 */
class ViewTimeline final : public wxScrolledCanvas, public PictureObserver {
private:
    void OnLeftDown(wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnPaint(wxPaintEvent& event);

    /// Bitmap image for the pointer
    std::unique_ptr<wxImage> mPointerImage;

    /// Graphics bitmap to display
    wxGraphicsBitmap mPointerBitmap;

    /// Images directory member variable
    std::basic_string<wchar_t> mImagesDir;

    /// Flag to indicate we are moving the pointer
    bool mMovingPointer = false;

public:
    static const int Height = 90;      ///< Height to make this window

    ViewTimeline(wxFrame* parent);
    void UpdateObserver() override;

    /**
    * Handle an Edit>Timeline Properties... menu option
    * @param event The menu event
    */
    void OnEditTimelineProperties(wxCommandEvent& event);

    /**
    * Handle a Set keyframe menu option
    * @param event The menu event
    */
    void OnSetKeyframe(wxCommandEvent& event);

    /**
    * Handle a delete keyframe menu option
    * @param event The menu event
    */
    void OnDeleteKeyframe(wxCommandEvent& event);

    /**
    * Gets the image directory
    * @returns the image directory
    */
    std::basic_string<wchar_t> GetImagesDir() const { return mImagesDir; }

    /**
    * Sets the image directory
    * @param imagesDir The image directory
     * @returns the new image directory
    */
    void SetImagesDir(std::basic_string<wchar_t> imagesDir) { mImagesDir = imagesDir; }
};


#endif //CANADIANEXPERIENCE_VIEWTIMELINE_H
