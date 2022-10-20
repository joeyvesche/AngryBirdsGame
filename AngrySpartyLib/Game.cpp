/**
 * @file Game.cpp
 * @author Yuqi Pan, Joey Vesche
 */
#include "pch.h"
#include "Game.h"
#include <wx/graphics.h>
#include "Consts.h"
#include "Item.h"
#include "Block.h"
#include <vector>

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
    mBackground = std::make_unique<wxBitmap>(L"images/background1.png", wxBITMAP_TYPE_ANY);
    mSlingshot = std::make_unique<wxBitmap>(L"images/slingshot.png", wxBITMAP_TYPE_ANY);

    // load all levels from files
    for (auto const & filename : LevelFiles) {
        mLevels.emplace_back(LevelDirectory + filename);
    }
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
    auto playingAreaSize = wxSize(GetWidth(), GetHeight());
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

    auto wid = mWidth*Consts::MtoCM;
    auto hit = mHeight*Consts::MtoCM;

    graphics->PushState();
    graphics->Scale(1, -1);
    graphics->DrawBitmap(*mBackground,
            -wid/2,
            -hit,
            wid, hit);
    graphics->PopState();

    graphics->PushState();
    graphics->Scale(0.17, -0.17);
    graphics->DrawBitmap(*mSlingshot,
            -3500,
            -920,
            350, 900);
    graphics->PopState();

    wxFont bigFont(wxSize(40, 70),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_BOLD);
    graphics->SetFont(bigFont, wxColour(255, 0, 0));
    graphics->GetTextExtent(L"000", &wid, &hit);
    graphics->DrawText(L"000", 5.5*Consts::MtoCM, 7*Consts::MtoCM);
    graphics->DrawText(L"000", -6.75*Consts::MtoCM, 7*Consts::MtoCM);

    //
    // From here we are dealing with centimeter pixels
    // and Y up being increase values
    //
    // INSERT YOUR DRAWING CODE HERE
    mLevel.OnDraw(graphics);

    graphics->PopState();

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
 * Save the Game as a .aqua XML file.
 *
 * Open an XML file and stream the Game data to it.
 *
 * @param filename The filename of the file to save the Game to
 */
void Game::Save(const wxString& filename)
{
    wxXmlDocument xmlDoc;

    auto root = new wxXmlNode(wxXML_ELEMENT_NODE, L"aqua");
    xmlDoc.SetRoot(root);

    // Iterate over all items and save them

    if (!xmlDoc.Save(filename, wxXML_NO_INDENTATION)) {
        wxMessageBox(L"Write to XML failed");
        return;
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

}

void Game::Accept(ItemVisitor* visitor)
{
    for (auto & item: mLevel) {
        item.Accept(visitor);
    }
}
