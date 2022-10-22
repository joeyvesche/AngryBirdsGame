/**
 * @file Foe.cpp
 * @author Will Morant
 */

#include "pch.h"
#include "Foe.h"
#include "Game.h"
#include "Item.h"

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

}
