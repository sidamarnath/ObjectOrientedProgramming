/**
 * @file ViewTimeline.cpp
 * @author Charles B. Owen
 */

#include "pch.h"

#include <wx/dcbuffer.h>
#include <wx/xrc/xmlres.h>
#include <sstream>

#include "ViewTimeline.h"
#include "TimelineDlg.h"
#include "Picture.h"
#include "Timeline.h"
#include "MainFrame.h"
#include "Actor.h"

/// Y location for the top of a tick mark
const int TickTop = 15;

/// The spacing between ticks in the timeline
const int TickSpacing = 4;

/// The length of a short tick mark
const int TickShort = 10;

/// The length of a long tick mark
const int TickLong = 20;

/// Size of the tick mark labels
const int TickFontSize = 15;

/// Space to the left of the scale
const int BorderLeft = 10;

/// Space to the right of the scale
const int BorderRight = 10;

/// Filename for the pointer image
const std::wstring PointerImageFile = L"/pointer.png";

/**
 * Constructor
 * @param parent The main wxFrame object
 */
ViewTimeline::ViewTimeline(wxFrame* parent) :
        wxScrolledCanvas(parent,
            wxID_ANY,
            wxDefaultPosition,
            wxSize(100, Height),
            wxBORDER_SIMPLE)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &ViewTimeline::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &ViewTimeline::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &ViewTimeline::OnLeftUp, this);
    Bind(wxEVT_MOTION, &ViewTimeline::OnMouseMove, this);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
            &ViewTimeline::OnEditTimelineProperties, this,
            XRCID("EditTimelineProperties"));

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
            &ViewTimeline::OnSetKeyframe, this,
            XRCID("EditSetKeyframe"));

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
            &ViewTimeline::OnDeleteKeyframe, this,
            XRCID("EditDeleteKeyframe"));

}


/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void ViewTimeline::OnPaint(wxPaintEvent& event)
{
    auto timeline = this->GetPicture()->GetTimeline();
    //auto size = GetPicture()->GetSize();
    SetVirtualSize(timeline->GetNumFrames() * TickSpacing + BorderLeft + BorderRight, Height);
    SetScrollRate(1, 0);

    wxAutoBufferedPaintDC dc(this);
    DoPrepareDC(dc);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));

    wxPen pen(wxColour(0, 0, 0), 1);
    graphics->SetPen(pen);


    for(int tickNum = 0; tickNum <= timeline->GetNumFrames(); tickNum++)
    {
        bool onSecond = (tickNum % timeline->GetFrameRate()) == 0;

        if(onSecond)
        {
            wxFont font(wxSize(0, TickFontSize),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
            graphics->SetFont(font, *wxBLACK);

            // Convert the tick number to seconds in a string
            std::wstringstream str;
            str << tickNum / timeline->GetFrameRate();
            std::wstring wstr = str.str();

            double w, h;
            graphics->GetTextExtent(wstr, &w, &h);

            graphics->StrokeLine(BorderLeft + TickSpacing * tickNum, TickTop, BorderLeft + TickSpacing * tickNum, TickTop+TickLong);
            graphics->DrawText(wstr, (BorderLeft + TickSpacing * tickNum) - (0.5 * w) , TickTop + TickLong + 1.5);
        }
        else
        {
            graphics->StrokeLine(BorderLeft + TickSpacing * tickNum, TickTop, BorderLeft + TickSpacing * tickNum, TickTop+TickShort);
        }
    }
    mPointerImage = std::make_unique<wxImage>(mImagesDir + PointerImageFile, wxBITMAP_TYPE_ANY);
    mPointerBitmap = graphics->CreateBitmapFromImage(*mPointerImage);
    graphics->DrawBitmap(mPointerBitmap,
            timeline->GetCurrentFrame() * TickSpacing + BorderLeft - (0.5 * mPointerImage->GetWidth()), 10,
            mPointerImage->GetWidth(),
            mPointerImage->GetHeight());

}

/**
 * Handle the left mouse button down event
 * @param event
 */
void ViewTimeline::OnLeftDown(wxMouseEvent &event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());

    int x = click.x;

    // Get the timeline
    Timeline *timeline = GetPicture()->GetTimeline();
    int pointerX = (int)(timeline->GetCurrentTime() *
            timeline->GetFrameRate() * TickSpacing + BorderLeft);

    mMovingPointer = x >= pointerX - mPointerImage->GetWidth() / 2 &&
            x <= pointerX + mPointerImage->GetWidth() / 2;

    if(mMovingPointer)
    {
        int xx = 0;
    }
}

/**
* Handle the left mouse button up event
* @param event
*/
void ViewTimeline::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);
}

/**
* Handle the mouse move event
* @param event
*/
void ViewTimeline::OnMouseMove(wxMouseEvent &event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());
    int x = click.x;
    // Get the timeline
    Timeline *timeline = GetPicture()->GetTimeline();

    if (mMovingPointer && event.LeftIsDown())
    {
        double time = (x - BorderLeft) / double((timeline->GetFrameRate() * TickSpacing));
        if (time >= 0 && time <= timeline->GetDuration())
        {
            GetPicture()->SetAnimationTime(time);
        }
    }
}

/**
 * Force an update of this window when the picture changes.
 */
void ViewTimeline::UpdateObserver()
{
    Refresh();
}

/**
 * Handle an Edit>Timeline Properties... menu option
 * @param event The menu event
 */
void ViewTimeline::OnEditTimelineProperties(wxCommandEvent& event)
{
    TimelineDlg dlg(this->GetParent(), this->GetPicture()->GetTimeline());
    if(dlg.ShowModal() == wxID_OK)
    {
        // The dialog box has changed the Timeline settings
        UpdateObserver();

    }
}

void ViewTimeline::OnSetKeyframe(wxCommandEvent& event)
{
    auto picture = GetPicture();
    for (auto actor : *picture)
    {
        actor->SetKeyframe();
    }
}

void ViewTimeline::OnDeleteKeyframe(wxCommandEvent& event)
{
    auto picture = GetPicture();
    auto timeline = picture->GetTimeline();
    timeline->DeleteKeyframe();
}