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
   double mWidth = 0.0;
   double mHeight = 0.0;

   std::shared_ptr<wxBitmap> mBackground = std::make_shared<wxBitmap>
           (L"images/background1.png", wxBITMAP_TYPE_ANY);

public:

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    double GetWidth() {return mWidth;}
    double GetHeight() {return mHeight;}
    void XmlLoad(wxXmlNode *node);
    void Accept(ItemVisitor * visitor) override {}

};

#endif //PROJECT1_BACKGROUND_H
