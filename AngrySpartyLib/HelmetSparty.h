/**
 * @file HelmetSparty.h
 * @author Will Morant
 *
 *
 */

#ifndef PROJECT1_HELMETSPARTY_H
#define PROJECT1_HELMETSPARTY_H

#include "AngrySparty.h"

class HelmetSparty: public AngrySparty {
private:

public:
    /// Default constructor (disabled)
    HelmetSparty() = delete;

    /// Copy constructor (disabled)
    HelmetSparty(const HelmetSparty &) = delete;

    /// Assignment operator
    void operator=(const HelmetSparty &) = delete;

    HelmetSparty(Game *game);

    void Accept(ItemVisitor * visitor) override {};

};

#endif //PROJECT1_HELMETSPARTY_H
