/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IWIDGET_H_
#define IWIDGET_H_

#include "ITreeWidget.h"

/**
 *
 */
struct T_IWidget : public Util::ITreeWidget {

        virtual ~T_IWidget () {}
        virtual std::string const &getName () const = 0;
};

#	endif /* IWIDGET_H_ */
