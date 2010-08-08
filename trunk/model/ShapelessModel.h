/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SHAPELESSMODEL_H_
#define SHAPELESSMODEL_H_

#include <Exceptions.h>
#include "AbstractModel.h"

namespace Model {

/**
 * Klasa modeli, ktore nie mają kształtu. Implementuje domyślne
 * metody, które normalnie dają informację o kształcie.
 */
class ShapelessModel : public AbstractModel {
public:
        virtual ~ShapelessModel () {}

        virtual double getWidth () const { throw Core::UnsupportedOperationException (); }
        virtual double getHeight () const { throw Core::UnsupportedOperationException (); }

        virtual bool enclose (const Geometry::Point &p) const { throw Core::UnsupportedOperationException (); }

};

} // nam

#	endif /* SHAPELESSMODEL_H_ */
