/**
 * @file ItemTest.cpp
 * @author Josep Pauls
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <Level.h>

/// Demo item filename, in this case a helmet sparty
const std::wstring HelmetSpartyImageName = L"helmet-sparty.png";
class ItemVisitor;
/** Mock class for testing the class Item */
class ItemMock : public Item {
public:
    ItemMock(Level *level) : Item(level, HelmetSpartyImageName) {}

    void Draw(wxDC *dc) {}
    void Accept(ItemVisitor *) {}
};


// Test Item construction
TEST(ItemTest, Construct)
{
    Level level;
    ItemMock item(&level);

}

// Test our item getters and setters
TEST(ItemTest, GettersSetters){
    Level level;
    ItemMock item(&level);

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
    Level level;
    ItemMock item(&level);

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