/**
 * @file SidharthAmarnathView.cpp
 * @author Sid Amarnath
 */
#include "pch.h"
#include "SidharthAmarnathView.h"

#include <wx/dcbuffer.h>

/**
 * Initialize the white view window class.
 * @param parent The parent window for this class
 */
void SidharthAmarnathView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &SidharthAmarnathView::OnPaint, this);

}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void SidharthAmarnathView::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // stadium outline
    wxPen stadiumOutline(wxColour(0, 0, 0), 2);
    dc.SetPen(stadiumOutline);
    dc.DrawRoundedRectangle(85, 10, 550, 750, 30);

    wxBrush stadiumOutlineBrush(wxColour(173, 216, 230));
    dc.SetBrush(stadiumOutlineBrush);
    dc.DrawRoundedRectangle(85, 10, 550, 750, 30);

    // stands outline
    wxPen standsOutline(wxColour(0, 0, 0), 2);
    dc.SetPen(standsOutline);
    dc.DrawRoundedRectangle(130, 55, 450, 650, 30);

    wxBrush standsOutlineBrush(wxColour(255, 255, 255));
    dc.SetBrush(standsOutlineBrush);
    dc.DrawRoundedRectangle(130, 55, 450, 650, 30);

    // tennis court outline
    wxPen tennisCourtOutline(wxColour(0, 0, 0), 2);
    dc.SetPen(tennisCourtOutline);
    dc.DrawRectangle(200, 140, 300, 475);

    wxBrush tennisCourtOutlineBrush(wxColour(204, 153, 255));
    dc.SetBrush(tennisCourtOutlineBrush);
    dc.DrawRectangle(200, 140, 300, 475);

    // singles sideline (left)
    wxPen tennisCourtLines(wxColour(0, 0, 0), 2);
    dc.SetPen(tennisCourtOutline);
    dc.DrawLine(475, 140, 475, 613);
    // singles sideline (right)
    dc.DrawLine(225, 140, 225, 613);

    //net outline
    wxPen netOutline(wxColour(255, 255, 255), 2);
    dc.SetPen(netOutline);
    dc.DrawLine(200, 375, 500, 375);

    // service box one
    wxPen serviceBox1(wxColour(0, 0, 0), 2);
    dc.SetPen(tennisCourtOutline);
    dc.DrawRectangle(225, 250, 125, 125);

    wxBrush serviceBoxBrush1(wxColour(255, 204, 203));
    dc.SetBrush(serviceBoxBrush1);
    dc.DrawRectangle(225, 250, 125, 125);

    // service box two
    dc.DrawRectangle(350, 250, 125, 125);

    wxBrush serviceBoxBrush2(wxColour(173, 216, 230));
    dc.SetBrush(serviceBoxBrush2);
    dc.DrawRectangle(350, 250, 125, 125);

    // service box three
    dc.DrawRectangle(350, 375, 125, 125);

    wxBrush serviceBoxBrush3(wxColour(144, 238, 144));
    dc.SetBrush(serviceBoxBrush3);
    dc.DrawRectangle(350, 375, 125, 125);

    // service box four
    dc.DrawRectangle(225, 375, 125, 125);

    wxBrush serviceBoxBrush4(wxColour(255, 255, 153));
    dc.SetBrush(serviceBoxBrush4);
    dc.DrawRectangle(225, 375, 125, 125);

    // center line 1
    dc.DrawLine(350, 140, 350, 150);
    // center line 2
    dc.DrawLine(350, 603, 350, 613);

    // right bench bottom
    dc.DrawLine(550, 425, 550, 575);
    dc.DrawLine(540, 425, 540, 575);

    // right bench top
    dc.DrawLine(550, 200, 550, 350);
    dc.DrawLine(540, 200, 540, 350);

    // left bench bottom
    dc.DrawLine(160, 200, 160, 350);
    dc.DrawLine(170, 200, 170, 350);

    // left bench top
    dc.DrawLine(160, 425, 160, 575);
    dc.DrawLine(170, 425, 170, 575);

    // tennis balls
    wxBrush tennisBall(wxColour(220, 253, 80));
    dc.SetBrush(tennisBall);
    dc.DrawCircle(300,200,10);

    wxBrush tennisBall2(wxColour(220, 253, 80));
    dc.SetBrush(tennisBall2);
    dc.DrawCircle(310,218,10);

    wxBrush tennisBall3(wxColour(220, 253, 80));
    dc.SetBrush(tennisBall3);
    dc.DrawCircle(320,200,10);

    // Creates a 20-pixel tall font
    wxFont font(wxSize(40, 40),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
    dc.SetFont(font);

    dc.SetTextForeground(wxColour(0, 0, 0));
    dc.DrawText(L"Detroit",  // Text to draw
            285,     // x coordinate for the left size of the text
            80);
}
