/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_MODEDL_INTERFACE_BOX_H_
#define BAJKA_MODEDL_INTERFACE_BOX_H_

#include <core/Object.h>
#include "geometry/Box.h"

namespace Model {

/**
 * Interfejs modeli Boxowych (w momencie pisania Box, CPBox i RelativeGroup).
 */
class IBox : public virtual Core::Object {
public:

        virtual ~IBox () {}

/*--------------------------------------------------------------------------*/

        /// Szerokość.
        virtual double getWidth () const = 0;
        /// Szerokość.
        virtual void setWidth (double w)  = 0;
        /// Wysokość.
        virtual double getHeight () const = 0;
        /// Wysokość.
        virtual void setHeight (double h) = 0;
        /// Metoda pomocnicza zwracająca pudełko o rozmiarach width i height i ll = 0.
        virtual Geometry::Box getBox () const = 0;

};

} /* namespace Model */

#	endif /* BOXB_H_ */
