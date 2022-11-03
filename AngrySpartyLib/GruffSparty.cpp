/**
 * @file GruffSparty.cpp
 * @author Will Morant
 */

#include "pch.h"
#include "GruffSparty.h"
#include <string>
#include "Game.h"

///Useful Constants
/// The image to use for this sparty
const std::wstring GruffSpartyImage = L"gruff-sparty.png";

/**
 * Constructor
 * @param level Level
 */
GruffSparty::GruffSparty(Level *level) : AngrySparty(level, GruffSpartyImage)
{

}

/**
 * Get the Radius and Velocity factor
 * @return Pair of the constants
 */
std::pair<double,float> GruffSparty::GetConstants()
{
    return std::pair<double,float>(mGruffSpartyRadius, mGruffSpartyVelocityFactor);
}