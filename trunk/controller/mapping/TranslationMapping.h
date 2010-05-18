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
#include <Reflection.h>

#include "AbstractMapping.h"
#include "AbstractModel.h"

namespace Controller {

class TranslationMapping : public AbstractMapping <Geometry::Point, Model::AbstractModel> {
public:
        __c (void)

        virtual ~TranslationMapping () {}

        virtual void run () {
                if (getSequence ()->hasNext ()) {
                        getModel ()->setMove (getSequence ()->next ());
                }
        }

        _m (setModel)
        _m (setSequence)
        _e (TranslationMapping)
};

} // nam

#	endif /* RELATIVEMOVEMENTMAPPING_H_ */
