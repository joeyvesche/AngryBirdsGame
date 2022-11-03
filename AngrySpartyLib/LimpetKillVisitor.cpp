/**
 * @file LimpetKillVisitor.cpp
 * @author Will Morant
 */

#include "pch.h"
#include "LimpetKillVisitor.h"


/**
* Sets true if visitor finds a foe
*/

void LimpetKillVisitor::VisitFoe(Foe* foe)
{
    mKey = true;
}