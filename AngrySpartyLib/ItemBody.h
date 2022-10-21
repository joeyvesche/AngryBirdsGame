/**
 * @file ItemBody.h
 * @author Will Morant
 *
 *
 */

#ifndef PROJECT1_ITEMBODY_H
#define PROJECT1_ITEMBODY_H
#include "Item.h"
#include "Block.h"
#include "Physics.h"

class ItemBody: public Item {
private:

    b2Body* mBody; /// Box2d Body for Item

    b2Vec2 mPosition; /// Position vector for Item

    b2Vec2 mSize; ///Size of the item

    float mFriction = 0; ///Friction of item

    float mDensity = 0; /// Density of item

    float mRestitution = 0; /// Restitution of item

    bool mStatic = 0; /// is this a static image?

    float mAngle = 0; /// Angle for the body




public:

    ///ItemBody(Block *block, wxXmlNode *node);

    ///void MakeBody(Physics *physics);

};

#endif //PROJECT1_ITEMBODY_H
