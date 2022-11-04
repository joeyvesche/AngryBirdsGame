/**
 * @file LevelFinishChecker.h
 * @author Yuqi Pan
 *
 * Checks if the level is Finished
 */

#ifndef PROJECT1_LEVELFINISHCHECKER_H
#define PROJECT1_LEVELFINISHCHECKER_H

#include "ItemVisitor.h"

/**
 * A class that describes a visitor that checks if a level is finished
 */
class LevelFinishChecker : public ItemVisitor {
private:
    /// Remaining sparty count
    int mSpartyCount = 0;
    ///Remaining foe count
    int mFoeCount = 0;

public:
    /**
     * The three states of a level finish
     */
    enum class Stat{
        GoOn,
        ReTry,
        NextLevel
    };

    /**
     * Visits Foe Object
     * @param foe Foe Object
     */
    void VisitFoe(Foe* foe) override{ mFoeCount++; }

    /**
     * Visits Sparty Object
     * @param sparty Sparty Object
     */
    void VisitSparty(AngrySparty* sparty) override{ mSpartyCount++; }

    /**
     * Sets the Level Status
     * @return Level Status
     */
    Stat LevelStat(){
        if(mSpartyCount > 0 && mFoeCount >0)
            return Stat::GoOn;

        else if(mFoeCount == 0)
            return Stat::NextLevel;

        else
            return Stat::ReTry;
    }
};

#endif //PROJECT1_LEVELFINISHCHECKER_H
