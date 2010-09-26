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
 * TODO Zastanowić się nad strukturą dziedziczenia w modelu - czy ten shape
 * jest napewno OK? Trochę zamęt jest. On powinien być abstrakcyjny ten shape (absttract
 * model też i nie powinien mieć pustych metody, tylko pure virtual i zeby one były zdefiniowane
 * w klasach konkretnych i nie jako puste, ale żeby robiły coś sensownego).
 * \ingroup Model
 */
class Shape : public AbstractModel {
public:
        __d
        _b ("AbstractModel")

        virtual ~Shape () {}

        virtual double getWidth () const { return getBoundingBox ().getX2 () - getBoundingBox ().getX1 (); }
        virtual double getHeight () const { return getBoundingBox ().getY2 () - getBoundingBox ().getY1 (); }

        virtual Geometry::Point const &screenToModel (Geometry::Point const &) const;
        virtual Geometry::Point const &modelToScreen (Geometry::Point const &) const;

        /**
         * Najpierw sprawdza, czy jakieś z dzieci nie zwóci true, a jeśli nie, to
         * sprawdza, czy p jest wewnątrz bounding box.
         */
        virtual bool enclose (const Geometry::Point &p) const;


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
