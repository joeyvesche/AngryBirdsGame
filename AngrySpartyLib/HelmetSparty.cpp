/**
 * @file HelmetSparty.cpp
 * @author Will
 */

#include "pch.h"
#include "HelmetSparty.h"
#include <string>
#include "Game.h"

/// Useful Constants
/// The image to use for this sparty
const std::wstring HelmetSpartyImage = L"helmet-sparty.png";


/**
 * Helmet Sparty initializer
 * @param level
 */

HelmetSparty::HelmetSparty(Level *level) : AngrySparty(level, HelmetSpartyImage)
{

}


std::pair<double,float> HelmetSparty::GetConstants()
{
    return std::pair<double,float>(mHelmetSpartyRadius, mHelmetSpartyVelocityFactor);
}