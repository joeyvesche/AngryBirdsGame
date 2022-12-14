/**
 * @file LimpetSparty.h
 * @author Will Morant
 *
 * Class that Initializes the Limpet Sparty
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
    const float mLimpetSpartyVelocityFactor = 10.0;

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

    std::pair<double,float> GetConstants();

    bool Obliterate(b2Body *body);
    void Accept(ItemVisitor *visitor) override;
};

#endif //PROJECT1_LIMPETSPARTY_H
