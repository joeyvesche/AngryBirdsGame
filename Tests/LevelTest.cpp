/**
 * @file LevelTest.cpp
 * @author Will Skaggs
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Level.h>
#include <string>
#include <utility>
#include <algorithm>
#include <vector>

std::wstring const testFile = L"test/test.xml";

TEST(LevelTest, LoadFromFile)
{
    // load the test file from disk
    Level testLevel(testFile);

    // Make sure we can access the root tag and its attributes
    ASSERT_EQ(testLevel.GetSize(), std::make_pair(12.0, 8.0));

    // Make sure both the items and angry tags are loaded
    auto view = testLevel.Contents();

    auto items = view.begin();
    auto angry = ++view.begin();

    ASSERT_EQ(items->GetName(), L"items");
    ASSERT_EQ(angry->GetName(), L"angry");

    // Make sure all elements are showing up inside items
    std::vector<std::wstring> expectedItems = {
            L"block", L"block", L"block", L"block", L"block"
    };
    std::vector<std::wstring> foundItems;

    for (auto item : XmlView(*items))
    {
        foundItems.push_back(item.GetName().ToStdWstring());
    }

    ASSERT_EQ(foundItems, expectedItems);

    // Make sure all elements are showing up inside angry
    std::vector<std::wstring> expectedSparty = {
            L"gruff-sparty", L"helmet-sparty", L"gruff-sparty"
    };
    std::vector<std::wstring> foundSparty;

    for (auto sparty : XmlView(*angry))
    {
        foundSparty.push_back(sparty.GetName().ToStdWstring());
    }

    ASSERT_EQ(foundSparty, expectedSparty);

}