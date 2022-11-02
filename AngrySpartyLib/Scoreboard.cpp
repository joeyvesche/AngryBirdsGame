/**
 * @file Scoreboard.cpp
 * @authors joeyv, Joseph Pauls
 */

#include "pch.h"
#include "Scoreboard.h"
#include <wx/graphics.h>

#include "Consts.h"
#include <string>
Scoreboard::Scoreboard()
{
    mLevelScore = 0;
    mGameScore = 0;
}


/**
* Scoreboard Drawer
 * @param graphics Graphics context to draw on
 * @param height Height of the game
 * @param width width of the game
*/

void Scoreboard::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, double width, double height)
{

    // Pass in mWidth and mHeight from the game
    auto wid = width*Consts::MtoCM;
    auto hit = height*Consts::MtoCM;
    wxFont bigFont(wxSize(40, 70),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_BOLD);
    graphics->PushState();
    graphics->Scale(1, -1);
    graphics->SetFont(bigFont, wxColour(255, 0, 0));
    graphics->GetTextExtent(std::to_wstring(mGameScore), &wid, &hit);

    if (width!=20)
    {
        // aligns the zero to the right properly when the level score is only 1 digit long
        if (mLevelScore == 0)
        {
            graphics->DrawText(std::to_wstring(mLevelScore), 6.5*Consts::MtoCM, -8*Consts::MtoCM);
        }
        else
        {
            graphics->DrawText(std::to_wstring(mLevelScore), 5.5*Consts::MtoCM, -8*Consts::MtoCM);
        }
        graphics->DrawText(std::to_wstring(mGameScore), -6.75*Consts::MtoCM, -8*Consts::MtoCM);
    }

    // account for level 2 being wider than the others
    else
    {
        if (mLevelScore == 0)
        {
            graphics->DrawText(std::to_wstring(mLevelScore), 9.5*Consts::MtoCM, -8*Consts::MtoCM);
        }
        else
        {
            graphics->DrawText(std::to_wstring(mLevelScore), 8.5*Consts::MtoCM, -8*Consts::MtoCM);
        }
        graphics->DrawText(std::to_wstring(mGameScore), -9.75*Consts::MtoCM, -8*Consts::MtoCM);
    }
    graphics->PopState();
}
