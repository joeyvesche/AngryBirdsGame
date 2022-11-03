/**
 * @file SlingShot.cpp
 * @authors Joseph Pauls, joeyv
 */

#include "pch.h"
#include "SlingShot.h"
#include <string>
#include "Consts.h"

/// Filename for the slingshot image
const std::wstring WoodSlingshotBaseName = L"slingshot.png";

/// Filename for the extra slingshot arm to draw when loaded
const std::wstring WoodSlingshotArmFilename = L"slingshot-front.png";

/// Size of the slingshot image in meters
const b2Vec2 WoodSlingshotSize = b2Vec2(0.5, 1.446);

/// Back band attachment point (in cm)
const b2Vec2 WoodSlingshotBandAttachBack = b2Vec2(-0.15f, 1.12f);

/// Front band attachment point (in cm)
const b2Vec2 WoodSlingshotBandAttachFront = b2Vec2(0.15f, 1.2f);

/// Maximum amount the slingshot can be pulled in meters
const double WoodSlingshotMaximumPull = 1;

/// Pull angles from -pi to this value are allowed
const double SlingshotMaximumNegativePullAngle = -1.7;

/// Pull angles from +pi to this value are allowed
const double SlingshotMinimumPositivePullAngle = 2.42;

/// Width of the slingshot band in centimeters
const int SlingshotBandWidth = 15;

/// The slingshot band colour
const wxColour SlingshotBandColor = wxColour(55, 18, 1);

SlingShot::SlingShot(Level* level) : Shooter(level, WoodSlingshotBaseName, WoodSlingshotArmFilename)
{
   mSize = WoodSlingshotSize;
   mBandAttachBack = WoodSlingshotBandAttachBack;
   mBandAttachFront = WoodSlingshotBandAttachFront;
   mMaxPull = WoodSlingshotMaximumPull;
   mBandColor = SlingshotBandColor;
   mBandWidth = SlingshotBandWidth;
}



