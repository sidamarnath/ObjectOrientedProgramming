/**
 * @file MainFrame.cpp
 * @author Sid Amarnath
 */
#include "pch.h"
#include "MainFrame.h"
#include "SidharthAmarnathView.h"
#include "SidharthAmarnathViewGreen.h"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Sidharth Amarnath", wxDefaultPosition,  wxSize( 1000,800 ));

    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer( wxHORIZONTAL );

    auto sidharthAmarnathViewGreen = new SidharthAmarnathViewGreen();
    sidharthAmarnathViewGreen->Initialize(this);

    // Add it to the sizer
    sizer->Add(sidharthAmarnathViewGreen,1,  wxEXPAND | wxALL);

    // Create the view class object as a child of MainFrame
    auto sidharthAmarnathView = new SidharthAmarnathView();
    sidharthAmarnathView->Initialize(this);

    // Add it to the sizer
    sizer->Add(sidharthAmarnathView,3,  wxEXPAND | wxALL);

    // Set the sizer for this frame
    SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();
}

