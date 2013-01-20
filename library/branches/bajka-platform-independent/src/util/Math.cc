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
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/lagged_fibonacci.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include "Math.h"

namespace Util {

unsigned int nextSqr (unsigned int n)
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

/****************************************************************************/

static boost::mt19937 genInt (time (0));

int randInt (int from, int to)
{
        boost::uniform_int <> dist (from, to);
        return dist (genInt);
}

/****************************************************************************/

static boost::lagged_fibonacci3217 genDouble (time (0));

double randDouble (double from, double to)
{
        boost::uniform_real <> dist (from, to);
        return dist (genDouble);
}

/****************************************************************************/

int numberOfSetBits (int i)
{
    i = i - ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

}
