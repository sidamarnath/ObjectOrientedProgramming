/**
 * @file SpartyGnomeApp.cpp
 * @author Derek Hubler
 */

#include "pch.h"
#include "SpartyGnomeApp.h"
#include <MainFrame.h>

/**
 * Initialize the application.
 * @return bool
 */
bool SpartyGnomeApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;
}