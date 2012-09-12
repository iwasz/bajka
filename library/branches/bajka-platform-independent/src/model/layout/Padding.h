/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_LAYOUT_PADDING_H_
#define BAJKA_LAYOUT_PADDING_H_

#include <string>
#include "util/ReflectionMacros.h"

namespace Model {

/**
 * Definicja paddingu.
 */
struct Padding {

        Padding () : top (0), right (0), bottom (0), left (0) {}

        C__ (std::string const &);
        Padding (std::string const &s);

        float top;
        float right;
        float bottom;
        float left;

        E_ (Padding)
};

} /* namespace Model */
#endif /* PADDING_H_ */
