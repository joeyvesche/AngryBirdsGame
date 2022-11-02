/**
 * @file Poly.cpp
 * @author joeyv
 */

#include "pch.h"
#include "Poly.h"
#include "Game.h"
#include "Consts.h"

Poly::Poly(Level *level, const std::wstring &filename) : Item(level, filename)
{
}

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

void Poly::Accept(ItemVisitor* visitor)
{
    visitor->VisitPoly(this);
}

void Poly::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    //auto body = GetBody();
   // auto position = body->GetPosition();
   // auto angle = body->GetAngle();

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