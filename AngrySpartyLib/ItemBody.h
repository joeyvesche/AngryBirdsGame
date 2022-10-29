/**
 * @file ItemBody.h
 * @author Will Morant
 *
 *
 */

#ifndef PROJECT1_ITEMBODY_H
#define PROJECT1_ITEMBODY_H
#include "Item.h"
#include "Physics.h"
#include <memory>

class Block;
class AngrySparty;
class Foe;
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
    double mRadius = 0; ///Radius for the object
    double mDown = 0;  /// Down for foe




public:

    ItemBody(Block* block, wxXmlNode* node);
    ItemBody(AngrySparty * angry);
    ItemBody(Foe *foe, wxXmlNode* node);

    void MakeBody(std::shared_ptr<Physics> physics, int key);

    b2Body* GetBody() {return mBody;}

    b2Vec2 GetPosition() {return mPosition;}

    b2Body* CreateBody(std::shared_ptr<Physics> physics);

    void CreateSparty(std::shared_ptr<Physics> physics, int key);
};

#endif //PROJECT1_ITEMBODY_H
