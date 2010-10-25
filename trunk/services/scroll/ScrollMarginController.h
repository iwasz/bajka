/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SCROLLMARGINCONTROLLER_H_
#define SCROLLMARGINCONTROLLER_H_

#include <Signal.h>
#include "../../controller/SimpleController.h"

namespace Model {
class Box;
}

namespace Service {

/**
 * Customowy kontroler, który jest częścią widgeta, który wysyła sygnały
 * kiedy kursor myszy najedzie na jego obszar. Sygnały mają parametr speed,
 * ktory jest tym większy im głębiej wjedziemy myszką na obiekt.
 *
 * Ten kontroler jest pomyślany do wspólpracy ze ScrollService, które ma
 * odpowiednie handlery dla powyżych sygnałów.
 * \ingroup Service
 */
class ScrollMarginController : public Controller::SimpleController {
public:
        __c (void)
        _b ("SimpleController")

        /**
         * Typ marginesu (jego pozycja). Zgodnie ze
         * wskazówkami zegara, czyli TOP = 0, RIGHT = 1,
         * BOTTOM = 2, LEFT = 3
         */
        enum Type { TOP, RIGHT, BOTTOM, LEFT };

        ScrollMarginController () :
                up ("/scroll/up"),
                down ("/scroll/down"),
                left ("/scroll/left"),
                right ("/scroll/right"),
                box (0) {}

        virtual ~ScrollMarginController () {}

        bool onMouseMotion (Event::MouseMotionEvent *e);
        bool onMouseOut (Event::MouseMotionEvent *e);

        Type getType () { return type; }
        // TODO kiedyś kontener będzie obsługiwał enumy, to zamienić typ.
        _m (setType) void setType (/*Type t*/int t) { type = (Type)t; }

        void setModel (Ptr <Model::IModel> m);

private:

        Signal::Sender up, down, left, right;
        Type type;
        Model::Box *box;

        _e (ScrollMarginController)
};

}

#	endif /* SCROLLMARGINCONTROLLER_H_ */
