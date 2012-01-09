/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_POLYGON_H_
#define BAJKA_POLYGON_H_

#include "Widget.h"

namespace View {

class Polygon : public Widget {
public:
        virtual ~Polygon ();
};

///**
// * Rysuje prostokąt.
// * \ingroup View
// */
//class Rectangle : public Widget {
//public:
////        __c (void)
////        _b ("AbstractWidget")
//
//        virtual ~Rectangle () {}
//
//        virtual void update (Model::IModel *model);
//
////// Żeby nie trzeba było kastowac modelu na box w pochodnych.
////protected:
////
////        Model::Box *box;
////        _e (Rectangle)
//};

} // namespace

#	endif /* POLYGON_H_ */
