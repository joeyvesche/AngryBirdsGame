/**
 * @file Level.h
 * @author Will Skaggs
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
#include "Physics.h"

class Item;
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

    void LoadItemsXml(wxXmlNode * items);
    void LoadSpartysXml(wxXmlNode * angry);

    std::shared_ptr<Physics> mPhysics; ///The physics system for this level


public:
    /// Default constructor (disabled)
    Level() = delete;

    Level(std::wstring const & filepath);

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics);

    void Reset();

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
     * get an iterator to one past the end of the items
     *
     * @return iterator to one past the end
     */
    auto end() { return mItems.end(); }

    std::shared_ptr<Physics> GetPhysics() {return mPhysics;}

    double GetWidth() const {return mWidth;}
    double GetHeight() const {return mHeight;}

    /**
     * Add an item to this level
     *
     * @param item the item to add to this level
     */
    void Add(std::shared_ptr<Item> item) { mItems.push_back(item); }
};


#endif //PROJECT1_LEVEL_H
