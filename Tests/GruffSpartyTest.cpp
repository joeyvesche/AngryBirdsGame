/**
 * @file GruffSpartyTest.cpp
 * @author Will Morant
 */

#include <pch.h>
#include <GruffSparty.h>
#include <Level.h>
#include "gtest/gtest.h"



TEST(GruffSpartyTest, Construct)
{
    Level level;
    GruffSparty gruff(&level);
}