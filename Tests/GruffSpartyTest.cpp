/**
 * @file GruffSpartyTest.cpp
 * @author Will Morant
 */

#include <pch.h>
#include <GruffSparty.h>
#include <Game.h>
#include "gtest/gtest.h"



TEST(GruffSpartyTest, Construct)
{
    Game game;
    GruffSparty gruff(&game);
}