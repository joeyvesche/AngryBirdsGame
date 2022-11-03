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
#include "Shooter.h"

class SlingShot : public Shooter {
private:

public:
    /// Default constructor (disabled)
    SlingShot() = delete;

    /// Copy constructor (disabled)
    SlingShot(const SlingShot &) = delete;

    SlingShot(Level* level);

};

#endif //PROJECT1_SLINGSHOT_H
