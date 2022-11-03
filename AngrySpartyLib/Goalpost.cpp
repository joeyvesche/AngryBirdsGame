/**
 * @file Goalpost.cpp
 * @author Joseph Pauls
 */

#include "pch.h"
#include "Goalpost.h"

/**
 * Goalposts Constants
 */
/// Base filename for the Goalpost image
const std::wstring GoalpostsBaseName = L"goalposts.png";

/// filename of the extra goalpost arm to draw when it is loaded
const std::wstring GoalPostsArmImageFilename = L"goalposts-front.png";

/// Size of the Goalpost image in meters
const b2Vec2 GoalpostsSize = b2Vec2(1, 2.649);

/// Back band attachment point
const b2Vec2 GoalpostsBandAttachBack = b2Vec2(-0.42f, 2.3f);

/// Front band attachment point
const b2Vec2 GoalpostsBandAttachFront = b2Vec2(0.34f, 2.32f);

/// Maximum amount the Goalpost can be pulled in meters
const double GoalpostsMaximumPull = 2;

/// The Goalpost band colour
const wxColour GoalpostBandColor = wxColour(55, 18, 1);

/// Width of the Goalpost band in centimeters
const int GoalpostBandWidth = 15;


/**
 * Goalpost constructor
 * @param level
 */
Goalposts::Goalposts(Level* level) : Shooter(level, GoalpostsBaseName, GoalPostsArmImageFilename)
{
    mSize = GoalpostsSize;
    mBandAttachBack = GoalpostsBandAttachBack;
    mBandAttachFront = GoalpostsBandAttachFront;
    mMaxPull = GoalpostsMaximumPull;
    mBandColor = GoalpostBandColor;
    mBandWidth = GoalpostBandWidth;
}
