/**
 * @file HelmetSparty.cpp
 * @author Will
 */

#include "pch.h"
#include "HelmetSparty.h"
#include "AngrySparty.h"
#include <string>
#include "Game.h"

/// Useful Constants
/// The image to use for this sparty
const std::wstring HelmetSpartyImage = L"helmet-sparty.png";

/// The radius in meters
const double HelmetSpartyRadius = 0.25;

/// The velocity factor for Helmet Sparty
const float HelmetSpartyVelocityFactor = 20.0;
///


/**
 * Helmet Sparty initializer
 * @param level
 */

HelmetSparty::HelmetSparty(Level *level) : AngrySparty(level, HelmetSpartyImage)
{

}


