/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "EventIdex.h"
#include "../model/IGroup.h"

namespace Event {

unsigned int EventIndex::add (unsigned int eventMask, Model::IModel *m)
{
        /*
         * Wszystkie eventy na które reagują moje dzieci - ja już nie muszę na nie reagować,
         * bo eventy idą od dziecka do rodzica i wówczas jest jeszcze jedno sprawdzenie
         */
        unsigned int childMask = 0x0;

        if (m->isGroup ()) {
                Model::IGroup *g = dynamic_cast <Model::IGroup *> (m);

                for (Model::ModelVector::const_iterator i = g->getChildren ().begin ();
                         i != g->getChildren ().end ();
                         ++i) {

                                childMask |= add (eventMask, *i);
                }
        }

        unsigned int eventsToRun = 0x0;

        if (m->getController ()) {
                eventsToRun = m->getController ()->getEventMask ();

                if (!eventsToRun) {
                        return 0;
                }

                eventsToRun &= ~(eventsToRun & childMask);
                childMask = eventsToRun; // Zmienna uzyta ponownie, ale w innym celu.

                for (unsigned int i = 1; i != Event::EVENT_TERMINATOR; i <<= 1) {

                        if (m->getController ()->getEventMask () & i) {
                                index.insert (std::make_pair ((Event::Type)i, m));
                                childMask &= ~i;
                        }
                }

                return childMask;
        }

        return eventsToRun;

}

/****************************************************************************/

void EventIndex::remove (Model::IModel *m)
{
        if (m->isGroup ()) {
                Model::IGroup *g = dynamic_cast <Model::IGroup *> (m);

                for (Model::ModelVector::const_iterator i = g->getChildren ().begin ();
                         i != g->getChildren ().end ();
                         ++i) {

                                remove (*i);
                }
        }

        index.get <1> ().erase (m);
}

} /* namespace Model */
