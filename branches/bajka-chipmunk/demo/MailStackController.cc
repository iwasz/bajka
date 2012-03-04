/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include "MailStackController.h"
#include "../events/types/UpdateEvent.h"
#include "../util/Math.h"

using Util::Math;

namespace Demo {

MailStackController::MailStackController () : image (NULL), offsetX (0)
{
        speed = Math::randDouble (0.01, 0.1);
}

/****************************************************************************/

void MailStackController::onUpdate (Event::UpdateEvent *e, Model::IModel *m, View::IView *v)
{
        offsetX += e->getDeltaMs () * speed;
        image->setOffsetX (offsetX);
}

} /* namespace Demo */
