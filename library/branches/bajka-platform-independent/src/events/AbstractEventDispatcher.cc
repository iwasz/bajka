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
#include "types/MouseEvent.h"
#include "types/MouseMotionEvent.h"
#include "Platform.h"

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
                MouseEvent *mev = static_cast <MouseEvent *> (e);
                G::Point const &p = mev->getPosition ();
                Event::Handling h = Event::IGNORE;

/**
 * Smartfony nie generują czegoś takiego jak event on mouseOver i on mouseOut.
 */
//#ifndef USE_TOUCH_SCREEN
                if (type & Event::MOUSE_MOTION_EVENT) {
                        MouseMotionEvent *mmev = static_cast <MouseMotionEvent *> (e);

                        /*
                         * Sprawdzamy czy onMouseOut. Uwaga! pointerInside jest unordered (hash), czyli
                         * onMouseOut odpali się w losowej kolejności. Zastanowić się, czy to bardzo źle.
                         */
                        typedef Event::PointerInsideIndex::Iterator Iterator;
                        for (Iterator i = pointerInsideIndex->begin (); i != pointerInsideIndex->end ();) {
                                M::IModel *parent;
                                G::Point copy = p;

                                if ((parent = (*i)->getParent ())) {
                                        dynamic_cast <M::IGroup *> (parent)->groupToScreen (&copy);
                                }

                                if (!(*i)->contains (copy)) {
                                        Iterator j = i;
                                        ++j;

                                        // Zawsze będzie kontroler (bo to on dodaje model do kolekcji pointerInside), ale i tak sprawdzamy.
                                        C::IController *ctr;
                                        if ((ctr = (*i)->getController ())) {
                                                h = ctr->onMouseOut (mmev, *i, (*i)->getView ());

                                                if (h != Event::IGNORE) {
                                                        eventHandled = true;
                                                }

                                                if (h == Event::BREAK) {
                                                        break;
                                                }
                                        }

                                        pointerInsideIndex->remove (*i);
                                        i = j;
                                }
                                else {
                                        ++i;
                                }
                        }
                }

//#endif
                if (h != Event::BREAK) {
                        M::IModel *model = m->findContains (p);

                        if (model) {
                                eventHandled |= dispatchEventBackwards (model, mev, pointerInsideIndex);
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
