/**
 * @file AngrySparty.h
 * @author Will Morant
 *
 * AngrySparty Base Class
 */

#ifndef PROJECT1_ANGRYSPARTY_H
#define PROJECT1_ANGRYSPARTY_H

#include "Item.h"
#include "Level.h"
#include "ItemBody.h"


/**
 * Base class that describes any AngrySparty Object
 */
class AngrySparty: public Item {
private:
        ///Body of the AngrySparty object
        b2Body* mBody;


public:

    AngrySparty(Level *level, const std::wstring &filename);

    /// Default constructor (disabled)
    AngrySparty() = delete;

    /// Copy constructor (disabled)
    AngrySparty(const AngrySparty &) = delete;

    /// Assignment operator
    void operator=(const AngrySparty &) = delete;

    /**
     * Draw this item
     * @param dc Device context to draw on
     */
     void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
     void SetBody(Level *level);
};

#endif //PROJECT1_ANGRYSPARTY_H
