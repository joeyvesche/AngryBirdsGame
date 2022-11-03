/**
 * @file HelmetSparty.cpp
 * @author Will Morant
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
 * @param level Level
 */

HelmetSparty::HelmetSparty(Level *level) : AngrySparty(level, HelmetSpartyImage)
{

}

/**
 * Get the Radius and Velocity factor
 * @return Pair of the constants
 */
std::pair<double,float> HelmetSparty::GetConstants()
{
    return std::pair<double,float>(mHelmetSpartyRadius, mHelmetSpartyVelocityFactor);
}