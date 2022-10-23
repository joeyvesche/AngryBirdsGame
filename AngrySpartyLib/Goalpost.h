/**
 * @file Goalposts.h
 * @author Joseph Pauls
 *
 *
 */

#ifndef PROJECT1_GOALPOSTS_H
#define PROJECT1_GOALPOSTS_H

#include "Item.h"
#include "Consts.h"

class Level;

/**
 * A class that describes a goalpost
 */
class Goalposts : public Item {
private:
    std::shared_ptr<wxImage> mArmImage; ///< Image of the goalpost arm
    std::shared_ptr<wxBitmap> mArmBitmap; ///< Bitmap of the goalpost arm

public:

    Goalposts(Level * level);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void Accept(ItemVisitor * visitor) override {}

    void XmlLoad(wxXmlNode *node);

};

#endif //PROJECT1_GOALPOSTS_H
