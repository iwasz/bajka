/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 22, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ROTATIONMAPPING_H_
#define ROTATIONMAPPING_H_

#include "AbstractMapping.h"
#include "Model.h"

namespace Controller {

/**
 * Absolute rotation.
 */
class RotationMapping : public AbstractMapping <double, Model::Item> {
public:
        virtual ~RotationMapping () {}

        virtual void run () {
                if (getSequence ()->hasNext ()) {
                        getModel ()->setRotateAngle (getSequence ()->next ());
                }
        }
};

}

#	endif /* ROTATIONMAPPING_H_ */
