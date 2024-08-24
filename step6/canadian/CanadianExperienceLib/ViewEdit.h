/**
 * @file ViewEdit.h
 * @author Charles B. Owen
 *
 * Basic edit view class for the Canadian Experience
 *
 * The window is a child of the main frame, which holds this
 * window, the menu bar, and the status bar.
 */

#ifndef CANADIANEXPERIENCE_VIEWEDIT_H
#define CANADIANEXPERIENCE_VIEWEDIT_H

#include "PictureObserver.h"

/// Forward references
class Actor;
class Drawable;

/**
 * Basic edit view class for the Canadian Experience
 */
class ViewEdit final : public wxScrolledCanvas, public PictureObserver {
private:
    /// Handle the left mouse button down event
    void OnLeftDown(wxMouseEvent &event);

    /// Handle the left mouse button up event
    void OnLeftUp(wxMouseEvent& event);

    /// Handle the mouse button move event
    void OnMouseMove(wxMouseEvent& event);

    /// Paint event, draws the window.
    void OnPaint(wxPaintEvent& event);

    /// Handle the movement event
    void OnEditMove(wxCommandEvent& event);

    /// Handle the rotation event
    void OnEditRotate(wxCommandEvent& event);

    /// Handle the update movement event
    void OnUpdateEditMove(wxUpdateUIEvent& event);

    /// Handle the update rotate event
    void OnUpdateEditRotate(wxUpdateUIEvent& event);

    /// The last mouse position
    wxPoint mLastMouse = wxPoint(0, 0);

    /// The current mouse mode
    enum class Mode {Move, Rotate};

    /// The currently set mouse mode
    Mode mMode = Mode::Move;

    /// The currently selected actor
    std::shared_ptr<Actor> mSelectedActor;

    /// The currently selected drawable
    std::shared_ptr<Drawable> mSelectedDrawable;


public:
    ViewEdit(wxFrame* parent);
    void UpdateObserver() override;
};

#endif //CANADIANEXPERIENCE_VIEWEDIT_H
