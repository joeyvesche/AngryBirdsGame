/**
 * @file BackgroundTest.cpp
 * @author Will Morant
 *
 * tests for Background loading
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Background.h>
#include <Level.h>
#include <Item.h>

TEST(BackgroundTest, Construct)
{
    Level level1(L"levels/level1.xml");
}

