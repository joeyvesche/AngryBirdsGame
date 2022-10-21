/**
 * @file Background.cpp
 * @author Will
 */

#include "pch.h"
#include "Background.h"
#include "Consts.h"

 void Background::XmlLoad(wxXmlNode *node)
{
    node->GetAttribute(L"width", L"0").ToDouble(&mWidth);
    node->GetAttribute(L"height", L"0").ToDouble(&mHeight);
}


void Background::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    auto wid = mWidth * Consts::MtoCM;
    auto hit = mHeight * Consts::MtoCM;

    std::shared_ptr<wxBitmap> bitmap = mBackground;

    graphics->PushState();
    graphics->Scale(1, -1);
    graphics->DrawBitmap(*bitmap,
            -wid/2,
            -hit,
            wid, hit);
    graphics->PopState();
}