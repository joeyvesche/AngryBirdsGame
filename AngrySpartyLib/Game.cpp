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
// The directory that contains all level xml files
std::wstring const LevelDirectory = L"levels/";

// an ordered list of level xml file names
std::vector<std::wstring> const LevelFiles =
        {L"level0.xml", L"level1.xml", L"level2.xml", L"level3.xml"};

/**
 * Game Constructor
 */
Game::Game()
{
    // load all levels from files
    for (auto const & filename : LevelFiles) {
        mLevels.push_back(std::make_shared<Level>(LevelDirectory + filename));
    }

    SetLevel(1);
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
    int score = mLevel->OnDraw(graphics);
    wxTimer start_text;

    if(mDebug)
    {
        DebugDraw debugDraw(graphics);
        debugDraw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_centerOfMassBit);
        mLevel->GetPhysics()->GetWorld()->SetDebugDraw(&debugDraw);
        mLevel->GetPhysics()->GetWorld()->DebugDraw();
    }
    mScore.AddLevelScore(score);
    mScore.OnDraw(graphics, GetWidth(), GetHeight());

    graphics->PopState();

    LevelFinishChecker visitor;
    mLevel->Accept(&visitor);
    auto stat = visitor.LevelStat();

    if(levelTime <= 2)
    {
        // Draw the level failed text for a second
        wxFont bigFont(wxSize(50, 80),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD);
        graphics->PushState();
        graphics->Scale(1, -1);
        graphics->SetFont(bigFont, wxColour(0, 0, 255));
        std::string levelStartText = "Level " + std::to_string(mLevelNo) + " Begin";
        graphics->DrawText(levelStartText, -2.5*Consts::MtoCM, -4.5*Consts::MtoCM);
        graphics->PopState();
    }
    // Restart the level if it is failed
    if(stat == LevelFinishChecker::Stat::ReTry)
    {
        // Draw the level failed text for a second
        wxFont bigFont(wxSize(80, 110),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD);
        graphics->PushState();
        graphics->Scale(1, -1);
        graphics->SetFont(bigFont, wxColour(0, 0, 255));
        graphics->DrawText("Level Failed!", 0, 0);
        graphics->PopState();

        mScore.ClearLevelScore();
        mLevel->Reset();
    }
    // go to next level if level is won
    else if(stat == LevelFinishChecker::Stat::NextLevel)
    {
        // Draw the level success text for a second
        wxFont bigFont(wxSize(40, 70),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD);
        graphics->PushState();
        graphics->Scale(1, -1);
        graphics->SetFont(bigFont, wxColour(0, 0, 255));
        graphics->DrawText("Level Complete!", 0, 0);
        graphics->PopState();
        mScore.UpdateGameScore();
        SetLevel((mLevelNo + 1)% mLevels.size());
    }

}

/**
 * Add an item to the Game
 * @param item New item to add
 */
void Game::Add(std::shared_ptr<Item> item)
{
    //mItems.push_back(item);
}

/**
 * Test an x,y click location to see if it clicked
 * on some item in the Game.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<Item> Game::HitTest(int x, int y)
{
    return nullptr;
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
 * Clear the Game data.
 *
 * Deletes all known items in the Game.
 */
void Game::Clear()
{
}


/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Game::Update(double elapsed)
{
    mLevel->UpdateL(elapsed);
    levelTime += elapsed;
}

void Game::Accept(ItemVisitor* visitor)
{
    for (auto item: *mLevel) {
        item->Accept(visitor);
    }
}

void Game::SetLevel(int index)
{
    mLevelNo = index;
    mLevel = mLevels[index];
    mLevel->Reset();
    levelTime = 0;
}
