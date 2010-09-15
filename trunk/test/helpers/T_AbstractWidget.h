/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTWIDGET_H_
#define ABSTRACTWIDGET_H_

#include "TreeWidget.h"

/**
 *
 */
class T_AbstractWidget : public Base::TreeWidget {
public:

        T_AbstractWidget (std::string const &s) : name (s) {}
        virtual ~T_AbstractWidget () {}

        std::string const &getName () const { return name; }

private:

        std::string name;

};

#	endif /* ABSTRACTWIDGET_H_ */
