/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef POINTERINSIDEINDEX_H_
#define POINTERINSIDEINDEX_H_

#include <boost/unordered_set.hpp>

namespace Model {
class IModel;
}

namespace Event {

/**
 * Index zawierający modele, które w danym momencie mają nad sobą kursor myszy.
 * Indeks ten pozwala zaobserwować moment, kiedy ten kursor wyjedzie poza obszar
 * obiektu i dzięki temu pozwala wygenerowac event onMotionOut. Wskaźnik do tego
 * indeksu mają app, EventDispatcher i wszystkie grupy. EventDispatcher dodaje
 * modele do indeksu, a app i grupy usuwają (kiedy wyjmiemy akiś model z grupy).
 */
class PointerInsideIndex {
public:

        typedef boost::unordered_set <Model::IModel *> Index;
        typedef Index::const_iterator Iterator;

        void add (Model::IModel *m) { index.insert (m); }
        void remove (Model::IModel *m);
        void clear () { index.clear (); }

        Iterator begin () const { return index.begin (); }
        Iterator end () const { return index.end (); }

        bool isPointerInside (Model::IModel *m) const { return index.find (m) != index.end (); }

private:

        Index index;

};

} /* namespace Event */
#endif /* POINTERINSIDEINDEX_H_ */
