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


GruffSparty::GruffSparty(Level *level) : AngrySparty(level, GruffSpartyImage)
{

}

std::pair<double,float> GruffSparty::GetConstants()
{
    return std::pair<double,float>(mGruffSpartyRadius, mGruffSpartyVelocityFactor);
}