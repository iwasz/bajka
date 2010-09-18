/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef T_ABSTRACTCONTROLLER_H_
#define T_ABSTRACTCONTROLLER_H_

#include "../../controller/AbstractController.h"

/**
 *
 */
class T_AbstractController : public Controller::AbstractController {
public:

        T_AbstractController (std::string const &s) :
                AbstractController (Ptr <View::IWidget> ()),
                name (s) {}

        virtual ~T_AbstractController () {}

        void init () {}
        void draw () {}
        Ptr <Controller::IMapping> getMapping () {}

/*--------------------------------------------------------------------------*/

        std::string const &getName () const { return name; }

private:

        std::string name;

};

#	endif /* ABSTRACTCONTROLLER_H_ */
