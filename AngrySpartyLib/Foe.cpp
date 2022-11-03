/**
 * @file Foe.cpp
 * @author Will Morant, Joey Vesche
 */

#include "pch.h"
#include "Foe.h"
#include "Game.h"
#include "Consts.h"

const double StopMovingFactor = 0.0000005;
Foe::Foe(Level *level, const std::wstring &filename) : Item(level, filename)
{

}

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

void Foe::Accept(ItemVisitor* visitor)
{
    visitor->VisitFoe(this);
}

void Foe::Accept(LimpetKillVisitor* visitor)
{
    visitor->VisitFoe(this);
}

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

bool Foe::IsDead()
{
    if(mMoving)
        return false;
    return (GetY() - (mLastY / Consts::MtoCM)) >= (mDown / Consts::MtoCM);
}

void Foe::Detach()
{
    mBody->GetWorld()->DestroyBody(mBody);
}
