/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 22, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MATH_H_
#define MATH_H_

namespace Util {

struct Math {

        /**
         * Returns next power of two equal or greater than i.
         */
        static unsigned int nextSqr (unsigned int i);
        static int randInt (int from, int to);
        static double randDouble (double from, double to);
};

}

#	endif /* MATH_H_ */
