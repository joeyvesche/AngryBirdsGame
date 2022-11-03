/**
 * @file LimpetKillVisitor.h
 * @author Will
 *
 *
 */

#ifndef PROJECT1_LIMPETKILLVISITOR_H
#define PROJECT1_LIMPETKILLVISITOR_H


#include "ItemVisitor.h"


class LimpetKillVisitor : public ItemVisitor {
private:
    bool mKey = false;

public:
    bool GetKey()
    {
        return mKey;
    }

    void VisitFoe(Foe *foe);
};

#endif //PROJECT1_LIMPETKILLVISITOR_H
