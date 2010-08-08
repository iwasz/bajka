/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef RELATIVEMOVEMENTMAPPING_H_
#define RELATIVEMOVEMENTMAPPING_H_

#include "AbstractMapping.h"
#include "AbstractModel.h"
#include "geometry/Point.h"

namespace Controller {

/**
 * Używając sekwencji wywołuje metodę relatywnego ruchu Model::IModel::setMove.
 * \ingroup Mapping
 */
class RelativeMovementMapping : public AbstractMapping <Geometry::Point, Model::AbstractModel> {
public:

        virtual ~RelativeMovementMapping () {}

        virtual void run () {
                if (getSequence ()->hasNext ()) {
                        getModel ()->setMove (getSequence ()->next ());
                }
        }

};

} // nam

#	endif /* RELATIVEMOVEMENTMAPPING_H_ */
