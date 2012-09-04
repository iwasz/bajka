/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_MODEDL_BOXB_H_
#define BAJKA_MODEDL_BOXB_H_

#include "../AbstractModel.h"
#include "../../geometry/Box.h"
#include "../IBox.h"
#include "IView.h"

namespace Model {

class Box : public IBox, public AbstractModel {
public:

        C__ (void)
        b_ ("AbstractModel")

        Box () : autoUpdateToViewSize (false) {}
        virtual ~Box () {}

/*--------------------------------------------------------------------------*/

        double getWidth () const;/* { return box.getWidth (); }*/
        void setWidth (double w) { box.setWidth (w); }
        double getHeight () const;/* { return box.getHeight (); }*/
        void setHeight (double h) { box.setHeight (h); }

        Geometry::Box getBox () const;/* { return box; }*/
        m_ (setBox) void setBox (Geometry::Box const &b) { box = b; }

        bool isBox () const { return true; }

        /**
         * Auto dopasowywanie rozmiaru do widoku. Ustawienie tego switcha na true powoduje, że przy operacjach
         * zwracajacych rozmiary tego modelu, sprawdza on rozmiary widoku (widthHint i heightHint). Taki tryb
         * może być dosyc kosztowny. Aby jenorazowo dopasowac rozmiar, nalezy użyć metody updateToViewSize ().
         * Mozna ją podać jako init-methd w XML.
         */
        bool getAutoUpdateToViewSize () const { return autoUpdateToViewSize; }
        m_ (setAutoUpdateToViewSize)
        void setAutoUpdateToViewSize (bool b) { autoUpdateToViewSize = b; }
        m_ (updateToViewSize) inline void updateToViewSize () const;

/*--------------------------------------------------------------------------*/

        Geometry::Point computeCenter () const;
        virtual Geometry::Box getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const;
        virtual bool contains (Geometry::Point const &p) const;

protected:

        inline void updateToViewSizeIf () const;

protected:

        Geometry::Box box;
        bool autoUpdateToViewSize;

        E_ (Box)
};

/****************************************************************************/

void Box::updateToViewSize () const
{
        Box *b = const_cast <Box *> (this);

        if (b->getView ()) {
                b->box.setWidth (b->getView ()->getWidthHint ());
                b->box.setHeight (b->getView ()->getHeightHint ());
        }
}

/****************************************************************************/

void Box::updateToViewSizeIf () const
{
        if (autoUpdateToViewSize) {
                updateToViewSize ();
        }
}

} /* namespace Model */

#	endif /* BOXB_H_ */
