/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TREESLAVEITERATOR_H_
#define TREESLAVEITERATOR_H_

#include <iterator>

namespace Util {

/**
 * Iterator dla TreeSlave.
 * \ingroup Tree
 */
template <typename T, typename TreeMasterType, typename Extractor>
class TreeSlaveIterator : public std::iterator <std::forward_iterator_tag, T> {
public:

        typedef typename TreeMasterType::Iterator TreeMasterIterator;

        TreeSlaveIterator () : extractor (), body () {}
        TreeSlaveIterator (const TreeMasterIterator &b) : extractor (), body (b) {}
        TreeSlaveIterator(const TreeSlaveIterator &i) : body (i.body) {}

        T const operator* () const
        {
                return extractor (*body);
        }

        T operator* ()
        {
                return extractor (*body);
        }

        T const * operator-> () const {
                return &(operator* ());
        }

        T* operator-> () {
                return &(operator* ());
        }

        TreeSlaveIterator&
        operator++()
        {
                body++;
                return *this;
        }

        TreeSlaveIterator
        operator++(int)
        {
                TreeSlaveIterator tmp = *this;
                body++;
                return tmp;
        }

        bool operator== (const TreeSlaveIterator &i) const { return body == i.body; }
        bool operator!= (const TreeSlaveIterator &i) const { return body != i.body; }

private :

        Extractor extractor;
        TreeMasterIterator body;

};

} // namespace Util

#	endif /* TREESLAVEITERATOR_H_ */
