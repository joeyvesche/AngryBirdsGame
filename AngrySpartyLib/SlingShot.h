/**
 * @file SlingShot.h
 * @author joeyv
 *
 *
 */

#ifndef PROJECT1_SLINGSHOT_H
#define PROJECT1_SLINGSHOT_H

#include "Item.h"
#include <string>

class SlingShot : public Item{
private:
    std::unique_ptr<wxBitmap> mSlingshot;

public:
    /// Default constructor (disabled)
    SlingShot() = delete;

    /// Copy constructor (disabled)
    SlingShot(const SlingShot &) = delete;

    SlingShot(Level* level, const std::wstring& filename);

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

};

#endif //PROJECT1_SLINGSHOT_H
