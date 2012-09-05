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

MailStackController::MailStackController () : image (NULL), offsetX (0), currentMs (0)
{
        currentSpeed = Math::randDouble (0.01, 0.1);
        nextSpeed = Math::randDouble (0.01, 0.1);
        nextChangeMs = Math::randInt (500, 2000);
}

/****************************************************************************/

void MailStackController::onUpdate (Event::UpdateEvent *e, Model::IModel *m, View::IView *v)
{
        currentMs += e->getDeltaMs ();

        // Losuj nastepną prędkość.
        if (currentMs >= nextChangeMs) {
                currentMs = 0;
                nextChangeMs = Math::randInt (500, 2000);
                nextSpeed = Math::randDouble (0.01, 0.1);
        }

        // Płynnie przyspiesz lub zwolnij do nastepnej prędkości.
        if (currentSpeed > nextSpeed + 0.005) {
                currentSpeed -= 0.005;
        }
        else if (currentSpeed < nextSpeed - 0.005) {
                currentSpeed += 0.005;
        }

        // Wykonaj przesunięcie.
        offsetX += e->getDeltaMs () * currentSpeed;
        image->setOffsetX (offsetX);
}

} /* namespace Demo */
