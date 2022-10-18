/**
 * @file XmlView.h
 * @author Will Skaggs
 *
 * This class allows easier parsing of an
 * XML node's children
 */

#ifndef PROJECT1_XMLVIEW_H
#define PROJECT1_XMLVIEW_H

/**
 * This class will view the children of an XML node
 * and allow for easier parsing of data
 */
class XmlView {
private:
    wxXmlNode const * mParent = nullptr; ///< the parent node we are viewing

public:
    /**
     * Construct a new XmlView object
     *
     * @param parent pointer to the XML node we are viewing
     */
    XmlView(wxXmlNode const * parent) : mParent{parent} {}

    /**
     * Construct a new XmlView object
     *
     * @param parent the XML node we are viewing
     */
    XmlView(wxXmlNode const & parent) : mParent{&parent} {}

    /** Iterator for the children of an XmlNode **/
    class XmlIterator {
    private:
        wxXmlNode const * mNode = nullptr; ///< The XML node we are currently on

    public:
        /**
         * Construct a new XML iterator
         *
         * @param node starting node of iteration
         */
        XmlIterator(wxXmlNode const * node) : mNode{node} {}


        /**
         * Check if two XmlIterators are equivalent
         *
         * @param other the other XmlIterator to compare to
         *
         * @return true if XmlIterators are equivalent, false otherwise
         */
        bool operator==(XmlIterator const & other) const { return mNode == other.mNode; }

        /**
         * Check if two XmlIterators are not equivalent
         *
         * @param other the other XmlIterator to compare to
         *
         * @return true if XmlIterators are not equivalent, false otherwise
         */
        bool operator!=(XmlIterator const & other) const { return mNode != other.mNode; }

        /**
         * Dereference an XmlIterator and get the underlying Node
         *
         * @return the XML node at the current point of iteration
         */
        wxXmlNode const & operator*() { return *mNode; }

        /**
         * Allow accessing the underlying node with the arrow operator
         *
         * @return pointer to an XML node
         */
        wxXmlNode const * operator->() { return mNode; }

        /**
         * Increment an XmlIterator to the next position
         *
         * If the XmlIterator is past the end, the behavior is undefined
         */
        XmlIterator & operator++()
        {
            mNode = mNode->GetNext();
            return *this;
        }
    };

    /**
     * Get an iterator to the beginning of the children nodes
     *
     * @return an XmlIterator to the beginning
     */
    XmlIterator begin()
    {
        return XmlIterator(mParent == nullptr ? nullptr : mParent->GetChildren());
    }

    /**
     * Get an iterator past the end of the children nodes
     *
     * @return a past-the-end XmlIterator
     */
    XmlIterator end() { return XmlIterator(nullptr); }
};


#endif //PROJECT1_XMLVIEW_H
