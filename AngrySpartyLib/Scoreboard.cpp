/**
 * @file Scoreboard.cpp
 * @author joeyv
 */

#include "pch.h"
#include "Scoreboard.h"
#include "ItemVisitor.h"
/**
* Scoreboard Constructor
 * @param game the overall structure of the game
*/

//Scoreboard::Scoreboard(Game* game) :Item(game) {}
void Scoreboard::Accept(ItemVisitor* visitor)
{
    visitor->VisitScoreboard(this);
}
