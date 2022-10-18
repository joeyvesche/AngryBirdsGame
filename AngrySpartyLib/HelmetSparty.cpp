/**
 * @file HelmetSparty.cpp
 * @author Will
 */

#include "pch.h"
#include "HelmetSparty.h"
#include "AngrySparty.h"
#include <string>
#include "Game.h"

/// HelmetSparty filename
const std::wstring HelmetSpartyImageName = L"helmet-sparty.png";

HelmetSparty::HelmetSparty(Game *game) : AngrySparty(game, HelmetSpartyImageName)
{

}


