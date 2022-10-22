/**
 * @file Goalposts.cpp
 * @author Joseph Pauls
 */

#include "pch.h"
#include "Goalpost.h"

/**
 * Goalposts Constants
 */
/// Base filename for the Goalpost image
const std::wstring GoalpostsBaseName = L"goalposts";

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
Goalposts::Goalposts(Level* level)
        :Item(level, L"goalposts.png")
{
    mGoalpost = std::make_shared<wxBitmap>(L"images/goalposts.png", wxBITMAP_TYPE_ANY);
}

/**
 * Load variables from XML
 * @param node
 */
void Goalposts::XmlLoad(wxXmlNode *node)
{
    Item::XmlLoad(node);
}

/**
 * Draw the goalpost
 * @param graphics graphics context for the game
 */
void Goalposts::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    // Get the center x and y position of this item
    auto posX = GetX() * Consts::MtoCM, posY= GetY() * Consts::MtoCM;

    // Calculate the width and height of the item in centimeters
    double width = GoalpostsSize.x * Consts::MtoCM;
    double height = GoalpostsSize.y * Consts::MtoCM;

    // translate to the correct location to draw the image
    graphics->Translate(posX, posY);

    // draw the actual Goalpost
    graphics->Scale(1, -1);
    graphics->DrawBitmap(*GetBitmap(),
            -width / 2,
            -height,
            width, height);
    graphics->Scale(1, -1);

    // draw the band on the Goalpost
    wxPen pen(GoalpostBandColor, GoalpostBandWidth);
    graphics->SetPen(pen);

    graphics->StrokeLine(GoalpostsBandAttachBack.x * Consts::MtoCM,
            GoalpostsBandAttachBack.y * Consts::MtoCM,
            GoalpostsBandAttachFront.x * Consts::MtoCM,
            GoalpostsBandAttachFront.y * Consts::MtoCM);

    graphics->PopState();

}
