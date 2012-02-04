/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_FONT_H_
#define BAJKA_FONT_H_

#include <Object.h>
#include "../draw/Color.h"

namespace View {

struct IFont : public Core::Object {
        virtual ~IFont () {}
        virtual void *render (std::string const &text, View::Color const &fgColor, View::Color const &bgColor) = 0;
};

} /* namespace View */

#       endif /* TTFFONT_H_ */
