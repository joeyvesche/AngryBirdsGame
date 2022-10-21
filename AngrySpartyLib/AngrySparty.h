/**
 * @file AngrySparty.h
 * @author Will Morant
 *
 * AngrySparty Base Class
 */

#ifndef PROJECT1_ANGRYSPARTY_H
#define PROJECT1_ANGRYSPARTY_H

#include "Item.h"

/**
 * Base class that describes anb AngrySparty Object
 */
class AngrySparty: public Item {
private:

protected:
    AngrySparty(Level *level, const std::wstring &filename);

public:
    /// Default constructor (disabled)
    AngrySparty() = delete;

    /// Copy constructor (disabled)
    AngrySparty(const AngrySparty &) = delete;

    /// Assignment operator
    void operator=(const AngrySparty &) = delete;
};

#endif //PROJECT1_ANGRYSPARTY_H
