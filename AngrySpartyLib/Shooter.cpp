/**
 * @file Shooter.cpp
 * @author Will Skaggs
 */

#include "pch.h"
#include "Shooter.h"
#include "Consts.h"
#include "ShooterVisitor.h"

/**
 * Construct a new shooter
 * @param level the level this shooter belongs to
 * @param imageFile the image filename for this shooter
 * @param armImageFile the image file for the extra arm
 */
Shooter::Shooter(Level * level, std::wstring const & imageFile, std::wstring const & armImageFile)
    : Item(level, imageFile)
{
    auto [img, bitmap] = LoadImageW(armImageFile);
    mArmImage = img;
    mArmBitmap = bitmap;
}

/**
 * Draw the shooter
 *
 * @param graphics the graphics context to draw on
 */
void Shooter::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    // Get the center x and y position of this item
    auto posX = GetX() * Consts::MtoCM, posY= GetY() * Consts::MtoCM;

    // Calculate the width and height of the item in centimeters
    double width = mSize.x * Consts::MtoCM;
    double height = mSize.y * Consts::MtoCM;

    // translate to the correct location to draw the image
    graphics->PushState();

    graphics->Translate(posX, posY);

    // draw the actual shooter
    graphics->Scale(1, -1);
    graphics->DrawBitmap(*GetBitmap(),
            -width / 2,
            -height,
            width, height);
    graphics->Scale(1, -1);

    graphics->PopState();

    // draw the band on the shooter
    auto attachBackCM = Consts::MtoCM * (mBandAttachBack + b2Vec2(GetX(), GetY()));
    auto attachFrontCM = Consts::MtoCM * (mBandAttachFront + b2Vec2(GetX(), GetY()));

    wxPen pen(mBandColor, mBandWidth);
    graphics->SetPen(pen);

    if (IsLoaded())
    {
        auto spartyLoc = Consts::MtoCM * mSparty->GetBody()->GetPosition();
        auto spartyRadius = Consts::MtoCM * mSparty->GetConstants().first;

        // line from left bar to back of sparty
        graphics->StrokeLine(attachBackCM.x, attachBackCM.y,
                        spartyLoc.x - spartyRadius, spartyLoc.y);

        // shooter takes care of drawing the sparty that is loaded
        graphics->PushState();

        graphics->Translate(spartyLoc.x, spartyLoc.y);
        graphics->Scale(1, -1);
        graphics->DrawBitmap(*mSparty->GetBitmap(), -spartyRadius, -spartyRadius,
                             spartyRadius * 2, spartyRadius * 2);

        graphics->PopState();

        // draw line from back of sparty to right arm
        graphics->StrokeLine(spartyLoc.x - spartyRadius, spartyLoc.y,
                        attachFrontCM.x, attachFrontCM.y);

        // draw the extra arm
        graphics->PushState();

        graphics->Translate(posX, posY);
        graphics->Scale(1, -1);
        graphics->DrawBitmap(*mArmBitmap, -width / 2, -height, width, height);

        graphics->PopState();

    } else
    {
        graphics->StrokeLine(attachBackCM.x,attachBackCM.y,
                attachFrontCM.x,attachFrontCM.y);
    }

    graphics->PopState();
}

/**
 * Load a sparty onto the slingshot
 *
 * @param sparty the sparty to load on the slingshot
 */
void Shooter::LoadSparty(std::shared_ptr<AngrySparty> sparty)
{
    mSparty = sparty;
    mState = State::Loaded;

    // set sparty to the proper location
    auto midpoint = GetArmMidpoint();
    mSparty->GetBody()->SetTransform(midpoint, mSparty->GetAngle());
    mSparty->SetLocation(midpoint.x, midpoint.y);
}

/**
 * Shoot the current loaded sparty
 */
bool Shooter::Shoot()
{
    if (!IsLoaded()) return false;

    // Get pull vector
    b2Vec2 pullVec = mSparty->GetBody()->GetPosition() - GetArmMidpoint();

    // if the pull magnitude is too low, reset the angry sparty
    if (pullVec.Length() < mMinimumPullLength) {
        mSparty->GetBody()->SetTransform(GetArmMidpoint(),mSparty->GetAngle());
        return false;
    }

    // the angry sparty will travel in the opposite direction
    mSparty->SetDynamic();
    auto direction = -pullVec;
    direction *= mSparty->GetConstants().second;
    mSparty->GetBody()->SetLinearVelocity(direction);
    mState = State::Fired;
    return true;
}

b2Vec2 Shooter::GetArmMidpoint()
{
    auto pointBack = mBandAttachBack + b2Vec2(GetX(), GetY());
    auto pointFront = mBandAttachFront + b2Vec2(GetX(), GetY());
    return 0.5 * (pointBack + pointFront);
}