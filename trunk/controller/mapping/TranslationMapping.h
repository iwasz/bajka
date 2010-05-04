/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 21, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSOLUTEMOVEMENTMAPPING_H_
#define ABSOLUTEMOVEMENTMAPPING_H_

#include <iostream>
#include "AbstractMapping.h"

namespace Controller {

class TranslationMapping : public AbstractMapping <Model::Point, Model::Item> {
public:

        virtual ~TranslationMapping () {}

        virtual void run () {
                if (getSequence ()->hasNext ()) {
                        getModel ()->setTranslatePoint (getSequence ()->next ());
                }
        }

        __e (TranslationMapping)
};

} // nam

#	endif /* RELATIVEMOVEMENTMAPPING_H_ */
