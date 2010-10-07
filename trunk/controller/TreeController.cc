/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <algorithm>
#include <cstddef>
#include <boost/functional.hpp>

#include "TreeController.h"

namespace Controller {
using namespace View;
using namespace Model;

void TreeController::setModel (Ptr <IModel> m)
{
        model = m;

        if (!model->getOwner () || (!model->getOwner ()->ownsChildren () && ownsChildren ())) {
                model->setOwner (this);
        }

//        if (!model->getOwnerForParent () /*|| (!model->getOwnerForParent ()->getParentMAW () && getParentMAW ())*/) {
                model->setOwnerForParent (this);
//        }
}

/****************************************************************************/

ControllerConstIter TreeController::begin () const
{
        return children.begin ();
}

/****************************************************************************/

ControllerIter TreeController::begin ()
{
        return children.begin ();
}

/****************************************************************************/

ControllerConstIter TreeController::end () const
{
        return children.end ();
}

/****************************************************************************/

ControllerIter TreeController::end ()
{
        return children.end ();
}

/****************************************************************************/

ModelConstIter TreeController::beginForModel () const
{
        return ModelConstIter (children.begin ());
}

/****************************************************************************/

ModelIter TreeController::beginForModel ()
{
        return ModelIter (children.begin ());
}

/****************************************************************************/

ModelConstIter TreeController::endForModel () const
{
        return ModelConstIter (children.end ());
}

/****************************************************************************/

ModelIter TreeController::endForModel ()
{
        return ModelIter (children.end ());
}

/****************************************************************************/

WidgetConstIter TreeController::beginForWidget () const
{
        return WidgetConstIter (children.begin ());
}

/****************************************************************************/

WidgetIter TreeController::beginForWidget ()
{
        return WidgetIter (children.begin ());
}

/****************************************************************************/

WidgetConstIter TreeController::endForWidget () const
{
        return WidgetConstIter (children.end ());
}

/****************************************************************************/

WidgetIter TreeController::endForWidget ()
{
        return WidgetIter (children.end ());
}

/****************************************************************************/

void TreeController::removeChild (ControllerChildType e)
{
        ControllerCollection::iterator i = std::find (children.begin (), children.end (), e);

        if (i != children.end ()) {
                e->setParent (NULL);
                children.erase (i);
        }
}

/****************************************************************************/

void TreeController::clearChildren ()
{
        std::for_each (children.begin (),
                       children.end (),
                       ConvertPtr <ControllerChildType> (boost::bind2nd (boost::mem_fun (&ControllerChildBaseType::setParent), NULL)));

        children.clear ();
}

/****************************************************************************/

void TreeController::setChildren (ControllerCollection *col)
{
        clearChildren ();
        addChildren (col);
}

/****************************************************************************/

void TreeController::addChildren (ControllerCollection *col)
{
        for (ControllerCollection::iterator i = col->begin (); i != col->end (); ++i) {
                addChild (*i);
        }
}

} // namespace
