/**
 * @file ItemBody.cpp
 * @author Will, Joey Vesche
 */

#include "pch.h"
#include "ItemBody.h"
#include "AngrySparty.h"

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

ItemBody::ItemBody(AngrySparty *angry)
{
    mPosition.Set(float(angry->GetX()), float(angry->GetY()));
}

ItemBody::ItemBody(Foe *foe, wxXmlNode* node)
{
    node->GetAttribute(L"radius", L"0").ToDouble(&mRadius);
    node->GetAttribute(L"down", L"0").ToDouble(&mDown);
    node->GetAttribute(L"x", "0").ToDouble(&mX);
    node->GetAttribute("y", "0").ToDouble(&mY);
    mPosition.Set(float(mX), float(mY));
}

/**
 * Make the physics body for an object.
 * @param physics physics system for this level
 * @param key key that determines which item was passed to this function
 */
void ItemBody::MakeBody(std::shared_ptr<Physics> physics, int key)
{

    b2World* world = physics->GetWorld();


    // Create the body definition
    b2BodyDef bodyDefinition;
    bodyDefinition.position = mPosition;
    bodyDefinition.angle = mAngle;

    ///Set static for objects that dont load it
    if (key == 1)
    {
        mStatic = 1;
    }
    bodyDefinition.type = mStatic ? b2_staticBody : b2_dynamicBody;
    auto body = world->CreateBody(&bodyDefinition);

    /// Block
    if (key == 0)
    {
        // Create the box
        b2PolygonShape box;
        box.SetAsBox(mSize.x/2, mSize.y/2);

        if (mStatic) {
            body->CreateFixture(&box, 0.0f);
        }
        else {
            b2FixtureDef fixtureDef;
            fixtureDef.shape = &box;
            fixtureDef.density = (float) mDensity;
            fixtureDef.friction = (float) mFriction;
            fixtureDef.restitution = (float) mRestitution;

            body->CreateFixture(&fixtureDef);

        }
        mBody = body;
    }
    ///Angry Sparty object
    if (key == 1)
    {

        // Create the shape
        b2CircleShape circle;

        circle.m_radius = (float)mRadius;

        body->CreateFixture(&circle, 0.0f);

        mBody = body;
    }

    ///Foe object
    if (key == 2)
    {
        // Create the shape
        b2CircleShape circle;

        circle.m_radius = (float)mRadius;

        body->CreateFixture(&circle, 0.0f);

        mBody = body;
    }
}
