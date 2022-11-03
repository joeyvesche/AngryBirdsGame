/**
 * @file Goalpost.h
 * @author Joseph Pauls
 */

#ifndef PROJECT1_GOALPOSTS_H
#define PROJECT1_GOALPOSTS_H

#include "Item.h"
#include "Consts.h"
#include "Shooter.h"

class Level;

/**
 * A class that describes a goalpost
 */
class Goalposts : public Shooter {
private:

public:
    /// Default constructor (disabled)
    Goalposts() = delete;

    /// Copy constructor (disabled)
    Goalposts(const Goalposts &) = delete;

    /// Assignment operator
    void operator=(const Goalposts &) = delete;

    Goalposts(Level * level);
};

#endif //PROJECT1_GOALPOSTS_H
