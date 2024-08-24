/**
 * @file SidharthAmarnathApp.cpp
 * @author Sid Amarnath
 */
#include "pch.h"
#include "SidharthAmarnathApp.h"
#include <MainFrame.h>

/**
 * Initialize the application.
 * @return
 */
bool SidharthAmarnathApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;
}