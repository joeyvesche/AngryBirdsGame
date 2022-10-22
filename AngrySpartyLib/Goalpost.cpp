/**
 * @file Goalposts.cpp
 * @author Joseph Pauls
 */

#include "pch.h"
#include "Goalposts.h"

/**
 * Goalposts Constants
 */
/// Base filename for the slingshot image
const std::wstring GoalpostsBaseName = L"goalposts";

/// Size of the slingshot image in meters
const b2Vec2 GoalpostsSize = b2Vec2(1, 2.649);

/// Back band attachment point
const b2Vec2 GoalpostsBandAttachBack = b2Vec2(-0.42f, 2.3f);

/// Front band attachment point
const b2Vec2 GoalpostsBandAttachFront = b2Vec2(0.34f, 2.32f);

/// Maximum amount the slingshot can be pulled in meters
const double GoalpostsMaximumPull = 2;


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
    b2Vec2 position(GetX(), GetY());
    graphics->PushState();

    graphics->Translate(position.x*Consts::MtoCM,
            position.y*Consts::MtoCM);

    // Make this is left side of the rectangle
    double x = -GoalpostsSize.x/2*Consts::MtoCM;

    // And the top
    double y = GoalpostsSize.y/2*Consts::MtoCM;

    // The width of the slingshot
    double xw = GoalpostsSize.x/1*Consts::MtoCM;

    graphics->Translate(0, y);
    graphics->Scale(1, -1);
    graphics->DrawBitmap(*mGoalpost,
            x,
            -y,
            xw, GoalpostsSize.y*Consts::MtoCM);
    graphics->PopState();

}
