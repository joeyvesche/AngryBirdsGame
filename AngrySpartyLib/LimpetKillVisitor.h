/**
 * @file LimpetKillVisitor.h
 * @author Will
 *
 *
 */

#ifndef PROJECT1_LIMPETKILLVISITOR_H
#define PROJECT1_LIMPETKILLVISITOR_H


#include "ItemVisitor.h"

/**
 * Class that describes a visitor for the LimpetSparty's destroy block functionality.
 */
class LimpetKillVisitor : public ItemVisitor {
private:
    /// Key for VisitFoe, true if it visits a foe
    bool mKey = false;
    ///Limpet sparty gathered by visitor
    LimpetSparty *mLimpet = nullptr;

public:
    /**
     * Get the key
     * @return
     */
    bool GetKey()
    {
        return mKey;
    }
    /**
     * Returns the limpet gathered by this visitor
     * @return
     */
    LimpetSparty * GetNextLimpet() {return mLimpet;}

    void VisitFoe(Foe *foe) override;
    void VisitLimpet(LimpetSparty* mLimpet) override;
};

#endif //PROJECT1_LIMPETKILLVISITOR_H
