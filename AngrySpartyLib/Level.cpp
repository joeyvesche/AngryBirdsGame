/**
 * @file level.cpp
 * @author Will Skaggs
*/

#include "pch.h"
#include "Level.h"

/**
 * Parse the xml node that contains all items
 * contained in this level and store the items
 *
 * @param items pointer to the items xml node
 */
void Level::LoadItemsXml(wxXmlNode * items)
{
    for (auto child = items->GetChildren(); child != nullptr; child = child->GetNext())
    {
        std::wstring name = child->GetName().ToStdWstring();

        if (name == L"background")
        {

        } else if (name == L"block")
        {

        } else if (name == L"poly")
        {

        } else if (name == L"foe")
        {

        } else if (name == L"slingshot")
        {

        } else if (name == L"goalposts")
        {

        }
    }
}

/**
 * Process the xml node that contains all angry spartys
 * contained in this level and store them.
 *
 * @param angry pointer to the angry xml node
 */
void Level::LoadSpartysXml(wxXmlNode * angry)
{
    // grab the specified location and spacing for the angry spartys
    double x, y, spacing;

    angry->GetAttribute("x").ToDouble(&x);
    angry->GetAttribute("y").ToDouble(&y);
    angry->GetAttribute("spacing").ToDouble(&spacing);

    // parse and store angry spartys
    for (auto child = angry->GetChildren(); child != nullptr; child = child->GetNext())
    {
        std::wstring name = child->GetName().ToStdWstring();

        if (name == L"gruff-sparty")
        {

        } else if (name == L"helmet-sparty")
        {

        }
    }
}

/**
 * Construct a new level object
 *
 * Load and store data from and XML file located
 * at the given filepath
 *
 * @param filepath the path to the level XML file
 */
Level::Level(std::wstring const & filepath)
{
    wxXmlDocument doc;

    // exit if loading the xml file was unsuccessful
    if (!doc.Load(filepath)) return;

    // Process all items in the xml file
    auto root = doc.GetRoot();

    for (auto child = root->GetChildren(); child != nullptr; child = child->GetNext())
    {
        if (child->GetName() == L"items")
        {
            LoadItemsXml(child);
        } else if (child->GetName() == L"angry")
        {
            LoadSpartysXml(child);
        }
    }
}