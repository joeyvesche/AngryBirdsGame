/**
 * @file Block.h
 * @author Joseph Pauls, Will Morant
 *
 *Base Class for block items. inherited from Item
 */

#ifndef PROJECT1_BLOCK_H
#define PROJECT1_BLOCK_H
#include "Item.h"
#include <string>
#include "Physics.h"
#include "Consts.h"
#include "ItemBody.h"
#include "Level.h"

/**
 * Base Class for a block
 */
class Block : public Item {
private:

    b2Body* mBody; /// Box2d Body for block


    b2Vec2 mSize; /// size vector of block


    std::shared_ptr<wxImage> mBlockImage; ///Image for block
    std::shared_ptr<wxBitmap> mBlockBitmap; ///Bitmap for block

    int mRepeatX = 1; /// Amount of times to repeat block








public:
    /// Default constructor (disabled)
    Block() = delete;

    /// Copy constructor (disabled)
    Block(const Block &) = delete;

    Block(Level* level, const std::wstring& filename);

    void XmlLoad(wxXmlNode* node) override;
    void Accept(ItemVisitor * visitor) override;

    ///getter for box2D Body object
    b2Body *GetBody() {return mBody;}

    b2Vec2 GetPosition() {return mBody->GetPosition();}

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;


};

#endif //PROJECT1_BLOCK_H
