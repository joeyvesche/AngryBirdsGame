/**
 * @file Foe.h
 * @author Will Morant
 *
 * Foe class
 */

#ifndef PROJECT1_FOE_H
#define PROJECT1_FOE_H

#include "Item.h"
#include <string>
/**
 * Class that describes a foe object
 */
class Foe : public Item {
private:

    ///File Name. Set when loading in the foe from an XML file
    std::wstring mFoeFileName;
protected:
    Foe(Level *level, const std::wstring &filename);

public:
    /// Default constructor (disabled)
    Foe() = delete;

    /// Copy constructor (disabled)
    Foe(const Foe &) = delete;

    /// Assignment operator
    void operator=(const Foe &) = delete;
};

#endif //PROJECT1_FOE_H
