/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_MODEDL_INTERFACE_BOX_H_
#define BAJKA_MODEDL_INTERFACE_BOX_H_

#include <Object.h>

namespace Model {

/**
 * Interfejs modeli Boxowych (w momencie pisania Box, CPBox i BoxGroup).
 */
class IBox : public virtual Core::Object {
public:

        virtual ~IBox () {}

/*--------------------------------------------------------------------------*/

        virtual double getWidth () const = 0;
        virtual double getHeight () const = 0;
        virtual Geometry::Box getBox () const = 0;

};

} /* namespace Model */

#	endif /* BOXB_H_ */
