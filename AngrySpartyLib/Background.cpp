/**
 * @file Background.cpp
 * @author Will Morant
 */

#include "pch.h"
#include "Background.h"
#include "Consts.h"

/**
 * Background Constructor, Sets image
 * @param level
 * @param filename
 */
Background::Background(Level *level, const std::wstring &filename) : Item(level, filename)
{
}

void Background::XmlLoad(wxXmlNode *node)
{
    node->GetAttribute(L"width", L"0").ToDouble(&mWidth);
    node->GetAttribute(L"height", L"0").ToDouble(&mHeight);
}


void Background::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    auto wid = mWidth * Consts::MtoCM;
    auto hit = mHeight * Consts::MtoCM;

    graphics->PushState();
    graphics->Scale(1, -1);
    graphics->DrawBitmap(*GetBitmap(),
            -wid/2,
            -hit,
            wid, hit);
    graphics->PopState();
}