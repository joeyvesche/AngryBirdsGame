/**
 * @file AngrySpartyApp.cpp
 * @author Will Skaggs
 */

#include <pch.h>
#include "AngrySpartyApp.h"
#include <MainFrame.h>

// DEVELOPMENT: Add testing for memory leaks on Windows
#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#endif

/**
 * Initialize the application
 *
 * @return true if initialization was successful, false otherwise
 */
bool AngrySpartyApp::OnInit()
{
    // Memory leak testing for Windows
    #ifdef WIN32
        _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    #endif

    // exit if the up-called initialization was unsuccessful
    if (!wxApp::OnInit()) {
        return false;
    }

    // Add image type handlers
    wxInitAllImageHandlers();

    // Initialize and display the main frame of the application
    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;
}