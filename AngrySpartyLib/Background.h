/**
 * @file Background.h
 * @author Will Morant
 *
 *
 */

#ifndef PROJECT1_BACKGROUND_H
#define PROJECT1_BACKGROUND_H

#include <wx/xml/xml.h>
#include <wx/graphics.h>
#include "Item.h"


class Background: public Item {
private:
   double mWidth = 0.0; /// Width of the background
   double mHeight = 0.0; /// Height of the background

public:

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    double GetWidth() {return mWidth;}
    double GetHeight() {return mHeight;}
    void XmlLoad(wxXmlNode *node);
    void Accept(ItemVisitor * visitor) override {}
    Background(Level *level, const std::wstring &filename);

};

#endif //PROJECT1_BACKGROUND_H
