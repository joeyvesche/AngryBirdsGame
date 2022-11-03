/**
 * @file ShooterVisitor.h
 * @author Will Skaggs
 *
 * Slingshot shooter Visitor
 */

#ifndef PROJECT1_SHOOTERVISITOR_H
#define PROJECT1_SHOOTERVISITOR_H

#include "ItemVisitor.h"

class Shooter;

/**
 * This visitor searches for the shooter objects of a level.
 * If there are multiple shooters in a level, this object will
 * remember the last in the sequence.
 * If there are not any shooter in a level, this object will
 * default to nullptr
 */
class ShooterVisitor : public ItemVisitor {
private:
    Shooter * mShooter = nullptr;

public:
    /**
     * Visit a Shooter object and store its location
     *
     * @param shooter pointer to a Shooter object
     */
    void VisitShooter(Shooter * shooter) override { mShooter = shooter; }

    /**
     * Get the Shooter object
     *
     * @return pointer to a Shooter object, nullptr if DNE
     */
    Shooter * Get() { return mShooter; }

};

#endif //PROJECT1_SHOOTERVISITOR_H
