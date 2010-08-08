/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 22, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SCREEN_H_
#define SCREEN_H_

#include <Reflection.h>
#include "AbstractWidget.h"

namespace View {

/**
 * Widok przeznaczony do stosowania z głownym kontrolerem (root
 * kontrolerem). Czyści ekran etc.
 */
class Screen : public AbstractWidget {
public:
        __c (void)

        virtual ~Screen () {}
//        _m (setModel) virtual void setModel (Ptr <Model::IModel> model);

        void preDraw ();
        void postDraw ();
        void doDraw ();

//private:
//
//        Ptr <Model::Primitive> model;

        _e (Screen)
};

}

#	endif /* SCREEN_H_ */
