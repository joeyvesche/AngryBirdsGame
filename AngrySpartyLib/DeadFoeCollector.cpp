/**
 * @file DeadFoeCollector.cpp
 * @author Yuqi Pan
 */
#include "pch.h"
#include "DeadFoeCollector.h"
#include "Foe.h"
void DeadFoeCollector::VisitFoe(Foe* foe)
{
    if(foe->IsDead())
    {
        mDeath.push_back(foe);
    }
}
