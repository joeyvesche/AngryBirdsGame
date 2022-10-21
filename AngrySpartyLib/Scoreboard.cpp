/**
 * @file Scoreboard.cpp
 * @authors joeyv, Joseph Pauls
 */

#include "pch.h"
#include "Scoreboard.h"
#include <wx/graphics.h>

#include "Consts.h"

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
    graphics->SetFont(bigFont, wxColour(255, 0, 0));
    graphics->GetTextExtent(L"000", &wid, &hit);
    graphics->DrawText(L"000", 5.5*Consts::MtoCM, 7*Consts::MtoCM);
    graphics->DrawText(L"000", -6.75*Consts::MtoCM, 7*Consts::MtoCM);

}
