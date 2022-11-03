/**
 * @file Shooter.h
 * @author Will Skaggs
 *
 * Implementing the slingshot firing
 */

#ifndef PROJECT1_SHOOTER_H
#define PROJECT1_SHOOTER_H

#include "Item.h"
#include "Level.h"
#include <string>
#include "AngrySparty.h"
#include "ItemVisitor.h"

class Shooter : public Item {
private:
    std::shared_ptr<wxImage> mArmImage; ///< Image of the extra arm
    std::shared_ptr<wxBitmap> mArmBitmap; ///< Bitmap of the extra arm
    std::shared_ptr<AngrySparty> mSparty = nullptr; ///< A pointer to the sparty currently in the slingshot

    /** The states of a shooter **/
    enum class State { Loaded, Fired, Reloading };

    State mState = State::Reloading; ///< The current state of the shooter

    double mMinimumPullLength = 0.25; ///< the minimum pull back length in meters

protected:
    b2Vec2 mSize; ///< The size of this shooter
    b2Vec2 mBandAttachBack; ///< The back attachment point of the band relative to the base
    b2Vec2 mBandAttachFront; ///< The front attachment point of the band relative to the base
    double mMaxPull; ///< The maximum pull of the slingshot
    wxColor mBandColor; ///< The color of the band
    int mBandWidth; ///< The width of the band in cm

public:
    /// Default constructor (disabled)
    Shooter() = delete;

    /// Copy constructor (disabled)
    Shooter(const Shooter &) = delete;

    /// Assignment operator
    void operator=(const Shooter &) = delete;

    Shooter(Level * level, std::wstring const & imageFile, std::wstring const & armImageFile);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Accept an item visitor
     *
     * @param visitor the ItemVisitor
     */
    void Accept(ItemVisitor * visitor) override { visitor->VisitShooter(this); }

    /**
     * Determine if the shooter has a sparty loaded on it
     *
     * @return true if the shooter is loaded, false otherwise
     */
    bool IsLoaded() const { return mState == State::Loaded; }

    void LoadSparty(std::shared_ptr<AngrySparty> sparty);

    /**
     * release the currently loaded sparty from the shooter
     */
    void Release()
    {
        mSparty = nullptr;
        mState = State::Reloading;
    }

    bool Shoot();

    /**
     * Get the AngrySparty currently loaded on the shooter
     *
     * @return AngrySpartyObject, nullptr if DNE
     */
    std::shared_ptr<AngrySparty> GetLoadedSparty() { return mSparty; }

    b2Vec2 GetArmMidpoint();

    /**
     * Get the maximum pull length of the shooter
     *
     * @return maximum pull length in meters
     */
    double GetMaxPull() const { return mMaxPull; }
};

#endif //PROJECT1_SHOOTER_H
