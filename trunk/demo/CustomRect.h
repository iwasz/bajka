/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CUSTOMRECT_H_
#define CUSTOMRECT_H_

#include "../view/Rectangle.h"

/**
 * To jest testowy prostokąt, który ma opcję wypełnienia.
 */
class CustomRect : public View::Rectangle {
public:
        __c (void)
        _b ("Rectangle")

        CustomRect () : fill (false) {}
        virtual ~CustomRect () {}

        void setFill (bool b) { fill = b; }
        bool getFill () const { return fill; }

        void doDraw ();

private:

        bool fill;
        _e (CustomRect)
};

#	endif /* CUSTOMRECT_H_ */
