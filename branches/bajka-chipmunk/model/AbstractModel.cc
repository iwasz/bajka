/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AbstractModel.h"
#include "../view/Widget.h"
#include <algorithm>
#include <boost/bind.hpp>

namespace Model {

/****************************************************************************/

void AbstractModel::setChildren (ModelVector const &c)
{
        std::for_each (c.begin (), c.end (), boost::bind (&AbstractModel::addChild, this, _1));
}

/****************************************************************************/

void AbstractModel::addChild (IModel *m)
{
        children.push_back (m);
        m->setParent (this);
        m->parentCallback (this);
}

/****************************************************************************/

bool AbstractModel::update ()
{
        if (controller) {
                controller->preUpdate (this, view);
                controller->update (this, view);
        }

        if (view) {
                view->preUpdate (this);
                view->update (this);
        }
        else {
        	View::Widget::defaultPreUpdate (this);
        }

        std::for_each (begin (), end (), boost::mem_fn (&IModel::update));

        if (controller) {
                controller->postUpdate (this, view);
        }

        if (view) {
                view->postUpdate (this);
        }
        else {
        	View::Widget::defaultPostUpdate (this);
        }
}

} /* namespace Model1 */
