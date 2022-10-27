/**
 * @file AngrySparty.cpp
 * @author Will Morant
 */

#include "pch.h"
#include "AngrySparty.h"

/**
 * Constructs the angry sparty object
 * @param level
 * @param filename
 */
AngrySparty::AngrySparty(Level *level, const std::wstring &filename) : Item(level, filename)
{

    std::shared_ptr<Physics> physics = level->GetPhysics();
    std::shared_ptr<ItemBody> body = std::make_shared<ItemBody>(this);
    body->MakeBody(physics, 1);
    mBody = body->GetBody();
}


void AngrySparty::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

}


