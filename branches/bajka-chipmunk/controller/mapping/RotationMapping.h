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

#include <Reflection.h>

#include "AbstractMapping.h"
#include "AbstractModel.h"

namespace Controller {

/**
 * Używając sekwencji wywołuje metodę abslutnej (?) rotacji Model::IModel::setRotate.
 * \ingroup Mapping
 */
class RotationMapping : public AbstractMapping <double, Model::AbstractModel> {
public:
        __c (void)

        virtual ~RotationMapping () {}

        virtual void run () {
                if (getSequence ()->hasNext ()) {
                        getModel ()->setRotate (getSequence ()->next ());
                }
        }

        _m (setModel)
        _m (setSequence)
        _e (RotationMapping)
};

}

#	endif /* ROTATIONMAPPING_H_ */
