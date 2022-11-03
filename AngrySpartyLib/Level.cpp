/**
 * @file Level.cpp
 * @authors Will Skaggs, Joseph Pauls, Joey Vesche
*/

#include "pch.h"
#include "Level.h"
#include "Block.h"
#include "SlingShot.h"
#include "Poly.h"
#include "Background.h"
#include "Goalpost.h"
#include "GruffSparty.h"
#include "HelmetSparty.h"
#include "LimpetSparty.h"
#include "Physics.h"
#include "DeadFoeCollector.h"
#include "ShooterVisitor.h"

/**
 * Parse the xml node that contains all items
 * contained in this level and store the items
 *
 * @param items pointer to the items xml node
 */
void Level::LoadItemsXml(wxXmlNode * items)
{
    bool blockSet = false; ///set to true when friction and restitution are loaded in
    double friction = 0;
    double restitution = 0;
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
            if (blockSet == false)
            {
                child->GetAttribute(L"friction", L"0").ToDouble(&friction);
                child->GetAttribute(L"restitution", L"0").ToDouble(&restitution);
                if (friction != 0)
                {
                    blockSet = true;
                }

            }

            block->SetFricRest(friction, restitution);
            block->XmlLoad(child);
            item = block;

        } else if (name == L"poly")
        {
            auto poly = std::make_shared<Poly>(this, child->GetAttribute(L"image").ToStdWstring());

            poly->XmlLoad(child);
            item = poly;

        } else if (name == L"foe")
        {
            auto foe = std::make_shared<Foe>(this, child->GetAttribute(L"image").ToStdWstring());
            foe->XmlLoad(child);
            item = foe;
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
        else if (name == L"limpet-sparty")
        {
            sparty = std::make_shared<LimpetSparty>(this);
        }
        mItems.push_back(sparty);
        mSpartys.push_back(sparty);
        sparty->SetLocation(x, y);
        sparty->SetBody(this);
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
    mSpartys.clear();

    // process root tag attributes
    auto root = mDoc.GetRoot();

    root->GetAttribute("width").ToDouble(&mWidth);
    root->GetAttribute("height").ToDouble(&mHeight);

    // Create a new physics world for our items
    b2Vec2 size;
    size.Set(mWidth, mHeight);
    mPhysics = std::make_shared<Physics>(size);
    SetContactListener();

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
 * @return Score of this draw
 */
void Level::OnDraw(std::shared_ptr<wxGraphicsContext> graphics)
{
    ShooterVisitor shooterVisitor;
    Accept(&shooterVisitor);
    auto shooter = shooterVisitor.Get();

    for (auto & item : mItems)
    {
        if (shooter == nullptr || shooter->GetLoadedSparty() != item || !shooter->IsLoaded())
        {
            item->Draw(graphics);
        }
    }

}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Level::UpdateL(double elapsed)
{
    mPhysics->UpdateP(elapsed);
    for (auto element: mSpartys) {
        bool flip = element->Obliterate(mObliterateBody);
        if (flip == true)
            break;
    }
}

void Level::Accept(ItemVisitor* visitor)
{
    for(auto item : mItems)
    {
        item->Accept(visitor);
    }
}

void Level::Accept(LimpetKillVisitor* visitor)
{
    for (auto item : mItems)
    {
        item->Accept(visitor);
    }
}

/**
 * Contact Listener for box2D, allows custom functions on contact between objects.
 * @param contact
 */

void Level::AngryContactListener::BeginContact(b2Contact *contact)
{
    b2Body *firstBody = contact->GetFixtureA()->GetBody();
    b2Body *secondBody = contact->GetFixtureB()->GetBody();



    for (auto i = mParent->SpartyBegin(); i != mParent->SpartyEnd(); i++)
    {
        if ((*i)->GetBody() == firstBody) /// If the item is the first body in contact
        {
            mParent->SetObliterateBody(secondBody);
        }
        else if ((*i)->GetBody() == secondBody)
        {
            mParent->SetObliterateBody(firstBody);
        }
    }
}

void Level::SetObliterateBody(b2Body* body)
{
    mObliterateBody = body;
}

/**
 * Remove foes from the deathList from the items list.
 * @param deathList a list of foes that have been determined to be dead
 */
void Level::KillFoe(std::vector<Foe*> deathList)
{
    for(auto item: deathList)
    {
        auto target = mItems.begin();
        for(; target != mItems.end(); target++)
        {
            if((*target).get() == item)
                break;
        }
        if(target!=mItems.end())
        {
            item->Detach();
            mItems.erase(target);
        }
    }
}
