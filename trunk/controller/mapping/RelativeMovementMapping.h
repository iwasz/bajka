/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 21, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef RELATIVEMOVEMENTMAPPING_H_
#define RELATIVEMOVEMENTMAPPING_H_

#include "AbstractMapping.h"

namespace Controller {

class RelativeMovementMapping : public AbstractMapping <Model::Point, Model::Item> {
public:

        virtual ~RelativeMovementMapping () {}

        virtual void run () {
                if (getSequence ()->hasNext ()) {
                        getModel ()->translate (getSequence ()->next ());
                }
        }

};

} // nam

#	endif /* RELATIVEMOVEMENTMAPPING_H_ */
