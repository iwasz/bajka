/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AbstractModel.h"

namespace Model {

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

        std::for_each (begin (), end (), boost::mem_fn (&IModel::update));

        if (controller) {
                controller->postUpdate (this, view);
        }

        if (view) {
                view->postUpdate (this);
        }
}

} /* namespace Model1 */
