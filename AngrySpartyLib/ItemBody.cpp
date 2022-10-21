/**
 * @file ItemBody.cpp
 * @author Will
 */

#include "pch.h"
#include "ItemBody.h"

ItemBody::ItemBody(Block *block, wxXmlNode *node)
{
    node->GetAttribute(L"angle", L"0").ToDouble(&mAngle);
    node->GetAttribute(L"friction", L"0").ToDouble(&mFriction);
    node->GetAttribute(L"restitution", L"0").ToDouble(&mRestitution);

    if (node->GetAttribute(L"type", L"0") == "static")
    {
        mStatic = 1;
    }

    node->GetAttribute(L"x", "0").ToDouble(&mX);
    node->GetAttribute(L"y", "0").ToDouble(&mY);
    mPosition.Set(float(mX), float(mY));

    node->GetAttribute(L"width", "0").ToDouble(&mWidth);
    node->GetAttribute(L"height", "0").ToDouble(&mHeight);
    mSize.Set(float(mWidth), float(mHeight));

}

void ItemBody::MakeBody(std::shared_ptr<Physics> physics)
{

    b2World* world = physics->GetWorld();

    // Create the box
    b2PolygonShape box;
    box.SetAsBox(mSize.x/2, mSize.y/2);

    // Create the body definition
    b2BodyDef bodyDefinition;
    bodyDefinition.position = mPosition;
    bodyDefinition.angle = mAngle;
    bodyDefinition.type = mStatic ? b2_staticBody : b2_dynamicBody;
    auto body = world->CreateBody(&bodyDefinition);

    if(mStatic)
    {
        body->CreateFixture(&box, 0.0f);
    }
    else
    {
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &box;
        fixtureDef.density = (float)mDensity;
        fixtureDef.friction = (float)mFriction;
        fixtureDef.restitution = (float)mRestitution;

        body->CreateFixture(&fixtureDef);

    }
    mBody = body;
}