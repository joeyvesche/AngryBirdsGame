/**
 * @file MainFrame.cpp
 * @author Will Skaggs
 */

#include "pch.h"
#include "MainFrame.h"

void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Angry Sparty",
            wxDefaultPosition, wxSize(1600, 900));

    // Create a menu bar
    auto menuBar = new wxMenuBar();

    // File menu
    auto fileMenu = new wxMenu();
    menuBar->Append(fileMenu, L"&File");

    // Level menu
    auto levelMenu = new wxMenu();
    menuBar->Append(levelMenu, L"&Level");

    // View menu
    auto viewMenu = new wxMenu();
    menuBar->Append(viewMenu, L"&View");

    // Help menu
    auto helpMenu = new wxMenu();
    menuBar->Append(helpMenu, L"&Help");

    // Set the menu bar to this frame
    SetMenuBar(menuBar);
}