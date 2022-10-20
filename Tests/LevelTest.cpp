/**
 * @file LevelTest.cpp
 * @author Will Skaggs
*/

#include <pch.h>
#include "gtest/gtest.h"
#include <string>
#include <Level.h>

std::wstring const TestLevelDirectory = L"levels/TestLevels/";

TEST(LevelTest, BasicXmlLoad)
{
    // load a level xml file into a level object
    std::wstring const filepath = TestLevelDirectory + L"basicLevel.xml";
    Level level(filepath);

    // make sure the root tag was processed correctly
    auto [width, height] = level.Size();
    ASSERT_DOUBLE_EQ(width, 14.22);
    ASSERT_DOUBLE_EQ(height, 8);

}