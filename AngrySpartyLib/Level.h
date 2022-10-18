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
#include "XmlView.h"
#include <utility>

/**
 * This class stores the contents of an XML level
 * file and supports parsing of the stored data
 */
class Level {
private:
    wxXmlDocument mDoc; ///< The XML document from a level file

public:
    Level(std::wstring const & filepath);

    std::pair<double, double> GetSize() const;

    /**
     * View the XML contents of a level
     *
     * @return an XML view of the xml root
     */
    XmlView Contents() const { return XmlView(mDoc.GetRoot()); }
};


#endif //PROJECT1_LEVEL_H
