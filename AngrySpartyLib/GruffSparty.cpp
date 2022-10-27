/**
 * @file GruffSparty.cpp
 * @author Will
 */

#include "pch.h"
#include "GruffSparty.h"
#include <string>
#include "Game.h"
#include "AngrySparty.h"

///Useful Constants
/// The image to use for this sparty
const std::wstring GruffSpartyImage = L"gruff-sparty.png";

/// The radius in meters
const double GruffSpartyRadius = 0.25;

/// The velocity factor for Gruff Sparty
const float GruffSpartyVelocityFactor = 12.0;

GruffSparty::GruffSparty(Level *level) : AngrySparty(level, GruffSpartyImage)
{

}
