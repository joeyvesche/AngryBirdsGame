/**
 * @file level.cpp
 * @author Will Skaggs
*/

#include "pch.h"
#include "Level.h"
#include "Block.h"
#include "Background.h"

/**
 * Parse the xml node that contains all items
 * contained in this level and store the items
 *
 * @param items pointer to the items xml node
 */
void Level::LoadItemsXml(wxXmlNode * items)
{
    for (auto child = items->GetChildren(); child != nullptr; child = child->GetNext())
    {
        std::shared_ptr<Item> item;
        std::wstring name = child->GetName().ToStdWstring();

        if (name == L"background")
        {
            auto background = std::make_shared<Background>(this, L"background1.png");
            background->XmlLoad(child);
            item = background;

        } else if (name == L"block")
        {
           item = std::make_shared<Block>(this, child->GetAttribute(L"image").ToStdWstring());
        } else if (name == L"poly")
        {

        } else if (name == L"foe")
        {

        } else if (name == L"slingshot")
        {

        } else if (name == L"goalposts")
        {

        }

        if(item !=nullptr) {
            mItems.push_back(item);
        }
    }
}

/**
 * Process the xml node that contains all angry spartys
 * contained in this level and store them.
 *
 * @param angry pointer to the angry xml node
 */
void Level::LoadSpartysXml(wxXmlNode * angry)
{
    // grab the specified location and spacing for the angry spartys
    double x, y, spacing;

    angry->GetAttribute("x").ToDouble(&x);
    angry->GetAttribute("y").ToDouble(&y);
    angry->GetAttribute("spacing").ToDouble(&spacing);

    // parse and store angry spartys
    for (auto child = angry->GetChildren(); child != nullptr; child = child->GetNext())
    {
        std::wstring name = child->GetName().ToStdWstring();

        if (name == L"gruff-sparty")
        {

        } else if (name == L"helmet-sparty")
        {

        }
    }
}

/**
 * Create a level object from an XML file located
 * at the given filepath
 *
 * @param filepath the path to the level XML file
 */
Level::Level(std::wstring const & filepath)
{
    wxXmlDocument doc;

    // exit if loading the xml file was unsuccessful
    if (!doc.Load(filepath)) return;

    // process root tag attributes
    auto root = doc.GetRoot();

    root->GetAttribute("width").ToDouble(&mWidth);
    root->GetAttribute("height").ToDouble(&mHeight);
    b2Vec2 size;
    size.Set(float(mWidth), float(mHeight));
    Physics phys(size);
    mPhysics = &phys;


    // process everything else
    for (auto child = root->GetChildren(); child != nullptr; child = child->GetNext())
    {
        if (child->GetName() == L"items")
        {
            LoadItemsXml(child);
        } else if (child->GetName() == L"angry")
        {
            LoadSpartysXml(child);
        }
    }
}

/**
 * Draw the items
 *
 * @param graphics the graphics context to draw on
 */
void Level::OnDraw(std::shared_ptr<wxGraphicsContext> graphics)
{
    for (auto & item : mItems)
    {
        item->Draw(graphics);
    }
}

void Level::Add(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}