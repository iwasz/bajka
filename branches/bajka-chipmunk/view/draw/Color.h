/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 17, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_DRAW_COLOR_H_
#define BAJKA_DRAW_COLOR_H_

#include "ReflectionMacros.h"

namespace View {

/**
 * Model reprezentujący kolor.
 */
class Color {
public:

        C__ (void)
        Color ();
        C_ (bool)
        Color (bool random);
        Color (double r, double g, double b, double a = 1.0) : r (r), g (g), b (b), a (a) {}
        Color (unsigned int color);
        C_ (std::string const &)
        Color (std::string const &s);

        double getR () const { return r; }
        m_ (setR) void setR (double r) { this->r = r; }

        double getG () const { return g; }
        m_ (setG) void setG (double g) { this->g = g; }

        double getB () const { return b; }
        m_ (setB) void setB (double b) { this->b = b; }

        double getA () const { return a; }
        m_ (setA) void setA (double a) { this->a = a; }

        static Color BLACK;
        static Color RED;
        static Color GREEN;
        static Color YELLOW;
        static Color BLUE;
        static Color MAGENTA;
        static Color CYAN;
        static Color WHITE;

private:

        void initFromHex (unsigned int color);

public:

        double r;
        double g;
        double b;
        double a;

        E_ (Color)
};

} // nam

#	endif /* COLOR_H_ */
