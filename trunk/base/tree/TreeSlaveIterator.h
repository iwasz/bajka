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
#include "Pointer.h"

namespace Base {

/**
 * Podwójny iterator. Jest to szablon iteratorów które są zwracane z modeli i widgetów. 
 * Wewnętrznie zawiera dwa iteratory STL i dwa extraktory + do tego znacznik, czy używać
 * iteratora A, czy B. Wyłuskując z iteratora, albo uzywając operatora -> używane są 
 * ekstraktory. 
 * 
 * Jeśli obydwa iteratory nie są ustawione, to operacje zwiększenia i wyłuskania i -> powodują
 * niezdefiniowane zachowanie.
 *
 * \inplace Util
 */
template <typename Element, typename IterA, typename ExtractorA, typename IterB, typename ExtractorB>
class TreeIter : public std::iterator <std::forward_iterator_tag, Element> {
public:

        TreeIter () : iterA (), iterB () {}
        TreeIter (IterA const &i) : isIterA (true), iterA (i), iterB () {}
        TreeIter (IterB const &i) : isIterA (false), iterA (), iterB (i) {}
        TreeIter (TreeIter const &i) : isIterA (i.isIterA), iterA (i.iterA), iterB (i.iterB) {}

        Element const operator* () const { return (isIterA) ? (extractorA (iterA.operator* ())) : (extractorB (iterB.operator* ())); }
        Element operator* () { return (isIterA) ? (extractorA (iterA.operator* ())) : (extractorB (iterB.operator* ())); }

        Element const *operator-> () const { return (isIterA) ? (&extractorA (iterA.operator* ())) : (&extractorB (iterB.operator* ())); }

        /*
         * Nie ma operatora nie-const, ponieważ nie ma metod zwracających nie-stałą
         * referencję do wskaźnika.
         */
        // Element* operator-> () { return base->operator-> (); }

        TreeIter& operator++ () { (isIterA) ? ((void)iterA.operator++ ()) : ((void)iterB.operator++ ()); return *this; }
        TreeIter operator++ (int) { TreeIter tmp (*this); operator++ (); return tmp; }

        TreeIter &operator= (TreeIter const &i) { isIterA = i.isIterA; iterA = i.iterA; iterB = i.iterB; return *this; }

        bool operator== (const TreeIter &i) const { return (isIterA) ? (iterA.operator== (i.iterA)) : (iterB.operator== (i.iterB)); }
        bool operator!= (const TreeIter &i) const { return (isIterA) ? (iterA.operator!= (i.iterA)) : (iterB.operator!= (i.iterB)); }

private:

        bool isIterA;
        IterA iterA;
        IterB iterB;
        ExtractorA extractorA;
        ExtractorB extractorB;
};


} // namespace

#	endif /* TREESLAVEITERATOR_H_ */
