/**
 * @file LimpetSparty.h
 * @author Will Morant
 *
 *
 */

#ifndef PROJECT1_LIMPETSPARTY_H
#define PROJECT1_LIMPETSPARTY_H
#include "AngrySparty.h"
/**
 * Class that describes a Limpet Sparty
 */
class LimpetSparty : public AngrySparty {
private:

    /// The radius in meters
    const double mLimpetSpartyRadius = 0.25;

    /// The velocity factor for Limpet Sparty
    const float mLimpetSpartyVelocityFactor = 20.0;

    ///Number of items destroyed
    int mDestroyedItems = 0;

public:
    /// Default constructor (disabled)
    LimpetSparty() = delete;

    /// Copy constructor (disabled)
    LimpetSparty(const LimpetSparty &) = delete;

    /// Assignment operator
    void operator=(const LimpetSparty &) = delete;

    LimpetSparty(Level *level);

    std::pair<double,float> GetConstants() override;
};

#endif //PROJECT1_LIMPETSPARTY_H
