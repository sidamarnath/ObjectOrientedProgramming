/**
 * @file SidharthAmarnathViewGreen.cpp
 * @author Sid Amarnath
 *
 */
#include "pch.h"
#include "SidharthAmarnathViewGreen.h"

/**
 * Initialize the green view window class.
 * @param parent The parent window for this class
 */
void SidharthAmarnathViewGreen::Initialize(wxFrame* child)
{
    Create(child, wxID_ANY);
    SetBackgroundColour(wxColour(24, 69, 59));

}

