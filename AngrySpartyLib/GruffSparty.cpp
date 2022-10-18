/**
 * @file GruffSparty.cpp
 * @author Will
 */

#include "pch.h"
#include "GruffSparty.h"
#include <string>
#include "Game.h"
#include "AngrySparty.h"

/// GruffSparty filename
const std::wstring GruffSpartyImageName = L"gruff-sparty.png";

GruffSparty::GruffSparty(Game *game) : AngrySparty(game, GruffSpartyImageName)
{

}
