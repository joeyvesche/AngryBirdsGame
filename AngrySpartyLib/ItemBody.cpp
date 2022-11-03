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

    auto friction = node->GetAttribute(L"friction", L"NA");
    if (friction != L"NA") friction.ToDouble(&mFriction);

    auto restitution = node->GetAttribute(L"restitution", L"NA");
    if (restitution != L"NA") restitution.ToDouble(&mRestitution);

    auto density = node->GetAttribute(L"density", L"NA");
    if (density != L"NA") density.ToDouble(&mDensity);
}

ItemBody::ItemBody(AngrySparty *angry)
{
    mPosition.Set(float(angry->GetX()), float(angry->GetY()));
    std::pair<double, float> constants = angry->GetConstants();
    mRadius = constants.first;
    mAngle = angry->GetAngle();
    mStatic = 1;
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
 * Make the physics body for Foe
 * @param physics physics system for this level
 * @param key key that determines which item was passed to this function
 */
void ItemBody::CreateFoe(std::shared_ptr<Physics> physics)
{

    b2Body* body = CreateBody(physics);


    // Create the vertices for the octagon
    std::vector<b2Vec2> vertices;
    double angle = 360.0 / 16.0; // the rotation from the horizontal axis in degrees

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

/**
 * Creates the physics body for a sparty
 * @param key  static(1) or dynamic(0)
 */

void ItemBody::CreateSparty(std::shared_ptr<Physics> physics, int key)
{
    mStatic = key;
    b2Body* body = CreateBody(physics);

    if (mStatic == 1)
    {
        // Create the shape
        b2CircleShape circle;

        circle.m_radius = (float) mRadius;

        body->CreateFixture(&circle, 0.0f);
    }
    else
    {
        body->SetAngularDamping(0.9);
        body->SetLinearDamping(0.1);

        // Create the shape
        b2CircleShape circle;
        circle.m_radius = (float)mRadius;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circle;
        fixtureDef.density = (float)5;
        fixtureDef.friction = 1;
        fixtureDef.restitution = 0.3;

        body->CreateFixture(&fixtureDef);

    }

    mBody = body;

}

/**
 * Create physics body for Block
 * @param physics
 */
void ItemBody::CreateBlock(std::shared_ptr<Physics> physics)
{
    b2Body* body = CreateBody(physics);
    // Create the box
    b2PolygonShape box;
    box.SetAsBox(mSize.x/2, mSize.y/2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.density = (float) mDensity;
    fixtureDef.friction = (float) mFriction;
    fixtureDef.restitution = (float) mRestitution;

    body->CreateFixture(&fixtureDef);

    mBody = body;
}

void ItemBody::CreatePoly(std::shared_ptr<Physics> physics, const std::vector<b2Vec2>& vertices)
{
    b2PolygonShape poly;
    poly.Set(vertices.data(), vertices.size());

    mBody = CreateBody(physics);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &poly;
    fixtureDef.density = mDensity;
    fixtureDef.friction = mFriction;
    fixtureDef.restitution = mRestitution;

    mBody->CreateFixture(&fixtureDef);
}

ItemBody::ItemBody(Poly* poly, wxXmlNode* node)
{
    node->GetAttribute(L"angle", L"0").ToDouble(&mAngle);

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

    auto friction = node->GetAttribute(L"friction", L"NA");
    if (friction != L"NA") friction.ToDouble(&mFriction);

    auto restitution = node->GetAttribute(L"restitution", L"NA");
    if (restitution != L"NA") restitution.ToDouble(&mRestitution);

    auto density = node->GetAttribute(L"density", L"NA");
    if (density != L"NA") density.ToDouble(&mDensity);
}



