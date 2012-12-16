/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef INSTRUCTIONS1CONTROLLER_H_
#define INSTRUCTIONS1CONTROLLER_H_

#include "../controller/EmptyController.h"

namespace Demo {

/**
 * Customowy kontroler do pierwszej planszy instrukcji.
 */
class Instructions1Controller : public Controller::EmptyController {
public:

        C__ (void)
        b_ ("EmptyController")
        Instructions1Controller () :
                player      (NULL),
                buttonLeft  (NULL),
                buttonRight (NULL),
                envelope1   (NULL),
                envelope2   (NULL),
                envelope3   (NULL),
                envelope4   (NULL),
                envelope5   (NULL) {}

        virtual ~Instructions1Controller () {}

        Event::Handling onManagerLoad (Event::ManagerEvent *e, Model::IModel *m, View::IView *v);
        Event::Handling onManagerUnload (Event::ManagerEvent *e, Model::IModel *m, View::IView *v);

        S_ (setPlayer) void setPlayer      (Model::IModel *m) { player = m; }
        S_ (setButtonLeft) void setButtonLeft  (Model::IModel *m) { buttonLeft = m; }
        S_ (setButtonRight) void setButtonRight (Model::IModel *m) { buttonRight = m; }
        S_ (setEnvelope1) void setEnvelope1   (Model::IModel *m) { envelope1 = m; }
        S_ (setEnvelope2) void setEnvelope2   (Model::IModel *m) { envelope2 = m; }
        S_ (setEnvelope3) void setEnvelope3   (Model::IModel *m) { envelope3 = m; }
        S_ (setEnvelope4) void setEnvelope4   (Model::IModel *m) { envelope4 = m; }
        S_ (setEnvelope5) void setEnvelope5   (Model::IModel *m) { envelope5 = m; }

private:

        Model::IModel *player;
        Model::IModel *buttonLeft;
        Model::IModel *buttonRight;
        Model::IModel *envelope1;
        Model::IModel *envelope2;
        Model::IModel *envelope3;
        Model::IModel *envelope4;
        Model::IModel *envelope5;

        E_ (Instructions1Controller)
};

} /* namespace Demo */

#	endif /* INSTRUCTIONS1CONTROLLER_H_ */
