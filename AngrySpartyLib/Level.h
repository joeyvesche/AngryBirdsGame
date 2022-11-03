/**
 * @file Level.h
 * @authors Will Skaggs, Joseph Pauls
 *
 * This class loads and stores the contents of an
 * XML level file
 */

#ifndef PROJECT1_LEVEL_H
#define PROJECT1_LEVEL_H

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include "AngrySparty.h"
#include "Foe.h"
class ItemVisitor;
class Item;
class AngrySparty;

/**
 * This class loads and stores the contents of a
 * level XML file
 */
class Level {
private:
    wxXmlDocument mDoc; ///< the xml document that represents this level

    double mWidth = 0.0;
    double mHeight = 0.0;
    std::vector<std::shared_ptr<Item>> mItems; ///< All items in this level
    std::vector<std::shared_ptr<AngrySparty>> mSpartys; ///< All Spartys in this level

    void LoadItemsXml(wxXmlNode * items);
    void LoadSpartysXml(wxXmlNode * angry);

    std::shared_ptr<Physics> mPhysics; ///The physics system for this level

    int mScore = 0; /// A score tracker for this level

    ///The b2Body to be obliterated, for the LimpetSparty
    b2Body* mObliterateBody = nullptr;

public:

    /// Default constructor (disabled)
    Level() = delete;

    Level(std::wstring const & filepath);

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics);

    void Reset();

    /**
     * Return the next sparty in line for the slingshot.
     *
     * @return shared_ptr to an AngrySparty
     */
    std::shared_ptr<AngrySparty> GetNextSparty() { return mSpartys.empty() ? nullptr : mSpartys.back(); }

    /**
     * Remove the most recently used sparty from the level
     */
    void PopSparty()
    {
        mItems.erase(std::find(mItems.begin(), mItems.end(), mSpartys.back()));
        mSpartys.pop_back();
    }

    /**
     * Get the size of the level in meters
     *
     * @return the {width, height} of this level in meters
     */
    //std::pair<double, double> Size() const { return mSize; }

    /**
     * get an iterator to the beginning of the items
     *
     * @return iterator to the beginning
     */
    auto begin() { return mItems.begin(); }

    /**
     * Iterator to beginning of Spartys
     * @return
     */
    auto SpartyBegin() {return mSpartys.begin();}

    /**
     * get an iterator to one past the end of the items
     *
     * @return iterator to one past the end
     */
    auto end() { return mItems.end(); }

    /**
     * Iterator to end of Spartys
     * @return
     */
    auto SpartyEnd() {return mSpartys.end();}

    std::shared_ptr<Physics> GetPhysics() {return mPhysics;}

    double GetWidth() const {return mWidth;}
    double GetHeight() const {return mHeight;}

    void SetObliterateBody(b2Body *body);

    /**
     * Add an item to this level
     *
     * @param item the item to add to this level
     */
    void Add(std::shared_ptr<Item> item) { mItems.push_back(item); }
    void remove(std::vector<std::shared_ptr<Item>>::iterator it) {mItems.erase(it);}
    void UpdateL(double elapsed);
    void Accept(ItemVisitor* visitor);

    /**
     * Contact Listener class for the physics world
     */

    class AngryContactListener : public b2ContactListener {
    private:
        Level *mParent = nullptr;
    public:
        AngryContactListener(Level* level) {mParent = level;}
        void BeginContact(b2Contact *contact) override;


    };

    /**
     * Sets contact listener for physics world
     */
    void SetContactListener()
    {
        mPhysics->GetWorld()->SetContactListener(new AngryContactListener(this));
    }

    void KillFoe(std::vector<Foe*> deathlist);
};


#endif //PROJECT1_LEVEL_H
