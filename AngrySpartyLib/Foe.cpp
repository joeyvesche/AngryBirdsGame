/**
 * @file Foe.cpp
 * @author Will Morant, Joey Vesche, Yuqi Pan
 */

#include "pch.h"
#include "Foe.h"
#include "Game.h"
#include "Consts.h"
const double FloorHeight = 0.25; ///< height of the floor
const double StopMovingFactor = 0.0000005; ///< The stop Moving factor

/**
 * Constructor
 * @param level Level
 * @param filename File name
 */
Foe::Foe(Level *level, const std::wstring &filename) : Item(level, filename)
{
}

/**
 * Loads in Foe
 * @param node Node foe
 */
void Foe::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);

    node->GetAttribute(L"radius", L"0").ToDouble(&mRadius);
    node->GetAttribute(L"down", L"0").ToDouble(&mDown);

    std::shared_ptr<ItemBody> body = std::make_shared<ItemBody>(this, node);
    Level *level = Item::GetLevel();
    std::shared_ptr<Physics> physics = level->GetPhysics();
    body->CreateFoe(physics);
    mBody = body->GetBody();

    mLastX = GetX();
    mLastY = GetY();
}

/**
 * Accepts an Item Visitor
 * @param visitor Visitor
 */
void Foe::Accept(ItemVisitor* visitor)
{
    visitor->VisitFoe(this);
}


/**
 * Draws the Foe
 * @param graphics The context to draw on
 */
void Foe::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();
    b2Body* body = mBody;
    auto position = body->GetPosition();
    auto angle = body->GetAngle();

    auto wid = mRadius * Consts::MtoCM * 2;
    auto x = position.x * Consts::MtoCM;
    auto y = position.y * Consts::MtoCM;

    if(abs((mLastX - x)) > StopMovingFactor || abs((mLastY - y)) > StopMovingFactor)
    {
        mMoving = true;
        mLastX = x;
        mLastY = y;
    }
    else
    {
        mMoving = false;
    }

    graphics->PushState();
    graphics->Translate(x, y);
    graphics->Rotate(angle);

    graphics->Scale(1, -1);
    graphics->DrawBitmap(*GetBitmap(),
            -wid/2,
            -wid/2,
            wid, wid);

    graphics->PopState();
    graphics->PopState();
}

/**
 * Checks to see if Foe is dead
 * @return True if dead
 */
bool Foe::IsDead()
{
    return ((GetY() - (mLastY / Consts::MtoCM)) >= (mDown) || mLastY / Consts::MtoCM - mRadius <= FloorHeight);
}

/**
 * Destorys the body
 */
void Foe::Detach()
{
    mBody->GetWorld()->DestroyBody(mBody);
}
