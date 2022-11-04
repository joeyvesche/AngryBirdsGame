/**
 * @file LimpetKillVisitor.cpp
 * @author Will Morant
 */

#include "pch.h"
#include "LimpetKillVisitor.h"
#include "LimpetSparty.h"
/**
 * Sets true if visitor finds a foe
 * @param foe Foe Object
 */
void LimpetKillVisitor::VisitFoe(Foe* foe)
{
    mKey = true;
}

/**
 * Gathers the limpet visited
 * @param limpet
 */
void LimpetKillVisitor::VisitLimpet(LimpetSparty* limpet)
{
    mLimpet = limpet;
}