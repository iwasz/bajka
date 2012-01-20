/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 22, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <climits>
#include "Math.h"

namespace Util {

unsigned int Math::nextSqr (unsigned int n)
{
        // http://en.wikipedia.org/wiki/Power_of_two#Algorithm_to_find_the_next-highest_power_of_two
//        if (k == 0) {
//                return 1;
//        }
//
//        k--;
//
//        for (int i = 1; i < sizeof(unsigned int) * CHAR_BIT; i <<= 1) {
//                k = k | k >> i;
//        }
//
//        return k + 1;

        // http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
        n--;
        n |= n >> 1;
        n |= n >> 2;
        n |= n >> 4;
        n |= n >> 8;
        n |= n >> 16;
        return ++n;
}


}
