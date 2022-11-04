/**
 * @file Poly.h
 * @author joeyv
 *
 * Initialing for the Poly Object
 */
#include "Item.h"
#include <string>

#ifndef PROJECT1_POLY_H
#define PROJECT1_POLY_H

/**
 * Class that describes a polygon object
 */
class Poly : public Item {
private:
    ///File Name. Set when loading in the foe from an XML file
    std::wstring mPolyFileName;

    /// Vertices
    std::vector<b2Vec2> mVertices;

    /// Each set of vertices
    b2Vec2 mVertex;

    /// the body of the poly in the physics engine
    b2Body * mBody;

public:
    /// Default constructor (disabled)
    Poly() = delete;

    /// Copy constructor (disabled)
    Poly(const Poly &) = delete;

    Poly(Level *level, const std::wstring &filename);

    void Accept(ItemVisitor * visitor) override;

    void XmlLoad(wxXmlNode *node);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
};

#endif //PROJECT1_POLY_H
