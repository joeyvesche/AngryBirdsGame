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
/**
 * Base Class for a block
 */
class Block : public Item {
private:

    b2Body* mBody; /// Box2d Body for object

    b2Vec2 mPosition;

    b2Vec2 mSize;

    bool mStatic = 0;






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

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    ///void Draw(std::shared_ptr<wxGraphicsContext> graphics); -uncoimment later

};

#endif //PROJECT1_BLOCK_H
