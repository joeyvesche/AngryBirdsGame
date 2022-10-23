/**
 * @file SlingShot.cpp
 * @author joeyv
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

SlingShot::SlingShot(Level* level) : Item(level, WoodSlingshotBaseName)
{
    auto [img, bitmap] = LoadImage(WoodSlingshotArmFilename);
    mArmImage = img;
    mArmBitmap = bitmap;
}

void SlingShot::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    // Get the center x and y position of this item
    auto posX = GetX() * Consts::MtoCM, posY= GetY() * Consts::MtoCM;

    // Calculate the width and height of the item in centimeters
    double width = WoodSlingshotSize.x * Consts::MtoCM;
    double height = WoodSlingshotSize.y * Consts::MtoCM;

    // translate to the correct location to draw the image
    graphics->Translate(posX, posY);

    // draw the actual slingshot
    graphics->Scale(1, -1);
    graphics->DrawBitmap(*GetBitmap(),
                         -width / 2,
                         -height,
                         width, height);
    graphics->Scale(1, -1);

    // draw the band on the slingshot
    wxPen pen(SlingshotBandColor, SlingshotBandWidth);
    graphics->SetPen(pen);

    graphics->StrokeLine(WoodSlingshotBandAttachBack.x * Consts::MtoCM,
                         WoodSlingshotBandAttachBack.y * Consts::MtoCM,
                         WoodSlingshotBandAttachFront.x * Consts::MtoCM,
                         WoodSlingshotBandAttachFront.y * Consts::MtoCM);

    graphics->PopState();

}