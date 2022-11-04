/**
 * @file Game.cpp
 * @authors Yuqi Pan, Joey Vesche, Will Morant, Joseph Pauls
 */
#include "pch.h"
#include "Game.h"
#include <wx/graphics.h>
#include "Consts.h"
#include "Item.h"
#include "Block.h"
#include <vector>
#include "DebugDraw.h"
#include "LevelFinishChecker.h"
#include "ShooterVisitor.h"
#include "Shooter.h"
#include "DeadFoeCollector.h"

/// The directory that contains all level xml files
std::wstring const LevelDirectory = L"levels/";

/// an ordered list of level xml file names
std::vector<std::wstring> const LevelFiles =
        {L"level0.xml", L"level1.xml", L"level2.xml", L"level3.xml"};

/// the delay of loading a level in seconds
double const TransitionDelayAll = 2;

/// the minimum pull length of the shooter in meters
const double ShooterMinimumPullLength = 0.25;

/// The minimum velocity of a sparty in meters / second
const double MinimumSpartyVelocity = 0.1;

/**
 * Game Constructor
 */
Game::Game()
{
    // load all levels from files
    for (auto const & filename : LevelFiles) {
        mLevels.push_back(std::make_shared<Level>(LevelDirectory + filename));
    }

    SetLevel(3);
}

/**
 * Handle drawing the game on the screen including all subsystems.
 * @param graphics Graphics context to draw on
 * @param width Width of the window in pixels
 * @param height Height of the window in pixels
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{

    wxBrush background(*wxBLACK);
    graphics->SetBrush(background);
    graphics->DrawRectangle(0, 0, width, height);

    graphics->PushState();

    // Get the playing area size in centimeters
    b2Vec2 playingAreaSize = b2Vec2(GetWidth(), GetHeight());
    playingAreaSize *= Consts::MtoCM;

    //
    // Automatic Scaling
    // We use CM display units instead of meters
    // because a 1-meter wide line is very wide
    //
    auto scaleX = double(height)/double(playingAreaSize.y);
    auto scaleY = double(width)/double(playingAreaSize.x);
    mScale = scaleX<scaleY ? scaleX : scaleY;
    graphics->Scale(mScale, -mScale);

    // Determine the virtual size in cm
    auto virtualWidth = (double) width/mScale;
    auto virtualHeight = (double) height/mScale;

    // And the offset to the middle of the screen
    mXOffset = virtualWidth/2.0;
    mYOffset = -(virtualHeight-playingAreaSize.y)/2.0-playingAreaSize.y;

    graphics->Translate(mXOffset, mYOffset);

    //
    // From here we are dealing with centimeter pixels
    // and Y up being increase values
    //
    mLevel->OnDraw(graphics);
    wxTimer start_text;

    if(mDebug)
    {
        DebugDraw debugDraw(graphics);
        debugDraw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_centerOfMassBit);
        mLevel->GetPhysics()->GetWorld()->SetDebugDraw(&debugDraw);
        mLevel->GetPhysics()->GetWorld()->DebugDraw();
    }
    mScore.OnDraw(graphics, GetWidth(), GetHeight());

    graphics->PopState();


    // Draw a prompt to the center of the screen if needed
    wxFont bigFont(wxSize(50, 80),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_BOLD);

    std::wstring message;

    switch (mState)
    {
        case State::Loading:
        {
            message = L"Level " + std::to_wstring(mLevelNo)+ L" Begin";
            break;
        }
        case State::Failure:
        {
            message = L"Level Failed!";
            break;
        }
        case State::Success:
        {
            message = L"Level Complete!";
            break;
        }
    }

    if (!message.empty())
    {
        wxSize bigSize(GetWidth() * Consts::MtoCM / 10, GetHeight() * Consts::MtoCM / 10);

        wxFont bigFont(bigSize,
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD);

        graphics->PushState();

        double msgWidth, msgHeight; // width and height of the text (in cm thanks to scaling)
        graphics->GetTextExtent(message, &msgWidth, &msgHeight);

        graphics->Translate(-msgWidth / 2, (GetHeight() * Consts::MtoCM + msgHeight) / 2);
        graphics->Scale(1, -1);
        graphics->SetFont(bigFont, wxColour(0, 0, 255));
        graphics->DrawText(message, 0, 0);

        graphics->PopState();
    }
}

/**
 * Shoot the current loaded sparty
 */
