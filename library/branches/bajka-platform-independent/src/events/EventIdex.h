/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_EVENTIDEX_H_
#define BAJKA_EVENTIDEX_H_

#include "events/types/IEvent.h"
#include "model/IModel.h"
#include <map>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>

namespace Event {

class EventIndex {
public:

        typedef std::pair <Event::Type, Model::IModel *> Element;

        typedef boost::multi_index::multi_index_container<
                Element,
                boost::multi_index::indexed_by<
                        boost::multi_index::ordered_non_unique<
                                boost::multi_index::member <Element, Event::Type, &Element::first>
                        >,

                        boost::multi_index::hashed_non_unique<
                                boost::multi_index::member <Element, Model::IModel *, &Element::second>
                        >
                >
        > Index;

        typedef Index::nth_index <0>::type::const_iterator Iterator;
        typedef std::pair <Iterator, Iterator> Pair;

        /**
         * Dodaje model do indeksu. Jeśli model jest typu IGroup, to do indeksu są
         * dodawane wszystkie dzieci spełniające zadane kryterium. Oczywiście maska
         * jest wyciągana z kontrolera modeli.
         */
        unsigned int add (unsigned int eventMask, Model::IModel *m);

        /**
         * Usuwa danu model z indeksu. Usuwa model i wszystkie jego dzieci. Działa
         * rekurencyjnie.
         */
        void remove (Model::IModel *m);

        /**
         * Czyści cały indeks.
         */
        void clear () { index.clear (); }

        Iterator begin () const { return index.get <0> ().begin (); }
        Iterator end () const { return index.get <0> ().end (); }

        Pair getModels (Event::Type type) const { return index.get <0> ().equal_range (type); }

private:

        Index index;

};

} /* namespace Event */

#endif /* EVENTIDEX_H_ */
