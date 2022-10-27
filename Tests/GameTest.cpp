/**
 * @file GameTest.cpp
 * @author Joseph Pauls
 */

#include <pch.h>

#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <wx/filename.h>

#include "gtest/gtest.h"
#include <Level.h>
#include <Item.h>
#include <ItemVisitor.h>
#include <Block.h>
using namespace std;
/// Demo item filename, in this case a helmet sparty
const std::wstring HelmetSpartyImageName = L"images/helmet-sparty.png";
const std::wstring TestXml = L"test/test.xml";
class ItemMock : public Item {
public:
    ItemMock(Level *level) : Item(level, HelmetSpartyImageName) {}

    void Draw(wxDC *dc) {}

};
class CountVisitor: public ItemVisitor {
public:
    std::vector<Item*> mItems;
    void VisitBlock(Block* block) override{ mItems.push_back(block);}
};
/*
TEST(GameTest, XmlLoadTest){
    Game game;
    game.Load(TestXml);
    CountVisitor visitor;
    game.Accept(&visitor);

    ASSERT_EQ(visitor.mItems[0]->GetX(), 100);
    ASSERT_EQ(visitor.mItems[0]->GetY(), 100);
    ASSERT_EQ(visitor.mItems[0]->GetAngle(), 1);

    ASSERT_EQ(visitor.mItems[1]->GetX(), 200);
    ASSERT_EQ(visitor.mItems[1]->GetY(), 200);
    ASSERT_EQ(visitor.mItems[1]->GetAngle(), 2);

    ASSERT_EQ(visitor.mItems[2]->GetX(), 300);
    ASSERT_EQ(visitor.mItems[2]->GetY(), 300);
    ASSERT_EQ(visitor.mItems[2]->GetAngle(), 3);

    ASSERT_EQ(visitor.mItems[3]->GetX(), 400);
    ASSERT_EQ(visitor.mItems[3]->GetY(), 400);
    ASSERT_EQ(visitor.mItems[3]->GetAngle(), 4);

    ASSERT_EQ(visitor.mItems[4]->GetX(), 700);
    ASSERT_EQ(visitor.mItems[4]->GetY(), 700);
    ASSERT_EQ(visitor.mItems[4]->GetAngle(), 5);
}*/
