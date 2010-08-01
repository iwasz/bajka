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

namespace Service {

/**
 * Customowy kontroler, który jest częścią widgeta, który wysyła sygnały
 * kiedy kursor myszy najedzie na jego obszar. Sygnały mają parametr speed,
 * ktory jest tym większy im głębiej wjedziemy myszką na obiekt.
 *
 * Ten kontroler jest pomyślany do wspólpracy ze ScrollService, które ma
 * odpowiednie handlery dla powyżych sygnałów.
 */
class ScrollMarginController : public Controller::SimpleController {
public:
        __c (void)
        _b ("SimpleController")


        ScrollMarginController () : sender (this) {}
        virtual ~ScrollMarginController () {}

        bool onMouseMotion (Event::MouseMotionEvent *e);

        // TODO to powinno być jakieś ENUM (ale jak tego użyć w kontenerze wtedy!?).
        std::string getType () { return type; }
        void setType (const std::string &t) { type = t; }

private:

        Signal::Sender sender;
        std::string type;

        _e (ScrollMarginController)
};

}

#	endif /* SCROLLMARGINCONTROLLER_H_ */
