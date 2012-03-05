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
#include "IFont.h"

namespace View {

class TTFFont : public IFont {
public:

        C__ (std::string const &)
        TTFFont (std::string const &path);

        C_ (std::string const &, int)
        TTFFont (std::string const &path, int ptSize);

        C_ (std::string const &, int, long int)
        TTFFont (std::string const &path, int ptSize, long int index);

        ~TTFFont ();

        enum Type {
                SOLID,
                SHADED,
                BLENDED
        };

        enum Encoding {
                ASCII,
                UTF8
        };

        void *render (std::string const &text, View::Color const &fgColor, View::Color const &bgColor);

        int getHinting () const;
        m_ (setHinting) void setHinting (int hint);

        int getType () const { return type; }
        m_ (setType) void setType (int t) { type = t; }

        int getEncoding () const { return encoding; }
        m_ (setEncoding) void setEncoding (int e) { encoding = e; }

private:

        void open (std::string const &path, int ptSize = -1, long int index = -1);

private:

        TTF_Font *font;
        int type; // TODO to powinno być typu Type
        int encoding; // TODO powinno być typu Encoding

        E_ (TTFFont)
};

} /* namespace View */

#	endif /* TTFFONT_H_ */
