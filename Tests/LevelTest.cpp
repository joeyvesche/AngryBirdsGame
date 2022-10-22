/**
 * @file LevelTest.cpp
 * @author Will Morant, Will Skaggs
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Level.h>
#include <algorithm>
#include <vector>

TEST(LevelTest, WidthHeight)
{
    Level level1(L"levels/level0.xml");
    double width = level1.GetWidth();
    double height = level1.GetHeight();
    ASSERT_EQ(width, 14.22);
    ASSERT_EQ(height, 8);

}

TEST(LevelTest, Load)
{
    Level level1(L"levels/level1.xml");

    // assert the correct number of items are loaded
    ASSERT_EQ(std::distance(level1.begin(), level1.end()), 23) << "Check all objects loaded from xml";

    // assert all have the correct x, y coordinates
    std::vector<std::pair<double, double>> expected =
            {
                {}
            };



}

