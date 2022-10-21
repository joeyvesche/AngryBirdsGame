/**
 * @file ItemBody.h
 * @author Will Morant
 *
 *
 */

#ifndef PROJECT1_ITEMBODY_H
#define PROJECT1_ITEMBODY_H
#include "Item.h"
//#include "Block.h"
#include "Physics.h"

class Block;
class ItemBody {
private:

    b2Body* mBody; /// Box2d Body for Item

    b2Vec2 mPosition; /// Position vector for Item

    b2Vec2 mSize; ///Size of the item

    double mFriction = 0; ///Friction of item

    double mDensity = 1; /// Density of item

    double mRestitution = 0; /// Restitution of item

    bool mStatic = 0; /// is this a static image?

    double mAngle = 0; /// Angle for the body

    double mX = 0;  /// X value for position
    double mY = 0;  /// Y value for position
    double mWidth = 0;  /// Width for size
    double mHeight = 0; /// Height for size




public:

    ItemBody(Block* block, wxXmlNode* node);

    void MakeBody(Physics *physics);

    b2Body* GetBody() {return mBody;}

    b2Vec2 GetPosition() {return mPosition;}
};

#endif //PROJECT1_ITEMBODY_H
