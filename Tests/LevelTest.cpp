/**
 * @file LevelTest.cpp
 * @author Will Morant
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Level.h>

TEST(LevelTest, WidthHeight)
{
    Level level1(L"levels/level0.xml");
    double width = level1.GetWidth();
    double height = level1.GetHeight();
    ASSERT_EQ(width, 14.22);
    ASSERT_EQ(height, 8);

}

