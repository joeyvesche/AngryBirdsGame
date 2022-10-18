/**
 * @file GruffSparty.h
 * @author Will Morant
 *
 * Gruff Sparty class
 */

#ifndef PROJECT1_GRUFFSPARTY_H
#define PROJECT1_GRUFFSPARTY_H

#include "AngrySparty.h"

class GruffSparty: public AngrySparty {
private:

public:

    /// Default constructor (disabled)
    GruffSparty() = delete;

    /// Copy constructor (disabled)
    GruffSparty(const GruffSparty &) = delete;

    /// Assignment operator
    void operator=(const GruffSparty &) = delete;

    GruffSparty(Game *game);
};

#endif //PROJECT1_GRUFFSPARTY_H
