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
#include <list>
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
    std::list<std::shared_ptr<Item>> mItems; ///< All items in this level

    void LoadItemsXml(wxXmlNode * items);
    void LoadSpartysXml(wxXmlNode * angry);

public:
    Level(std::wstring const & filepath);
};


#endif //PROJECT1_LEVEL_H
