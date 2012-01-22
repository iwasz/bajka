/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_TTFFONT_H_
#define BAJKA_TTFFONT_H_

#include "ReflectionMacros.h"
#include "Font.h"

namespace View {

class TTFFont : public Font {
public:

        C__ (std::string const &)
        TTFFont (std::string const &path);

        C_ (std::string const &, int)
        TTFFont (std::string const &path, int ptSize);

        C_ (std::string const &, int, long int)
        TTFFont (std::string const &path, int ptSize, long int index);

        ~TTFFont ();

        void *render (std::string const &text, View::Color const &fgColor, View::Color const &bgColor);

        int getHinting () const;
        m_ (setHinting) void setHinting (int hint);

private:

        void open (std::string const &path, int ptSize = -1, long int index = -1);

        void *renderSolid (std::string const &text, View::Color const &fgColor);
        void *renderShaded (std::string const &text, View::Color const &fgColor, View::Color const &bgColor);
        void *renderBlended (std::string const &text, View::Color const &fgColor);

private:

        TTF_Font *font;

        E_ (TTFFont)
};

} /* namespace View */

#	endif /* TTFFONT_H_ */
