/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef T_ABSTRACTWIDGET_H_
#define T_ABSTRACTWIDGET_H_

#include "../../view/AbstractWidget.h"

/**
 *
 */
class T_AbstractWidget : public View::AbstractWidget {
public:

        T_AbstractWidget (std::string const &s) : name (s) {}
        virtual ~T_AbstractWidget () {}
        void doDraw () {}

        std::string const &getName () const { return name; }

private:

        std::string name;

};

#	endif /* ABSTRACTWIDGET_H_ */
