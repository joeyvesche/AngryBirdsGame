/**
 * @file ItemTest.cpp
 * @author Josep Pauls, Will Skaggs
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <Level.h>
#include <unordered_set>
#include <algorithm>
#include <iterator>

/// Demo item filename, in this case a helmet sparty
const std::wstring HelmetSpartyImageName = L"helmet-sparty.png";

class ItemVisitor;

/** Mock class for testing the class Item */
class ItemMock : public Item {
public:
    ItemMock(Level *level, std::wstring const & filename) : Item(level, filename) {}

    void Draw(wxDC *dc) {}
    void Accept(ItemVisitor *) {}
};


// Test Item construction
TEST(ItemTest, Construct)
{
    ItemMock item(nullptr, L"helmet-sparty.png");

}

// Test our item getters and setters
TEST(ItemTest, GettersSetters){
    ItemMock item(nullptr, L"helmet-sparty.png");

    // Test initial values
    ASSERT_NEAR(0, item.GetX(), 0.0001);
    ASSERT_NEAR(0, item.GetY(), 0.0001);

    // Test SetLocation, GetX, and GetY
    item.SetLocation(10.5, 17.2);
    ASSERT_NEAR(10.5, item.GetX(), 0.0001);
    ASSERT_NEAR(17.2, item.GetY(), 0.0001);

    // Test a second with different values
    item.SetLocation(-72, -107);
    ASSERT_NEAR(-72, item.GetX(), 0.0001);
    ASSERT_NEAR(-107, item.GetY(), 0.0001);
}

TEST(ItemTest, HitTest) {
    // Create an item to test
    ItemMock item(nullptr, L"helmet-sparty.png");

    // Give it a location
    // Always make the numbers different, in case they are mixed up
    item.SetLocation(300, 300);

    // Center of the item should be a true
    ASSERT_TRUE(item.HitTest(300, 300));

    // Left of the item
    ASSERT_FALSE(item.HitTest(0, 200));

    // Right of the item
    ASSERT_FALSE(item.HitTest(600, 200));

    // Above the item
    ASSERT_FALSE(item.HitTest(100, 0));

    // Below the item
    ASSERT_FALSE(item.HitTest(100, 600));

    // On am item transparent pixel (the upperleft most, in this case)
    ASSERT_FALSE(item.HitTest(300 - 255, 300 - 255));


}

/**
 * Ensure that the images and bitmaps used for items
 * are only loaded once. If two items use the same image,
 * they should have pointers to the same image object.
 *
 * Note for slingshots/goalposts: these classes have additional
 * images for when a sparty is loaded on them. This test does not
 * account for these extra images
 */
TEST(ItemTest, ImagesLoadOnlyOnce)
{
    // Basic: two items with the same image
    ItemMock basicItem1(nullptr, HelmetSpartyImageName);
    ItemMock basicItem2(nullptr, HelmetSpartyImageName);

    ASSERT_EQ(basicItem1.GetBitmap(), basicItem2.GetBitmap());

    // Check all items of a (basic) level
    Level level0(L"levels/level0.xml");
    std::unordered_set<wxBitmap *> uniqueBitmaps;
    std::transform(level0.begin(), level0.end(), std::inserter(uniqueBitmaps, uniqueBitmaps.begin()),
                   [](std::shared_ptr<Item> item) { return item->GetBitmap().get(); });

    ASSERT_EQ(uniqueBitmaps.size(), 10);

    // Check all items of a more advanced level
    Level level1(L"levels/level1.xml");
    uniqueBitmaps.clear();
    std::transform(level1.begin(), level1.end(), std::inserter(uniqueBitmaps, uniqueBitmaps.begin()),
                   [](std::shared_ptr<Item> item) { return item->GetBitmap().get(); });

    ASSERT_EQ(uniqueBitmaps.size(), 16);
}