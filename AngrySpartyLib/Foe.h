/**
 * @file Foe.h
 * @author Will Morant
 *
 * Foe class
 */

#ifndef PROJECT1_FOE_H
#define PROJECT1_FOE_H

#include "Item.h"
#include <string>
/**
 * Class that describes a foe object
 */
class Foe : public Item {
private:
    double mRadius = 0;
    double mDown = 0;
    ///File Name. Set when loading in the foe from an XML file


public:
    /// Default constructor (disabled)
    Foe() = delete;

    /// Copy constructor (disabled)
    Foe(const Foe &) = delete;

    /// Assignment operator
    void operator=(const Foe &) = delete;

    void XmlLoad(wxXmlNode* node) override;

    void Accept(ItemVisitor * visitor) override;
    Foe(Level *level, const std::wstring &filename);
    /**
     * Draw this item
     * @param dc Device context to draw on
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
};

#endif //PROJECT1_FOE_H
