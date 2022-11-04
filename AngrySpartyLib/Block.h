/**
 * @file Block.h
 * @author Joseph Pauls, Will Morant
 *
 * Base Class for block items. inherited from Item
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
    /// Box2d Body for block
    b2Body* mBody;

    /// size vector of block
    b2Vec2 mSize;

    /// Amount of times to repeat block
    int mRepeatX = 1;

    /// Friction for the block
    double mFriction = 0.0;

    /// Restitution for the block
    double mRestitution = 0.0;


public:
    /// Default constructor (disabled)
    Block() = delete;

    /// Copy constructor (disabled)
    Block(const Block &) = delete;

    Block(Level* level, const std::wstring& filename);

    void XmlLoad(wxXmlNode* node) override;
    void Accept(ItemVisitor * visitor) override;

    /**
     * Getter for box2D body
     * @return  b2Body of the object
     */
    b2Body *GetBody() override {return mBody;}

    /**
     * Get the position of the object
     * @return
     */
    b2Vec2 GetPosition() {return mBody->GetPosition();}

    /**
     * Get the size of the object
     * @return
     */
    b2Vec2 GetSize() {return mSize;};

    void SetFricRest(double friction, double restitution);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
};

#endif //PROJECT1_BLOCK_H
