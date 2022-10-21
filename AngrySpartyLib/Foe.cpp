/**
 * @file Foe.cpp
 * @author Will Morant
 */

#include "pch.h"
#include "Foe.h"
#include "Game.h"
#include "Item.h"

Foe::Foe(Level *level, const std::wstring &filename) : Item(level, mFoeFileName)
{

}
