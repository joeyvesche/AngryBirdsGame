/**
 * @file DeadFoeCollector.h
 * @author Yuqi Pan
 *
 * Collecting the dead Foes
 */

#ifndef PROJECT1_DEADFOECOLLECTOR_H
#define PROJECT1_DEADFOECOLLECTOR_H

#include "ItemVisitor.h"

/**
 * Class that describes a visitor to count the number of dead foes.
 */
class DeadFoeCollector : public ItemVisitor {
private:
    /// list of dead foes
    std::vector<Foe*> mDeath;
public:
    /**
     * Death list of foes
     * @return List of dead foes
     */
    std::vector<Foe*>& DeathList() { return mDeath; }
    void VisitFoe(Foe* foe) override;

};

#endif //PROJECT1_DEADFOECOLLECTOR_H
