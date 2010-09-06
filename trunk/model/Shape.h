/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SHAPE_MODEL_H_
#define SHAPE_MODEL_H_

#include <Exceptions.h>
#include "AbstractModel.h"
#include "geometry/Box.h"

namespace Model {

/**
 * Klasa modeli, które mają kształt. Dodatkowo jej układ odniesienia
 * jest wyśrodkowany do jej pubktu getBoundingBox ().getLL ().
 *
 * TODO enclose zawsze tutaj zwróci false. Czemu w takim razie instancjonuję
 * to klasę w main2.xml?
 *
 * \ingroup Model
 */
class Shape : public AbstractModel {
public:
        __c (void)
        _b ("AbstractModel")

        virtual ~Shape () {}

        virtual double getWidth () const { return getBoundingBox ().getX2 () - getBoundingBox ().getX1 (); }
        virtual double getHeight () const { return getBoundingBox ().getY2 () - getBoundingBox ().getY1 (); }

        virtual bool enclose (const Geometry::Point &) const;

        virtual Geometry::Point const &screenToModel (Geometry::Point const &) const;
        virtual Geometry::Point const &modelToScreen (Geometry::Point const &) const;
//        virtual Geometry::Box const &getBoundingBox () const { return boundingBox; }
//        virtual void setBoundingBox (Geometry::Box const &b) { boundingBox = b; }
//
//private:
//
//        Geometry::Box boundingBox;

        _e (Shape)
};

} // nam

#	endif /* SHAPELESSMODEL_H_ */
