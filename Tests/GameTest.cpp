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
#include <Game.h>
#include <Item.h>

using namespace std;
/// Demo item filename, in this case a helmet sparty
const std::wstring HelmetSpartyImageName = L"images/helmet-sparty.png";
const std::wstring TestXml = L"test/test.xml";
class ItemMock : public Item {
public:
    ItemMock(Game *game) : Item(game, HelmetSpartyImageName) {}

    void Draw(wxDC *dc) {}

};
TEST(GameTest, XmlLoadTest){
    Game game;
    game.Load(TestXml);


}