/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "model/IModel.h"
#include "model/IGroup.h"
#include "AbstractEventDispatcher.h"
#include "EventIdex.h"
#include "PointerInsideIndex.h"
#include "types/IEvent.h"
#include "types/MotionEvent.h"
#include "Platform.h"
#include "types/MotionMoveEvent.h"

namespace Event {
namespace M = Model;
namespace V = View;
namespace C = Controller;
namespace G = Geometry;

bool AbstractEventDispatcher::dispatch (Model::IModel *m, Event::EventIndex const &modeliIndex, Event::PointerInsideIndex *pointerInsideIndex, Event::IEvent *e)
{
        bool eventHandled = false;

        if (!e) {
                return eventHandled;
        }

        Event::Type type = e->getType();

        if (type & MOUSE_EVENTS) {
                MotionEvent *mev = dynamic_cast <MotionEvent *> (e);
                Event::Handling h = Event::IGNORE;

                // Obsługa motionOver and Out.
                if (type & Event::MOTION_MOVE_EVENT && mev->getSource () == MOUSE) {
                        MotionMoveEvent *mmev = static_cast <MotionMoveEvent *> (e);

                        /*
                         * Sprawdzamy czy onMotionOut. Uwaga! pointerInside jest unordered (hash), czyli
                         * onMotionOut odpali się w losowej kolejności. Zastanowić się, czy to bardzo źle.
                         */
                        typedef Event::PointerInsideIndex::Iterator Iterator;
                        for (Iterator i = pointerInsideIndex->begin (); i != pointerInsideIndex->end ();) {
                                M::IModel *parent;
                                G::Point copy = mev->getPointer (0).position;

                                if ((parent = (*i)->getParent ())) {
                                        dynamic_cast <M::IGroup *> (parent)->groupToScreen (&copy);
                                }

                                if (!(*i)->contains (copy)) {
                                        Iterator j = i;
                                        ++j;

                                        // Zawsze będzie kontroler (bo to on dodaje model do kolekcji pointerInside), ale i tak sprawdzamy.
                                        C::IController *ctr;
                                        if ((ctr = (*i)->getController ())) {
                                                h = ctr->onMotionOut (mmev, *i, (*i)->getView ());
                                        }

                                        pointerInsideIndex->remove (*i);
                                        i = j;

                                        if (h != Event::IGNORE) {
                                                eventHandled = true;
                                        }

                                        if (h == Event::BREAK) {
                                                break;
                                        }
                                }
                                else {
                                        ++i;
                                }
                        }
                }

                if (h != Event::BREAK) {
                        for (int i = 0; i < mev->getPointerCount (); ++i) {
                                M::IModel *model = m->findContains (mev->getPointer (i).position);

                                if (model) {
#if 0
                                        printlog ("m=%p, model=%p", m, model);
#endif
                                        eventHandled |= dispatchEventBackwards (model, mev, pointerInsideIndex);
                                }
                        }
                }
        }
        else {
                typedef Event::EventIndex::Iterator Iterator;
                typedef Event::EventIndex::Pair Pair;

                Pair pair = modeliIndex.getModels (type);
                bool breakChain = false;

                for (Iterator i = pair.first; i != pair.second; ++i) {
                        eventHandled |= dispatchEventBackwards (i->second, e, pointerInsideIndex, &breakChain);

                        if (breakChain) {
                                break;
                        }
                }
        }

        return eventHandled;
}

/****************************************************************************/

bool AbstractEventDispatcher::dispatchEventBackwards (Model::IModel *m, IEvent *e, Event::PointerInsideIndex *pointerInsideIndex, bool *breakChain)
{
        C::IController *controller = m->getController ();
        Handling h = IGNORE;

        if (controller && controller->getEventMask () & e->getType ()) {
                h = e->runCallback (m, m->getView (), controller, pointerInsideIndex);
        }

        if (h == BREAK) {
                return true;
        }

#if 0
        std::cerr << typeid (*m).name() << ", parent=" << bool (m->getParent ()) << std::endl;
#endif

        if ((m = m->getParent ())) {
                return dispatchEventBackwards (m, e, pointerInsideIndex);
        }

        return h != IGNORE;
}

} /* namespace Event */
