/**
 * @file Poly.cpp
 * @author Joey Vesche
 */

#include "pch.h"
#include "Poly.h"
#include "Game.h"
#include "Consts.h"

/**
 * Poly Constructor
 * @param level Level
 * @param filename File name
 */
Poly::Poly(Level *level, const std::wstring &filename) : Item(level, filename)
{
}

/**
 * Loads Poly in from XML
 * @param node Poly node
 */
void Poly::XmlLoad(wxXmlNode *node)
{
    Item::XmlLoad(node);
    double x, y;
    for (auto child = node->GetChildren(); child != nullptr; child = child->GetNext()) {

        child->GetAttribute(L"x", L"0").ToDouble(&x);
        child->GetAttribute(L"y", L"0").ToDouble(&y);

        mVertex.Set(x, y);
        mVertices.push_back(mVertex);
    }

    std::shared_ptr<ItemBody> body = std::make_shared<ItemBody>(this, node);
    Level *level = Item::GetLevel();
    std::shared_ptr<Physics> physics = level->GetPhysics();
    body->CreatePoly(physics, mVertices);
    mBody = body->GetBody();
}

/**
 * Accepts an Item Visitor
 * @param visitor Visitor
 */
void Poly::Accept(ItemVisitor* visitor)
{
    visitor->VisitPoly(this);
}

/**
 * Draws a poly objects
 * @param graphics Context to draw on
 */
void Poly::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
   graphics->PushState();

   auto position = mBody->GetPosition();
   auto angle= mBody->GetAngle();

    // Find the minimum and maximum x/y values
    b2Vec2 minimums = mVertices[0];
    b2Vec2 maximums = mVertices[0];
    for(auto v : mVertices)
    {
    minimums.x = fmin(minimums.x, v.x);
    minimums.y = fmin(minimums.y, v.y);
    maximums.x = fmax(maximums.x, v.x);
    maximums.y = fmax(maximums.y, v.y);
    }

    auto size = maximums - minimums;

    auto x = position.x * Consts::MtoCM;
    auto y = position.y * Consts::MtoCM;

    graphics->PushState();
    graphics->Translate(x, y);
    graphics->Rotate(angle);

    graphics->Scale(1, -1);
    graphics->DrawBitmap(*GetBitmap(),
            minimums.x * Consts::MtoCM,
            minimums.y * Consts::MtoCM,
            size.x * Consts::MtoCM,
            size.y * Consts::MtoCM);

    graphics->PopState();


}