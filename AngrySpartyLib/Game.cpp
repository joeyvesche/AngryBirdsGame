/**
 * @file Game.cpp
 * @author Yuqi Pan, Joey Vesche
 */
#include "pch.h"
#include "Game.h"
#include <wx/graphics.h>
#include "Consts.h"
#include "Item.h"
/**
 * Game Constructor
 */
Game::Game()
{
    mBackground = std::make_unique<wxBitmap>(L"images/background1.png", wxBITMAP_TYPE_ANY);
    mSlingshot = std::make_unique<wxBitmap>(L"images/slingshot.png", wxBITMAP_TYPE_ANY);
}


/**
 * Handle drawing the game on the screen including all subsystems.
 * @param graphics Graphics context to draw on
 * @param width Width of the window in pixels
 * @param height Height of the window in pixels
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    wxBrush background(*wxWHITE);
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
    auto scaleX = double(height) / double(playingAreaSize.y);
    auto scaleY = double(width) / double(playingAreaSize.x);
    mScale = scaleX < scaleY ? scaleX : scaleY;
    graphics->Scale(mScale, -mScale);

    // Determine the virtual size in cm
    auto virtualWidth = (double)width / mScale;
    auto virtualHeight = (double)height / mScale;

    // And the offset to the middle of the screen
    mXOffset = virtualWidth / 2.0;
    mYOffset = -(virtualHeight - playingAreaSize.y) / 2.0 - playingAreaSize.y;

    graphics->Translate(mXOffset, mYOffset);

    //
    // From here we are dealing with centimeter pixels
    // and Y up being increase values
    //
    // INSERT YOUR DRAWING CODE HERE
    auto wid = mWidth * Consts::MtoCM;
    auto hit = mHeight * Consts::MtoCM;

    graphics->PushState();
    graphics->Scale(1, -1);
    graphics->DrawBitmap(*mBackground,
            -wid/2,
            -hit,
            wid, hit);
    graphics->PopState();

    graphics->PushState();
    graphics->Scale(0.1, -0.1);
    graphics->DrawBitmap(*mSlingshot,
                -3300,
                -600,
                wid/2, hit);
    graphics->PopState();
}

/**
 * Add an item to the Game
 * @param item New item to add
 */
void Game::Add(std::shared_ptr<Item> item)
{

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
void Game::Save(const wxString &filename)
{
    wxXmlDocument xmlDoc;

    auto root = new wxXmlNode(wxXML_ELEMENT_NODE, L"aqua");
    xmlDoc.SetRoot(root);

    // Iterate over all items and save them
    for (auto item : mItems)
    {

    }



    if(!xmlDoc.Save(filename, wxXML_NO_INDENTATION))
    {
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
void Game::Load(const wxString &filename)
{
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Game file");
        return;
    }

    Clear();

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    //
    // Traverse the children of the root
    // node of the XML document in memory!!!!
    //
    auto child = root->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"item")
        {
            XmlItem(child);
        }
    }
}

/**
 * Clear the Game data.
 *
 * Deletes all known items in the Game.
 */
void Game::Clear()
{
    mItems.clear();
}

/**
 * Handle a node of type item.
 * @param node XML node
 */
void Game::XmlItem(wxXmlNode *node)
{
    // A pointer for the item we are loading
    std::shared_ptr<Item> item;

    // We have an item. What type?
    auto type = node->GetAttribute(L"type");
    /*
    if (type == L"block")
    {
        item = make_shared<Block>(this);
    }
     */

    if (item != nullptr)
    {
        Add(item);
        item->XmlLoad(node);
    }
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Game::Update(double elapsed)
{

}