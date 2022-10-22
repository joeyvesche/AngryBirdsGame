/**
 * @file SlingShot.h
 * @authors joeyv, Joseph Pauls
 *
 *
 */

#ifndef PROJECT1_SLINGSHOT_H
#define PROJECT1_SLINGSHOT_H

#include "Item.h"
#include <string>

class SlingShot : public Item{
private:

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
