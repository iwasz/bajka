/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTMODEL_H_
#define ABSTRACTMODEL_H_

#include "IModel.h"
#include "geometry/Point.h"
#include "geometry/Box.h"
#include "tree/TreeSlave.h"

namespace Model {

/**
 * Implementacja typowych operacji na modelu. Implemenacja IModel, która zbiera
 * najczęściej używane operacje do kupy.
 * \ingroup Model
 */
class AbstractModel :
        public IModel,
        public Util::TreeSlave <IModel> {
public:
        __d

        virtual ~AbstractModel () {}

/*------affine-transformations----------------------------------------------*/

        _m (setMove) virtual void setMove (const Geometry::Point &p);
        _m (setRotate) virtual void setRotate (double r);
        virtual void setResize (double w, double h);
        _m (setResizeW) virtual void setResizeW (double w) { setResize (w, 1); }
        _m (setResizeH) virtual void setResizeH (double h) { setResize (1, h); }

        virtual Geometry::AffineMatrix const &
        getMatrix () const { return matrix; }

        virtual Geometry::Point const &screenToModel (Geometry::Point const &) const;
        virtual Geometry::Point const &modelToScreen (Geometry::Point const &) const;

        // TODO To do zastanowienia.
        Geometry::AffineMatrix const &updateMatrixStack () const;

        /// Zwraca 0. AbstractModel sam w sobie ma wielkość punktu.
        virtual double getWidth () const { return 0.0; }

        /// Zwraca 0. AbstractModel sam w sobie ma wielkość punktu.
        virtual double getHeight () const { return 0.0; }

        /**
         * AbstractModel sam w sobie ma wielkość punktu, więc nigdy nic nie jest w jego środku, ale
         * deleguje jeszcze sprawdzenie do swoich dzieci. Jeżeli ktorekolwiek z nich zwróci prawdę,
         * to ta metoda także zwrac prawdę.
         */
        virtual bool enclose (const Geometry::Point &) const;

        /// Pudełko o zerowym rozmiarze.
        virtual Geometry::Box const &getBoundingBox () const { static Geometry::Box b; return b; }

protected:

        AbstractModel ();

protected:

        // Relative to root-element
        Geometry::AffineMatrix matrix;

private:

        mutable Geometry::AffineMatrix matrixStack;
        mutable Geometry::Point tmpPoint;

        _e (AbstractModel)
};

} // namespace

#	endif /* ABSTRACTMODEL_H_ */
