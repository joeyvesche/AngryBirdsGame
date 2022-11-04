/**
 * @file Foe.h
 * @author Will Morant, Joey Vesche
 *
 * Base class for Foe
 */

#ifndef PROJECT1_FOE_H
#define PROJECT1_FOE_H

#include "Item.h"
#include "LimpetKillVisitor.h"

class ItemBody;

/**
 * Class that describes a foe object
 */
class Foe : public Item {
private:
    /// Radius of the foe
    double mRadius = 0;
    /// Y-value for a foe to be considered "dead"
    double mDown = 0;

    ///Body of the AngrySparty object
    b2Body* mBody;

    /// Previous x position
    double mLastX = 0;

    ///Previous Y position
    double mLastY = 0;

    /// Is this foe moving?
    bool mMoving = false;
public:
    /// Default constructor (disabled)
    Foe() = delete;

    /// Copy constructor (disabled)
    Foe(const Foe &) = delete;

    /// Assignment operator
    void operator=(const Foe &) = delete;

    void XmlLoad(wxXmlNode* node) override;

    void Accept(ItemVisitor * visitor) override;
    Foe(Level *level, const std::wstring &filename);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Gets the physics body for a foe object
     * @return
     */
    b2Body* GetBody() override {return mBody;}

    bool IsDead();
    void Detach();
};
#endif //PROJECT1_FOE_H
