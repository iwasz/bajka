/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Timeline.h"

namespace Tween {

Timeline *timeline ()
{
        return Timeline::create ();
}

/****************************************************************************/

Timeline *Timeline::create ()
{
        // TODO pool
        return new Timeline;
}

/****************************************************************************/

void Timeline::initExit ()
{
        currentRepetition = repetitions;
}

/****************************************************************************/

void Timeline::finishedExit ()
{
        currentRepetition = repetitions;
}

/****************************************************************************/

void Timeline::runEntry ()
{
        current = tweens.begin ();
        currentr = tweens.rbegin ();
}

/****************************************************************************/

void Timeline::update (int deltaMs, bool reverse)
{
        if (state == FINISHED) {
                return;
        }
        else if (state == INIT) {

                if (delayMs) {
                        transition(DELAY);
                }
                else {
                        transition (RUN);
                }

                update (deltaMs, reverse); // Żeby nie stracić iteracji.
        }
        else if (state == DELAY) {
                currentMs += deltaMs;
                int remainingMs = currentMs - delayMs;

                if (remainingMs >= 0) {
                        transition (RUN);
                }

                if (remainingMs > 0) {
                        update(remainingMs, reverse);
                }
        }
        else if (state == RUN) {

                bool direction = currentDirection ^ reverse;

//                if (currentDirection) {
//                        currentMs += deltaMs;
//
//                        if (currentMs > durationMs) {
//                                currentMs = durationMs;
//                        }
//                }
//                else {
//                        currentMs -= deltaMs;
//
//                        if (currentMs < 0) {
//                                currentMs = 0;
//                        }
//                }

                if (direction) {
                        (*current)->update (deltaMs, !direction);
//                        ++current;
                }
                else {
                        (*currentr)->update (deltaMs, !direction);
//                        ++currentr;
                }

                if ((direction && (*current)->getState () == FINISHED && ++current == tweens.end ()) ||
                    (!direction && (*currentr)->getState () == INIT && ++currentr == tweens.rend ())) {

//                if ((*current)->getState () == FINISHED && ((!direction && current == tweens.end ()) || (direction && currentr == tweens.rend ()))) {

                        if (!currentRepetition) {
                                transition ((reverse) ? (DELAY) : (FINISHED));
                        }
                        else {
                                --currentRepetition;

                                if (yoyo) {
                                        currentDirection = !currentDirection;
                                }

                                transition (RUN);
                        }
                }
        }


//        if (finished || tweens.empty ()) {
//                return;
//        }
//
//        (*current)->update (deltaMs);
//
//        if ((*current)->getFinished ()) {
//                if (++current == tweens.end ()) {
//                        finished = true;
//                        return;
//                }
//        }
}

/****************************************************************************/

Timeline *Timeline::add (ITween *tween)
{
        tweens.push_back (tween);
        current = tweens.begin ();
        return this;
}

} /* namespace Tween */
