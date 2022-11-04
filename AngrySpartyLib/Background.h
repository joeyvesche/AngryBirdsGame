/**
 * @file Background.h
 * @author Will Morant
 *
 * Background Base class
 */

#ifndef PROJECT1_BACKGROUND_H
#define PROJECT1_BACKGROUND_H

#include <wx/xml/xml.h>
#include <wx/graphics.h>
#include "Item.h"

/**
 * Class that describes the background for the game
 */
class Background: public Item {
private:
    /// Width of the background
   double mWidth = 0.0;

    /// Height of the background
   double mHeight = 0.0;

public:

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    /**
     * Returns the width for the background
     * @return
     */
    double GetWidth() {return mWidth;}
    /**
     * Returns the height for the background
     * @return
     */
    double GetHeight() {return mHeight;}
    void XmlLoad(wxXmlNode *node);
    /**
     * Accept an item visitor
     * @param visitor
     */
    void Accept(ItemVisitor * visitor) override {}
    Background(Level *level, const std::wstring &filename);

};

#endif //PROJECT1_BACKGROUND_H
