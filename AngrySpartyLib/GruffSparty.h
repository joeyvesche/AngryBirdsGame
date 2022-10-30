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
    /// The radius in meters
    const double mGruffSpartyRadius = 0.25;

    /// The velocity factor for Gruff Sparty
    const float mGruffSpartyVelocityFactor = 12.0;
public:

    /// Default constructor (disabled)
    GruffSparty() = delete;

    /// Copy constructor (disabled)
    GruffSparty(const GruffSparty &) = delete;

    /// Assignment operator
    void operator=(const GruffSparty &) = delete;

    GruffSparty(Level *level);


    std::pair<double,float> GetConstants() override;


};

#endif //PROJECT1_GRUFFSPARTY_H
