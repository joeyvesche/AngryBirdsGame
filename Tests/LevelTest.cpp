/**
 * @file LevelTest.cpp
 * @author Will Morant, Will Skaggs
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Level.h>
#include <algorithm>
#include <vector>
#include <iterator>

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
    Level level(L"levels/level0.xml");

    // assert the correct number of items are loaded
    ASSERT_EQ(std::distance(level.begin(), level.end()), 10) << "Check all objects loaded from xml";

    // assert all have the correct x, y coordinates
    std::vector<std::pair<double, double>> xyPairs;
    std::transform(level.begin(), level.end(), std::back_inserter(xyPairs),
                   [](auto item) { return std::make_pair(item->GetX(), item->GetY()); });


    std::vector<std::pair<double, double>> expected =
            {
                {0, 0},
                {-5.5, 0.25},
                {0, 0.125},
                {2.99512, 0.76678},
                {4.01709, 0.769644},
                {3.52113, 1.41129},
                {3.86058, 1.8335},
                {3.09669, 1.8305},
                {-6.5, 0.3},
                {-5.9, 0.3},
            };

    ASSERT_EQ(xyPairs, expected) << "Test all items are positioned correctly";
}

