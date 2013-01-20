/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 22, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_UTIL_MATH_H_
#define BAJKA_UTIL_MATH_H_

namespace Util {

/**
 * Returns next power of two equal or greater than i.
 */
extern unsigned int nextSqr (unsigned int i);
extern int randInt (int from, int to);
extern double randDouble (double from, double to);
extern int numberOfSetBits (int i);

}

#	endif /* MATH_H_ */
