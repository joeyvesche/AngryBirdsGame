/**
 * @file SlingShot.cpp
 * @author joeyv
 */

#include "pch.h"
#include "SlingShot.h"

SlingShot::SlingShot(Game* game, const std::wstring& filename)
        :Item(game, filename)
{
    mSlingshot = std::make_unique<wxBitmap>(L"images/slingshot.png", wxBITMAP_TYPE_ANY);
}

void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
//    graphics->PushState();
//    graphics->Scale(1, -1);
//    graphics->DrawBitmap(*mSlingshot,
//            -width/2,
//            -height,
//           width, height);
//    graphics->PopState();


}