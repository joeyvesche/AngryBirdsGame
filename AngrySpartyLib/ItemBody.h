/**
 * @file ItemBody.h
 * @author Will Morant
 *
 * Underlying Body class for all the Objects
 */

#ifndef PROJECT1_ITEMBODY_H
#define PROJECT1_ITEMBODY_H
#include "Item.h"
#include "Physics.h"
#include <memory>

class Block;
class AngrySparty;
class Foe;
class Poly;

/**
 * Class that describes the physics body for an item
 */
class ItemBody {
private:

    /// Box2d Body for Item
    b2Body* mBody;

    /// Position vector for Item
    b2Vec2 mPosition;

    ///Size of the item
    b2Vec2 mSize;

    ///Friction of item
    double mFriction = 0.5;

    /// Density of item
    double mDensity = 1;

    /// Restitution of item
    double mRestitution = 0.5;

    /// is this a static image?
    bool mStatic = 0;

    /// Angle for the body
    double mAngle = 0;

    /// X value for position
    double mX = 0;
    /// Y value for position
    double mY = 0;
    /// Width for size
    double mWidth = 0;
    /// Height for size
    double mHeight = 0;
    ///Radius for the object
    double mRadius = 0;
    /// Down for foe
    double mDown = 0;

public:

    ItemBody(Block* block, wxXmlNode* node);
    ItemBody(AngrySparty * angry);
    ItemBody(Foe *foe, wxXmlNode* node);
    ItemBody(Poly *poly, wxXmlNode* node);
    void CreateFoe(std::shared_ptr<Physics> physics);

    /**
     * Get the b2Body created by this object
     * @return
     */
    b2Body* GetBody() {return mBody;}

    /**
     * Get the position of this b2Body
     * @return
     */
    b2Vec2 GetPosition() {return mPosition;}

    b2Body* CreateBody(std::shared_ptr<Physics> physics);

    void CreateSparty(std::shared_ptr<Physics> physics, int key);

    void CreateBlock(std::shared_ptr<Physics> physics);
    void CreatePoly(std::shared_ptr<Physics> physics, const std::vector<b2Vec2>& vertices);
};

#endif //PROJECT1_ITEMBODY_H
