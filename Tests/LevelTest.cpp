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
    ASSERT_EQ(std::distance(level.begin(), level.end()), 11) << "Check all objects loaded from xml";

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

    ///ASSERT_EQ(xyPairs, expected) << "Test all items are positioned correctly";

    for(int i = 0; i < expected.size(); i++)
    {
        ASSERT_NEAR(xyPairs[i].first, expected[i].first, 0.000001);
        ASSERT_NEAR(xyPairs[i].second, expected[i].second, 0.000001);
    }
}

TEST(LevelTest, Load2)
{
    Level level(L"levels/TestLevels/test.xml");

    // Check width and height are correctly loaded from root
    ASSERT_EQ(level.GetWidth(), 12);
    ASSERT_EQ(level.GetHeight(), 8);

    // make sure the correct number of items were loaded
    ASSERT_EQ(std::distance(level.begin(), level.end()), 8);

    // Check all values were loaded correctly
    std::vector<std::pair<double, double>> items;

    std::transform(level.begin(), level.end(), std::back_inserter(items),
                   [](auto item) { return std::make_pair(item->GetX(), item->GetY()); });

    std::vector<std::pair<double, double>> expected =
            {
                    {100, 100},
                    {200, 200},
                    {300, 300},
                    {400, 400},
                    {700, 700},
                    {-6.5, 0.3},
                    {-5.9, 0.3},
                    {-5.3, 0.3}
            };

    // This one seems to have some rounding errors (need to assert for each double)
    ASSERT_EQ(items.size(), expected.size());

    for (int i = 0; i < static_cast<int>(items.size()); ++i) {
        ASSERT_DOUBLE_EQ(items[i].first, expected[i].first);
        ASSERT_DOUBLE_EQ(items[i].second, expected[i].second);
    }
}

TEST(LevelTest, ResetLevels)
{
    Level level1Original(L"levels/level1.xml");
    Level level1Modified(L"levels/level1.xml");

    std::shared_ptr<Item> original = *level1Original.begin();
    std::shared_ptr<Item> modified = *level1Modified.begin();

    int modifiedX = original->GetX() + 5;
    int modifiedY = original->GetY() + 2;

    // apply changes to an item and make sure the changes are applied
    modified->SetLocation(modifiedX, modifiedY);
    ASSERT_EQ(modified->GetX(), modifiedX);
    ASSERT_EQ(modified->GetY(), modifiedY);

    // reset the level and see if the changes are reverted
    level1Modified.Reset();

    ASSERT_EQ(std::distance(level1Original.begin(), level1Original.end()),
              std::distance(level1Modified.begin(), level1Modified.end())) << "Contains the same number of elements";

    ASSERT_TRUE(modified != *level1Modified.begin()) << "Make sure the modified element was deleted and reconstructed";

    modified = *level1Modified.begin();
    ASSERT_EQ(modified->GetX(), original->GetX()) << "X location was restored to its original state";
    ASSERT_EQ(modified->GetY(), original->GetY()) << "Y location was restored to its original state";
}