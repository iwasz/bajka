/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MAILSTACKCONTROLLER_H_
#define MAILSTACKCONTROLLER_H_

#include "../controller/EmptyController.h"
#include "../view/LoopImage.h"

namespace Demo {

/**
 * Porusza stosami poczty w głownym menu.
 */
class MailStackController : public Controller::EmptyController {
public:

        C__ (void)
        b_ ("EmptyController")

        MailStackController ();
        virtual ~MailStackController () {}
        void onUpdate (Event::UpdateEvent *e, Model::IModel *m, View::IView *v);

        m_ (setImage) void setImage (View::LoopImage *i) { image = i; }

private:

        View::LoopImage *image;
        double offsetX, currentSpeed, nextSpeed;
        unsigned int currentMs, nextChangeMs;

        E_ (MailStackController)
};

} /* namespace Demo */

#	endif /* MAILSTACKCONTROLLER_H_ */
