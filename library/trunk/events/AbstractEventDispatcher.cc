/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 18, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AbstractEventDispatcher.h"
#include "Common.h"
#include "PointerInsideIndex.h"
#include "EventIdex.h"

namespace Event {
namespace M = Model;
namespace V = View;
namespace C = Controller;
namespace G = Geometry;

/****************************************************************************/

bool AbstractEventDispatcher::dispatch (Model::IModel *m, Event::EventIndex const &modeliIndex, Event::PointerInsideIndex *pointerInsideIndex, void *platformDependentData)
{
        Event::IEvent *e = translate (platformDependentData);

        if (!e) {
                return false;
        }

        Event::Type type = e->getType();

        if (type & MOUSE_EVENTS) {
                MouseEvent *mev = static_cast <MouseEvent *> (e);
                G::Point const &p = mev->getPosition ();

/**
 * Smartfony nie generują czegoś takiego jak event on mouseOver i on mouseOut.
 */
#ifndef USE_TOUCH_SCREEN
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
                                                ctr->onMouseOut (mmev, *i, (*i)->getView ());
                                        }

                                        pointerInsideIndex->remove (*i);
                                        i = j;
                                }
                                else {
                                        ++i;
                                }
                        }
                }

                if (app->getDropIteration ()) {
                        return;
                }
#endif

                M::IModel *model = m->findContains (p);

                if (model) {
                        dispatchEventBackwards (model, mev, pointerInsideIndex);
                }
        }
        else {
                typedef Event::EventIndex::Iterator Iterator;
                typedef Event::EventIndex::Pair Pair;

                Pair pair = modeliIndex.getModels (type);

                for (Iterator i = pair.first; i != pair.second; ++i) {
                        dispatchEventBackwards (i->second, e, pointerInsideIndex);

                        if (app->getDropIteration ()) {
                                break;
                        }
                }
        }
}

/****************************************************************************/

void AbstractEventDispatcher::dispatchEventBackwards (Model::IModel *m, IEvent *e, Event::PointerInsideIndex *pointerInsideIndex)
{
        C::IController *controller = m->getController ();

        if (controller && controller->getEventMask () & e->getType ()) {
                e->runCallback (m, m->getView (), controller, pointerInsideIndex);

                if (app->getDropIteration ()) {
                        return;
                }
        }

        if ((m = m->getParent ())) {
                dispatchEventBackwards (m, e, pointerInsideIndex);
        }
}

} // nam
