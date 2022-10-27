/**
 * @file level.cpp
 * @author Will Skaggs
*/

#include "pch.h"
#include "Level.h"
#include "Block.h"
#include "SlingShot.h"
#include "Poly.h"
#include "Background.h"
#include "SlingShot.h"
#include "Goalpost.h"
#include "Foe.h"
#include "GruffSparty.h"
#include "HelmetSparty.h"

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
            std::shared_ptr<Background> background;
            background = std::make_shared<Background>(this, child->GetAttribute(L"image").ToStdWstring());
            background->XmlLoad(child);
            item = background;

        } else if (name == L"block")
        {
           auto block = std::make_shared<Block>(this, child->GetAttribute(L"image").ToStdWstring());
           block->XmlLoad(child);
           item = block;

        } else if (name == L"poly")
        {
            auto poly = std::make_shared<Poly>(this, child->GetAttribute(L"image").ToStdWstring());

            poly->XmlLoad(child);
            item = poly;

        } else if (name == L"foe")
        {
            item = std::make_shared<Foe>(this, child->GetAttribute(L"image").ToStdWstring());

        } else if (name == L"slingshot")
        {
            auto slingshot = std::make_shared<SlingShot>(this);
            slingshot->XmlLoad(child);
            item = slingshot;
        } else if (name == L"goalposts")
        {
            auto goalpost = std::make_shared<Goalposts>(this);
            goalpost->XmlLoad(child);
            item = goalpost;
        }

        if(item !=nullptr) {
            mItems.push_back(item);
            item->XmlLoad(child);
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
        std::shared_ptr<AngrySparty> sparty;
        if (name == L"gruff-sparty")
        {
            sparty = std::make_shared<GruffSparty>(this);
        } else if (name == L"helmet-sparty")
        {
            sparty = std::make_shared<HelmetSparty>(this);
        }
        mItems.push_back(sparty);
        sparty->SetLocation(x, y);
        x += spacing;
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
    mDoc.Load(filepath);
    Reset();
}

/**
 * Reset the level to its original state from
 * the xml file
 */
void Level::Reset()
{
    // clear any previously stored items
    mItems.clear();

    // process root tag attributes
    auto root = mDoc.GetRoot();

    root->GetAttribute("width").ToDouble(&mWidth);
    root->GetAttribute("height").ToDouble(&mHeight);
    b2Vec2 size;
    size.Set(float(mWidth), float(mHeight));
    mPhysics = std::make_shared<Physics>(size);

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
