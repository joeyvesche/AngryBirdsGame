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
}