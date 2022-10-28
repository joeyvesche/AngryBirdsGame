/**
 * @file SlingShot.h
 * @authors joeyv, Joseph Pauls
 *
 *
 */

#ifndef PROJECT1_SLINGSHOT_H
#define PROJECT1_SLINGSHOT_H

#include "Item.h"
#include "AngrySparty.h"
#include <string>
#include <memory>

class SlingShot : public Item{
private:
    std::shared_ptr<wxImage> mArmImage; ///< Image of the slingshot arm
    std::shared_ptr<wxBitmap> mArmBitmap; ///< Bitmap of the slingshot arm
    std::shared_ptr<AngrySparty> mSparty; ///< A pointer to the sparty currently in the slingshot

public:
    /// Default constructor (disabled)
    SlingShot() = delete;

    /// Copy constructor (disabled)
    SlingShot(const SlingShot &) = delete;

    SlingShot(Level* level);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void Accept(ItemVisitor * visitor) override {}
};

#endif //PROJECT1_SLINGSHOT_H
