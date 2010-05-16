/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IMODEL_H_
#define IMODEL_H_

#include <Object.h>
#include "geometry/Utils.h"

namespace Model2 {

/// Marker
struct IModel : virtual public Core::Object {
        virtual ~IModel () {}

        /**
         * Returns affine transformation matrix for this object.
         */
        virtual
        AffineMatrix const &
        getMatrix () const = 0;

};

}

#	endif /* IMODEL_H_ */
