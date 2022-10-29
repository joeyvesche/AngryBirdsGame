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

    double density, friction, restitution;
    std::wstring type;

    node->GetAttribute("density", "1").ToDouble(&density);
    node->GetAttribute("friction", "0.5").ToDouble(&friction);
    node->GetAttribute("restitution", "0.5").ToDouble(&restitution);
    type = node->GetAttribute("type", "dynamic");

    b2PolygonShape poly;
    poly.Set(mVertices.data(), mVertices.size());

    // Create the body definition
    b2BodyDef bodyDefinition;
    bodyDefinition.position = b2Vec2(GetX(), GetY());
    bodyDefinition.angle = GetAngle();
    bodyDefinition.type = type == L"static" ? b2_staticBody : b2_dynamicBody;

    mBody = GetLevel()->GetPhysics()->GetWorld()->CreateBody(&bodyDefinition);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &poly;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;

    mBody->CreateFixture(&fixtureDef);
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