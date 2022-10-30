/**
 * @file AngrySparty.cpp
 * @authors Will Morant, Joseph Pauls
 */

#include "pch.h"
#include "AngrySparty.h"
#include "Game.h"
#include "Consts.h"
#include "ItemVisitor.h"
/**
 * Constructs the angry sparty object
 * @param level
 * @param filename
 */
AngrySparty::AngrySparty(Level *level, const std::wstring &filename) :Item(level, filename)
{

}

void AngrySparty::SetBody(Level *level)
{
    std::shared_ptr<Physics> physics = level->GetPhysics();
    std::shared_ptr<ItemBody> body = std::make_shared<ItemBody>(this);
    body->CreateSparty(physics, 1); /// key = 1 for static body
    mBody = body->GetBody();
}

/**
 *  Draws the Angry Spartys
 * @param graphics
 */
void AngrySparty::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();
    auto position = mBody->GetPosition();
    auto angle = mBody->GetAngle();

    auto wid = 0.25 * Consts::MtoCM * 2;
    auto x = position.x * Consts::MtoCM;
    auto y = position.y * Consts::MtoCM;

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

void AngrySparty::Accept(ItemVisitor* visitor)
{
    visitor->VisitSparty(this);
}

