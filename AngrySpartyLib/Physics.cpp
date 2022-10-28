/**
 * @file Physics.cpp
 * @author Will Morant
 */

#include "pch.h"
#include "Physics.h"



/// Gravity in meters per second per second
const float Gravity = -9.8f;

/// Number of velocity update iterations per step
const int VelocityIterations = 6;

/// Number of position update iterations per step
const int PositionIterations = 2;


/**
 * Constructor
 * @param size The size of the level in meters
 */
Physics::Physics(const b2Vec2& size) : mWorld(b2Vec2(0.0f, Gravity))
{
    // Create a ground body at 0,0 to use as a reference
    b2BodyDef bodyDefinition;
    bodyDefinition.position.Set(0, 0.1);
    bodyDefinition.type = b2_staticBody;
    mGround = mWorld.CreateBody(&bodyDefinition);

    // Bottom
    b2PolygonShape box;
    box.SetAsBox(size.x*2, 0.1);
    mGround->CreateFixture(&box, 0.0f);

    // Right side
    box.SetAsBox(0.1, size.y, b2Vec2(size.x, size.y), 0);
    mGround->CreateFixture(&box, 0.0f);

    // Left side
    box.SetAsBox(0.1, size.y, b2Vec2(-size.x, size.y), 0);
    mGround->CreateFixture(&box, 0.0f);
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Physics::UpdateP(double elapsed)
{
    mWorld.Step(elapsed, VelocityIterations, PositionIterations);
}
