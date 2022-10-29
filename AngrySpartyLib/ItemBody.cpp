/**
 * @file ItemBody.cpp
 * @author Will, Joey Vesche
 */

#include "pch.h"
#include "ItemBody.h"
#include "AngrySparty.h"
#include "Consts.h"

ItemBody::ItemBody(Block *block, wxXmlNode *node)
{
    node->GetAttribute(L"angle", L"0").ToDouble(&mAngle);
    node->GetAttribute(L"friction", L"0").ToDouble(&mFriction);
    node->GetAttribute(L"restitution", L"0").ToDouble(&mRestitution);

    if (node->GetAttribute(L"type", L"dynamic") == "static")
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
    std::pair<double, float> constants = angry->GetConstants();
    mRadius = constants.first;
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
 * Creates a new b2Body in the world
 * @param physics physics system in this world
 * @return
 */
b2Body* ItemBody::CreateBody(std::shared_ptr<Physics> physics)
{
    b2World* world = physics->GetWorld(); ///Get world from physics


    // Create the body definition
    b2BodyDef bodyDefinition;
    bodyDefinition.position = mPosition;
    bodyDefinition.angle = mAngle * Consts::DtoR;

    bodyDefinition.type = mStatic ? b2_staticBody : b2_dynamicBody;
    auto body = world->CreateBody(&bodyDefinition);

    return body;

}

/**
 * Make the physics body for an object.
 * @param physics physics system for this level
 * @param key key that determines which item was passed to this function
 */
void ItemBody::MakeBody(std::shared_ptr<Physics> physics, int key)
{

    /// Block
    b2Body* body = CreateBody(physics);

    if (key == 0)
    {
        // Create the box
        b2PolygonShape box;
        box.SetAsBox(mSize.x/2, mSize.y/2);

        if (mStatic == 1) {
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

    ///Foe object
    if (key == 2)
    {
        // Create the vertices for the octagon
        std::vector<b2Vec2> vertices;
        double angle = 0; // the rotation from the horizontal axis in degrees

        for (int i = 0; i < 8; ++i, angle += 360.0 / 8)
        {
            double angleRad = angle * Consts::DtoR;
            vertices.push_back(mRadius * b2Vec2(std::cos(angleRad), std::sin(angleRad)));
        }

        // assign the vertices to a polygon shape
        b2PolygonShape octagon;
        octagon.Set(vertices.data(), vertices.size());

        // assign this shape to the body
        body->CreateFixture(&octagon, 1.0f);
        mBody = body;
    }
}

/**
 * Creates the physics body for a sparty
 * @param key  static(1) or dynamic(0)
 */

void ItemBody::CreateSparty(std::shared_ptr<Physics> physics, int key)
{
    mStatic = key;
    b2Body* body = CreateBody(physics);

    // Create the shape
    b2CircleShape circle;

    circle.m_radius = (float)mRadius;

    body->CreateFixture(&circle, 0.0f);

    mBody = body;

}



