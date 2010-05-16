/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 17, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef COLOR_H_
#define COLOR_H_

#include <Reflection.h>

namespace Model {

/**
 * Kolor.
 */
class Color {
public:
        __c (void)

        Color () : r (0.0), g (0.0), b (0.0), a (1.0) {}
        Color (double r, double g, double b, double a = 1.0) : r (r), g (g), b (b), a (a) {}

        double getR () const { return r; }
        _m (setR) void setR (double r) { this->r = r; }

        double getG () const { return g; }
        _m (setG) void setG (double g) { this->g = g; }

        double getB () const { return b; }
        _m (setB) void setB (double b) { this->b = b; }

        double getA () const { return a; }
        _m (setA) void setA (double a) { this->a = a; }

        static Color BLACK;
        static Color RED;
        static Color GREEN;
        static Color YELLOW;
        static Color BLUE;
        static Color MAGENTA;
        static Color CYAN;
        static Color WHITE;

        static Color fromInt (unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
        {
                return Color (r / 255.0, g / 255.0, b / 255.0, a / 255.0);
        }

        static Color fromHex ()
        {
                return MAGENTA;
        }

private:

        double r;
        double g;
        double b;
        double a;

        _e (Color)
};

} // nam

#	endif /* COLOR_H_ */
