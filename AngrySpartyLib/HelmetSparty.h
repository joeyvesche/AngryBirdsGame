/**
 * @file HelmetSparty.h
 * @author Will Morant
 *
 * Base class for the Helmet Sparty
 */

#ifndef PROJECT1_HELMETSPARTY_H
#define PROJECT1_HELMETSPARTY_H

#include "AngrySparty.h"

/**
 * Class that describes a helmet sparty object
 */
class HelmetSparty: public AngrySparty {
private:

    /// The radius in meters
    const double mHelmetSpartyRadius = 0.25;

    /// The velocity factor for Helmet Sparty
    const float mHelmetSpartyVelocityFactor = 20.0;

public:
    /// Default constructor (disabled)
    HelmetSparty() = delete;

    /// Copy constructor (disabled)
    HelmetSparty(const HelmetSparty &) = delete;

    /// Assignment operator
    void operator=(const HelmetSparty &) = delete;

    HelmetSparty(Level *level);

    std::pair<double,float> GetConstants() override;
};

#endif //PROJECT1_HELMETSPARTY_H
