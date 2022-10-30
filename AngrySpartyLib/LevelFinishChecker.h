/**
 * @file LevelFinishChecker.h
 * @author Yuqi Pan
 *
 *
 */

#ifndef PROJECT1_LEVELFINISHCHECKER_H
#define PROJECT1_LEVELFINISHCHECKER_H
#include "ItemVisitor.h"


class LevelFinishChecker : public ItemVisitor {
private:
    int mSpartyCount = 0;
    int mFoeCount = 0;
public:
    enum class Stat{
        GoOn,
        ReTry,
        NextLevel
    };
    void VisitFoe(Foe* foe) override{ mFoeCount++; }
    void VisitSparty(AngrySparty* sparty) override{ mSpartyCount++; }
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
