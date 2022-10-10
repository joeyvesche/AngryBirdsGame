/**
 * @file AngrySpartyApp.cpp
 * @author Will Skaggs
 */

#include "pch.h"
#include "AngrySpartyApp.h"
#include <MainFrame.h>

/**
 * Initialize the application
 *
 * @return true if initialization was successful, false otherwise
 */
bool AngrySpartyApp::OnInit()
{
    // exit if the up-called initialization was unsuccessful
    if (!wxApp::OnInit()) return false;

    // Initialize and display the main frame of the application
    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show();

    return true;
}