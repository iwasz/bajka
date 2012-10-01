/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 17, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Color.h"
#include <cstdlib>

namespace View {

Color::Color () : r (0.0), g (0.0), b (0.0), a (1.0) {}

/****************************************************************************/

//Color::Color (bool random)
//{
//        if (random) {
//                r = rand () / double (RAND_MAX);
//                g = rand () / double (RAND_MAX);
//                b = rand () / double (RAND_MAX);
//                a = 1;
//        }
//        else {
//                r = 0;
//                g = 0;
//                b = 0;
//                a = 1;
//        }
//}

/****************************************************************************/

Color::Color (unsigned int color)
{
        initFromHex (color);
}

/****************************************************************************/

Color::Color (std::string const &s)
{
        char * p;
        unsigned long n = strtoul (s.c_str (), &p, 16);

        if (*p != 0) {
                r = 0;
                g = 0;
                b = 0;
                a = 1;
        }

        initFromHex (n);
}

/****************************************************************************/

void Color::initFromHex (unsigned int color)
{
        r = ((color >> 24) & 0xFF) / 255.0;
        g = ((color >> 16) & 0xFF) / 255.0;
        b = ((color >> 8) & 0xFF) / 255.0;
        a = (color & 0xFF) / 255.0;
}

Color Color::BLACK = Color (0.0, 0.0, 0.0);
Color Color::RED = Color (1.0, 0.0, 0.0);
Color Color::GREEN = Color (0.0, 1.0, 0.0);
Color Color::YELLOW = Color (1.0, 1.0, 0.0);
Color Color::BLUE = Color (0.0, 0.0, 1.0);
Color Color::MAGENTA = Color (1.0, 0.0, 1.0);
Color Color::CYAN = Color (0.0, 1.0, 1.0);
Color Color::WHITE = Color (1.0, 1.0, 1.0);
Color Color::TRANSPARENT = Color (0, 0, 0, 0);
}
