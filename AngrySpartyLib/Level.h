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
#include "Item.h"
#include "AngrySparty.h"

/**
 * This class loads and stores the contents of a
 * level XML file
 */
class Level {
private:
    std::pair<double, double> mSize; ///< {width, height} of the level in meters
    std::vector<Item> mItems; ///< All items in this level

    void LoadItemsXml(wxXmlNode * items);
    void LoadSpartysXml(wxXmlNode * angry);

public:
    /**
     * Construct a new empty level object
     */
    Level() = default;

    Level(std::wstring const & filepath);

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Get the size of the level in meters
     *
     * @return the {width, height} of this level in meters
     */
    std::pair<double, double> Size() const { return mSize; }

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
};


#endif //PROJECT1_LEVEL_H
