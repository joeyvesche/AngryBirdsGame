/**
 * @file Foe.cpp
 * @author Will Morant
 */

#include "pch.h"
#include "Foe.h"
#include "Game.h"
#include "Item.h"
#include "Consts.h"

Foe::Foe(Level *level, const std::wstring &filename) : Item(level, filename)
{

}

void Foe::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);
    node->GetAttribute(L"radius", L"0").ToDouble(&mRadius);
    node->GetAttribute(L"down", L"0").ToDouble(&mDown);
}

void Foe::Accept(ItemVisitor* visitor)
{
    visitor->VisitFoe(this);
}

void Foe::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    auto position = b2Vec2(GetX(), GetY());
    auto angle = GetAngle();

    auto wid = mRadius * Consts::MtoCM * 2;
    auto x = position.x * Consts::MtoCM;
    auto y = position.y * Consts::MtoCM;

    graphics->PushState();
    graphics->Translate(x, y);
    graphics->Rotate(angle);



    graphics->Scale(1, -1);
    graphics->DrawBitmap(*GetBitmap(),
            -wid/2,
            -wid/2,
            wid, wid);

    graphics->PopState();

}
