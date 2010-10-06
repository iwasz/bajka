/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MODEL_BOX_H_
#define MODEL_BOX_H_

#include "geometry/Box.h"
#include "AbstractModel.h"

namespace Model {

/**
 * Model reprezentujący pudełko. Może służyć jako model do prostokąta, albo
 * do jakiegoś innego prostokątnego cudaka.
 * \ingroup Model
 */
class Box : public AbstractModel, public Geometry::Box {
public:
        __c (void)
        _b ("AbstractModel", "Box")

        Box () : AbstractModel (), Geometry::Box () {}
        Box (double a, double b, double c, double d) : AbstractModel (), Geometry::Box (a, b, c, d) {}

        /// Pomocnicza.
        static Ptr <Box> create (double a = 0.0, double b = 0.0, double c = 0.0, double d = 0.0) { return Ptr <Box> (new Box (a, b, c, d)); }
        virtual ~Box () {}

/*--------------------------------------------------------------------------*/

        virtual bool enclose (const Geometry::Point &p) const;

//        const Geometry::Box &toScreenCoords () const { updateScreenCoords (); return screenCoords; }

/*--------------------------------------------------------------------------*/

        /*
         * TODO Te metody bym wywalił, bo:
         * - są uż metody do ustawiania rozmiaru : x2 i y2
         * - dają złudne wrażenie, że jak zmienię x1,y1, to rozmiary zostaną zachowane.
         */
        void setWidth (double d) { setX2 (getX1 () + d); }
        void setHeight (double d) { setY2 (getY1 () + d); }

        virtual Geometry::Box getBoundingBox () const;

        /// Zawsze zwraca LL.
        Geometry::Point const &getOrigin () const { return getLL (); }

private:

//        // TODO Test
//        void updateScreenCoords () const;
//        mutable Geometry::Box screenCoords;

        _e (Model::Box)
};

} // namespace

#	endif /* ABSTRACTMODEL_H_ */
