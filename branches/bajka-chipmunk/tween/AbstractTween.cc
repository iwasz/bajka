/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AbstractTween.h"
#include "Manager.h"

namespace Tween {

void AbstractTween::start (Manager *m)
{
        if (m) {
                m->setTween (this);
        }
        else {
                Manager::getMain ()->setTween (this);
        }
}

/****************************************************************************/

} /* namespace Tween */