void Game::Shoot()
{
    ShooterVisitor shooterVisitor;
    mLevel->Accept(&shooterVisitor);
    Shooter * shooter = shooterVisitor.Get();
    bool success = shooter->Shoot();

    if (success)
    {
        mState = State::Wait;
    }
}


/**
 * Load the Game from a .aqua XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param filename The filename of the file to load the Game from.
 */
void Game::Load(const wxString& filename)
{

}


/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Game::Update(double elapsed)
{
    mLevel->UpdateL(elapsed);
    mLevelTime += elapsed;

    switch (mState)
    {
        case State::Loading:
        {
            mTimer += elapsed;

            if (mTimer >= TransitionDelayAll)
            {
                mTimer = 0;
                mState = State::Ready;
            }
            break;
        }

        case State::Failure:
        {
            mTimer += elapsed;

            if (mTimer >= TransitionDelayAll)
            {
                mTimer = 0;
                mScore.ClearLevelScore();
                SetLevel(mLevelNo);
            }
            break;
        }

        case State::Success:
        {
            mTimer += elapsed;

            if (mTimer >= TransitionDelayAll)
            {
                mScore.UpdateGameScore();
                mTimer = 0;

                // if we're on the last level, stay on that level. Otherwise, move forward
                if (mLevelNo + 1 == mLevels.size())
                {
                    SetLevel(mLevelNo);
                } else
                {
                    SetLevel((mLevelNo + 1) % mLevels.size());
                }
            }

            break;
        }

        case State::Wait:
        {
            // make sure angry sparty is done before moving on
            ShooterVisitor shooterVisitor;
            mLevel->Accept(&shooterVisitor);
            auto shooter = shooterVisitor.Get();
            auto sparty = shooter->GetLoadedSparty();

            if (sparty->GetBody()->GetLinearVelocity().Length() < MinimumSpartyVelocity)
            {
                mTimer += elapsed;

                if (mTimer < TransitionDelayAll) break;

                mTimer = 0;
                shooter->Release();
                mLevel->PopSparty();
                mLevel->GetPhysics()->GetWorld()->DestroyBody(sparty->GetBody());

                // Check if foes are dead at the end of the turn and remove dead foes from the items list.
                DeadFoeCollector deathVisitor;
                Accept(&deathVisitor);
                auto deathList = deathVisitor.DeathList();
                mScore.AddLevelScore(deathList.size() * 100) ; //< each foe is worth 100 points
                mLevel->KillFoe(deathList);

                // If the level is over, count two seconds before restarting or moving on
                LevelFinishChecker visitor;
                mLevel->Accept(&visitor);
                auto stat = visitor.LevelStat();

                if(stat == LevelFinishChecker::Stat::ReTry)
                {
                    mState = State::Failure;
                }
                else if(stat == LevelFinishChecker::Stat::NextLevel)
                {
                    mState = State::Success;
                }
                else
                {
                    mState = State::Ready;
                }
            }

            break;
        }

        case State::Ready:
        {
            // Search for the shooter in the level
            ShooterVisitor shooterVisitor;
            mLevel->Accept(&shooterVisitor);
            auto shooter = shooterVisitor.Get();

            // if the shooter DNE, there's nothing more to do
            if (shooter == nullptr) break;

            // load a sparty if needed
            if (shooter->GetLoadedSparty() == nullptr)
            {
                shooter->LoadSparty(mLevel->GetNextSparty());
            }

            break;
        }


    }
}
/**
 * Accepts an Item Visitor
 * @param visitor Visitor
 */
void Game::Accept(ItemVisitor* visitor)
{
    for (auto item: *mLevel) {
        item->Accept(visitor);
    }
}

/**
 * Sets the Level
 * @param index Level to set
 */
void Game::SetLevel(int index)
{
    mLevelNo = index;
    mLevel = mLevels[index];
    mLevel->Reset();
    mState = State::Loading;
    mLevelTime = 0;
    mTimer = 0;
    mScore.ClearLevelScore();
}
