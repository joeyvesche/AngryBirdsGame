/**
 * @file LimpetSparty.cpp
 * @author Will
 */

#include "pch.h"
#include "LimpetSparty.h"

/// Useful Constants
/// The image to use for this sparty
const std::wstring LimpetSpartyImage = L"limpet.png";


/**
 * Limpet Sparty initializer
 * @param level
 */

LimpetSparty::LimpetSparty(Level *level) : AngrySparty(level, LimpetSpartyImage)
{

}


std::pair<double,float> LimpetSparty::GetConstants()
{
    return std::pair<double,float>(mLimpetSpartyRadius, mLimpetSpartyVelocityFactor);
}
